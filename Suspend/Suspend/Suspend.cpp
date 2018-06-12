#include "Suspend.h"
#include <QApplication>
#include <QDesktopWidget>

Suspend::Suspend(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_pSmallDialog = new Small();
	m_timer = new QTimer(this);
	connect(ui.pushButton, &QPushButton::clicked, this, &Suspend::HideShowWindow);
	connect(m_timer, &QTimer::timeout, this, &Suspend::ShowMain);
	
}
void Suspend::HideShowWindow()
{
	this->hide();
	m_timer->start(1000);
	m_pSmallDialog->m_bStateFlag = false;
	m_pSmallDialog->m_IsVisible = true;
	m_pSmallDialog->show();

	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect screenRect = desktopWidget->screenGeometry();
	int x = screenRect.width();
	m_pSmallDialog->move((x-m_pSmallDialog->width())/2, 0);
}
void Suspend::ShowMain()
{
	if (m_pSmallDialog->m_bStateFlag)
	{
		m_pSmallDialog->m_bStateFlag = false;
		this->showNormal();	
	}
	//m_timer->stop();	
}
