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
		enum boardSize{
			WIDTH=150,
			HEIGHT=60
	} _board_size;

	enum boardMargin{
		LEFT_MARGIN=100,
		TOP_MARGIN=100
	} _boardMargin;
public:
	GridScene(QObject *parent);
	~GridScene();
	//void drawCircle(const QPoint& center,int radius);
	void drawGrid();
	//void drawBoardPixmap();
	bool loadBackgroundImg(const QString& fileName);
	void adjustSceneSize();
	void drawBoundingBox();
	bool loadPixmap(const QString& fileName);
	void calculateBoardImgRect();
	bool loadOpenCVImg(const QString& fileName);
	QGraphicsPixmapItem* pixmapItem();
	

private:
	CrossPoint* myPoint;
	QList<QGraphicsLineItem*> vLines,gLines;
	QImage* bg_image_ ;
	QPixmap board_img;
	QGraphicsPixmapItem* board_PixmapItem;
	QGraphicsRectItem* img_rect_item;
	QSize pixel_in_mm;
	QSize sceneSize;
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
	void scaleBoardImg();
	void drawGridLegend(const QSize& sizeGrid=QSize(0,0));
	//void drawHorizRuler(const QPoint& origin,int length,int step,const QPen& pen,int mult_length_dash=3);
//	void drawVertRuler(const QPoint& origin,int length,int step,const QPen& pen,int mult_length_dash=3);
	void calculatePixelInMm();
	QPointF translate_to_board_coordinate(const QPoint& inPoint);
	QPointF translate_to_phisical_coordinate(const QPointF& in,const QSize& pixel_in_mm);
	QPointF originScenePoint();
public:
	void adjustBoardImg(void);
	
	QRect boardImgRect();
};

#endif // GRIDSCENE_H