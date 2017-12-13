/*!
 * @file  ComponentListItem.cpp
 * @brief コンポーネントリストアイテム
 *
 */

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









/**
 * @brief コンストラクタ
 */
ComponentListItem::ComponentListItem()
{

};

/**
* @brief デストラクタ
*/
ComponentListItem::~ComponentListItem()
{
	ComponentListView *cv = ComponentListView::instance();
	if (cv)
	{
		ComponentListView::instance()->killprocess();
	}
};

/**
 * @brief コピーコンストラクタ
 * @param org コピー元
 */
ComponentListItem::ComponentListItem(const ComponentListItem& org)
//	: _area(NULL),
//	  _mwin(NULL)
{
	setName(org.name());

	/*
	if (_mwin == NULL)
	{
		_area = new ScrollArea();
		_mwin = new ComponentList();

		std::string dir = (filesystem::path(executableTopDirectory()) / CNOID_SHARE_SUBDIR / "rtc").generic_string();
		_mwin->load(dir.c_str());
		_area->setWidget(_mwin);
		_area->show();
		
		

	}
	*/

	
};



/**
 * @brief 初期化関数
 * @param ext 
 */
void ComponentListItem::initialize(ExtensionManager* ext)
{
	static bool initialized = false;
	if(!initialized){
		ext->itemManager().registerClass<ComponentListItem>(N_("ComponentList"));
		ext->itemManager().addCreationPanel<ComponentListItem>(NULL);
		initialized = true;
	}
}




/**
 * @brief プロパティ設定
 * @param putProperty プロパティ 
 */
void ComponentListItem::doPutProperties(cnoid::PutPropertyFunction& putProperty)
{
}

/**
 * @brief 複製する
 * @return 複製オブジェクト
 */
cnoid::Item* ComponentListItem::doDuplicate() const
{
	return new ComponentListItem(*this);
}

/**
 * @brief 保存する
 * @param archive 
 */
bool ComponentListItem::store(cnoid::Archive& archive)
{
	ComponentListView *cv = ComponentListView::instance();
	if (cv)
	{
		ComponentListView::instance()->store(archive);
	}
	return true;
}

/**
 * @brief 復元する
 * @param archive 
 */
bool ComponentListItem::restore(const cnoid::Archive& archive)
{
	ComponentListView *cv = ComponentListView::instance();
	if (cv)
	{
		ComponentListView::instance()->restore(archive);
	}
	return true;
}

/**
 * @brief 
 */
void ComponentListItem::onPositionChanged()
{

}

/**
* @brief
*/
void ComponentListItem::onDisconnectedFromRoot()
{
	ComponentListView *cv = ComponentListView::instance();
	if (cv)
	{
		ComponentListView::instance()->killprocess();
	}
}



/**
* @brief シミュレーション開始時実行関数
* @return
*/
bool ComponentListItem::start()
{
	ComponentListView *cv = ComponentListView::instance();
	if (cv)
	{
		ComponentListView::instance()->start();
	}
	return true;
}

/**
* @brief 刻み幅取得
* @return 刻み幅
*/
double ComponentListItem::timeStep() const
{
	return 0;
}

/**
* @brief シミュレーション更新前実行関数
*/
void ComponentListItem::input()
{
	ComponentListView *cv = ComponentListView::instance();
	if (cv)
	{
		ComponentListView::instance()->input();
	}
}

/**
* @brief シミュレーション更新中実行関数
*/
bool ComponentListItem::control()
{
	ComponentListView *cv = ComponentListView::instance();
	if (cv)
	{
		ComponentListView::instance()->control();
	}
	return true;
}

/**
* @brief シミュレーション更新後実行関数
*/
void ComponentListItem::output()
{
	ComponentListView *cv = ComponentListView::instance();
	if (cv)
	{
		ComponentListView::instance()->output();
	}
}

/**
* @brief シミュレーション終了時実行関数
*/
void ComponentListItem::stop()
{
	ComponentListView *cv = ComponentListView::instance();
	if (cv)
	{
		ComponentListView::instance()->stop();
	}
}