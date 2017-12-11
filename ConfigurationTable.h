/*!
 * @file  ConfigurationTable.h
 * @brief �R���t�B�M�����[�V�����p�����[�^�ꗗ�\���N���X
 *
 */

#ifndef CONFIGURATIONTABLE_H
#define CONFIGURATIONTABLE_H


#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QDialog>

#include "BaseTab.h"
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

class ConfigParamDialog;
class RTC_MainWindow;


/**
 * @class ConfigParamWidgetBase
 * @brief �R���t�B�M�����[�V�����p�����[�^�ݒ�E�B���h�E�x�[�X�N���X
 */
class ConfigParamWidgetBase : public BaseTab
{
	Q_OBJECT

public:
	/**
	 * @brief �R���X�g���N�^
	 * @param parent �e�E�B�W�F�b�g
	 */
	ConfigParamWidgetBase(QWidget *parent = Q_NULLPTR);



private:
	BaseWidget _paramNameTextbox;
	BaseWidget _paramTypeCombox;
	BaseWidget _paramDefaultTextbox;
	BaseWidget _paramConstraintsTextbox;
	BaseWidget _paramWidgetCombox;
	BaseWidget _paramStepTextbox;
	QPushButton *_createButton;

};


/**
 * @class ConfigParamWidget
 * @brief �R���t�B�M�����[�V�����p�����[�^�ҏW�E�B�W�F�b�g
 */
class ConfigParamWidget : public ConfigParamWidgetBase
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param dialog �R���t�B�O���[�V�����p�����[�^�ҏW�_�C�A���O
	 * @param parent �e�E�B�W�F�b�g
	 */
	ConfigParamWidget(ConfigParamDialog *dialog, QWidget *parent = Q_NULLPTR);
private:
	ConfigParamDialog *_dialog;

};

/**
 * @class ConfigParamDialog
 * @brief �R���t�B�O���[�V�����p�����[�^�ҏW�_�C�A���O
 */
class ConfigParamDialog : public QDialog
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param parent �e�E�B�W�F�b�g
	 */
	ConfigParamDialog(QWidget *parent = Q_NULLPTR);
private Q_SLOTS:
	/**
	 * @brief �폜�{�^���������̃X���b�g
	 */
	void deleteButtonSlot();
private:
	QVBoxLayout *_mainLayout;
	ConfigParamWidget *_cfwidget;

};


/**
 * @class ConfigSettingButton
 * @brief �R���t�B�O���[�V�����p�����[�^�ҏW�_�C�A���O�N���{�^��
 */
class ConfigSettingButton : public QPushButton
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param name �\����
	 * @param profile �R���t�B�O���[�V�����p�����[�^�v���t�@�C���I�u�W�F�N�g
	 * @param parent �e�E�B�W�F�b�g
	 */
	ConfigSettingButton(QString name, RTC_XML::ConfigurationSet profile, RTC_MainWindow *parent = Q_NULLPTR);
private Q_SLOTS:
	/**
	 * @brief �{�^���������̃X���b�g
	 */
	void pushSlot();
private:
	RTC_MainWindow *_mainwindow;
	RTC_XML::ConfigurationSet _profile;

};


/**
 * @class ConfigurationTable
 * @brief �R���t�B�O���[�V�����p�����[�^�ꗗ�\���E�B�W�F�b�g
 */
class ConfigurationTable : public QTableWidget
{
    Q_OBJECT

public:
	/**
	 * @brief �R���X�g���N�^
	 * @param parent �e�E�B�W�F�b�g
	 */
	ConfigurationTable(RTC_MainWindow *parent = Q_NULLPTR);
	/**
	 * @brief ���X�g�X�V
	 * @param confsets �R���t�B�O���[�V�����p�����[�^�ꗗ
	 */
	virtual void list_update(QVector<RTC_XML::ConfigurationSet> confsets);
public Q_SLOTS:
//    void fileNew();

protected:





//    void fileOpen();


private:
	RTC_MainWindow *_mainLayout;
	

};

/**
 * @class ConfigurationTableRTP
 * @brief �R���t�B�O���[�V�����p�����[�^�ꗗ�\���E�B�W�F�b�g(���I�ҏW�Ή�)
 */
class ConfigurationTableRTP : public ConfigurationTable
{
	Q_OBJECT

public:
	/**
	 * @brief �R���X�g���N�^
	 * @param parent �e�E�B�W�F�b�g
	 */
	ConfigurationTableRTP(RTC_MainWindow *mainwindow, RTC_MainWindow *parent = Q_NULLPTR);
	/**
	 * @brief ���X�g�X�V
	 * @param confsets �R���t�B�O���[�V�����p�����[�^�ꗗ
	 */
	virtual void list_update(QVector<RTC_XML::ConfigurationSet> confsets);
private:
	RTC_MainWindow *_mainwindow;
};


#endif // TEXTEDIT_H
