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



#include "ComponentList.h"
#include "gettext.h"



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
		ComponentTabWidgwt *new_tab = new ComponentTabWidgwt();
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
	for(QMap<QString, ComponentTabWidgwt*>::iterator itr= tabList.begin();itr != tabList.end();itr++)
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

	_process = new QProcess();
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
		name << _comp.get_info().getName() + "Comp.exe";
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
		std::cout << cmd.toStdString() << std::endl;
		if (_process->state() == QProcess::Running)
		{
			_process->kill();
		}
		_process->start(cmd);
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
		name << _comp.get_info().getName() + ".dll";
	}
	else if (_comp.get_language().getKind() == "Python")
	{
		name << _comp.get_info().getName() + ".py";
	}
	QDirIterator it(_path, name, filters, flags);

	while (it.hasNext())
	{
		QString file = it.next();
		//std::cout << file.toStdString() << std::endl;
		return;
	}
	
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
 * @brief コンストラクタ
 */
ComponentTabWidgwt::ComponentTabWidgwt()
{
	_mainLayout = new QVBoxLayout();
	setLayout(_mainLayout);

	
	
	
}

/**
 * @brief RTC追加
 * @param cw RTC表示ウィジェット
 */
void ComponentTabWidgwt::addComponent(ComponentWidget *cw)
{
	
	if (_complist.count()%3==0)
	{
		
		QHBoxLayout *subLayout = new QHBoxLayout();
		_mainLayout->addLayout(subLayout);
		_subLayouts.push_back(subLayout);
		
		
	}
	
	
	_subLayouts.back()->addWidget(cw);
	_complist.push_back(cw);

	if (_complist.count() % 3 == 0)
	{
		
		_subLayouts.back()->addStretch();
	}
	
}

/**
 * @brief メインレイアウトの伸縮幅設定
 * @param v 伸縮幅
 */
void ComponentTabWidgwt::addStretchMain(int v)
{
	_mainLayout->addStretch(v);
}

/**
 * @brief サブレイアウトの伸縮幅設定
 * @param v 伸縮幅
 */
void ComponentTabWidgwt::addStretchSub(int v)
{
	if (!_subLayouts.empty())
	{
		_subLayouts.back()->addStretch(v);
	}
}

/**
 * @brief コンストラクタ
 * @param parent 親ウィジェット
 */
ScrollArea::ScrollArea(QWidget *parent)
	: QScrollArea(parent)
{
	setFixedWidth(1050);
	setFixedHeight(1050);
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