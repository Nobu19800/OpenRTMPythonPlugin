

#include <QAction>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QSignalMapper>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QDebug>
#include <QGroupBox>
#include <QTextCodec>

#include <iostream>



#include "ActivityTab.h"




ActivityTab::ActivityTab(ActivityCode name, QString text, QWidget *parent)
	: BaseTab(parent)
{


	_name = name;
	_text = text;

	

	_editor = new PythonEditor();
	
	
	mainLayout->addWidget(_editor);

	_highlight = new Highlighter(_editor->document());
	_editor->setPlainText(_text);
	setLayout(mainLayout);
	
	_editor->textCursor().setPosition(0, QTextCursor::MoveAnchor);
	
	
	this->setMinimumWidth(300);

}


ActivityTab::ActivityTab(QString name, QString text, QWidget *parent)
	: BaseTab(parent)
{

	

	_name = code_num;
	_text = text;



	_editor = new PythonEditor();
	

	mainLayout->addWidget(_editor);

	_highlight = new Highlighter(_editor->document());
	_editor->setPlainText(_text);
	setLayout(mainLayout);

	_editor->textCursor().setPosition(0, QTextCursor::MoveAnchor);

	
	this->setMinimumWidth(300);

}

QString ActivityTab::getText()
{
	return _editor->toPlainText();
}

void ActivityTab::setFontSize(int s)
{
	_editor->setFontSize(s);
}