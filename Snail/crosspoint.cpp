#include "crosspoint.h"
#include "qdebug.h"
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
CrossPoint::CrossPoint()
	: QGraphicsObject()
{
setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemSendsScenePositionChanges);
setDisplayCoordinate(QPoint(0,0));

}

CrossPoint::~CrossPoint()
{

}

void CrossPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
        if (event->modifiers() == Qt::ShiftModifier) {
            qDebug() << "Custom item left clicked with shift key.";
            // выберите предмет
            setSelected(true);
        } else if (event->modifiers() == Qt::AltModifier) {
            //qDebug() << "Custom item left clicked with alt key.";
            //// сбросить размер элемента
            //double radius = boundingRect().width() / 2.0;
            //QPointF topLeft = boundingRect().topLeft();
            //m_centerPointF = QPointF(topLeft.x() + pos().x() + radius, topLeft.y() + pos().y() + radius);
            //QPointF pos = event->scenePos();
            //qDebug() << boundingRect() << radius << this->pos() << pos << event->pos();
            //double dist = sqrt(pow(m_centerPointF.x()-pos.x(), 2) + pow(m_centerPointF.y()-pos.y(), 2));
            //if (dist / radius > 0.8) {
            //    qDebug() << dist << radius << dist / radius;
            //    m_bResizing = true;
            //} else {
            //    m_bResizing = false;
            //}
        } else {
			//setSelected(false);
            qDebug() << "Custom item left clicked.";
            QGraphicsItem::mousePressEvent(event);
            event->accept();
        }
    } else if (event->button() == Qt::RightButton) {
        qDebug() << "Custom item right clicked.";
        event->ignore();
    }
}

QRectF CrossPoint::boundingRect() const
{
	return QRectF(bounding_rect::TOP,bounding_rect::LEFT,bounding_rect::WIDTH,bounding_rect::HEIGHT);
}

void CrossPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	double width_pen=3;
	QPointF pos=data(1).toPointF();
			if(isSelected()){
	/*painter->setBrush(Qt::yellow);
	painter->setPen(QPen(Qt::red, 3, Qt::DashLine));*/

				painter->setBrush(Qt::NoBrush);
	painter->setPen(QPen(Qt::green, 3, Qt::SolidLine));
	painter->drawEllipse(QPoint(0,0),5,5);
	
	painter->setPen(QPen(Qt::green, 1, Qt::SolidLine));

	painter->drawLine(0,-7,0,7);
	painter->drawLine(-7,0,7,0);
	QString coordinate=QString("(%1,%2)").arg(pos.x(),0,'f',1).arg(pos.y(),0,'f',1);
	painter->drawText(5,5, coordinate);

	}
	else
	{
	painter->setBrush(Qt::NoBrush);
	painter->setPen(QPen(Qt::yellow, 3, Qt::SolidLine));
	painter->drawEllipse(QPoint(0,0),5,5);
	
	painter->setPen(QPen(Qt::yellow, 1, Qt::SolidLine));

	painter->drawLine(0,-7,0,7);
	painter->drawLine(-7,0,7,0);
	QString coordinate=QString("(%1,%2)").arg(pos.x(),0,'f',1).arg(pos.y(),0,'f',1);
	painter->drawText(5,5, coordinate);

	}
	
//	painter->drawEllipse(boundingRect());
//	painter->setPen(Qt::black);
//	QPointF pos=data(1).toPointF();
//		QString coordinate=QString("(%1,\n %2)").arg(pos.x(),0,'f',1).arg(pos.y(),0,'f',1);
//	painter->drawText(boundingRect(),Qt::AlignLeft|Qt::AlignVCenter,coordinate);
////painter->setCompositionMode(QPainter::RasterOp_SourceXorDestination);
//	painter->setBrush(Qt::NoBrush);
//	painter->setPen(QPen(Qt::yellow, 3, Qt::SolidLine));
//	painter->drawEllipse(QPoint(0,0),5,5);
//	
//	painter->setPen(QPen(Qt::yellow, 1, Qt::SolidLine));
//
//	painter->drawLine(0,-7,0,7);
//	painter->drawLine(-7,0,7,0);
//	QString coordinate=QString("(%1,%2)").arg(display_coordinate.x(),0,'f',1).arg(display_coordinate.y(),0,'f',1);
//	painter->drawText(5,5, coordinate);

}

void CrossPoint::setDisplayCoordinate(const QPointF& coord)
{
	display_coordinate=coord;
}

QVariant CrossPoint::itemChange(GraphicsItemChange change, const QVariant &value)
 {
     if (change == ItemSelectedChange) {
		 qDebug()<<value.toBool();
		// bool old_value=value.toBool();
         
     }
	 else if(change==ItemScenePositionHasChanged)
	 {
		 qDebug()<<"ItemScenePositionHasChanged"<<value;
		 setData(1,value);
	 }
     return QGraphicsItem::itemChange(change, value);
 }
int CrossPoint::type() const
{
    return UserType + 1;
}