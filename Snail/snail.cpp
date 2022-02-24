#include "snail.h"

Snail::Snail(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

}

Snail::~Snail()
{

}
void Snail::on_btnLoad_clicked()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	QString fileName = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.jpg *.png");
	GridScene* gridScene=reinterpret_cast<GridScene*>(ui.graphicsView->scene());
	gridScene->loadOpenCVImg(fileName);
	ui.graphicsView->fitInView(gridScene->pixmapItem());
	QApplication::restoreOverrideCursor();	

}
void Snail::on_btnAdjustImg_clicked()
{	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	GridScene* gridScene=reinterpret_cast<GridScene*>(ui.graphicsView->scene());
	gridScene->adjustBoardImg();
	//ui.graphicsView->fitInView(gridScene->pixmapItem());
	QApplication::restoreOverrideCursor();	
}