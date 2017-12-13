/*!
 * @file  ComponentList.cpp
 * @brief RTCランチャー表示クラス
 *
 */

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


#include <cnoid/ViewManager>
#include <cnoid/FileUtil>

#include <cnoid/ExecutablePath>

#include <cnoid/MessageView>


#include <cnoid/PythonExecutor>
#include <cnoid/PyUtil>

#ifdef CNOID_USE_PYBIND11
#include <pybind11/embed.h>
namespace py = pybind11;
#else
#include <boost/python.hpp>
namespace py = boost::python;
#endif


#include <rtm/RTObject.h>





#include "ComponentList.h"
#include "gettext.h"


using namespace cnoid;
using namespace boost;


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
 * @param parent 親ウィジェット
 */
ComponentList::ComponentList(QWidget *parent)
	: QTabWidget(parent)
{
	setWindowTitle(QTextCodec::codecForLocale()->toUnicode("RTC List"));
	


	

	//load("C:\\Program Files\\OpenRTM-aist\\1.2.0\\utils\\SettingRTSystem\\Components");

	
}


/**
 * @brief RTC追加
 * @param path モジュールパス
 */
void ComponentList::addComponent(QString path)
{
	//std::cout << path.toStdString() << std::endl;
	ComponentWidget *comp = new ComponentWidget(path);
	
	QString category = comp->getCategory();
	if (tabList.keys().indexOf(category) < 0)
	{
		ComponentTabWidget *new_tab = new ComponentTabWidget();
		tabList[category] = new_tab;
		addTab(new_tab, category);
		new_tab->addComponent(comp);
	}
	else
	{
		tabList[category]->addComponent(comp);
	}
	



}


/**
 * @brief モジュール一覧をロード
 * @param path モジュールリストのパス
 */
void ComponentList::load(QString path)
{
	
	QDir::Filters filters = QDir::Dirs;
	QDirIterator::IteratorFlags flags = QDirIterator::NoIteratorFlags;
	QStringList name;
	QDirIterator it(path, name, filters, flags);

	while (it.hasNext())
	{
		QString file = it.next();
		//std::cout << file.toStdString() << std::endl;
		file = file.replace("\\", "/");
		QStringList file_path =  file.split("/");
		//file_path.back();
		//std::cout << file_path.back().toStdString() << std::endl;
		if (file_path.back() != ".." && file_path.back() != ".")
		{
			addComponent(file);
		}
		
	}
	for(QMap<QString, ComponentTabWidget*>::iterator itr= tabList.begin();itr != tabList.end();itr++)
	{
		(*itr)->addStretchMain();
		(*itr)->addStretchSub();
	}
	
}




/**
 * @brief コンストラクタ
 * @param path モジュールパス
 * @param parent 親ウィジェット
 */
ComponentWidget::ComponentWidget(QString path, QWidget *parent)
	: QGroupBox(parent)
{
	_mainLayout = new QVBoxLayout();
	setLayout(_mainLayout);
	setModulePath(path);
	
	setFixedWidth(350);
	setFixedHeight(350);

	
}

/**
 * @brief モジュールパス設定
 * @param path モジュールパス
 */
void ComponentWidget::setModulePath(QString path)
{
	_path = path;
	QDir::Filters filters = QDir::Files;
	QDirIterator::IteratorFlags flags = QDirIterator::NoIteratorFlags;
	QStringList name;
	name << "RTC.xml";
	QDirIterator it(path, name, filters, flags);

	while (it.hasNext())
	{
		QString file = it.next();
		//std::cout << file.toStdString() << std::endl;
		_comp.loadXML(file);
		_vw = new RTCViewWidget(&_comp, this);

		_mainLayout->addWidget(_vw);
		_vw->setFixedHeight(250);
		_vw->setFixedWidth(330);
		this->setTitle(_comp.get_info().getName());

		_processButton = new QPushButton(_("run(new Process)"));
		QObject::connect(_processButton, SIGNAL(clicked()), this, SLOT(run_process()));
		_mainLayout->addWidget(_processButton);
		_managerButton = new QPushButton(_("run(rtcd)"));
		QObject::connect(_managerButton, SIGNAL(clicked()), this, SLOT(run_rtcd()));
		_mainLayout->addWidget(_managerButton);

		_mainLayout->addStretch();
		return;
	}
	
}



/**
 * @brief RTCを別プロセスで起動
 */
