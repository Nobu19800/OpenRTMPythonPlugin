

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

class ModuleSettingWidget : public QWidget
{
	Q_OBJECT
public:
	ModuleSettingWidget(QWidget *parent = Q_NULLPTR);
private:
	PythonEditor *textEdit;
	QHBoxLayout *mainLayout;
	QHBoxLayout *editLayout;
};

class RTC_MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit RTC_MainWindow(QWidget *parent = Q_NULLPTR,
                        Qt::WindowFlags flags = 0);
	void addActivityTab(ActivityCode name, QString text);

	void deleteServicePort(QString name);
	void deleteDataPort(QString name);
	void deleteConfig(QString name);
	void createMenus();
	QString getFileName();
	cnoid::Signal<void(std::string)>  sigSaveButton;
	
public Q_SLOTS:
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
