#ifndef COMPONENTLISTITEM_H
#define COMPONENTLISTITEM_H

#include <cnoid/Item>
#include <cnoid/ItemManager>


#include <QWidget>
#include <QTableWidget>
#include <QDialog>
#include <QPushButton>
#include <QGroupBox>


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







#include "ComponentList.h"
#include "RTC_XML.h"

#include "exportdecl.h"










namespace rtmiddleware {
	
	class CNOID_EXPORT ComponentListItem : public cnoid::Item
	{
	public:
		ComponentListItem();
		ComponentListItem(const ComponentListItem& org);
		virtual ~ComponentListItem();
		static void initialize(cnoid::ExtensionManager* ext);



	protected:
		virtual void doPutProperties(cnoid::PutPropertyFunction& putProperty);
		virtual cnoid::Item* doDuplicate() const override;
		virtual bool store(cnoid::Archive& archive) override;
		virtual bool restore(const cnoid::Archive& archive) override;

		virtual void onPositionChanged();

		ScrollArea *_area;
		ComponentList *_mwin;
	};

};


#endif