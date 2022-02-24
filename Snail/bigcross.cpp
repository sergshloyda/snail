#include "bigcross.h"
#include "qdebug.h"
BigCross::BigCross()
	: QGraphicsObject()
{
cross_dimention.dX1=0;
	cross_dimention.dX2=0;
	cross_dimention.dY1=0;
	cross_dimention.dY2=0;
}

BigCross::~BigCross()
{

}
QRectF BigCross::boundingRect() const
{
	return QRectF(BigCrossBoundingRect::LEFT,BigCrossBoundingRect::TOP,BigCrossBoundingRect::WIDTH,BigCrossBoundingRect::HEIGHT);
}

void BigCross::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	//qDebug()<<"in BigCross Painter"<<cross_dimention.dX1<<cross_dimention.dX2<<cross_dimention.dY1<<cross_dimention.dY2;
	painter->setCompositionMode(QPainter::RasterOp_SourceXorDestination);

	QPen ROP_pen(Qt::white, 1, Qt::SolidLine);
	ROP_pen.setCosmetic(true);
	painter->setPen(ROP_pen);

	painter->drawLine(QPoint(0,cross_dimention.dY1),QPoint(0,cross_dimention.dY2));
	painter->drawLine(QPoint(cross_dimention.dX1,0),QPoint(cross_dimention.dX2,0));
	

}
void BigCross::setBoundingRect(const CrossDimention& dimention)
{
	cross_dimention.dX1=dimention.dX1;
	cross_dimention.dX2=dimention.dX2;
	cross_dimention.dY1=dimention.dY1;
	cross_dimention.dY2=dimention.dY2;
	
}