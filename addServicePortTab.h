/*!
 * @file  addServicePortTab.h
 * @brief �T�[�r�X�|�[�g�ݒ�^�u
 *
 */

#ifndef ADDSERVICEPORTTAB_H
#define ADDSERVICEPORTTAB_H


#include <QWidget>
#include "BaseTab.h"
#include "RTCViewWidget.h"
#include "ServicePortTable.h"




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
 * @class addDataPortTab
 * @brief �T�[�r�X�|�[�g�ݒ�^�u
 */
class addServicePortTab : public BaseTab
{
    Q_OBJECT

public:
	/**
	 * @brief �R���X�g���N�^
	 * @param comp �R���|�[�l���g�v���t�@�C���I�u�W�F�N�g
	 * @param viewWidget RTC�\���E�B�W�F�b�g
	 * @param listWidget �T�[�r�X�|�[�g�ꗗ�\���E�B�W�F�b�g
	 * @param parent �e�E�B�W�F�b�g
	 */
	addServicePortTab(RTC_XML::RTC_ProfileRTP *comp, RTCViewWidget *viewWidget, ServicePortTable *listWidget, QWidget *parent = 0);
	/**
	 * @brief �T�[�r�X�|�[�g����
	 * @param name �|�[�g��
	 * @param ret �T�[�r�X�^�|�[�g�v���t�@�C���I�u�W�F�N�g
	 * @param return true�F�w��|�[�g���̃T�[�r�X�|�[�g�����݂��� false:���݂��Ȃ�����
	 */
	bool searchPort(QString name, RTC_XML::ServicePorts &ret);
	/**
	 * @brief �T�[�r�X�|�[�g�ǉ�
	 * @param profile �T�[�r�X�|�[�g�v���t�@�C���I�u�W�F�N�g
	 */
	void addPort(RTC_XML::ServicePorts profile);
	


public Q_SLOTS:
	/**
	 * @brief IDL�t�@�C���ݒ�{�^���������̃X���b�g
	 */
	void IDLFileButtonSlot();
	/**
	 * @brief IDL�C���N���[�h�p�X�ݒ�{�^���������̃X���b�g
	 */
	void IDLPathButtonSlot();
	/**
	 * @brief �����{�^���������̃X���b�g
	 */
	void createButtonSlot();
//    void fileNew();

protected:





//    void fileOpen();


private:
	RTCViewWidget *_viewWidget;
	ServicePortTable *_listWidget;
	BaseWidget _portNameTextbox;
	BaseWidget _interfaceNameTextbox;
	BaseWidget _dinterfaceDirCombox;
	BaseWidget _interfaceDirCombox;
	BaseWidget _IDLTextbox;
	BaseWidget _interfaceTypeCombox;
	BaseWidget _IDLPathTextbox;
	QPushButton *_IDLFileButton;
	QPushButton *_IDLPathButton;
	QPushButton *_createButton;
	RTC_XML::RTC_ProfileRTP *_comp;

};

#endif // TEXTEDIT_H
