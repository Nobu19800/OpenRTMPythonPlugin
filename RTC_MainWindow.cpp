

#include "RTC_MainWindow.h"


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
#include <QTextCodec>


#include "Highlighter.h"

#include "gettext.h"


ModuleSettingWidget::ModuleSettingWidget(QWidget *parent)
	: QWidget(parent)
{
	mainLayout = new QHBoxLayout();
	setLayout(mainLayout);




	editLayout = new QHBoxLayout();
	mainLayout->addLayout(editLayout);

	textEdit = new PythonEditor(this);
	editLayout->addWidget(textEdit);

	Highlighter *highlighter = new Highlighter(textEdit->document());
}

RTC_MainWindow::RTC_MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
	
	
    setObjectName("RTC_MainWindow");
    setWindowTitle(_("RTC Editor"));


	_comp = new RTC_XML::RTC_ProfileRTP();
	


	cw = new QWidget(this);
	tab_widget = new QTabWidget(this);

	ml = new QVBoxLayout();

	subLayout = new QHBoxLayout();
	

	tabLayout = new QVBoxLayout();
	subLayout->addLayout(tabLayout);

	ml->addLayout(subLayout);

	tabLayout->addWidget(tab_widget);

	setCentralWidget(cw);
	cw->setLayout(ml);
	//setCentralWidget(textEdit);

	vw = new RTCViewWidgetRTP(_comp, this);
	vw->setFixedWidth(350);

	rtcLayout = new QHBoxLayout();
	subLayout->addLayout(rtcLayout);

	viewLayout = new QVBoxLayout();
	viewLayout->addWidget(vw);

	_controlCompWidget = new ControlCompWidget();
	viewLayout->addWidget(_controlCompWidget);

	rtcLayout->addLayout(viewLayout);


	rtc_tab_widget = new QTabWidget(this);

	rtc_tab_widget->setFixedWidth(350);
	rtcLayout->addWidget(rtc_tab_widget);

	_dataport_widget = new DataPortTable();
	_addDataPortTab = new addDataPortTab(_comp, vw, _dataport_widget, this);
	rtc_tab_widget->addTab(_addDataPortTab, _("DataPort"));
	rtc_tab_widget->addTab(_dataport_widget, _("DataPort Variable Name"));

	_config_widget = new ConfigurationTable(this);
	_addConfigurationTab = new addConfigurationTab(_comp, vw, _config_widget, this);
	rtc_tab_widget->addTab(_addConfigurationTab, _("Configuration Parameter"));
	rtc_tab_widget->addTab(_config_widget, _("Configuration Parameter Variable Name"));



	_serviceport_widget = new ServicePortTable();
	_addServicePortTab = new addServicePortTab(_comp, vw, _serviceport_widget, this);
	rtc_tab_widget->addTab(_addServicePortTab, _("ServicePort"));
	rtc_tab_widget->addTab(_serviceport_widget, _("ServicePort Variable Name"));

	



	//ModuleSettingWidget *msw = new ModuleSettingWidget();
	//rtcLayout->addWidget(msw);
	/**/
	for (int i = 0; i < code_num; i++)
	{
		activities[(ActivityCode)i] = "\n\nreturn RTC.RTC_OK";
		addActivityTab((ActivityCode)i, activities[(ActivityCode)i]);

	}


	global_tab = new ActivityTab("global", "");
	tab_widget->addTab(global_tab, _("Global"));
	
	tab_widget->setCurrentIndex(code_onExecute);

	save_button = new QPushButton(_("Update"));
	tabLayout->addWidget(save_button);
	QObject::connect(save_button, SIGNAL(clicked()), this, SLOT(save_button_slot()));

}


QString RTC_MainWindow::getFileName()
{
	QString filename = "rtc_module.py";
	
	return _tmp_dir.path() + "/" + filename;
}

void RTC_MainWindow::save_button_slot()
{

	//std::cout << tmp_dir.path().toStdString() << std::endl;
	
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QString file_name = getFileName();
	QFile file(file_name);
	
	//std::cout << QDir().mkdir(tmp_dir.path()) << std::endl;

	//std::cout << (_tmp_dir.path() + "/" + filename).toStdString() << std::endl;
	if (!file.open(QIODevice::WriteOnly))
	{
		std::cout << "test" << std::endl;
		return;
	}
	QTextStream stream(&file);
	stream.setCodec(codec);

	stream << "#!/usr/bin/env python\n";
	stream << "# -*- coding: utf-8 -*-\n";
	stream << "import RTC\n";
	stream << "import OpenRTM_aist\n";
	
	{
		QString text = global_tab->getText();

		stream << text;
	}

	for (int i = 0; i < code_num; i++)
	{
		QString s = Activity_toString((ActivityCode)i);
		stream << "def " + s + "(self):" + "\n";
		QString text = tab_list[(ActivityCode)i]->getText();
		if (text.isEmpty())
		{
			text = "return RTC.RTC_OK";
		}
		QStringList split_text = text.split("\n");
		for (QStringList::iterator itr = split_text.begin(); itr < split_text.end(); itr++)
		{
			stream << "\t" << (*itr) << "\n";
		}
		
	}
	file.close();
	//Q_EMIT save_button_signal(file_name);
	sigSaveButton(file_name.toStdString());
	
}




void RTC_MainWindow::addActivityTab(ActivityCode name, QString text)
{
	tab_list[name] = new ActivityTab(name, text);
	QString s = Activity_toString(name);
	
	tab_widget->addTab(tab_list[name], s);
	

}


void RTC_MainWindow::deleteServicePort(QString name)
{
	vw->getRenderRTC()->removePort(name);
	if (_comp != NULL)
	{
		RTC_XML::ServicePorts profile;

		_comp->removeServicePort(name);
		_serviceport_widget->list_update(_comp->get_svcports());
	}
}
void RTC_MainWindow::deleteDataPort(QString name)
{
	vw->getRenderRTC()->removePort(name);
	if (_comp != NULL)
	{
		RTC_XML::DataPorts profile;

		_comp->removeDataPort(name);
		_dataport_widget->list_update(_comp->get_dataports());
	}
}
void RTC_MainWindow::deleteConfig(QString name)
{

	if (_comp != NULL)
	{
		RTC_XML::ConfigurationSet profile;

		_comp->removeConfigurationSet(name);
		_config_widget->list_update(_comp->get_confsets());
	}
}

void RTC_MainWindow::createMenus()
{

}
