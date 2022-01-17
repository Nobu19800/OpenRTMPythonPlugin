/*!
 * @file  PyRTCItem.cpp
 * @brief PyRTCアイテム
 *
 */

#include <cnoid/MenuManager>
#include <cnoid/MessageView>

#include <cnoid/PythonExecutor>
#include <cnoid/PyUtil>
#include "cnoid/PythonPlugin"

#include <cnoid/Item>
#include <cnoid/ItemManager>


#include <cnoid/BodyItem>
#include <cnoid/ControllerItem>
#include <cnoid/Body>
#include <cnoid/Light>
#include <cnoid/Archive>
#include <cnoid/stdx/filesystem>
#include <fmt/format.h>


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

#include <pybind11/embed.h>
namespace py = pybind11;


#include "PyRTCItem.h"
#include "gettext.h"

using namespace cnoid;


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




namespace rtmiddleware {

	/**
	 * @brief コンストラクタ
	 */
	PyRTCItemBase::PyRTCItemBase() :
		relativePathBaseType(N_RELATIVE_PATH_BASE_TYPES, CNOID_GETTEXT_DOMAIN_NAME),
		execContextType(N_EXEC_CONTEXT_TYPES, CNOID_GETTEXT_DOMAIN_NAME)
	{
		body_item = NULL;
	}

	/**
	 * @brief コンストラクタ
	 */
	PyRTCItem::PyRTCItem()
	{



		relativePathBaseType.setSymbol(RTC_DIRECTORY, N_("RTC directory"));
		relativePathBaseType.setSymbol(PROJECT_DIRECTORY, N_("Project directory"));
		relativePathBaseType.select(RTC_DIRECTORY);

		execContextType.setSymbol(PERIODIC_EXECUTION_CONTEXT, N_("PeriodicExecutionContext"));
		execContextType.setSymbol(CHOREONOID_EXECUTION_CONTEXT, N_("SimulatorExecutionContext"));
		execContextType.select(CHOREONOID_EXECUTION_CONTEXT);

	};

	/**
	 * @brief コピーコンストラクタ
	 * @param org コピー元
	 */
	PyRTCItem::PyRTCItem(const PyRTCItem& org)
	{
		setName(org.name());
		relativePathBaseType = org.relativePathBaseType;
		moduleNameProperty = org.moduleNameProperty;
		execContextType = org.execContextType;
	};

	/**
	 * @brief デストラクタ
	 */
	PyRTCItem::~PyRTCItem()
	{
	}



	/**
	 * @brief 初期化関数
	 * @param ext
	 */
	void PyRTCItem::initialize(ExtensionManager* ext)
	{
		static bool initialized = false;
		if (!initialized) {
			ext->itemManager().registerClass<PyRTCItem>(N_("PyRTCItem"));
			ext->itemManager().addCreationPanel<PyRTCItem>(NULL);
			initialized = true;
		}
	}

	/**
	 * @brief プロパティ設定
	 * @param putProperty プロパティ
	 */
	void PyRTCItem::doPutProperties(PutPropertyFunction& putProperty)
	{
		FilePathProperty pyFileProperty(
			moduleNameProperty,
			{ _("RT-Component module file(*.py)") });

		ControllerItem::doPutProperties(putProperty);
		if (!moduleNameProperty.empty() && checkAbsolute(cnoid::stdx::filesystem::path(moduleNameProperty))) {
			cnoid::stdx::filesystem::path dir = cnoid::stdx::filesystem::path(moduleNameProperty).parent_path().generic_string();
			pyFileProperty.setBaseDirectory(dir.string());
		}
		else if (relativePathBaseType.is(RTC_DIRECTORY)) {
			cnoid::stdx::filesystem::path dir = cnoid::stdx::filesystem::path(executableTopDirectory()) / CNOID_PLUGIN_SUBDIR / "rtc_python";
			pyFileProperty.setBaseDirectory(dir.string());

		}

		putProperty(_("RTC module"), pyFileProperty,
			[&](const std::string& name) { this->createComp(name); return true; });


		putProperty(_("Execution context"), execContextType,
			[&](int which) { this->setExecContextType(which); return true; });


		putProperty(_("Relative path base"), relativePathBaseType,
			[&](int which) { this->setRelativePathBaseType(which); return true; });

	}

	/**
	 * @brief 実行コンテキスト設定
	 * @param which 実行コンテキストID
	 */
	void PyRTCItemBase::setExecContextType(int which)
	{
		if (which != execContextType.which()) {
			execContextType.select(which);
		}
	}


	/**
	 * @brief 相対パス設定
	 * @param which ID
	 */
	void PyRTCItem::setRelativePathBaseType(int which)
	{
		if (which != relativePathBaseType.which()) {
			relativePathBaseType.select(which);
		}
	}

	/**
	 * @brief RTC生成
	 * @param name 名前
	 */
	void PyRTCItem::createComp(std::string name)
	{
		//MessageView::instance()->putln(MessageView::ERROR,
		//	format(_(name.c_str())));
		if (name.empty())
		{
			return;
		}
		{
			PyGILock lock;

			try
			{
				cnoid::PythonPlugin* pythonPlugin = cnoid::PythonPlugin::instance();
				if (pythonPlugin)
				{
					if (!comp_name.empty())
					{
						pythonPlugin->globalNamespace()["exitComp"](comp_name.c_str());
					}
					comp_name = pybind11::str(pythonPlugin->globalNamespace()["createComp"](name.c_str())).cast<std::string>();
					moduleNameProperty = name;
				}
			}
			catch (const py::error_already_set& e)
			{
				MessageView::instance()->putln(MessageView::ERROR,
					fmt::format(_("{}"), e.what()));
			}
			catch (...)
			{

			}

		}
	}

