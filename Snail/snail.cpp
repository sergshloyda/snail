#include "snail.h"
#include <QDesktopWidget>

Snail::Snail(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

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
	ui.graphicsView->fitInView(gridScene->pixmapItem(),Qt::KeepAspectRatio);
	QApplication::restoreOverrideCursor();	

}
void Snail::on_btnAdjustImg_clicked()
{	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	GridScene* gridScene=reinterpret_cast<GridScene*>(ui.graphicsView->scene());
	gridScene->adjustBoardImg();
	//ui.graphicsView->fitInView(gridScene->pixmapItem());
	QApplication::restoreOverrideCursor();	
}