void ComponentWidget::run_process()
{
	QDir::Filters filters = QDir::Files;
	QDirIterator::IteratorFlags flags = QDirIterator::Subdirectories;
	QStringList name;
	QString cmd;
	if (_comp.get_language().getKind() == "C++")
	{
#ifdef Q_OS_WIN32
		name << _comp.get_info().getName() + "Comp.exe";
#else
		name << _comp.get_info().getName() + "Comp";
#endif
	}
	else if (_comp.get_language().getKind() == "Python")
	{
		name << _comp.get_info().getName() + ".py";
		cmd = "python ";
	}
	QDirIterator it(_path, name, filters, flags);

	while (it.hasNext())
	{
		QString file = it.next();
		//std::cout << file.toStdString() << std::endl;
		cmd = cmd + "\"" + file + "\"";
		//std::cout << cmd.toStdString() << std::endl;
		
		QProcess *p = new QProcess();
		/*if (_process->state() == QProcess::Running)
		{
			_process->kill();
		}*/
		p->start(cmd);
		_process.push_back(p);
		cnoid::MessageView::instance()->putln(0, boost::format(_("Generate %1%")) % _comp.get_info().getName().toStdString());
		return;
	}


}

/**
 * @brief RTCをマネージャで起動
 */
void ComponentWidget::run_rtcd()
{
	QDir::Filters filters = QDir::Files;
	QDirIterator::IteratorFlags flags = QDirIterator::Subdirectories;
	QStringList name;
	if (_comp.get_language().getKind() == "C++")
	{
#ifdef Q_OS_WIN32
		name << _comp.get_info().getName() + ".dll";
#else
		name << _comp.get_info().getName() + ".so";
#endif
	}
	else if (_comp.get_language().getKind() == "Python")
	{
		name << _comp.get_info().getName() + ".py";
	}
	QDirIterator it(_path, name, filters, flags);

	while (it.hasNext())
	{
		QString file = it.next();
		//cnoid::MessageView::instance()->putln(0, boost::format(_("%1%"))% _comp.get_language().getKind().toStdString());
		if (_comp.get_language().getKind() == "C++")
		{
			RTC::Manager *mgr = &RTC::Manager::instance();
			if (mgr)
			{
				QFileInfo f(file);
				QString mod_name = f.completeBaseName();
				QString init_func = mod_name + "Init";
#ifdef Q_OS_WIN32
				file = file.replace("/", "\\");
#endif
				RTC::ReturnCode_t ret = mgr->load(file.toStdString(), init_func.toStdString());
				if (ret == RTC::RTC_OK)
				{
					RTC::RTObject_impl *rto = mgr->createComponent(mod_name.toLocal8Bit());
					//std::cout << file.toStdString() << std::endl;
					if (rto)
					{
						cnoid::MessageView::instance()->putln(0, boost::format(_("Generate %1%")) % _comp.get_info().getName().toStdString());
						_cpp_modules.push_back(rto);
					}
					else
					{
						cnoid::MessageView::instance()->putln(0, boost::format(_("Failed Generate %1%")) % _comp.get_info().getName().toStdString());
						//cnoid::MessageView::instance()->putln(0, boost::format(_("%1%")) % (int)ret);
					}
				}
				else
				{
					cnoid::MessageView::instance()->putln(0, boost::format(_("Failed Generate %1%")) % _comp.get_info().getName().toStdString());
					//cnoid::MessageView::instance()->putln(0, boost::format(_("%1%")) % (int)ret);
					//cnoid::MessageView::instance()->putln(0, boost::format(_("%1%")) % file.toStdString());
					//cnoid::MessageView::instance()->putln(0, boost::format(_("%1%")) % mod_name.toStdString());
					//cnoid::MessageView::instance()->putln(0, boost::format(_("%1%")) % init_func.toStdString());
				}
			}
			else
			{
				cnoid::MessageView::instance()->putln(0, boost::format(_("not running %1% Manager"))% _comp.get_language().getKind().toStdString());
			}
		}
		else if (_comp.get_language().getKind() == "Python")
		{
			
			{
				PyGILock lock;
				
				try
				{
					
#ifdef CNOID_USE_PYBIND11
					std::string comp_name = pybind11::str(getGlobalNamespace()["createCompList"]((const char*)file.toLocal8Bit())).cast<std::string>();
					
#else
					comp_name = python::extract<std::string>(cnoid::getGlobalNamespace()["createCompList"]((const char*)file.toLocal8Bit()));
#endif
					_python_module.push_back(comp_name);
					cnoid::MessageView::instance()->putln(0, boost::format(_("Generate %1%")) % _comp.get_info().getName().toStdString());

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
					cnoid::MessageView::instance()->putln(0, boost::format(_("Failed Generate %1%")) % _comp.get_info().getName().toStdString());


				}




			}
		}
		else
		{
			cnoid::MessageView::instance()->putln(0, boost::format(_("not supported %1%")) % _comp.get_language().getKind().toStdString());
		}
		return;
	}

}


