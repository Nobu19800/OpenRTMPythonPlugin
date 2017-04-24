#include <cnoid/MenuManager>
#include <cnoid/MessageView>
#include <boost/bind.hpp>

#include <boost/python.hpp>
#include <boost/ref.hpp>

#include <cnoid/PythonExecutor>
#include <cnoid/PyUtil>
#include <boost/version.hpp>

#include <cnoid/Item>
#include <cnoid/ItemManager>


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


#include "gettext.h"
#include "PyRTCItem.h"

using namespace cnoid;
using namespace boost;
using namespace rtmiddleware;


controlLink::controlLink()
{
}



LinkPtr controlLink::getLink(Body *ioBody, const char* name)
{
	return ioBody->link(name);
}


void controlLink::setJointPosition(LinkPtr *lb, double q)
{
	(*lb)->q() = q;
};
double controlLink::getJointPosition(LinkPtr *lb)
{
	return (*lb)->q();
};
void controlLink::setJointVelocity(LinkPtr *lb, double dq)
{
	
	(*lb)->dq() = dq;
};
double controlLink::getJointVelocity(LinkPtr *lb)
{
	return (*lb)->dq();
};
void controlLink::setJointAcceralation(LinkPtr *lb, double ddq)
{
	(*lb)->ddq() = ddq;
};
double controlLink::getJointAcceralation(LinkPtr *lb)
{
	return (*lb)->ddq();
};
void controlLink::setJointForce(LinkPtr *lb, double u)
{
	(*lb)->u() = u;
};
double controlLink::getJointForce(LinkPtr *lb)
{
	return (*lb)->u();
};
LightPtr controlLink::getLight(Body *ioBody, const char* name)
{
	return ioBody->findDevice<Light>(name);
};
void controlLink::lightOn(LightPtr *lb, bool on)
{
	(*lb)->on(on);
	(*lb)->notifyStateChange();
};












PyRTCItem::PyRTCItem():
relativePathBaseType(N_RELATIVE_PATH_BASE_TYPES, CNOID_GETTEXT_DOMAIN_NAME),
execContextType(N_EXEC_CONTEXT_TYPES, CNOID_GETTEXT_DOMAIN_NAME)
{
	body_item = NULL;


	relativePathBaseType.setSymbol(RTC_DIRECTORY, N_("RTC directory"));
	relativePathBaseType.setSymbol(PROJECT_DIRECTORY, N_("Project directory"));
	relativePathBaseType.select(RTC_DIRECTORY);

	execContextType.setSymbol(PERIODIC_EXECUTION_CONTEXT,  N_("PeriodicExecutionContext"));
	execContextType.setSymbol(CHOREONOID_EXECUTION_CONTEXT,  N_("ChoreonoidExecutionContext"));
	execContextType.select(CHOREONOID_EXECUTION_CONTEXT);

};


PyRTCItem::PyRTCItem(const PyRTCItem& org)
{
	setName(org.name());
	relativePathBaseType = org.relativePathBaseType;
	moduleNameProperty = org.moduleNameProperty;
	execContextType = org.execContextType;
};


PyRTCItem::~PyRTCItem()
{
}




void PyRTCItem::initialize(ExtensionManager* ext)
{
	static bool initialized = false;
	if(!initialized){
		ext->itemManager().registerClass<PyRTCItem>(N_("PyRTCItem"));
		ext->itemManager().addCreationPanel<PyRTCItem>(NULL);
		initialized = true;
	}
}


void PyRTCItem::doPutProperties(PutPropertyFunction& putProperty)
{
	FileDialogFilter filter;
	filter.push_back(std::string("RT-Component module file(*.py)"));
	std::string dir;

	ControllerItem::doPutProperties(putProperty);
	if(!moduleNameProperty.empty() && checkAbsolute(filesystem::path(moduleNameProperty))){
		dir = filesystem::path(moduleNameProperty).parent_path().generic_string();
	} else if(relativePathBaseType.is(RTC_DIRECTORY)) {
		dir = (filesystem::path(executableTopDirectory()) / CNOID_PLUGIN_SUBDIR / "rtc_python").generic_string();
		
	}
	
	
	

	putProperty("RTC module", FilePath(moduleNameProperty, filter, dir),
                [&](const std::string& name){ this->createComp(name);return true; });






	putProperty(_("Execution context"), execContextType,
	[&](int which){ this->setExecContextType(which); return true; });


	putProperty(_("Relative path base"), relativePathBaseType,
                [&](int which){ this->setRelativePathBaseType(which); return true; });

}


