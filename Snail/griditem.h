#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsObject>
#include <qpainter.h>
#include <qpen.h>
#include <qdebug.h>
class GridItem : public QGraphicsObject
{
	Q_OBJECT

public:
	GridItem(QGraphicsObject *parent=0);
	~GridItem();
	void setBoardPhisicalSize(const QSize& size);
private:
	QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void drawHorizRuler(QPainter *painter,const QPointF& origin,int length,int step,int mult_length_dash=3);
	void drawVertRuler(QPainter *painter,const QPointF& origin,int length,int step,int mult_length_dash=3);
	void calculatePixelInMm();
private:
	QPen pen_thin;
	QPen pen_fat;
	QSize pixel_in_mm;
	QSize phisicalSize;
};

#endif // GRIDITEM_H
