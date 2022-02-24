#include "snail.h"
#include "gridscene.h"
#include <qmath.h>
class QGraphicsTextItem;
class QGraphicsRectItem;
GridScene::GridScene(QObject *parent)
	: QGraphicsScene(parent),
	sceneSize(640,640),
	mouse_pointer_in_board_img_rect(false)
{
	bg_image_=new QImage();
	cross=new BigCross();
	setBackgroundBrush(QColor("#393939"));
	openCVImage=new OpenCVImage();
	gridItem=new GridItem();

}

GridScene::~GridScene()
{

}


void GridScene::drawGrid()
{


	QPen pen_fat(Qt::yellow, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	img_rect_item=addRect(board_img_rect,pen_fat,QBrush(Qt::NoBrush));
	img_rect_item->setCursor(Qt::PointingHandCursor);



	QPen pen_ruler(Qt::yellow, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

	drawGridLegend();
	addItem(cross);



}


//calculate size scene based on background img size
void GridScene::adjustSceneSize(void)
{
	if(bg_image_){
		sceneSize.setWidth(bg_image_->width());
		sceneSize.setHeight(bg_image_->height());
	}
	setSceneRect(0,0, sceneSize.width() , sceneSize.height());
}


void GridScene::drawBoundingBox(void)
{
	QPen pen(Qt::red, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
	addRect(sceneRect(),pen,QBrush(Qt::NoBrush));

}

bool GridScene::loadPixmap(const QString& fileName)
{
	bool load_result=false;
	load_result= board_img.load(fileName);
	return load_result;
}
void GridScene::calculateBoardImgRect()
{
	int delta_x = sceneRect().width()-board_img.width();     
	int delta_y =sceneRect().height()-board_img.height(); 
	QPoint img_top_left(delta_x/2,delta_y/2);
	//	board_PixmapItem->setPos(img_top_left);
	board_img_rect.setTopLeft(img_top_left);
	board_img_rect.setWidth(board_img.width());
	board_img_rect.setHeight(board_img.height());


}


void GridScene::scaleBoardImg()
{
	int width_scale_factor=(sceneRect().width()/boardSize::WIDTH)-1;
	int height_scale_factor=(sceneRect().height()/boardSize::HEIGHT)-1;
	int scale_factor=qMin(width_scale_factor,height_scale_factor);
	int predict_width=boardSize::WIDTH*scale_factor;
	int predict_height=boardSize::HEIGHT*scale_factor;
	board_img= board_img.scaled(QSize(predict_width,predict_height));

}


void GridScene::drawGridLegend(const QSize& sizeGrid)
{
	QFont legend_font("Arial", 14);

	QString origin_txt=QString("%1").arg(0);
	QString right_top_txt=QString("%1").arg(boardSize::WIDTH);
	QString left_bottom_txt=QString("%1").arg(boardSize::HEIGHT);

	QGraphicsTextItem* text_item_origin=addText(origin_txt,legend_font);
	QGraphicsTextItem* text_item_top_right=addText(right_top_txt,legend_font);
	QGraphicsTextItem* text_item_bottom_left=addText(left_bottom_txt,legend_font);

	QPoint pt_origin_text(board_img_rect.topLeft());
	pt_origin_text-=QPoint(25,20);
	text_item_origin->setPos(pt_origin_text);

	QPoint pt_top_right__text(board_img_rect.topRight());
	pt_top_right__text+=QPoint(5,-20);
	text_item_top_right->setPos(pt_top_right__text);

	QPoint pt_bottom_left__text(board_img_rect.bottomLeft());
	pt_bottom_left__text-=QPoint(30,20);
	text_item_bottom_left->setPos(pt_bottom_left__text);

}


void GridScene::calculatePixelInMm()
{
	pixel_in_mm.setWidth(board_img_rect.width()/boardSize::WIDTH);
	pixel_in_mm.setHeight(board_img_rect.height()/boardSize::HEIGHT);
}
void GridScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

	cursor_position.setX(mouseEvent->scenePos().x());
	cursor_position.setY(mouseEvent->scenePos().y());
	CrossDimention cross_dimention;

	if(board_img_rect.contains(cursor_position,true))
	{

		cross_dimention.dX1=-(-img_rect_item->boundingRect().left()+cursor_position.x());

		cross_dimention.dY1=-(-img_rect_item->boundingRect().top()+cursor_position.y());
		cross_dimention.dX2=img_rect_item->boundingRect().width()+cross_dimention.dX1;
		cross_dimention.dY2=img_rect_item->boundingRect().height()+cross_dimention.dY1;
		QApplication::setOverrideCursor(Qt::BlankCursor/*Qt::CrossCursor*/);
		//qDebug()<<cursor_position;
		cross->setBoundingRect(cross_dimention);
		cross->setPos(mouseEvent->scenePos() );
		cross->show();
		mouse_pointer_in_board_img_rect=true;
		QPointF boardCoordinate=translate_to_board_coordinate(cursor_position);
		emit change_cursor_position(translate_to_phisical_coordinate(boardCoordinate,pixel_in_mm));

	}
	else
	{
		QApplication::setOverrideCursor(Qt::ArrowCursor);
		cross->hide();

		mouse_pointer_in_board_img_rect=false;

	}
}
void GridScene::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	QGraphicsScene::mousePressEvent(event);
	if(!mouse_pointer_in_board_img_rect) return QGraphicsScene::mousePressEvent(event);









	if (!event->isAccepted()) {
		if (event->button() == Qt::LeftButton) {
			// Добавляем настраиваемый элемент в сцену
			QPointF point = event->scenePos();
			CrossPoint *item = new CrossPoint();
			item->setPos(point);
			item->setData(1,QVariant(point));
			//   item->setRect(point.x()-25, point.y()-25, 60, 60);
			addItem(item);
		} else if (event->button() == Qt::RightButton) {
			// Проверяем, есть ли под курсором элемент
			QGraphicsItem *itemToRemove = NULL;
			foreach (QGraphicsItem *item, items(event->scenePos())) {
				if (item->type() == QGraphicsItem::UserType+1) {
					itemToRemove = item;
					break;
				}
			}
			// Удаляем элемент из сцены
			if (itemToRemove != NULL)
				removeItem(itemToRemove);
		}
	}




}

QPointF GridScene::translate_to_board_coordinate(const QPoint& in)
{
	QPointF boardCoordinate=in-board_img_rect.topLeft();//offset from corner board_img_rect
	return boardCoordinate;
}


QPointF GridScene::translate_to_phisical_coordinate(const QPointF& in,const QSize& pixel_in_mm)
{
	QPointF phisical_coordinate(in.x()/pixel_in_mm.width(),in.y()/pixel_in_mm.height());
	return phisical_coordinate;
}


void GridScene::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Delete) {
		// Удаляем все выбранные элементы
		qDebug() << "selected items " << selectedItems().size();
		while (!selectedItems().isEmpty()) {
			removeItem(selectedItems().front());
		}
	} else if(event->key()==Qt::Key_Up)
	{
		foreach (QGraphicsItem *item, selectedItems())  item->setPos(item->x(),item->y()-1);      
	}
	else if(event->key()==Qt::Key_Down)
	{
		foreach (QGraphicsItem *item, selectedItems())  item->setPos(item->x(),item->y()+1);      
	}
	else if(event->key()==Qt::Key_Left)
	{
		foreach (QGraphicsItem *item, selectedItems())  item->setPos(item->x()-1,item->y());      
	}
	else if(event->key()==Qt::Key_Right)
	{
		foreach (QGraphicsItem *item, selectedItems())  item->setPos(item->x()+1,item->y());      
	}
	else {
		QGraphicsScene::keyPressEvent(event);
	}
}
bool GridScene::loadOpenCVImg(const QString& fileName)
{
	openCVImage->loadUndistortFile("calibration_matrix.yaml");
	openCVImage->loadImage(fileName);
	openCVImage->undistortImage();
	openCVImage->resizeImage(0.5,0.5);
	QPixmap pixmap=openCVImage->curPixmap();
	clear();
	board_PixmapItem=addPixmap(pixmap);

	return true;
}
QGraphicsPixmapItem* GridScene::pixmapItem()
{
	return board_PixmapItem;
}

void GridScene::adjustBoardImg()
{
	openCVImage->adjustImgToBoundingRect();
	board_img=openCVImage->curPixmap();
	scaleBoardImg();
	board_img_rect=board_img.rect();
	clear();
	board_PixmapItem=addPixmap(board_img);
	board_PixmapItem->setPos(originScenePoint());
	gridItem->setBoardPhisicalSize(QSize(150,60));
	gridItem->setPos(originScenePoint());
	addItem(gridItem);
}


QPointF GridScene::originScenePoint(void)
{
	return QPointF(sceneRect().left()+boardMargin::LEFT_MARGIN,sceneRect().top()+boardMargin::TOP_MARGIN);
}


QRect GridScene::boardImgRect()
{
	return board_img_rect;
}
