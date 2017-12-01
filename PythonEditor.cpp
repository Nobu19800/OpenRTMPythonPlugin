

#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QFontComboBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QTextCodec>
#include <QTextEdit>
#include <QStatusBar>
#include <QToolBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QtDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMimeData>

#include <iostream>

#include "PythonEditor.h"

const int PythonEditor::tab_keywords_size = 2;
const char *PythonEditor::tab_keywords[tab_keywords_size] = { "break", "return" };



PythonEditor::PythonEditor(QWidget *parent)
    : QTextEdit(parent),
	fontSize(12),
	wrapColumn(80)
{

	setTabStopWidth(20);
	createFont(fontSize, wrapColumn);
}



void PythonEditor::createFont(const int fontSize, const int wrapColumn)
{
	QFont font("monospace", fontSize);
	font.setStyleHint(QFont::TypeWriter);
	int fontPxSize = QFontMetrics(font).width('0');
	setFont(font);
	setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
	setLineWrapMode(QTextEdit::FixedPixelWidth);
	setLineWrapColumnOrWidth(fontSize * wrapColumn);
}


void PythonEditor::insertFromMimeData(const QMimeData * source)
{

	if (source->hasText())
	{
		textCursor().insertText(source->text());
	}
}


void PythonEditor::setFontSize(const int s)
{
	createFont(s, wrapColumn);
}


void PythonEditor::keyPressEvent(QKeyEvent *e)
{
	QTextEdit::keyPressEvent(e);
	QTextCursor cu = textCursor();
	int c = document()->lineCount();
	if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
	{
		QString s = document()->findBlockByLineNumber(cu.blockNumber() - 1).text();
		if (!s.isEmpty())
		{
			QString add_str = "";
			int c_t = 0;
			int c_s = 0;
			for (int i = 0; i < s.size(); i++)
			{
				if (s[i] == "\t")
				{
					c_t += 1;
				}
				else if (s[i] == " ")
				{
					c_s += 1;
				}
				else
				{
					break;
				}

			}
			
			
			if (s.at(s.length() - 1) == ":")
			{
				add_str += "\t";
			}

			QString p = s.replace("\t", " ");
			QStringList pl = p.split(" ");
			
			if (!pl.isEmpty())
			{
				p = pl.back();
				for (int i = 0; i < tab_keywords_size; i++)
				{


					if (p == tab_keywords[i])
					{
						if (c_t > 0)c_t -= 1;
						else if (c_s > 0)c_s -= 1;
					}
				}
			}
			for (int i = 0; i < c_t; i++)
			{
				add_str += "\t";
			}

			for (int i = 0; i < c_s; i++)
			{
				add_str += " ";
			}
			std::cout << c_s << "\t" << c_t << std::endl;
			cu.insertText(add_str);
		}

	}
}
