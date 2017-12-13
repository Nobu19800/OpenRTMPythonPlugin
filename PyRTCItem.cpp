/*!
 * @file  PyRTCItem.cpp
 * @brief PyRTC�A�C�e��
 *
 */

#include <cnoid/MenuManager>
#include <cnoid/MessageView>
#include <boost/bind.hpp>




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

#ifdef CNOID_USE_PYBIND11
#include <pybind11/embed.h>
namespace py = pybind11;
#else
#include <boost/python.hpp>
namespace py = boost::python;
#endif


#include "PyRTCItem.h"
#include "gettext.h"

using namespace cnoid;
using namespace boost;
using namespace rtmiddleware;


/**
 * @class PyGILock
 * @brief Python���s���̃��b�N�I�u�W�F�N�g
 */
class PyGILock
{
	PyGILState_STATE gstate;
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	PyGILock() {
		gstate = PyGILState_Ensure();
	};
	/**
	 * @brief �f�X�g���N�^
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
 * @brief �R���X�g���N�^
 */
PyRTCItemBase::PyRTCItemBase() :
	relativePathBaseType(N_RELATIVE_PATH_BASE_TYPES, CNOID_GETTEXT_DOMAIN_NAME),
	execContextType(N_EXEC_CONTEXT_TYPES, CNOID_GETTEXT_DOMAIN_NAME)
{
	body_item = NULL;
}

/**
 * @brief �R���X�g���N�^
 */
PyRTCItem::PyRTCItem()
{
	


	relativePathBaseType.setSymbol(RTC_DIRECTORY, N_("RTC directory"));
	relativePathBaseType.setSymbol(PROJECT_DIRECTORY, N_("Project directory"));
	relativePathBaseType.select(RTC_DIRECTORY);

	execContextType.setSymbol(PERIODIC_EXECUTION_CONTEXT,  N_("PeriodicExecutionContext"));
	execContextType.setSymbol(CHOREONOID_EXECUTION_CONTEXT,  N_("ChoreonoidExecutionContext"));
	execContextType.select(CHOREONOID_EXECUTION_CONTEXT);

};

/**
 * @brief �R�s�[�R���X�g���N�^
 * @param org �R�s�[��
 */
PyRTCItem::PyRTCItem(const PyRTCItem& org)
{
	setName(org.name());
	relativePathBaseType = org.relativePathBaseType;
	moduleNameProperty = org.moduleNameProperty;
	execContextType = org.execContextType;
};

/**
 * @brief �f�X�g���N�^
 */
PyRTCItem::~PyRTCItem()
{
}



/**
 * @brief �������֐�
 * @param ext 
 */
void PyRTCItem::initialize(ExtensionManager* ext)
{
	static bool initialized = false;
	if(!initialized){
		ext->itemManager().registerClass<PyRTCItem>(N_("PyRTCItem"));
		ext->itemManager().addCreationPanel<PyRTCItem>(NULL);
		initialized = true;
	}
}

/**
 * @brief �v���p�e�B�ݒ�
 * @param putProperty �v���p�e�B 
 */
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
	
	
	

	putProperty(_("RTC module"), FilePath(moduleNameProperty, filter, dir),
                [&](const std::string& name){ this->createComp(name);return true; });






	putProperty(_("Execution context"), execContextType,
	[&](int which){ this->setExecContextType(which); return true; });


	putProperty(_("Relative path base"), relativePathBaseType,
                [&](int which){ this->setRelativePathBaseType(which); return true; });

}

/**
 * @brief ���s�R���e�L�X�g�ݒ�
 * @param which ���s�R���e�L�X�gID 
 */
void PyRTCItemBase::setExecContextType(int which)
{
	if(which != execContextType.which()){
        		execContextType.select(which);
    		}
}


/**
 * @brief ���΃p�X�ݒ�
 * @param which ID
 */
void PyRTCItem::setRelativePathBaseType(int which)
{
	if(which != relativePathBaseType.which()){
		relativePathBaseType.select(which);
	}
}

/**
 * @brief RTC����
 * @param name ���O
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
			if(!comp_name.empty())
			{
#ifdef CNOID_USE_PYBIND11
				getGlobalNamespace()["exitComp"](comp_name.c_str());
#else
				python::extract<std::string>(cnoid::getGlobalNamespace()["exitComp"](comp_name.c_str()));
				//python::extract<std::string>(cnoid::pythonMainNamespace()["exitComp"](comp_name.c_str()));
#endif
			}
#ifdef CNOID_USE_PYBIND11
			comp_name = pybind11::str(getGlobalNamespace()["createComp"](name.c_str())).cast<std::string>();
#else
			comp_name = python::extract<std::string>(cnoid::getGlobalNamespace()["createComp"](name.c_str()));
			//comp_name = python::extract<std::string>(cnoid::pythonMainNamespace()["createComp"](name.c_str()));
#endif
			moduleNameProperty = name;
		}
		catch (const py::error_already_set&e)
		{
#ifdef CNOID_USE_PYBIND11
			MessageView::instance()->putln(MessageView::ERROR,
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
 * @brief ��������
 * @return �����I�u�W�F�N�g
 */
