

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


class ServicePortOperationDialog : public QDialog
{
	Q_OBJECT
public:
	ServicePortOperationDialog(QWidget *parent = 0);
private:
	QVBoxLayout *_mainLayout;

};


class ServicePortSettingButton : QPushButton
{
	Q_OBJECT
public:
	ServicePortSettingButton(QString name);
	void pushSlot();
private:
	ServicePortOperationDialog *_dialog;
};


class ServicePortTable : public QTableWidget
{
	Q_OBJECT

public:
	ServicePortTable();
	void list_update(QVector<RTC_XML::ServicePorts> ports);

	//    void fileNew();

protected:



private Q_SLOTS :

		//    void fileOpen();


private:



};

#endif // TEXTEDIT_H
