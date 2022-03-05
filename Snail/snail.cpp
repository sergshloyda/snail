#include "snail.h"
#include <QDesktopWidget>
#include "boardsizedlg.h"
Snail::Snail(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
	additionalSetupUI();
	connectSignals();

 

}

Snail::~Snail()
{

}
void Snail::on_btnLoad_clicked()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	QString fileName = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.jpg *.png");
	if(fileName.isEmpty())
		{
			QApplication::restoreOverrideCursor();	
			return;
		}
	GridScene* gridScene=reinterpret_cast<GridScene*>(ui.graphicsView->scene());
	gridScene->loadOpenCVImg(fileName);
	ui.graphicsView->fitInView(gridScene->pixmapItem(),Qt::KeepAspectRatio);
	QApplication::restoreOverrideCursor();	

}
void Snail::on_btnAdjustImg_clicked()
{	

	GridScene* gridScene=reinterpret_cast<GridScene*>(ui.graphicsView->scene());
		BoardSizeDlg* dlg=new BoardSizeDlg(this);
	if(dlg->exec()==QDialog::Accepted){
		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
		gridScene->adjustBoardImg(dlg->boardSize());
		QApplication::restoreOverrideCursor();	
	}
	delete dlg;

	//ui.graphicsView->fitInView(gridScene->pixmapItem());

}


void Snail::on_btnAdjGrid_clicked()
{
	GridScene* gridScene=reinterpret_cast<GridScene*>(ui.graphicsView->scene());
	
		gridScene->adjustGrid();
		ui.graphicsView->setMouseTracking(true);

}

void Snail::additionalSetupUI()
{
	cursorPosLabel=new CursorPosLabel(this);
    statusBar()->addPermanentWidget(cursorPosLabel);
	QLabel* statusRight = new QLabel("Right", this);
    statusRight->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	statusBar()->addPermanentWidget(statusRight,1);
}


void Snail::connectSignals()
{
	connect(ui.graphicsView->scene(),SIGNAL(changeCursorPosition(const QString&)),cursorPosLabel,SLOT(ChangeLabelText(const QString&)));
}
