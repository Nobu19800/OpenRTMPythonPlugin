/*!
 * @file  RTC_MainWindow.cpp
 * @brief RTCEditorメインウィンドウクラス
 *
 */

#include <cnoid/MenuManager>
#include <cnoid/MessageView>
#include <boost/bind.hpp>

#include <QTextCodec>

//#include <src/OpenRTMPlugin/RTSItem.h>


#include <boost/ref.hpp>

#include <cnoid/PythonExecutor>
#include <cnoid/PyUtil>
#include <boost/version.hpp>

#include <cnoid/Item>
#include <cnoid/ItemManager>



#include <cnoid/LazyCaller>

#include <cnoid/BodyItem>
#include <cnoid/ControllerItem>
#include <cnoid/Body>
#include <cnoid/Light>
#include <cnoid/Archive>


#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QSignalMapper>
#include <QRegExp>



#include <cnoid/FileUtil>
#include <cnoid/ExecutablePath>

#ifdef CNOID_USE_PYBIND11
#include <pybind11/embed.h>
namespace py = pybind11;
#else
#include <boost/python.hpp>
namespace py = boost::python;
#endif


#include <src/OpenRTMPlugin/RTSDiagramView.h>

#include "RTCEditorItem.h"
#include "gettext.h"

using namespace cnoid;
using namespace boost;
using namespace rtmiddleware;



/**
 * @class PyGILock
 * @brief Python実行時のロックオブジェクト
 */
class PyGILock
{
	PyGILState_STATE gstate;
public:
	/**
	 * @brief コンストラクタ
	 */
	PyGILock() {
		gstate = PyGILState_Ensure();
	};
	/**
	 * @brief デストラクタ
	 */
	~PyGILock() {
		PyGILState_Release(gstate);
	};
};



namespace cnoid {
# if defined _WIN32 || defined __CYGWIN__
	__declspec(dllimport) python::object getGlobalNamespace();
#else
	python::object getGlobalNamespace();
#endif
}



/**
 * @brief コンストラクタ
 */
RTCEditorItem::RTCEditorItem()
	: mwin(NULL)
{

};

/**
 * @brief コピーコンストラクタ
 * @param org コピー元
 */
RTCEditorItem::RTCEditorItem(const RTCEditorItem& org)
{
	setName(org.name());
	RTSDiagramView* rtsView = RTSDiagramView::instance();
	if (rtsView) {
		//std::bind(&RTCEditor::selectChanged, this, _1);
		if (!selectionChangedConnection.connected())
		{
			selectionChangedConnection = rtsView->sigDoubleClickEvent().connect(std::bind(&RTCEditorItem::onItemSelectionChanged, this, std::placeholders::_1));
		}
	}
	//if (mwin == NULL)
	{
		
		
		callLater([&] {
			mwin = new RTC_MainWindow();
			mwin->save_button_slot();
			createEditComp(mwin->getFileName().toLocal8Bit());
			mwin->sigSaveButton.connect(std::bind(&RTCEditorItem::update_comp, this, std::placeholders::_1));
			mwin->_controlCompWidget->sigActiveButton.connect(std::bind(&RTCEditorItem::activate_comp, this));
			mwin->_controlCompWidget->sigDeactiveButton.connect(std::bind(&RTCEditorItem::deactivate_comp, this));
			mwin->_controlCompWidget->sigResetButton.connect(std::bind(&RTCEditorItem::reset_comp, this));
			mwin->vw->getRenderRTC()->updateStatus.connect(std::bind(&RTCEditorItem::get_status, this, std::placeholders::_1));
			mwin->_addDataPortTab->sigAddPort.connect(std::bind(&RTCEditorItem::add_dataport, this, std::placeholders::_1));
			
			mwin->show(); 

			
		});
		
		
		
		//QObject::connect(mwin, SIGNAL(save_button_signal(QString)), this, SLOT(update(QString)));
	}
	
	
	
};

/**
 * @brief デストラクタ
 */
RTCEditorItem::~RTCEditorItem()
{
}

/**
 * @brief RTCのファイル更新
 * @param filename Pythonファイルのパス
 */
void RTCEditorItem::update_comp(const char* filename)
{
	//MessageView::instance()->putln(0, name);
	//MessageView::instance()->putln(0, item->name);
	/*if (filename.empty())
	{
		return;
	}*/

	if (comp_name.empty())
	{
		return;
	}



	{
		PyGILock lock;
		//MessageView::instance()->putln(0, _(name.c_str()));
		try
		{
#ifdef CNOID_USE_PYBIND11
			getGlobalNamespace()["updateEditComp"](comp_name.c_str(), filename);
#else
			python::extract<std::string>(cnoid::getGlobalNamespace()["updateEditComp"](name.c_str(), filename));
			//comp_name = python::extract<std::string>(cnoid::pythonMainNamespace()["createComp"](name));
#endif

		}
		catch (const py::error_already_set&e)
		{
#ifdef CNOID_USE_PYBIND11
			MessageView::instance()->putln(0,
				format(_("%1%")) % e.what());
#else
			PyErr_Print();
#endif
		}
		catch (...)
		{

		}




	}
}

