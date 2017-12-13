/*!
 * @file  ActivityTab.cpp
 * @brief 各コールバック関数編集タブ
 *
 */

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



/**
 * @brief コンストラクタ
 * @param name アクティビティのID
 * @param text テキスト
 * @param parent 親ウィジェット
 */
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

/**
 * @brief コンストラクタ
 * @param name アクティビティ名
 * @param text テキスト
 * @param parent 親ウィジェット
 */
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

/**
 * @brief テキスト取得
 * @return テキスト
 */
QString ActivityTab::getText()
{
	return _editor->toPlainText();
}

/**
* @brief テキスト設定
* @return テキスト
*/
void ActivityTab::setText(QString code)
{
	_editor->setText(code);
}


/**
 * @brief フォントサイズ設定
 * @param s フォントサイズ
 */
void ActivityTab::setFontSize(int s)
{
	_editor->setFontSize(s);
}