/*!
 * @file  addDataPortTab.h
 * @brief �f�[�^�|�[�g�ݒ�^�u
 *
 */



#ifndef ADDDATAPORTTAB_H
#define ADDDATAPORTTAB_H


#include <QWidget>
#include <cnoid/Signal>
#include "BaseTab.h"
#include "RTCViewWidget.h"
#include "DataPortTable.h"
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
 * @class addDataPortTab
 * @brief �f�[�^�|�[�g�ݒ�^�u
 */
class addDataPortTab : public BaseTab
{
    Q_OBJECT

public:
	/**
	 * @brief �R���X�g���N�^
	 * @param comp �R���|�[�l���g�v���t�@�C���I�u�W�F�N�g
	 * @param viewWidget RTC�\���E�B�W�F�b�g
	 * @param listWidget �f�[�^�|�[�g�ꗗ�\���E�B�W�F�b�g
	 * @param parent �e�E�B�W�F�b�g
	 */
	addDataPortTab(RTC_XML::RTC_ProfileRTP *comp, RTCViewWidget *viewWidget, DataPortTable *listWidget, QWidget *parent = 0);
	/**
	 * @brief �f�[�^�|�[�g����
	 * @param name �|�[�g��
	 * @param ret �f�[�^�|�[�g�v���t�@�C���I�u�W�F�N�g
	 * @param return true�F�w��|�[�g���̃f�[�^�|�[�g�����݂��� false:���݂��Ȃ�����
	 */
	bool searchPort(QString name, RTC_XML::DataPorts &ret);
	/**
	 * @brief �f�[�^�|�[�g�ǉ�
	 * @param profile �f�[�^�|�[�g�v���t�@�C���I�u�W�F�N�g
	 */
	void addPort(RTC_XML::DataPorts profile);
	cnoid::Signal<void(RTC_XML::DataPorts)>  sigAddPort;

public Q_SLOTS:
	/**
	 * @brief �����{�^���������̃X���b�g
	 */
	void createButtonSlot();
//    void fileNew();

protected:





//    void fileOpen();


private:
	RTCViewWidget *_viewWidget;
	DataPortTable *_listWidget;
	BaseWidget _portNameTextbox;
	BaseWidget _portTypeCombox;
	BaseWidget _dataTypeCombox;
	QPushButton *_createButton;
	RTC_XML::RTC_ProfileRTP *_comp;

};

#endif // TEXTEDIT_H
