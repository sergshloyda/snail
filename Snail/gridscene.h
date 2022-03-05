#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>

#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include "crosspoint.h"
#include <QPixmap>
#include <qcursor.h>
#include "bigcross.h"
#include <QKeyEvent>
#include "OpenCVImage.h"
#include "griditem.h"
#include <QMargins>
class GridScene : public QGraphicsScene
{
	Q_OBJECT


	enum boardMargin{
		LEFT_MARGIN=100,
		TOP_MARGIN=100
	} _boardMargin;
public:
	GridScene(QObject *parent);
	~GridScene();

	bool loadBackgroundImg(const QString& fileName);
	bool loadOpenCVImg(const QString& fileName);
	QGraphicsPixmapItem* pixmapItem();
	void adjustBoardImg(const QSize& sizeBoardInMM);
	void adjustGrid();
	QRectF boardImgRect();
private:
	CrossPoint* myPoint;
	QPixmap board_img;
	QGraphicsPixmapItem* board_PixmapItem;
	QGraphicsRectItem* img_rect_item;
	QSize pixel_in_mm;
	QSize sceneSize;
	QSize boardPhisicalSize;
	QRectF board_img_rect;
	bool mousePointerInBoardImgRect;
	QPoint cursor_position;
	QCursor cursor_target;
	OpenCVImage* openCVImage;
	GridItem* gridItem;
protected:
    void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void drawForeground(QPainter * painter, const QRectF & rect) ;


private:
	void scaleBoardImg(const QSize& sizeBoard);
	QPointF translateToBoardCoordinate(const QPointF& inPoint);
	QPointF translateToPhisicalCoordinate(const QPointF& in,const QSize& pixel_in_mm);
	QPointF originScenePoint();
public:
		signals:
		void changeCursorPosition(const QString& newPos);

};

#endif // GRIDSCENE_H