	/**
	 * @brief 複製する
	 * @return 複製オブジェクト
	 */
	Item* PyRTCItem::doDuplicate() const
	{
		return new PyRTCItem(*this);
	}



	/**
	 * @brief 保存する
	 * @param archive
	 */
	bool PyRTCItem::store(Archive& archive)
	{
		archive.writeRelocatablePath("moduleName", moduleNameProperty);
		archive.write("executionContext", execContextType.selectedSymbol(), DOUBLE_QUOTED);

		return ControllerItem::store(archive);
	}



	/**
	 * @brief 復元する
	 * @param archive
	 */
	bool PyRTCItem::restore(const Archive& archive)
	{
		std::string value;
		if (archive.read("moduleName", value)) {
			cnoid::stdx::filesystem::path path(archive.expandPathVariables(value));
			moduleNameProperty = getNativePathString(path);
			if (!moduleNameProperty.empty())createComp(moduleNameProperty);
		}
		std::string symbol;
		if (archive.read("executionContext", symbol)) {
			execContextType.select(symbol);
		}
		return ControllerItem::restore(archive);
	}

	/**
	 * @brief 初期化時実行関数
	 * @param ext
	 */
	bool PyRTCItemBase::initialize(ControllerIO* io)
	{

		{
			PyGILock lock;
			try
			{
				cnoid::PythonPlugin* pythonPlugin = cnoid::PythonPlugin::instance();
				if (pythonPlugin)
				{
					//controlLink *c = &m_crl;
					//cnoid::pythonMainNamespace()["ControlLinkObj"] = boost::ref(c);
					Body* b = io->body();
					pythonPlugin->globalNamespace()["setBody"](b, comp_name.c_str());
				}

			}
			catch (const py::error_already_set& e)
			{
				MessageView::instance()->putln(MessageView::ERROR,
					fmt::format(_("{}"), e.what()));
			}
			catch (...)
			{

			}


		}
		return true;
	}

	/**
	 * @brief
	 */
	void PyRTCItem::onPositionChanged()
	{

	}

	/**
	 * @brief シミュレーション開始時実行関数
	 * @return
	 */
	bool PyRTCItemBase::start()
	{
		if (!comp_name.empty()) {
			PyGILock lock;
			try
			{
				cnoid::PythonPlugin* pythonPlugin = cnoid::PythonPlugin::instance();
				if (pythonPlugin)
				{
					pythonPlugin->globalNamespace()["startSimulation"](comp_name, execContextType.which());
				}

			}
			catch (const py::error_already_set& e)
			{
				MessageView::instance()->putln(MessageView::ERROR,
					fmt::format(_("{}"), e.what()));

			}
			catch (...)
			{

			}




		}
		return true;
	};

	/**
	 * @brief 刻み幅取得
	 * @return 刻み幅
	 */
	double PyRTCItemBase::timeStep() const
	{
		return 0;
	};

	/**
	 * @brief シミュレーション更新前実行関数
	 */
	void PyRTCItemBase::input()
	{
		{
			PyGILock lock;
			try
			{
				cnoid::PythonPlugin* pythonPlugin = cnoid::PythonPlugin::instance();
				if (pythonPlugin)
				{
					pythonPlugin->globalNamespace()["inputFromSimulator"](comp_name);
					//cnoid::pythonMainNamespace()["inputFromSimulator"](comp_name);
				}
			}
			catch (const py::error_already_set& e)
			{
				PyErr_Print();
			}
			catch (...)
			{

			}
		}

	};


	/**
	 * @brief シミュレーション更新中実行関数
	 */
	bool PyRTCItemBase::control()
	{
		if (!comp_name.empty()) {
			PyGILock lock;
			try
			{
				cnoid::PythonPlugin* pythonPlugin = cnoid::PythonPlugin::instance();
				if (pythonPlugin)
				{
					pythonPlugin->globalNamespace()["tickEC"](comp_name, execContextType.which());
				}
			}
			catch (const py::error_already_set& e)
			{
				MessageView::instance()->putln(MessageView::ERROR,
					fmt::format(_("{}"), e.what()));
			}
			catch (...)
			{

			}




		}
		return true;
	};

	/**
	 * @brief シミュレーション更新後実行関数
	 */
	void PyRTCItemBase::output()
	{
		{
			PyGILock lock;
			try
			{
				cnoid::PythonPlugin* pythonPlugin = cnoid::PythonPlugin::instance();
				if (pythonPlugin)
				{
					pythonPlugin->globalNamespace()["outputToSimulator"](comp_name);
					//cnoid::pythonMainNamespace()["outputToSimulator"](comp_name);
				}
			}
			catch (const py::error_already_set& e)
			{
				PyErr_Print();
			}
			catch (...)
			{

			}
		}

	};

	/**
	 * @brief シミュレーション終了時実行関数
	 */
	void PyRTCItemBase::stop()
	{
		if (!comp_name.empty()) {
			PyGILock lock;
			try
			{
				cnoid::PythonPlugin* pythonPlugin = cnoid::PythonPlugin::instance();
				if (pythonPlugin)
				{
					pythonPlugin->globalNamespace()["stopSimulation"](comp_name, execContextType.which());
				}

			}
			catch (const py::error_already_set& e)
			{
				MessageView::instance()->putln(MessageView::ERROR,
					fmt::format(_("{}"), e.what()));
			}
			catch (...)
			{

			}




		}

	};

}