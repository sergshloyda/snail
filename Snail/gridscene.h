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
private:
	CrossPoint* myPoint;
	QPixmap board_img;
	QGraphicsPixmapItem* board_PixmapItem;
	QGraphicsRectItem* img_rect_item;
	QSize pixel_in_mm;
	QSize sceneSize;
	QSize boardPhisicalSize;
	QRect board_img_rect;
	bool mouse_pointer_in_board_img_rect;
	QPoint cursor_position;
	QCursor cursor_target;
	BigCross* cross;
	OpenCVImage* openCVImage;
	GridItem* gridItem;
protected:
    void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
	signals:
		void change_cursor_position(const QPointF& pos);

private:
	void scaleBoardImg(const QSize& sizeBoard);
	void drawGridLegend(const QSize& sizeGrid=QSize(0,0));
	QPointF translate_to_board_coordinate(const QPoint& inPoint);
	QPointF translate_to_phisical_coordinate(const QPointF& in,const QSize& pixel_in_mm);
	QPointF originScenePoint();
public:
	void adjustBoardImg(const QSize& sizeBoardInMM);
	void adjustGrid();
	QRect boardImgRect();
};

#endif // GRIDSCENE_H