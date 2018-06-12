#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Suspend.h"
#include "Small.h"
#include <QTimer>

class Suspend : public QMainWindow
{
	Q_OBJECT

public:
	Suspend(QWidget *parent = Q_NULLPTR);

public slots:
	void HideShowWindow();
	void ShowMain();

private:
	Ui::SuspendClass ui;
	Small *m_pSmallDialog;
	QTimer *m_timer = nullptr;
};
