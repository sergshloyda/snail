#ifndef SNAIL_H
#define SNAIL_H

#include <QtWidgets/QMainWindow>
#include <QGuiApplication>
#include <QFileDialog>
#include <QColorDialog>
#include <QColor>

#include "ui_snail.h"
#include "gridscene.h"
#include "cursorposlabel.h"
#include "BoardPoinsModel.h"

class Snail : public QMainWindow
{
	Q_OBJECT

public:
	Snail(QWidget *parent = 0);
	~Snail();
public slots:
		void on_btnLoad_clicked();
		void on_btnAdjustImg_clicked();
		void on_btnAdjGrid_clicked();

		void addPointInBoardPointsModel(const BoardPoint& newPoint);
		void removePointFromBoardPointsModel(int indx);

private:
	CursorPosLabel* cursorPosLabel;
	Ui::SnailClass ui;
	BoardPointsModel* boardPointsModel;

	void additionalSetupUI();
	void connectSignals(void);
};

#endif // SNAIL_H
