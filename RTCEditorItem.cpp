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
#include <cnoid/ViewManager>


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

#define NCODE "N_CODE_REPLACE"
#define TCODE "T_CODE_REPLACE"



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
	execContextType.setSymbol(PERIODIC_EXECUTION_CONTEXT, N_("PeriodicExecutionContext"));
	execContextType.setSymbol(CHOREONOID_EXECUTION_CONTEXT, N_("ChoreonoidExecutionContext"));
	execContextType.select(CHOREONOID_EXECUTION_CONTEXT);
};

/**
 * @brief コピーコンストラクタ
 * @param org コピー元
 */
RTCEditorItem::RTCEditorItem(const RTCEditorItem& org)
{
	//MessageView::instance()->putln(0, "test");
	setName(org.name());
	execContextType = org.execContextType;
	
	showWindows();
	
	
};




/**
 * @brief デストラクタ
 */
RTCEditorItem::~RTCEditorItem()
{
}


/**
* @brief ビュー追加時実行関数
* @param item RTCダイアグラム上で選択中のRTC
*/
void RTCEditorItem::onVeiwAdded(cnoid::View* view)
{
	RTSDiagramView* rtsView = RTSDiagramView::instance();



	if (rtsView)
	{
		//std::bind(&RTCEditor::selectChanged, this, _1);
		if (!selectionChangedConnection.connected())
		{
			selectionChangedConnection = rtsView->sigDoubleClickEvent().connect(std::bind(&RTCEditorItem::onItemSelectionChanged, this, std::placeholders::_1));
		}
	}
}

/**
* @brief ウインドウ表示
*/
void RTCEditorItem::showWindows()
{
	if (!viewAddConnection.connected())
	{
		
		viewAddConnection = cnoid::ViewManager::sigViewCreated().connect(std::bind(&RTCEditorItem::onVeiwAdded, this, std::placeholders::_1));
	}

	onVeiwAdded(NULL);

	//if (mwin == NULL)
	{


		callLater([&] {
			m_mutex.lock();
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
			m_mutex.unlock();

		});



		//QObject::connect(mwin, SIGNAL(save_button_signal(QString)), this, SLOT(update(QString)));
	}
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
	putProperty(_("Execution context"), execContextType,
		[&](int which) { this->setExecContextType(which); return true; });
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
	RTC_XML::RTC_ProfileRTP *prof = mwin->getRTCProfile();
	QString name = prof->get_info().getName();

	archive.write("name", prof->get_info().getName().toStdString());
	archive.write("Category", prof->get_info().getCategory().toStdString());

	archive.write("Language", prof->get_language().getKind().toStdString());




	ListingPtr dportListing = new Listing();
	QVector<RTC_XML::DataPorts> dports = prof->get_dataports();

	for (QVector<RTC_XML::DataPorts>::iterator itr = dports.begin(); itr != dports.end(); itr++)
	{
		Mapping *dportMap = dportListing->newMapping();
		dportMap->write("name", (*itr).get_name().toStdString());
		dportMap->write("portType", (*itr).get_portType().toStdString());
		dportMap->write("type", (*itr).get_type().toStdString());

	}


	if (!dportListing->empty())
	{
		archive.insert("DataPorts", dportListing);
	}



	ListingPtr sportListing = new Listing();
	QVector<RTC_XML::ServicePorts> sports = prof->get_svcports();

	for (QVector<RTC_XML::ServicePorts>::iterator itr = sports.begin(); itr != sports.end(); itr++)
	{

		Mapping *sportMap = sportListing->newMapping();
		sportMap->write("name", (*itr).get_name().toStdString());

		QVector<RTC_XML::ServiceInterface> ifs = (*itr).get_interfaces();
		ListingPtr ifisting = new Listing();
		for (QVector<RTC_XML::ServiceInterface>::iterator if_itr = ifs.begin(); if_itr != ifs.end(); if_itr++)
		{
			Mapping *ifMap = ifisting->newMapping();
			ifMap->write("name", (*if_itr).get_name().toStdString());
			ifMap->write("idlFile", (*if_itr).get_idlFile().toStdString());
			ifMap->write("path", (*if_itr).get_path().toStdString());
			ifMap->write("type", (*if_itr).get_type().toStdString());
			ifMap->write("direction", (*if_itr).get_direction().toStdString());
		}
		if (!ifisting->empty())
		{
			sportMap->insert("Interfaces", ifisting);
		}

	}


	if (!sportListing->empty())
	{
		archive.insert("Serviceorts", sportListing);
	}



	ListingPtr configListing = new Listing();
	QVector<RTC_XML::ConfigurationSet> confs = prof->get_confsets();

	for (QVector<RTC_XML::ConfigurationSet>::iterator itr = confs.begin(); itr != confs.end(); itr++)
	{
		Mapping *confMap = configListing->newMapping();
		confMap->write("name", (*itr).get_name().toStdString());
		confMap->write("constraint", (*itr).get_constraint().toStdString());
		confMap->write("type", (*itr).get_type().toStdString());
		confMap->write("defaultValue", (*itr).get_defaultValue().toStdString());
		confMap->write("step", (*itr).get_step().toStdString());
		confMap->write("widget", (*itr).get_widget().toStdString());

	}


	if (!configListing->empty())
	{
		archive.insert("ConfigurationSets", configListing);
	}




	for (int i = 0; i < ActivityCode::code_num; i++)
	{
		QString code = mwin->get_code((ActivityCode)i);
		QString name = Activity_toString((ActivityCode)i);

		code = code.replace("\n", NCODE);
		code = code.replace("\t", TCODE);
		archive.write(name.toStdString(),(const char*)code.toLocal8Bit());
	}

	archive.write("executionContext", execContextType.selectedSymbol(), DOUBLE_QUOTED);
	

	return true;
}

