/*!
 * @file  ActivityTab.cpp
 * @brief �e�R�[���o�b�N�֐��ҏW�^�u
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
 * @brief �R���X�g���N�^
 * @param name �A�N�e�B�r�e�B��ID
 * @param text �e�L�X�g
 * @param parent �e�E�B�W�F�b�g
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
 * @brief �R���X�g���N�^
 * @param name �A�N�e�B�r�e�B��
 * @param text �e�L�X�g
 * @param parent �e�E�B�W�F�b�g
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
 * @brief �e�L�X�g�擾
 * @return �e�L�X�g
 */
QString ActivityTab::getText()
{
	return _editor->toPlainText();
}

/**
* @brief �e�L�X�g�ݒ�
* @return �e�L�X�g
*/
void ActivityTab::setText(QString code)
{
	_editor->setText(code);
}


/**
 * @brief �t�H���g�T�C�Y�ݒ�
 * @param s �t�H���g�T�C�Y
 */
void ActivityTab::setFontSize(int s)
{
	_editor->setFontSize(s);
}