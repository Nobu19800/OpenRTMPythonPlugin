/*!
 * @file  OpenRTMPythonPlugin.cpp
 * @brief OpenRTM連携プラグインPython版
 *
 */

#include <cnoid/Plugin>
#include <cnoid/MenuManager>
#include <cnoid/MessageView>

#include <fmt/format.h>

#include <cnoid/PyUtil>
#include "cnoid/PythonPlugin"

#include <pybind11/embed.h>
namespace py = pybind11;


//#include <src/OpenRTMPlugin/RTSNameServerView.h>







#include <cnoid/FileUtil>
#include <cnoid/ExecutablePath>
#include <cnoid/stdx/filesystem>

#include "exportdecl.h"
#include "PyRTCItem.h"
#include "RTCEditorItem.h"
#include "ComponentListItem.h"
#include "ComponentList.h"

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

	/*
	class controlLink
	{
	public:

		controlLink(){};

		static LinkPtr getLink(Body *ioBody, const char* name)
		{
			return ioBody->link(name);
		}


		static void setJointPosition(LinkPtr *lb, double q)
		{
			(*lb)->q() = q;
		};
		static double getJointPosition(LinkPtr *lb)
		{
			return (*lb)->q();
		};
		static void setJointVelocity(LinkPtr *lb, double dq)
		{

			(*lb)->dq() = dq;
		};
		static double getJointVelocity(LinkPtr *lb)
		{
			return (*lb)->dq();
		};
		static void setJointAcceralation(LinkPtr *lb, double ddq)
		{
			(*lb)->ddq() = ddq;
		};
		static double getJointAcceralation(LinkPtr *lb)
		{
			return (*lb)->ddq();
		};
		static void setJointForce(LinkPtr *lb, double u)
		{
			(*lb)->u() = u;
		};
		static double getJointForce(LinkPtr *lb)
		{
			return (*lb)->u();
		};
		static LightPtr getLight(Body *ioBody, const char* name)
		{
			return ioBody->findDevice<Light>(name);
		};
		static void lightOn(LightPtr *lb, bool on)
		{
			(*lb)->on(on);
			(*lb)->notifyStateChange();
		};


	};


	BOOST_PYTHON_MODULE(CnoidLink)
	{
		python::class_<Body>("Body", python::init<>())
		;
		python::class_<LinkPtr>("Link")
		;
		python::class_<LightPtr>("Light")
		;

		python::class_<controlLink>("controlLink")
		.def("getLink", &controlLink::getLink).staticmethod("getLink")
		.def("setJointPosition", &controlLink::setJointPosition, python::return_internal_reference<>()).staticmethod("setJointPosition")
		.def("getJointPosition", &controlLink::getJointPosition).staticmethod("getJointPosition")
		.def("setJointVelocity", &controlLink::setJointVelocity, python::return_internal_reference<>()).staticmethod("setJointVelocity")
		.def("getJointVelocity", &controlLink::getJointVelocity).staticmethod("getJointVelocity")
		.def("setJointAcceralation", &controlLink::setJointAcceralation, python::return_internal_reference<>()).staticmethod("setJointAcceralation")
		.def("getJointAcceralation", &controlLink::getJointAcceralation).staticmethod("getJointAcceralation")
		.def("setJointForce", &controlLink::setJointForce, python::return_internal_reference<>()).staticmethod("setJointForce")
		.def("getJointForce", &controlLink::getJointForce).staticmethod("getJointForce")
		.def("getLight", &controlLink::getLight).staticmethod("getLight")
		.def("lightOn", &controlLink::lightOn).staticmethod("lightOn")
		;

	}
	*/



	/**
	 * @class OpenRTMPythonPlugin
	 * @brief OpenRTM連携プラグインPython版
	 */
	class CNOID_EXPORT OpenRTMPythonPlugin : public Plugin
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		OpenRTMPythonPlugin();
		/**
		 * @brief デストラクタ
		 */
		virtual ~OpenRTMPythonPlugin();
		/**
		 * @brief 初期化関数
		 * @return true:成功 false:失敗
		 */
		virtual bool initialize();
		/**
		 * @brief 終了関数
		 * @return true:成功 false:失敗
		 */
		virtual bool finalize();


	};

	/**
	 * @brief コンストラクタ
	 */
	OpenRTMPythonPlugin::OpenRTMPythonPlugin() :
		Plugin("OpenRTMPython")
	{
		require("Body");
		require("Python");
		require("Corba");
		require("OpenRTM");



	}

	/**
	 * @brief デストラクタ
	 */
	OpenRTMPythonPlugin::~OpenRTMPythonPlugin()
	{

	}

	/**
	 * @brief 初期化関数
	 * @return true:成功 false:失敗
	 */
	bool OpenRTMPythonPlugin::initialize()
	{
		//itemManager().registerClass<PyRTCItem>(N_("PyRTCItem"));
		//itemManager().addCreationPanel<PyRTCItem>();
		/*
		if( PyImport_AppendInittab( "CnoidLink" , initCnoidLink ) == -1 )
		{
			return false;
		}

		*/

		{
			PyGILock lock;
			python::object obj;
			try
			{
				cnoid::PythonPlugin* pythonPlugin = cnoid::PythonPlugin::instance();
				if (pythonPlugin)
				{
					std::string dir = (cnoid::stdx::filesystem::path(executableTopDirectory()) / CNOID_PLUGIN_SUBDIR / "python/cnoid/OpenRTM_Python_plugin.py").generic_string();

					obj = py::eval_file
					(
						dir.c_str(),
						pythonPlugin->globalNamespace()
						//cnoid::pythonMainNamespace()
					);
				}
			}
			catch (const python::error_already_set& e)
			{
				MessageView::instance()->putln(0,
					fmt::format(_("{}"), e.what()));
			}
			catch (...)
			{

			}
		}

		{
			PyGILock lock;
			try
			{
				cnoid::PythonPlugin* pythonPlugin = cnoid::PythonPlugin::instance();
				if (pythonPlugin)
				{
					pythonPlugin->globalNamespace()["runManager"]();
					//cnoid::pythonMainNamespace()["runManager"]();
				}
			}
			catch (const python::error_already_set& e)
			{
				MessageView::instance()->putln(0,
					fmt::format(_("{}"), e.what()));
			}
			catch (...)
			{

			}
		}
		PyRTCItem::initialize(this);
		RTCEditorItem::initialize(this);
		ComponentListItem::initialize(this);

		ComponentListView::initializeClass(this);

		return true;
	}

	/**
	 * @brief 終了関数
	 * @return true:成功 false:失敗
	 */
	bool OpenRTMPythonPlugin::finalize()
	{
		{
			PyGILock lock;
			try
			{
				cnoid::PythonPlugin* pythonPlugin = cnoid::PythonPlugin::instance();
				if (pythonPlugin)
				{
					pythonPlugin->globalNamespace()["shutdownManager"]();
					//pythonMainNamespace()["shutdownManager"]();
				}
			}
			catch (const python::error_already_set& e)
			{
				MessageView::instance()->putln(0,
					fmt::format(_("{}"), e.what()));
			}
			catch (...)
			{

			}
		}
		return true;
	}
}

CNOID_IMPLEMENT_PLUGIN_ENTRY(rtmiddleware::OpenRTMPythonPlugin)
