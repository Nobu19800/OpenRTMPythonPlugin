#include <cnoid/MenuManager>
#include <cnoid/MessageView>
#include <boost/bind.hpp>

//#include <src/OpenRTMPlugin/RTSItem.h>


#include <boost/ref.hpp>


#include <cnoid/Item>
#include <cnoid/ItemManager>




#include <QAction>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QSignalMapper>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QDebug>
#include <QGroupBox>
#include <QTextCodec>
#include <QDesktopServices>
#include <QDirIterator>
#include <QScrollBar>
#include <QProcess>




#include <cnoid/FileUtil>
#include <cnoid/ExecutablePath>





#include "ComponentListItem.h"
#include "gettext.h"

using namespace cnoid;
using namespace boost;
using namespace rtmiddleware;










ComponentListItem::ComponentListItem()
	: _mwin(NULL),
	  _area(NULL)
{

};


ComponentListItem::ComponentListItem(const ComponentListItem& org)
{
	setName(org.name());
	if (_mwin == NULL)
	{
		
		_area = new ScrollArea();
		_mwin = new ComponentList();

		std::string dir = (filesystem::path(executableTopDirectory()) / CNOID_SHARE_SUBDIR / "rtc").generic_string();
		_mwin->load(dir.c_str());
		_area->setWidget(_mwin);
		_area->show();

	}

	
};


ComponentListItem::~ComponentListItem()
{
}

void ComponentListItem::initialize(ExtensionManager* ext)
{
	static bool initialized = false;
	if(!initialized){
		ext->itemManager().registerClass<ComponentListItem>(N_("ComponentList"));
		ext->itemManager().addCreationPanel<ComponentListItem>(NULL);
		initialized = true;
	}
}





void ComponentListItem::doPutProperties(cnoid::PutPropertyFunction& putProperty)
{
}
cnoid::Item* ComponentListItem::doDuplicate() const
{
	return new ComponentListItem(*this);
}
bool ComponentListItem::store(cnoid::Archive& archive)
{
	return true;
}
bool ComponentListItem::restore(const cnoid::Archive& archive)
{
	return true;
}

void ComponentListItem::onPositionChanged()
{

}