/***************************************************************************
 *   Copyright (C) 2008 by Glad Deschrijver                                *
 *   Glad.Deschrijver@UGent.be                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef TEMPLATEWIDGET_H
#define TEMPLATEWIDGET_H

#include "ui_templatewidget.h"

class TemplateWidget : public QWidget
{
	Q_OBJECT

public:
	TemplateWidget(QWidget *parent = 0);
	~TemplateWidget();
	void setFileName(const QString &fileName);
	void setReplaceText(const QString &replace);
	void setEditor(const QString &editor);
	QString fileName() const;

signals:
	void fileNameChanged(const QString &fileName);
	void focusEditor();

protected:
	void keyPressEvent(QKeyEvent *event);

private slots:
	void setTemplateFile();
	void editTemplateFile();

private:
	void readRecentTemplates();
	void saveRecentTemplates();

	Ui::TemplateWidget ui;

	QString m_editor;
};

#endif