void PyRTCItem::setExecContextType(int which)
{
	if(which != execContextType.which()){
        		execContextType.select(which);
    		}
}



void PyRTCItem::setRelativePathBaseType(int which)
{
	if(which != relativePathBaseType.which()){
		relativePathBaseType.select(which);
	}
}


void PyRTCItem::createComp(std::string name)
{
	{
		PyGILock lock;

		try
		{
			if(!comp_name.empty())
			{
				python::extract<std::string>(cnoid::pythonMainNamespace()["exitComp"](comp_name.c_str()));
			}
			comp_name = python::extract<std::string>(cnoid::pythonMainNamespace()["createComp"](name.c_str()));
			moduleNameProperty = name;
		}
		catch(const python::error_already_set&)
		{
			PyErr_Print();
		}
		catch (...)
		{
	
		}


		
		
	}
}


Item* PyRTCItem::doDuplicate() const
{
	return new PyRTCItem(*this);
}




bool PyRTCItem::store(Archive& archive)
{
	archive.writeRelocatablePath("moduleName", moduleNameProperty);
	archive.write("executionContext", execContextType.selectedSymbol(), DOUBLE_QUOTED);

	return ControllerItem::store(archive);
}




bool PyRTCItem::restore(const Archive& archive)
{
	std::string value;
	if(archive.read("moduleName", value)){
        		filesystem::path path(archive.expandPathVariables(value));
        		moduleNameProperty = getNativePathString(path);
		if(!moduleNameProperty.empty())createComp(moduleNameProperty);
    		}
	std::string symbol;
	if(archive.read("executionContext", symbol)){
		execContextType.select(symbol);
	}
    	return ControllerItem::restore(archive);
}


bool PyRTCItem::initialize(ControllerItemIO* io)
{
	
	{
		PyGILock lock;
		try
		{
			controlLink *c = &m_crl;
			cnoid::pythonMainNamespace()["ControlLinkObj"] = boost::ref(c);
			Body *b = io->body();
			python::extract<std::string>(cnoid::pythonMainNamespace()["setBody"](boost::ref(b), comp_name.c_str()));
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


void PyRTCItem::onPositionChanged()
{
	
}


bool PyRTCItem::start()
{
	if(!comp_name.empty()){
		PyGILock lock;
		try
		{
			python::extract<std::string>(cnoid::pythonMainNamespace()["activateComp"](comp_name,execContextType.which()));
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
};


double PyRTCItem::timeStep() const
{
	return 0;
};


void PyRTCItem::input()
{
	{
		PyGILock lock;
		try
		{
			cnoid::pythonMainNamespace()["inputFromSimulator"](comp_name);
		}
		catch(const python::error_already_set&)
		{
			PyErr_Print();
		}
		catch (...)
		{
	
		}
	}

};



bool PyRTCItem::control()
{
	if(!comp_name.empty()){
		PyGILock lock;
		try
		{
			python::extract<std::string>(cnoid::pythonMainNamespace()["tickEC"](comp_name,execContextType.which()));
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
};


void PyRTCItem::output()
{
	{
		PyGILock lock;
		try
		{
			cnoid::pythonMainNamespace()["outputToSimulator"](comp_name);
		}
		catch(const python::error_already_set&)
		{
			PyErr_Print();
		}
		catch (...)
		{
	
		}
	}

};


void PyRTCItem::stop()
{
	if(!comp_name.empty()){
		PyGILock lock;
		try
		{
			python::extract<std::string>(cnoid::pythonMainNamespace()["deactivateComp"](comp_name,execContextType.which()));
		}
		catch(const python::error_already_set&)
		{
			PyErr_Print();
		}
		catch (...)
		{
	
		}


		
		
	}

};
