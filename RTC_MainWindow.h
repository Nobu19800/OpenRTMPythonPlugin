/*!
 * @file  RTC_MainWindow.h
 * @brief RTCEditor���C���E�B���h�E�N���X
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTemporaryDir>
#include <cnoid/Signal>
#include "PythonEditor.h"
#include "RTCViewWidget.h"
#include "addDataPortTab.h"
#include "addServicePortTab.h"
#include "addConfigurationTab.h"
#include "ActivityTab.h"
#include "ActivityCode.h"
#include "ControlCompWidget.h"


QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
class QPrinter;
class QHBoxLayout;
class QVBoxLayout;
class QTemporaryDir;
QT_END_NAMESPACE

class ToolBar;
QT_FORWARD_DECLARE_CLASS(QMenu)

/**
 * @class ModuleSettingWidget
 * @brief 
 */
class ModuleSettingWidget : public QWidget
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param parent �e�E�B�W�F�b�g
	 */
	ModuleSettingWidget(QWidget *parent = Q_NULLPTR);
private:
	PythonEditor *textEdit;
	QHBoxLayout *mainLayout;
	QHBoxLayout *editLayout;
};


/**
 * @class RTC_MainWindow
 * @brief RTCEditor���C���E�B���h�E�N���X
 */
class RTC_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	/**
	 * @brief �R���X�g���N�^
	 * @param parent �e�E�B�W�F�b�g
	 * @param flags 
	 */
	explicit RTC_MainWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
	/**
	 * @brief �A�N�e�B�r�e�B�ҏW�^�u�ǉ�
	 * @param name ���O
	 * @param text �e�L�X�g
	 */
	void addActivityTab(ActivityCode name, QString text);
	/**
	 * @brief �T�[�r�X�|�[�g�폜
	 * @param name �T�[�r�X�|�[�g��
	 */
	void deleteServicePort(QString name);
	/**
	 * @brief �f�[�^�|�[�g�폜
	 * @param name �f�[�^�|�[�g��
	 */
	void deleteDataPort(QString name);
	/**
	 * @brief �R���t�B�O���[�V�����p�����[�^�폜
	 * @param name �R���t�B�O���[�V�����p�����[�^��
	 */
	void deleteConfig(QString name);
	/**
	 * @brief ���j���[�쐬
	 */
	void createMenus();
	/**
	 * @brief �ҏW����Python�t�@�C���p�X�擾
	 * @return Python�t�@�C���̃p�X
	 */
	QString getFileName();
	cnoid::Signal<void(const char*)>  sigSaveButton;
	
public Q_SLOTS:
	/**
	 * @brief �ۑ��{�^���������̃X���b�g
	 */
	void save_button_slot();
//public Q_SIGNAL:
//	void save_button_signal(QString filename);

public:
	QMap<ActivityCode, ActivityTab*> tab_list;
	QWidget *cw;
	QVBoxLayout *ml;
	QHBoxLayout *subLayout;
	QVBoxLayout *tabLayout;
	QTabWidget *tab_widget;
	QHBoxLayout *rtcLayout;
	RTCViewWidgetRTP *vw;
	QVBoxLayout* viewLayout;
	QTabWidget *rtc_tab_widget;
	addDataPortTab *_addDataPortTab;
	DataPortTable *_dataport_widget;
	addServicePortTab * _addServicePortTab;
	ServicePortTable *_serviceport_widget;
	addConfigurationTab *_addConfigurationTab;
	ConfigurationTable *_config_widget;
	QMap<ActivityCode, QString> activities;
	ControlCompWidget *_controlCompWidget;
	QPushButton *save_button;
	ActivityTab *global_tab;
	RTC_XML::RTC_ProfileRTP *_comp;
	QTemporaryDir _tmp_dir;
	/*
	QMenu *fileMenu;
	QMenu *exportMenu;
	QMenu *editMenu;
	QMenu *fontMenu;
	QMenu *optionMenu;
	QMenu *execMenu;
	QMenu *helpMenu;
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *saveAsAct;
	*/
};

#endif // MAINWINDOW_H