Item* PyRTCItem::doDuplicate() const
{
	return new PyRTCItem(*this);
}



/**
 * @brief �ۑ�����
 * @param archive 
 */
bool PyRTCItem::store(Archive& archive)
{
	archive.writeRelocatablePath("moduleName", moduleNameProperty);
	archive.write("executionContext", execContextType.selectedSymbol(), DOUBLE_QUOTED);

	return ControllerItem::store(archive);
}



/**
 * @brief ��������
 * @param archive 
 */
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

/**
 * @brief �����������s�֐�
 * @param ext 
 */
bool PyRTCItemBase::initialize(ControllerItemIO* io)
{
	
	{
		PyGILock lock;
		try
		{
			//controlLink *c = &m_crl;
			//cnoid::pythonMainNamespace()["ControlLinkObj"] = boost::ref(c);
			Body *b = io->body();
#ifdef CNOID_USE_PYBIND11;
			getGlobalNamespace()["setBody"](b, comp_name.c_str());
#else
			python::extract<std::string>(cnoid::getGlobalNamespace()["setBody"](boost::ref(b), comp_name.c_str()));
			//python::extract<std::string>(cnoid::pythonMainNamespace()["setBody"](boost::ref(b), comp_name.c_str()));
#endif
			
		}
		catch (const py::error_already_set&e)
		{
#ifdef CNOID_USE_PYBIND11
			MessageView::instance()->putln(MessageView::ERROR,
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

/**
 * @brief 
 */
void PyRTCItem::onPositionChanged()
{
	
}

/**
 * @brief �V�~�����[�V�����J�n�����s�֐�
 */
bool PyRTCItemBase::start()
{
	if(!comp_name.empty()){
		PyGILock lock;
		try
		{
#ifdef CNOID_USE_PYBIND11
			getGlobalNamespace()["startSimulation"](comp_name, execContextType.which());
#else
			python::extract<std::string>(cnoid::getGlobalNamespace()["startSimulation"](comp_name, execContextType.which()));
			//python::extract<std::string>(cnoid::pythonMainNamespace()["startSimulation"](comp_name,execContextType.which()));
#endif
			
		}
		catch (const py::error_already_set&e)
		{
#ifdef CNOID_USE_PYBIND11
			MessageView::instance()->putln(MessageView::ERROR,
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
};

/**
 * @brief ���ݕ��擾
 * @return ���ݕ�
 */
double PyRTCItemBase::timeStep() const
{
	return 0;
};

/**
 * @brief �V�~�����[�V�����X�V�O���s�֐�
 */
void PyRTCItemBase::input()
{
	{
		PyGILock lock;
		try
		{
			cnoid::getGlobalNamespace()["inputFromSimulator"](comp_name);
			//cnoid::pythonMainNamespace()["inputFromSimulator"](comp_name);
		}
		catch (const py::error_already_set&e)
		{
			PyErr_Print();
		}
		catch (...)
		{
	
		}
	}

};


/**
 * @brief �V�~�����[�V�����X�V�����s�֐�
 */
bool PyRTCItemBase::control()
{
	if(!comp_name.empty()){
		PyGILock lock;
		try
		{
#ifdef CNOID_USE_PYBIND11
			getGlobalNamespace()["tickEC"](comp_name, execContextType.which());
#else
			python::extract<std::string>(cnoid::getGlobalNamespace()["tickEC"](comp_name, execContextType.which()));
			//python::extract<std::string>(cnoid::pythonMainNamespace()["tickEC"](comp_name,execContextType.which()));
#endif
			
		}
		catch (const py::error_already_set&e)
		{
#ifdef CNOID_USE_PYBIND11
			MessageView::instance()->putln(MessageView::ERROR,
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
};

/**
 * @brief �V�~�����[�V�����X�V����s�֐�
 */
void PyRTCItemBase::output()
{
	{
		PyGILock lock;
		try
		{
			cnoid::getGlobalNamespace()["outputToSimulator"](comp_name);
			//cnoid::pythonMainNamespace()["outputToSimulator"](comp_name);
		}
		catch (const py::error_already_set&e)
		{
			PyErr_Print();
		}
		catch (...)
		{
	
		}
	}

};

/**
 * @brief �V�~�����[�V�����I�������s�֐�
 */
void PyRTCItemBase::stop()
{
	if(!comp_name.empty()){
		PyGILock lock;
		try
		{
#ifdef CNOID_USE_PYBIND11
			getGlobalNamespace()["stopSimulation"](comp_name, execContextType.which());
#else
			python::extract<std::string>(cnoid::getGlobalNamespace()["stopSimulation"](comp_name, execContextType.which()));
			//python::extract<std::string>(cnoid::pythonMainNamespace()["stopSimulation"](comp_name,execContextType.which()));
#endif
			
		}
		catch (const py::error_already_set&e)
		{
#ifdef CNOID_USE_PYBIND11
			MessageView::instance()->putln(MessageView::ERROR,
				format(_("%1%")) % e.what());
#else
			PyErr_Print();
#endif
		}
		catch (...)
		{
	
		}


		
		
	}

};
