/*!
 * @file  BaseTab.cpp
 * @brief �^�u�̊�{�N���X
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



#include "BaseTab.h"


/**
 * @brief �R���X�g���N�^
 * @param parent �e�E�B�W�F�b�g
 */
BaseTab::BaseTab(QWidget *parent)
    : QWidget(parent)
{

	mainLayout = new QVBoxLayout();
	setLayout(mainLayout);
	subLayouts.append(new QVBoxLayout());
	mainLayout->addLayout(subLayouts[subLayouts.size()-1]);
}


/**
 * @brief �E�B�W�F�b�g�ǉ�
 * @param wid �ǉ��E�B�W�F�b�g
 * @param name ���O
 * @param label ���x����
 * @param t �E�B�W�F�b�g�̎��
 * @return �E�B�W�F�b�g�i�[�N���X
 */
BaseWidget BaseTab::apendWidget(QWidget *wid, QString name, QString label, WidgetType t)
{
	QGroupBox *widget = new QGroupBox(label);
	QVBoxLayout *layout = new QVBoxLayout();
	widget->setLayout(layout);

	layout->addWidget(wid);
	subLayouts.back()->addWidget(widget);
	subLayouts.back()->addStretch();


	WidList[name] = BaseWidget(wid, layout, t);

	return WidList[name];
}



/**
 * @brief �R���{�{�b�N�X�ǉ�
 * @param name ���O
 * @param label ���x����
 * @param value �����̒l
 * @param ls �A�C�e�����X�g
 * @param default_s �f�t�H���g�l
 * @return �E�B�W�F�b�g�i�[�N���X
 */
BaseWidget BaseTab::addCombox(QString name, QString label, QVector<QString> value, QVector<QString> ls, QString default_s)
{
	QComboBox *wid_combo = new QComboBox();
	QWidget *wid = wid_combo;
	

	for(QVector<QString>::iterator it = ls.begin();it != ls.end(); ++it)
	{
		wid_combo->addItem(*it);
	}

	if(!value.isEmpty())
	{
		if(!value[0].isEmpty())
		{
			wid_combo->setCurrentIndex(wid_combo->findText(value[0]));
		}
		else
		{
			wid_combo->setCurrentIndex(wid_combo->findText(default_s));
		}
	}
	else
	{
		wid_combo->setCurrentIndex(wid_combo->findText(default_s));
	}

	BaseWidget wl = apendWidget(wid, name, label, Combox);

	return wl;


}


/**
 * @brief ���C���e�L�X�g�{�b�N�X�ǉ�
 * @param name ���O
 * @param label ���x����
 * @param value �����̒l
 * @param default_s �f�t�H���g�l
 * @return �E�B�W�F�b�g�i�[�N���X
 */
BaseWidget BaseTab::addTextBox(QString name, QString label, QVector<QString> value, QString default_s)
{
	QLineEdit *wid_line = new QLineEdit();
	QWidget *wid = wid_line;
	

	

	if(value.isEmpty())
	{
		wid_line->setText(default_s);
	}
	else if(value[0].isEmpty())
	{
		wid_line->setText(default_s);
	}
	else
	{
		wid_line->setText(value[0]);
	}

	BaseWidget wl = apendWidget(wid, name, label, TextBox);

	return wl;


}


/**
 * @brief �R���X�g���N�^
 * @param widget �E�B�W�F�b�g
 * @param layout ���C�A�E�g
 * @param t �E�B�W�F�b�g���
 */
BaseWidget::BaseWidget(QWidget *widget, QLayout *layout, WidgetType t)
	: _widget(widget),
	  _layout(layout),
	  _type(t)
{
}

/**
 * @brief ���C���e�L�X�g�{�b�N�X�Ƀe�L�X�g�ݒ�
 * @param text �e�L�X�g
 */
void BaseWidget::setText(QString text)
{
	QLineEdit *wid = dynamic_cast<QLineEdit*>(_widget);
	if (wid != NULL)
	{
		wid->setText(text);
	}
}

/**
 * @brief ���C���e�L�X�g�{�b�N�X�̃e�L�X�g�擾
 * @return �e�L�X�g
 */
QString BaseWidget::getText()
{
	QLineEdit *wid = dynamic_cast<QLineEdit*>(_widget);
	if (wid != NULL)
	{
		return wid->text();
	}
	return "";
}

/**
 * @brief �R���{�{�b�N�X�̃e�L�X�g�擾
 * @return �e�L�X�g
 */
QString BaseWidget::getItemText()
{
	QComboBox *wid = dynamic_cast<QComboBox*>(_widget);
	if (wid != NULL)
	{
		return wid->currentText();
	}
	return "";
}