/**
 * @brief RTCのアクティブ化
 */
void RTCEditorItem::activate_comp()
{


	if (comp_name.empty())
	{
		return;
	}



	{
		PyGILock lock;
		try
		{
#ifdef CNOID_USE_PYBIND11
			getGlobalNamespace()["activateComp"](comp_name.c_str(),0);
#else
			python::extract<std::string>(cnoid::getGlobalNamespace()["activateComp"](comp_name.c_str()));
			//comp_name = python::extract<std::string>(cnoid::pythonMainNamespace()["activateComp"](comp_name.c_str()));
#endif

		}
		catch (const py::error_already_set&e)
		{
#ifdef CNOID_USE_PYBIND11
			MessageView::instance()->putln(0,
				format(_("%1%")) % e.what());
#else
			PyErr_Print();
#endif
		}
		catch (...)
		{

		}




	}
}

/**
 * @brief RTCの非アクティブ化
 */
void RTCEditorItem::deactivate_comp()
{


	if (comp_name.empty())
	{
		return;
	}



	{
		PyGILock lock;
		try
		{
#ifdef CNOID_USE_PYBIND11
			getGlobalNamespace()["deactivateComp"](comp_name.c_str(), 0);
#else
			python::extract<std::string>(cnoid::getGlobalNamespace()["deactivateComp"](comp_name.c_str()));
			//comp_name = python::extract<std::string>(cnoid::pythonMainNamespace()["deactivateComp"](comp_name.c_str()));
#endif

		}
		catch (const py::error_already_set&e)
		{
#ifdef CNOID_USE_PYBIND11
			MessageView::instance()->putln(0,
				format(_("%1%")) % e.what());
#else
			PyErr_Print();
#endif
		}
		catch (...)
		{

		}




	}
}

/**
 * @brief RTCのリセット
 */
void RTCEditorItem::reset_comp()
{


	if (comp_name.empty())
	{
		return;
	}



	{
		PyGILock lock;
		try
		{
#ifdef CNOID_USE_PYBIND11
			getGlobalNamespace()["resetComp"](comp_name.c_str(), 0);
#else
			python::extract<std::string>(cnoid::getGlobalNamespace()["resetComp"](comp_name.c_str()));
			//comp_name = python::extract<std::string>(cnoid::pythonMainNamespace()["resetComp"](comp_name.c_str()));
#endif

		}
		catch (const py::error_already_set&e)
		{
#ifdef CNOID_USE_PYBIND11
			MessageView::instance()->putln(0,
				format(_("%1%")) % e.what());
#else
			PyErr_Print();
#endif
		}
		catch (...)
		{

		}




	}
}

/**
 * @brief データポート追加
 * @param port データポートプロファイル
 */
void RTCEditorItem::add_dataport(RTC_XML::DataPorts port)
{
	if (comp_name.empty())
	{
		return;
	}



	{
		PyGILock lock;
		try
		{
#ifdef CNOID_USE_PYBIND11
			getGlobalNamespace()["addDataPort"](comp_name.c_str(), port.get_name().toStdString().c_str(), port.get_portType().toStdString().c_str(), port.get_type().toStdString().c_str());
#else
			python::extract<std::string>(cnoid::getGlobalNamespace()["addDataPort"](comp_name.c_str(), port.get_name().toStdString().c_str(), port.get_portType().toStdString().c_str(), port.get_type().toStdString().c_str()));
			//comp_name = python::extract<std::string>(cnoid::pythonMainNamespace()["resetComp"](comp_name.c_str()));
#endif

		}
		catch (const py::error_already_set&e)
		{
#ifdef CNOID_USE_PYBIND11
			MessageView::instance()->putln(0,
				format(_("%1%")) % e.what());
#else
			PyErr_Print();
#endif
		}
		catch (...)
		{

		}




	}
}

/**
 * @brief 初期化関数
 * @param ext 
 */
void RTCEditorItem::initialize(ExtensionManager* ext)
{
	static bool initialized = false;
	if(!initialized){
		ext->itemManager().registerClass<RTCEditorItem>(N_("RTCEditor"));
		ext->itemManager().addCreationPanel<RTCEditorItem>(NULL);
		initialized = true;
	}
}


