/*!
 * @file  addConfigurationTab.h
 * @brief �R���t�B�M�����[�V�����ݒ�^�u
 *
 */

#ifndef ADDCONFIGURATIONTAB_H
#define ADDCONFIGURATIONTAB_H


#include <QWidget>
#include "BaseTab.h"
#include "RTCViewWidget.h"
#include "ConfigurationTable.h"
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
 * @class addConfigurationTab
 * @brief �R���t�B�M�����[�V�����ݒ�^�u
 */
class addConfigurationTab : public ConfigParamWidgetBase
{
    Q_OBJECT

public:
	/**
	 * @brief �R���X�g���N�^
	 * @param comp �R���|�[�l���g�v���t�@�C���I�u�W�F�N�g
	 * @param viewWidget RTC�\���E�B�W�F�b�g
	 * @param listWidget �R���t�B�O���[�V�����p�����[�^�ꗗ�\���E�B�W�F�b�g
	 * @param parent �e�E�B�W�F�b�g
	 */
	addConfigurationTab(RTC_XML::RTC_ProfileRTP *comp, RTCViewWidget *viewWidget, ConfigurationTable *listWidget, QWidget *parent = 0);

	


public Q_SLOTS:
	/**
	 * @brief �R���t�B�M�����[�V�����p�����[�^�ǉ�
	 * @param profile �R���t�B�O���[�V�����p�����[�^�v���t�@�C���I�u�W�F�N�g
	 */
	void addConfiguration(RTC_XML::ConfigurationSet profile);
	/**
	 * @brief �쐬�{�^���������̃X���b�g
	 */
	void createButtonSlot();
//    void fileNew();

protected:





//    void fileOpen();


private:
	RTCViewWidget *_viewWidget;
	ConfigurationTable *_listWidget;
	QPushButton *_createButton;
	RTC_XML::RTC_ProfileRTP *_comp;

	BaseWidget _paramNameTextbox;
	BaseWidget _paramTypeCombox;
	BaseWidget _paramDefaultTextbox;
	BaseWidget _paramConstraintsTextbox;
	BaseWidget _paramWidgetCombox;
	BaseWidget _paramStepTextbox;
	
};

#endif // TEXTEDIT_H
