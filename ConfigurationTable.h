

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



class ConfigParamWidgetBase : public BaseTab
{
	Q_OBJECT

public:
	ConfigParamWidgetBase(QWidget *parent = 0);



private:
	BaseWidget _paramNameTextbox;
	BaseWidget _paramTypeCombox;
	BaseWidget _paramDefaultTextbox;
	BaseWidget _paramConstraintsTextbox;
	BaseWidget _paramWidgetCombox;
	BaseWidget _paramStepTextbox;
	QPushButton *_createButton;

};


class ConfigParamWidget : public ConfigParamWidgetBase
{
	Q_OBJECT
public:
	ConfigParamWidget(ConfigParamDialog *dialog, QWidget *parent = 0);
private:
	ConfigParamDialog *_dialog;

};

class ConfigParamDialog : public QDialog
{
	Q_OBJECT
public:
	ConfigParamDialog(QWidget *parent = 0);
private Q_SLOTS:
	void deleteButtonSlot();
private:
	QVBoxLayout *_mainLayout;
	ConfigParamWidget *_cfwidget;

};


class ConfigSettingButton : public QPushButton
{
	Q_OBJECT
public:
	ConfigSettingButton(QString name, RTC_XML::ConfigurationSet profile, RTC_MainWindow *parent = 0);
private Q_SLOTS:
	void pushSlot();
private:
	RTC_MainWindow *_mainwindow;
	RTC_XML::ConfigurationSet _profile;

};


class ConfigurationTable : public QTableWidget
{
    Q_OBJECT

public:
	ConfigurationTable(RTC_MainWindow *parent = 0);
	virtual void list_update(QVector<RTC_XML::ConfigurationSet> confsets);
public Q_SLOTS:
//    void fileNew();

protected:





//    void fileOpen();


private:
	RTC_MainWindow *_mainLayout;
	

};


class ConfigurationTableRTP : public ConfigurationTable
{
	Q_OBJECT

public:
	ConfigurationTableRTP(RTC_MainWindow *mainwindow, RTC_MainWindow *parent = 0);
	virtual void list_update(QVector<RTC_XML::ConfigurationSet> confsets);
private:
	RTC_MainWindow *_mainwindow;
};


#endif // TEXTEDIT_H