/**
 * @brief RTCダイアグラム上の選択アイテム変更時実行関数
 * @param item RTCダイアグラム上で選択中のRTC
 */
void RTCEditorItem::onItemSelectionChanged(RTSComp* item)
{
	//MessageView::instance()->putln(0, item->name);
	//MessageView::instance()->putln(0, comp_name);
	
	if (item->name == comp_name)
	{
		if (mwin)
		{
			mwin->hide();
			mwin->show();

		}
	}
}

/**
 * @brief RTC生成
 * @param name RTC名
 */
void RTCEditorItem::createEditComp(const char* name)
{
	/*
	if (name.empty())
	{
		return;
	}
	*/

	

	{
		PyGILock lock;
		//MessageView::instance()->putln(0, _(name.c_str()));
		try
		{
			if (!comp_name.empty())
			{
#ifdef CNOID_USE_PYBIND11
				getGlobalNamespace()["exitComp"](comp_name.c_str());
#else
				python::extract<std::string>(cnoid::getGlobalNamespace()["exitComp"](comp_name.c_str()));
				//python::extract<std::string>(cnoid::pythonMainNamespace()["exitComp"](comp_name.c_str()));
#endif
			}
#ifdef CNOID_USE_PYBIND11
			comp_name = pybind11::str(getGlobalNamespace()["createEditComp"](name)).cast<std::string>();
			/*
			QString fileName = QFileDialog::getOpenFileName(NULL,
				_("Open Address Book"), "",
				_("Address Book (*.txt);;All Files (*)"));

			getGlobalNamespace()["testFunc"]((const char*)fileName.toStdString().c_str());
			*/
#else
			comp_name = python::extract<std::string>(cnoid::getGlobalNamespace()["createEditComp"](name));
			//comp_name = python::extract<std::string>(cnoid::pythonMainNamespace()["createComp"](name));
#endif
			moduleNameProperty = name;
		}
		catch (const py::error_already_set&e)
		{
#ifdef CNOID_USE_PYBIND11
			MessageView::instance()->putln(0,
				format(_("%1%")) % e.what());
#else
			PyErr_Print();
#endif
		}
		catch (...)
		{

		}




	}
}

/**
 * @brief RTCの状態取得
 * @param status RTCプロファイル
 */
void RTCEditorItem::get_status(RTC_XML::RTC_ProfileRTP::RTC_State& status)
{
	if (comp_name.empty())
	{
		return;
	}



	{
		PyGILock lock;
		//MessageView::instance()->putln(0, _("test1"));
		try
		{

#ifdef CNOID_USE_PYBIND11
			std::string status_str = pybind11::str(getGlobalNamespace()["getStatus"](comp_name.c_str(), 0)).cast<std::string>();
#else
			std::string status_str = python::extract<std::string>(cnoid::getGlobalNamespace()["getStatus"](name.c_str()));
			//comp_name = python::extract<std::string>(cnoid::pythonMainNamespace()["createComp"](name.c_str()));
#endif
			if (status_str == "ACTIVATE")
			{
				status = RTC_XML::RTC_ProfileRTP::RTP_Acitve;
			}
			else if (status_str == "INACTIVATE")
			{
				status = RTC_XML::RTC_ProfileRTP::RTP_InActive;
			}
			else if (status_str == "ERROR")
			{
				status = RTC_XML::RTC_ProfileRTP::RTP_Error;
			}
			else
			{
				status = RTC_XML::RTC_ProfileRTP::RTP_Created;
			}

		}
		catch (const py::error_already_set&e)
		{
#ifdef CNOID_USE_PYBIND11
			MessageView::instance()->putln(0,
				format(_("%1%")) % e.what());
#else
			PyErr_Print();
#endif
		}
		catch (...)
		{

		}




	}
}


/**
 * @brief プロパティ設定
 * @param putProperty プロパティ 
 */
void RTCEditorItem::doPutProperties(cnoid::PutPropertyFunction& putProperty)
{
}

/**
 * @brief 複製する
 * @return 複製オブジェクト
 */
cnoid::Item* RTCEditorItem::doDuplicate() const
{
	return new RTCEditorItem(*this);
}

/**
 * @brief 保存する
 * @param archive 
 */
bool RTCEditorItem::store(cnoid::Archive& archive)
{
	return true;
}

/**
 * @brief 復元する
 * @param archive 
 */
bool RTCEditorItem::restore(const cnoid::Archive& archive)
{
	return true;
}

/**
 * @brief 初期化時実行関数
 * @param ext 
 */
bool RTCEditorItem::initialize(cnoid::ControllerItemIO* io)
{
	return true;
}

/**
 * @brief 
 */
void RTCEditorItem::onPositionChanged()
{

}