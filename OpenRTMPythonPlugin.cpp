#include <cnoid/Plugin>
#include <cnoid/MenuManager>
#include <cnoid/MessageView>
#include <boost/bind.hpp>

#include <boost/python.hpp>
#include <boost/ref.hpp>

#include <cnoid/PythonExecutor>
#include <cnoid/PyUtil>







#include <cnoid/FileUtil>
#include <cnoid/ExecutablePath>

#include "exportdecl.h"
#include "gettext.h"


#include "PyRTCItem.h"

using namespace cnoid;
using namespace boost;
using namespace rtmiddleware;




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
	/*
	python::class_<Link>("Link")
	;
	
	python::class_<LightPtr>("Light")
	;
	python::class_<Body>("Body",python::init<>())
	.def("link", (Link*(Body:: *)(const std::string&)const)&Body::link, python::return_internal_reference<>())
	;
	*/
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





class CNOID_EXPORT OpenRTMPythonPlugin : public Plugin
{
public:

    OpenRTMPythonPlugin();
	virtual ~OpenRTMPythonPlugin();

    virtual bool initialize();
    virtual bool finalize();


};


OpenRTMPythonPlugin::OpenRTMPythonPlugin() :
Plugin("OpenRTMPythonPlugin")
{
	require("Body");
	require("Python");
	PyRTCItem::initialize(this);
}

OpenRTMPythonPlugin::~OpenRTMPythonPlugin()
{
	
}

bool OpenRTMPythonPlugin::initialize()
{

	if( PyImport_AppendInittab( "CnoidLink" , initCnoidLink ) == -1 )
	{
		return false;
	}


	{
		PyGILock lock;
		python::object obj;
		try
		{
			std::string dir = (filesystem::path(executableTopDirectory()) / CNOID_PLUGIN_SUBDIR / "python/cnoid/OpenRTM_Python_plugin.py").generic_string();
			
			obj = python::exec_file
				(
				dir.c_str(),
				 cnoid::pythonMainNamespace()
				);
		}
		catch(const python::error_already_set&)
		{
				PyErr_Print();
		}
		catch (...)
		{
		
		}
	}

	{
		PyGILock lock;
		try
		{
			cnoid::pythonMainNamespace()["runManager"]();
		}
		catch(const python::error_already_set&)
		{
			PyErr_Print();
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
			pythonMainNamespace()["shutdownManager"]();
		}
		catch(const python::error_already_set&)
		{
			PyErr_Print();
		}
		catch (...)
		{
		
		}
	}
	return true;
}

CNOID_IMPLEMENT_PLUGIN_ENTRY(OpenRTMPythonPlugin)
