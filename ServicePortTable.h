/*!
 * @file  ServicePortTable.h
 * @brief �T�[�r�X�|�[�g�ꗗ�\���N���X
 *
 */

#ifndef SERVICEPORTTABLE_H
#define SERVICEPORTTABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QDialog>
#include <QPushButton>

#include "RTC_XML.h"


QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
class QPrinter;
class QLayout;
class QLabel;
class QVBoxLayout;
QT_END_NAMESPACE


/**
 * @class ServicePortOperationDialog
 * @brief �T�[�r�X�|�[�g�ݒ�_�C�A���O
 */
class ServicePortOperationDialog : public QDialog
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param parent �e�E�B�W�F�b�g
	 */
	ServicePortOperationDialog(QWidget *parent = Q_NULLPTR);
private:
	QVBoxLayout *_mainLayout;

};


/**
 * @class ServicePortSettingButton
 * @brief �T�[�r�X�|�[�g�ݒ�{�^��
 */
class ServicePortSettingButton : QPushButton
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param name �\����
	 */
	ServicePortSettingButton(QString name);
protected Q_SLOTS:
	/**
	 * @brief �{�^���������X���b�g
	 */
	void pushSlot();
private:
	ServicePortOperationDialog *_dialog;
};

/**
 * @class ServicePortTable
 * @brief �T�[�r�X�|�[�g�ꗗ�\���E�B�W�F�b�g
 */
class ServicePortTable : public QTableWidget
{
	Q_OBJECT

public:
	/**
	 * @brief �R���X�g���N�^
	 */
	ServicePortTable();
	/**
	 * @brief ���X�g�X�V
	 * @param ports �f�[�^�|�[�g�ꗗ
	 */
	void list_update(QVector<RTC_XML::ServicePorts> ports);

	//    void fileNew();

protected:



private Q_SLOTS :

		//    void fileOpen();


private:



};

#endif // TEXTEDIT_H
