

#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <QWidget>
#include <QTableWidget>
#include <QDialog>
#include <QPushButton>
#include <QGroupBox>

#include "RTC_XML.h"
#include "RTCViewWidget.h"

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
class QHBoxLayout;
class QScrollArea;
class QGroupBox;
class QProcess;
QT_END_NAMESPACE


class ComponentWidget : public QGroupBox
{
	Q_OBJECT
public:
	ComponentWidget(QString path, QWidget *parent = 0);
	void setModulePath(QString path);
	QString getCategory();
private Q_SLOTS:
	void run_process();
	void run_rtcd();
private:
	QString _path;
	RTC_XML::RTC_Profile _comp;
	RTCViewWidget *_vw;
	QVBoxLayout *_mainLayout;
	QPushButton *_processButton;
	QPushButton *_managerButton;
	QProcess *_process;
};

class ComponentTabWidgwt : public QWidget
{
	Q_OBJECT
public:
	ComponentTabWidgwt();
	void addComponent(ComponentWidget *cw);
	void addStretchMain(int v = 0);
	void addStretchSub(int v = 0);
private:
	QVector<ComponentWidget *> _complist;
	QVBoxLayout *_mainLayout;
	QVector<QHBoxLayout*> _subLayouts;
};


class ComponentList : public QTabWidget
{
	Q_OBJECT
public:
	ComponentList(QWidget *parent = 0);
	void addComponent(QString path);
	void load(QString path);
private:
	QMap<QString, ComponentTabWidgwt*> tabList;


};

class ScrollArea : public QScrollArea
{
	Q_OBJECT
public:
	ScrollArea(QWidget *parent = 0);
private Q_SLOTS:
	void valueChanged(int v);
};


#endif // TEXTEDIT_H
