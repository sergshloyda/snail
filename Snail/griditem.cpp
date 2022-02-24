#include "griditem.h"
#include "gridscene.h"
GridItem::GridItem(QGraphicsObject *parent)
	: QGraphicsObject(parent)
{
		pen_fat=QPen(Qt::yellow, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
		pen_fat.setCosmetic(true);
		pen_thin=QPen(Qt::yellow, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
		pen_thin.setCosmetic(true);
}

GridItem::~GridItem()
{

}
void GridItem::setBoardPhisicalSize(const QSize& size)
{
phisicalSize=size;

}
void GridItem::calculatePixelInMm()
{
	pixel_in_mm.setWidth(boundingRect().width()/phisicalSize.width());
	pixel_in_mm.setHeight(boundingRect().height()/phisicalSize.height());

}
QRectF GridItem::boundingRect() const
{
  
	GridScene* scene=reinterpret_cast<GridScene*>(this->scene());
	
	return scene->boardImgRect();
}
 
void GridItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	calculatePixelInMm();
	painter->setPen(pen_fat);
	painter->drawRect(boundingRect());
	drawHorizRuler(painter,boundingRect().topLeft(),boundingRect().width(),pixel_in_mm.width());
	drawVertRuler(painter,boundingRect().topLeft(),boundingRect().height(),pixel_in_mm.height());
        Q_UNUSED(option);
        Q_UNUSED(widget);
}
void GridItem::drawHorizRuler(QPainter *painter,const QPointF& origin,int length,int step,int mult_length_dash)
{

	int ruler_origin=1;

	int step_cm=0,step_mm=0;

	for(int i=ruler_origin;i<length;i++)
	{
		if(!(i%step))
		{


			//pen_thin.setWidthF(0.8);
			step_mm+=step;
			if (!(i%step)&&((i%(step*5))&&(i%(step*10)))) {
				
				painter->setPen(pen_thin);
				QLine dash_mm(QPoint(origin.x()+step_mm,origin.y()),QPoint(origin.x()+step_mm,origin.y()+step));
					/*qDebug() << counter++;
					qDebug() << "Draw mm line #:" << dash_mm;*/
				painter->drawLine(dash_mm);
			}
		 if(!(i%(step*5))&&(i%(step*10))) {
				painter->setPen(pen_thin);
				QLine dash_mm(QPoint(origin.x()+step_mm,origin.y()),QPoint(origin.x()+step_mm,origin.y()+step*mult_length_dash));
				painter->drawLine(dash_mm);
			}
		}
		if(!(i%(step*10)))
		{
					//qDebug()<<"Draw cm line #:"+counter++;
			
			step_cm+=step*10;
			painter->setPen(pen_fat);
			QLine dash_cm(QPoint(origin.x()+step_cm,origin.y()),QPoint(origin.x()+step_cm,origin.y()+step*mult_length_dash));
					//qDebug()<<dash_cm;
			painter->drawLine(dash_cm);
		}

	}
}
void GridItem::drawVertRuler(QPainter *painter,const QPointF& origin,int length,int step,int mult_length_dash)
{

	int ruler_origin=1;

	int step_cm=0,step_mm=0;
	int counter=1;
	for(int i=ruler_origin;i<length;i++)
	{
		if(!(i%step))
		{

			qDebug()<< counter++;
			step_mm+=step;
			if (!(i%step)&&((i%(step*5))&&(i%(step*10)))) { 
				
					qDebug()<<"draw mm";
				painter->setPen(pen_thin);
				QLine dash_mm(QPoint(origin.x(),origin.y()+step_mm),QPoint(origin.x()+step,origin.y()+step_mm));
				painter->drawLine(dash_mm);
				
			}
			
				 if(!(i%(step*5))&&(i%(step*10))) {
				
						qDebug()<<"draw mm*5";
				painter->setPen(pen_thin);
				QLine dash_mm(QPoint(origin.x(),origin.y()+step_mm),QPoint(origin.x()+step*mult_length_dash,origin.y()+step_mm));
				painter->drawLine(dash_mm);
				}
				//continue;
			
						if(!(i%(step*10))) {
							
					qDebug()<<"draw cm";
			painter->setPen(pen_fat);
			step_cm+=step*10;
			QLine dash_cm(QPoint(origin.x(),origin.y()+step_cm),QPoint(origin.x()+step*mult_length_dash,origin.y()+step_cm));
			painter->drawLine(dash_cm);
						
		}
		
		}
	

	}
}