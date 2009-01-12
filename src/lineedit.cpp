/****************************************************************************
**
** Copyright (c) 2007 Trolltech ASA <info@trolltech.com>
**
** Use, modification and distribution is allowed without limitation,
** warranty, liability or support of any kind.
**
****************************************************************************/

#include "lineedit.h"
#include <QToolButton>
#include <QStyle>

LineEdit::LineEdit(QWidget *parent)
    : QLineEdit(parent)
{
	m_clearButton = new QToolButton(this);
	const QPixmap pixmap(":/images/edit-clear-locationbar-rtl.png");
	m_clearButton->setIcon(QIcon(pixmap));
	m_clearButton->setIconSize(pixmap.size());
	m_clearButton->setCursor(Qt::ArrowCursor);
	m_clearButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
	m_clearButton->setToolTip(tr("Clear input field"));
	m_clearButton->hide();
	connect(m_clearButton, SIGNAL(clicked()), this, SLOT(clear()));
	connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(updateClearButton(const QString&)));
	const int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
	setStyleSheet(QString("QLineEdit { padding-right: %1px; }").arg(m_clearButton->sizeHint().width() + frameWidth + 1));
//	QSize msz = minimumSizeHint();
//	setMinimumSize(qMax(msz.width(), m_clearButton->sizeHint().height() + frameWidth * 2 + 2),
//	               qMax(msz.height(), m_clearButton->sizeHint().height() + frameWidth * 2 + 2));
}

void LineEdit::resizeEvent(QResizeEvent *)
{
	const QSize sz = m_clearButton->sizeHint();
	const int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
	m_clearButton->move(rect().right() - frameWidth - sz.width(),
	                  (rect().bottom() + 1 - sz.height())/2);
}

void LineEdit::updateClearButton(const QString &text)
{
	m_clearButton->setVisible(!text.isEmpty());
}
