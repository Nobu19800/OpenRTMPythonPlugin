#include <cnoid/Plugin>
#include <cnoid/MenuManager>
#include <cnoid/MessageView>
#include <boost/bind.hpp>



#include <boost/ref.hpp>

#include <cnoid/PythonExecutor>
#include <cnoid/PyUtil>

#ifdef CNOID_USE_PYBIND11
#include <pybind11/embed.h>
namespace py = pybind11;
#else
#include <boost/python.hpp>
namespace py = boost::python;
#endif


//#include <src/OpenRTMPlugin/RTSNameServerView.h>

namespace cnoid {
# if defined _WIN32 || defined __CYGWIN__
	__declspec(dllimport) python::object getGlobalNamespace();
#else
	python::object getGlobalNamespace();
#endif
}





#include <cnoid/FileUtil>
#include <cnoid/ExecutablePath>

#include "exportdecl.h"
#include "PyRTCItem.h"
#include "RTCEditorItem.h"
#include "ComponentListItem.h"

#include "gettext.h"




using namespace cnoid;
using namespace boost;
using namespace rtmiddleware;


class PyGILock
{
	PyGILState_STATE gstate;
public:
	PyGILock() {
		gstate = PyGILState_Ensure();
	}
	~PyGILock() {
		PyGILState_Release(gstate);
	}
};


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




class CNOID_EXPORT OpenRTMPythonPlugin : public Plugin
{
public:

    OpenRTMPythonPlugin();
	virtual ~OpenRTMPythonPlugin();

    virtual bool initialize();
    virtual bool finalize();


};


OpenRTMPythonPlugin::OpenRTMPythonPlugin() :
Plugin("OpenRTMPython")
{
	require("Body");
	require("Python");
	require("Corba");
	require("OpenRTM");
	PyRTCItem::initialize(this);
	RTCEditorItem::initialize(this);
	ComponentListItem::initialize(this);
	
}

OpenRTMPythonPlugin::~OpenRTMPythonPlugin()
{
	
}

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
			std::string dir = (filesystem::path(executableTopDirectory()) / CNOID_PLUGIN_SUBDIR / "python/cnoid/OpenRTM_Python_plugin.py").generic_string();
#ifdef CNOID_USE_PYBIND11
			obj = py::eval_file
#else
			obj = py::exec_file
#endif
				(
				dir.c_str(),
				getGlobalNamespace()
				//cnoid::pythonMainNamespace()
				);
		}
		catch(const python::error_already_set&e)
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

	{
		PyGILock lock;
		try
		{
			getGlobalNamespace()["runManager"]();
			//cnoid::pythonMainNamespace()["runManager"]();
		}
		catch(const python::error_already_set&e)
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


        return true;
}


bool OpenRTMPythonPlugin::finalize()
{
	{
		PyGILock lock;
		try
		{
			getGlobalNamespace()["shutdownManager"]();
			//pythonMainNamespace()["shutdownManager"]();
		}
		catch(const python::error_already_set&e)
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
	return true;
}

CNOID_IMPLEMENT_PLUGIN_ENTRY(OpenRTMPythonPlugin)
