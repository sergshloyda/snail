#ifndef BIGCROSS_H
#define BIGCROSS_H
#pragma warning( disable : 4482 )
#include <QGraphicsObject>
#include <QPainter>
struct CrossDimention{
	int dX1;
	int dX2;
	int dY1;
	int dY2;
};

class BigCross : public QGraphicsObject
{
	Q_OBJECT
		enum BigCrossBoundingRect{
			LEFT=-1000,
			TOP=-1000,
			WIDTH=2000,
			HEIGHT=2000
	}_BigCrossBoundingRect;
public:
	BigCross();
	~BigCross();
	void	setBoundingRect(const CrossDimention& cross_dimention);
private:
	QRectF bounding_rect;


	CrossDimention cross_dimention;
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); 

};

#endif // BIGCROSS_H