/**
 * @brief 復元する
 * @param archive 
 */
bool RTCEditorItem::restore(const cnoid::Archive& archive)
{
	showWindows();
	
	/*
	for (int i = 0; i < 100; i++)
	{
		if (mwin == NULL)
		{
			coil::sleep(coil::TimeValue(0.1));
			MessageView::instance()->putln(0, "sleep");
		}
		else
		{
			MessageView::instance()->putln(0, "break");
			break;
		}

		if (i == 99)
		{
			MessageView::instance()->putln(0, "retrun");
			return false;
		}
	}
	return true;
	*/

	callLater([&] {
		m_mutex.lock();
		std::string name;
		std::string category;
		std::string kind;

		archive.read("name", name);
		archive.read("Category", category);
		archive.read("Language", kind);

		const Listing& dportListing = *archive.findListing("DataPorts");
		if (dportListing.isValid()) {
			for (int i = 0; i < dportListing.size(); i++) {
				const Mapping& dportMap = *dportListing[i].toMapping();

				RTC_XML::DataPorts dport;
				std::string dport_name;
				std::string dport_portType;
				std::string dport_type;

				dportMap.read("name", dport_name);
				dportMap.read("portType", dport_portType);
				dportMap.read("type", dport_type);

				dport.set_name(QString::fromStdString(dport_name));
				dport.set_portType(QString::fromStdString(dport_portType));
				dport.set_type(QString::fromStdString(dport_type));

				mwin->_addDataPortTab->addPort(dport);

			}
		}



		const Listing& sportListing = *archive.findListing("Serviceorts");
		if (sportListing.isValid()) {
			for (int i = 0; i < sportListing.size(); i++) {
				const Mapping& sportMap = *sportListing[i].toMapping();

				RTC_XML::ServicePorts sport;
				std::string sport_name;


				sportMap.read("name", sport_name);
				sport.set_name(QString::fromStdString(sport_name));

				const Listing& ifListing = *sportMap.findListing("Interfaces");
				if (ifListing.isValid()) {
					for (int j = 0; j < ifListing.size(); j++) {
						const Mapping& ifMap = *ifListing[j].toMapping();
						RTC_XML::ServiceInterface intf;
						std::string if_name;
						std::string if_idlFile;
						std::string if_path;
						std::string if_type;
						std::string if_direction;

						ifMap.read("name", if_name);
						ifMap.read("idlFile", if_idlFile);
						ifMap.read("path", if_path);
						ifMap.read("type", if_type);
						ifMap.read("direction", if_direction);

						intf.set_name(QString::fromStdString(if_name));
						intf.set_idlFile(QString::fromStdString(if_idlFile));
						intf.set_path(QString::fromStdString(if_path));
						intf.set_type(QString::fromStdString(if_type));
						intf.set_direction(QString::fromStdString(if_direction));

						sport.addInterface(intf);

					}
				}



				mwin->_addServicePortTab->addPort(sport);
			}
		}


		const Listing& confListing = *archive.findListing("ConfigurationSets");
		if (confListing.isValid()) {
			for (int i = 0; i < confListing.size(); i++) {
				const Mapping& confMap = *confListing[i].toMapping();

				RTC_XML::ConfigurationSet conf;
				std::string conf_name;
				std::string conf_constraint;
				std::string conf_type;
				std::string conf_defaultValue;
				std::string conf_step;
				std::string conf_widget;


				confMap.read("name", conf_name);
				confMap.read("constraint", conf_constraint);
				confMap.read("type", conf_type);
				confMap.read("defaultValue", conf_defaultValue);
				confMap.read("step", conf_step);
				confMap.read("widget", conf_widget);


				conf.set_name(QString::fromStdString(conf_name));
				conf.set_constraint(QString::fromStdString(conf_constraint));
				conf.set_type(QString::fromStdString(conf_type));
				conf.set_defaultValue(QString::fromStdString(conf_defaultValue));
				conf.set_step(QString::fromStdString(conf_step));
				conf.set_widget(QString::fromStdString(conf_widget));


				mwin->_addConfigurationTab->addConfiguration(conf);
			}
		}


		
		

		for (int i = 0; i < ActivityCode::code_num; i++)
		{
			std::string code;
			QString code_name = Activity_toString((ActivityCode)i);

			archive.read(code_name.toStdString(), code);
			QString code_ = QString::fromStdString(code);
			code_ = code_.replace(NCODE, "\n");
			code_ = code_.replace(TCODE,"\t");
			mwin->set_code((ActivityCode)i, code_);
		}

		std::string symbol;
		if (archive.read("executionContext", symbol)) {
			execContextType.select(symbol);
		}

		mwin->save_button_slot();
		
	});

	m_mutex.unlock();


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