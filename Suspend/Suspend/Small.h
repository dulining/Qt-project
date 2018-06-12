#pragma once

#include <QDialog>
#include "ui_Small.h"
//#include "Suspend.h"
#include <QLabel>

class Small : public QDialog
{
	Q_OBJECT

public:
	Small(QWidget *parent = Q_NULLPTR);
	~Small();
	bool m_bStateFlag;
	bool m_IsVisible = true;
	void HideDialog();
	void ShowDialog();
protected:
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);

public slots:
	void restoreWindow();

private:
	void MoveWindow(const QPoint & start, const QPoint & end, unsigned int step = 5);

	Ui::Small ui;
	QTimer * m_timer = nullptr;
	
	QPoint m_RecoverPosition;
	QLabel *m_testLabel;
};
