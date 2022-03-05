#ifndef SNAIL_H
#define SNAIL_H

#include <QtWidgets/QMainWindow>
#include <QGuiApplication>
#include "ui_snail.h"
#include "gridscene.h"
#include "cursorposlabel.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QColor>

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

private:
	CursorPosLabel* cursorPosLabel;
	Ui::SnailClass ui;

	void additionalSetupUI();
	void connectSignals(void);
};

#endif // SNAIL_H
