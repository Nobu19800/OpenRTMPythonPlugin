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
	.def("getLink", &controlLink::getLink)
	.def("setJointPosition", &controlLink::setJointPosition, python::return_internal_reference<>())
	.def("getJointPosition", &controlLink::getJointPosition)
	.def("setJointVelocity", &controlLink::setJointVelocity, python::return_internal_reference<>())
	.def("getJointVelocity", &controlLink::getJointVelocity)
	.def("setJointAcceralation", &controlLink::setJointAcceralation, python::return_internal_reference<>())
	.def("getJointAcceralation", &controlLink::getJointAcceralation)
	.def("setJointForce", &controlLink::setJointForce, python::return_internal_reference<>())
	.def("getJointForce", &controlLink::getJointForce)
	.def("getLight", &controlLink::getLight)
	.def("lightOn", &controlLink::lightOn)
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
