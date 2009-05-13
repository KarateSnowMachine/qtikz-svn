/***************************************************************************
 *   Copyright (C) 2007 by Florian Hackenberger                            *
 *   Copyright (C) 2007 by Glad Deschrijver                                *
 *   florian@hackenberger.at                                               *
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

#include <QApplication>

#include "tikzcommandinserter.h"
#include "tikzeditorhighlighter.h"

TikzHighlighter::TikzHighlighter(TikzCommandInserter *commandInserter, QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
	m_commandInserter = commandInserter;

	HighlightingRule rule;

	if (commandInserter)
	{
		m_highlightingRules << commandInserter->getHighlightingRules();
		m_highlightTypeNames << commandInserter->getHighlightTypeNames();
	}
	const int currentIndex = m_highlightTypeNames.size();
	m_highlightTypeNames << "Environments" << "Comments";

	QStringList keywordPatterns;
	keywordPatterns << "\\\\begin\\{[^\\}]*\\}" << "\\\\end\\{[^\\}]*\\}";
	foreach (QString pattern, keywordPatterns)
	{
		rule.type = m_highlightTypeNames.at(currentIndex);
		rule.pattern = QRegExp(pattern);
		m_highlightingRules.append(rule);
	}

	rule.type = m_highlightTypeNames.at(currentIndex + 1);
	rule.pattern = QRegExp("%[^\n]*");
	m_highlightingRules.append(rule);

	m_formatList = getDefaultHighlightFormats();
}

TikzHighlighter::~TikzHighlighter()
{
}

QMap<QString, QTextCharFormat> TikzHighlighter::getDefaultHighlightFormats()
{
	QMap<QString, QTextCharFormat> formatList;
	if (m_commandInserter)
		formatList = m_commandInserter->getDefaultHighlightFormats();
	const int currentIndex = m_highlightTypeNames.size() - 2;

	QTextCharFormat keywordFormat;
	keywordFormat.setForeground(Qt::darkBlue);
	keywordFormat.setFont(qApp->font());
	keywordFormat.setFontWeight(QFont::Bold);
	formatList[m_highlightTypeNames.at(currentIndex)] = keywordFormat;

	QTextCharFormat commentFormat;
	commentFormat.setForeground(Qt::gray);
	commentFormat.setFont(qApp->font());
	commentFormat.setFontWeight(QFont::Normal);
	formatList[m_highlightTypeNames.at(currentIndex + 1)] = commentFormat;

	return formatList;
}

QStringList TikzHighlighter::getTranslatedHighlightTypeNames()
{
	QStringList translatedHighlightTypeNames;
	if (m_commandInserter)
		translatedHighlightTypeNames = m_commandInserter->getTranslatedHighlightTypeNames();
	translatedHighlightTypeNames << tr("Environments") << tr("Comments");
	return translatedHighlightTypeNames;
}

QStringList TikzHighlighter::getHighlightTypeNames()
{
	return m_highlightTypeNames;
}

QMap<QString, QTextCharFormat> TikzHighlighter::getTextCharFormats()
{
	return m_formatList;
}

void TikzHighlighter::setTextCharFormats(const QMap<QString, QTextCharFormat> &formatList)
{
	m_formatList = formatList;
}

void TikzHighlighter::highlightBlock(const QString &text)
{
	// Try each highlighting pattern and apply formatting if it matches
	foreach (HighlightingRule rule, m_highlightingRules)
	{
//		const QRegExp expression(rule.pattern);
//		int index = text.indexOf(expression);
		QRegExp expression(rule.pattern);
		int index = expression.indexIn(text);
		while (index >= 0)
		{
			const int length = expression.matchedLength();
			if (index == 0 || text.at(index-1) != '\\')
				setFormat(index, length, m_formatList[rule.type]);
//			index = text.indexOf(expression, index + length);
			index = expression.indexIn(text, index + length);
		}
	}
	setCurrentBlockState(0);
}