

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





class addConfigurationTab : public ConfigParamWidgetBase
{
    Q_OBJECT

public:
	addConfigurationTab(RTC_XML::RTC_ProfileRTP *comp, RTCViewWidget *viewWidget, ConfigurationTable *listWidget, QWidget *parent = 0);

	


public Q_SLOTS:
	void addConfiguration(RTC_XML::ConfigurationSet profile);
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
