

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





class addDataPortTab : public BaseTab
{
    Q_OBJECT

public:
	addDataPortTab(RTC_XML::RTC_ProfileRTP *comp, RTCViewWidget *viewWidget, DataPortTable *listWidget, QWidget *parent = 0);

	bool searchPort(QString name, RTC_XML::DataPorts &ret);
	void addPort(RTC_XML::DataPorts profile);
	cnoid::Signal<void(RTC_XML::DataPorts)>  sigAddPort;

public Q_SLOTS:
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