/**
* @brief 終了処理
*/
void ComponentWidget::killprocess()
{

	
	for (QVector<QProcess *>::iterator itr = _process.begin(); itr != _process.end(); itr++)
	{
		if ((*itr)->state() == QProcess::Running)
		{
			(*itr)->kill();
		}
	}
	for (QVector<RTC::RTObject_impl *>::iterator itr = _cpp_modules.begin(); itr != _cpp_modules.end(); itr++)
	{
		(*itr)->exit();
	}
	for (QVector<std::string>::iterator itr = _python_module.begin(); itr != _python_module.end(); itr++)
	{
		{
			PyGILock lock;

			try
			{

#ifdef CNOID_USE_PYBIND11
				getGlobalNamespace()["exitComp"]((*itr).c_str());

#else
				cnoid::getGlobalNamespace()["exitComp"](name);
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

	
	
	_process.clear();
	_cpp_modules.clear();
	_python_module.clear();
}

/**
 * @brief カテゴリ取得
 * @return カテゴリ
 */
QString ComponentWidget::getCategory()
{
	return _comp.get_info().getCategory();
}


/**
* @brief 起動しているプロセス数の取得
* @return 起動しているプロセス数
*/
int ComponentWidget::get_process_count()
{
	return _process.size();
}

/**
* @brief マネージャで起動しているコンポーネント数の取得
* @return コンポーネント数
*/
int ComponentWidget::get_rtcd_count()
{
	return _cpp_modules.size() + _python_module.size();
}


/**
* @brief RTCプロファイルオブジェクトの取得
* @return RTCプロファイルオブジェクト
*/
RTC_XML::RTC_Profile ComponentWidget::get_comp_prof()
{
	return _comp;
}


/**
 * @brief コンストラクタ
 */
ComponentTabWidget::ComponentTabWidget()
{
	_mainLayout = new QVBoxLayout();
	setLayout(_mainLayout);




}

/**
 * @brief RTC追加
 * @param cw RTC表示ウィジェット
 */
void ComponentTabWidget::addComponent(ComponentWidget *cw)
{

	if (_complist.count() % 3 == 0)
	{

		QHBoxLayout *subLayout = new QHBoxLayout();
		_mainLayout->addLayout(subLayout);
		_subLayouts.push_back(subLayout);


	}


	_subLayouts.back()->addWidget(cw);
	_complist[cw->get_comp_prof().get_info().getName()] = cw;
	

	if (_complist.count() % 3 == 0)
	{

		_subLayouts.back()->addStretch();
	}

}

/**
 * @brief メインレイアウトの伸縮幅設定
 * @param v 伸縮幅
 */
void ComponentTabWidget::addStretchMain(int v)
{
	_mainLayout->addStretch(v);
}

/**
 * @brief サブレイアウトの伸縮幅設定
 * @param v 伸縮幅
 */
void ComponentTabWidget::addStretchSub(int v)
{
	if (!_subLayouts.empty())
	{
		_subLayouts.back()->addStretch(v);
	}
}


/**
* @brief 終了処理
*/
void ComponentTabWidget::killprocess()
{
	for(QMap<QString, ComponentWidget *>::iterator itr = _complist.begin(); itr != _complist.end(); itr++)
	{
		(*itr)->killprocess();
	}
}

/**
* @brief RTCウィジェット一覧取得
* @return RTCウィジェット一覧
*/
QMap<QString, ComponentWidget *>  ComponentTabWidget::getComponents()
{
	return _complist;
}

/**
* @brief 終了処理
*/
void ComponentList::killprocess()
{
	for (QMap<QString, ComponentTabWidget*>::iterator itr = tabList.begin(); itr != tabList.end(); itr++)
	{
		(*itr)->killprocess();
	}
}


/**
* @brief 保存する
* @param archive
*/
void ComponentList::store(cnoid::Archive& archive)
{
	ListingPtr tabListing = new Listing();
	for (QMap<QString, ComponentTabWidget *>::iterator tab_itr = tabList.begin(); tab_itr != tabList.end(); tab_itr++)
	{
	
		ComponentTabWidget *ctw = tab_itr.value();
		
		Mapping* tabMap = tabListing->newMapping();
		tabMap->write("name", tab_itr.key().toStdString());
		QMap<QString, ComponentWidget *> comps = ctw->getComponents();
		ListingPtr compListing = new Listing();
		for (QMap<QString, ComponentWidget *>::iterator comp_itr = comps.begin(); comp_itr != comps.end(); comp_itr++)
		{
			
			Mapping* compMap = compListing->newMapping();
			compMap->write("name", comp_itr.key().toStdString());
			compMap->write("process", comp_itr.value()->get_process_count());
			compMap->write("rtcd", comp_itr.value()->get_rtcd_count());

			

			
		}
		if (!compListing->empty())
		{
			tabMap->insert("RTCs", compListing);
		}
		
	}
	if (!tabListing->empty())
	{
		archive.insert("Tab", tabListing);
	}

}

/**
* @brief 復元する
* @param archive
*/
void ComponentList::restore(const cnoid::Archive& archive)
{
	archive.addPostProcess(
		std::bind(&ComponentList::restore_process, this, std::ref(archive)));
}

/**
* @brief 復元する
* @param archive
*/
void ComponentList::restore_process(const cnoid::Archive& archive)
{
	const Listing& tabListing = *archive.findListing("Tab");
	if (tabListing.isValid()) {
		for (int i = 0; i < tabListing.size(); i++) {
			const Mapping& tabMap = *tabListing[i].toMapping();
			std::string name;
			tabMap.read("name", name);

			const Listing& compListing = *tabMap.findListing("RTCs");
			if (compListing.isValid()) {
				for (int j = 0; j < compListing.size(); j++) {
					const Mapping& compMap = *compListing[j].toMapping();
					std::string comp_name;
					int process_count = 0;
					int rtcd_count = 0;
					compMap.read("name", comp_name);
					compMap.read("process", process_count);
					compMap.read("rtcd", rtcd_count);

					QString tname = QString::fromStdString(name);
					
					if (tabList.keys().indexOf(tname) >= 0)
					{
						QMap<QString, ComponentWidget *> comps = tabList[tname]->getComponents();
						QString cname = QString::fromStdString(comp_name);

						if (comps.keys().indexOf(cname) >= 0)
						{
							for (int k = 0; k < process_count; k++)
							{
								comps[cname]->run_process();
							}
							
							for (int k = 0; k < rtcd_count; k++)
							{
								comps[cname]->run_rtcd();
							}
						}
					}
				}
			}

		}
	}
}


/**
 * @brief コンストラクタ
 * @param parent 親ウィジェット
 */
ScrollArea::ScrollArea(QWidget *parent)
	: QScrollArea(parent)
{
	//setFixedWidth(1050);
	//setFixedHeight(1050);
	QScrollBar *bar = verticalScrollBar();
	QObject::connect(bar, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
}

/**
 * @brief スクロール時のスロット
 * @param v 移動量
 */
void ScrollArea::valueChanged(int v)
{
	widget()->update();
}


/**
* @brief コンストラクタ
*/
ComponentListView::ComponentListView()
{
	_area = new ScrollArea();
	_mwin = new ComponentList();

	std::string dir = (boost::filesystem::path(cnoid::executableTopDirectory()) / CNOID_SHARE_SUBDIR / "rtc").generic_string();
	_mwin->load(dir.c_str());
	_area->setWidget(_mwin);

	QHBoxLayout *mainLayout = new QHBoxLayout();
	mainLayout->addWidget(_area);
	this->setLayout(mainLayout);
}


/**
* @brief デストラクタ
*/
ComponentListView::~ComponentListView()
{
	killprocess();
}

/**
* @brief 初期化
* @param ext
*/
void ComponentListView::initializeClass(cnoid::ExtensionManager* ext)
{
	ext->viewManager().registerClass<ComponentListView>(
		"ComponentListView", N_("Component List"), cnoid::ViewManager::SINGLE_OPTIONAL);
}

/**
* @brief インスタンス取得
* @return インスタンス
*/
ComponentListView* ComponentListView::instance()
{
	return cnoid::ViewManager::findView<ComponentListView>();
}


/**
* @brief 終了処理
*/
void ComponentListView::killprocess()
{
	_mwin->killprocess();
}

/**
* @brief 保存する
* @param archive
*/
void ComponentListView::store(cnoid::Archive& archive)
{
	_mwin->store(archive);
}
/**
* @brief 復元する
* @param archive
*/
void ComponentListView::restore(const cnoid::Archive& archive)
{
	_mwin->restore(archive);
}