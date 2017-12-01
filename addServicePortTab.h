

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





class addServicePortTab : public BaseTab
{
    Q_OBJECT

public:
	addServicePortTab(RTC_XML::RTC_ProfileRTP *comp, RTCViewWidget *viewWidget, ServicePortTable *listWidget, QWidget *parent = 0);

	bool searchPort(QString name, RTC_XML::ServicePorts &ret);
	void addPort(RTC_XML::ServicePorts profile);
	


public Q_SLOTS:
	void IDLFileButtonSlot();
	void IDLPathButtonSlot();
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
