#include "Small.h"
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>

#define HIDE_BORDER 1  //Òþ²ØÊ±ÏÔÊ¾border
#define CHECK_BORDER 2 //±ß½ç¼ì²â¿í¶È

Small::Small(QWidget *parent)
	: QDialog(parent)
{
	m_bStateFlag = false;
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
	connect(ui.restoreButton,&QPushButton::clicked,this,&Small::restoreWindow);

	m_testLabel = new QLabel(this);
	m_testLabel->setText("Manual Label");
	m_testLabel->setGeometry(20, 20, 150, 50);

}

Small::~Small()
{
}
void Small::restoreWindow()
{
	m_bStateFlag = true;
	this->hide();
}
void Small::enterEvent(QEvent * e)
{
	if (m_timer && m_timer->isActive())
	{
		m_timer->stop();
	}
	ShowDialog();

	QWidget::enterEvent(e);
}

void Small::leaveEvent(QEvent * e)
{
	QPoint mousePos = mapFromGlobal(QCursor::pos());
	if (this->rect().contains(mousePos) == false && mousePos.x() != rect().width())
	{
		HideDialog();
	}
	else
	{
		if (m_timer == nullptr)
		{
			m_timer = new QTimer(this);
			connect(m_timer, &QTimer::timeout, this, [this]{
				QPoint mousePos = mapFromGlobal(QCursor::pos());
				if (this->rect().contains(mousePos) == false && mousePos.x() != rect().width())
				{
					HideDialog();
				}
			});
		}
		m_timer->start(500);
	}
	QWidget::leaveEvent(e);
}

void Small::HideDialog()
{
	if (m_IsVisible == false)
	{
		return;
	}

	m_IsVisible = false;

	int curHeight = height();
	int curWidth = width();

	QDesktopWidget * desktop = qApp->desktop();
	QRect rect = desktop->screenGeometry(this);

	if (this->frameGeometry().top()-CHECK_BORDER <= rect.top())
	{
		MoveWindow(pos(),pos() - QPoint(0,curHeight - HIDE_BORDER));
	}
	else
	{
		m_IsVisible = true;
	}

	if (m_IsVisible == false)
	{
		if (m_timer && m_timer->isActive())
		{
			m_timer->stop();
		}
	}
}

void Small::ShowDialog()
{
	if (m_IsVisible)
	{
		return;
	}

	m_IsVisible = true;

	int curHeight = height();
	int curWidth = width();

	QDesktopWidget * desktop = qApp->desktop();
	QRect rect = desktop->screenGeometry(this);
	QRect frameRect = frameGeometry();

	if (frameRect.top() == m_RecoverPosition.y() - (curHeight - HIDE_BORDER))
	{
		MoveWindow(pos(), m_RecoverPosition);
	}
	else
	{
		m_IsVisible = false;
	}
}

void Small::MoveWindow(const QPoint & start, const QPoint & end, unsigned int step)
{
	QPoint distance = end - start;
	QPoint stepPos, stepOne;
	if (end.x() == start.x())
	{
		stepOne.setY(step * (distance.y() > 0 ? 1 : -1));
	}
	else
	{
		stepOne.setX(step * (distance.x() > 0 ? 1 : -1));
	}
	stepPos = stepOne;

	int disLenght = distance.manhattanLength();
	while (stepPos.manhattanLength() <= disLenght)
	{
		move(start + stepPos);
		stepPos += stepOne;
	}

	move(end);
	m_RecoverPosition = start;
}

