/*!
 * @file  addDataPortTab.cpp
 * @brief データポート設定タブ
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

#include <iostream>



#include "addDataPortTab.h"
#include "CreateDataObject.h"

#include "gettext.h"


/**
 * @brief コンストラクタ
 * @param comp コンポーネントプロファイルオブジェクト
 * @param viewWidget RTC表示ウィジェット
 * @param listWidget データポート一覧表示ウィジェット
 * @param parent 親ウィジェット
 */
addDataPortTab::addDataPortTab(RTC_XML::RTC_ProfileRTP *comp, RTCViewWidget *viewWidget, DataPortTable *listWidget, QWidget *parent)
	: BaseTab(parent)
{
	_comp = comp;

	_viewWidget = viewWidget;
	_listWidget = listWidget;

	QList<QString> key_list = dataTypeList.keys();
	key_list.sort();

	QVector<QString> key_vec = QVector<QString>::fromList(key_list);
	
	
	
	
	_portNameTextbox  = addTextBox("portNameTextbox", _("Port Name"), QVector<QString>(), "port");
	_portTypeCombox = addCombox("portTypeCombox", _("Port Type"), QVector<QString>(), QVector<QString>({ "DataOutPort", "DataInPort" }), "DataOutPort");
	_dataTypeCombox = addCombox("dataTypeCombox ", _("Data Type"), QVector<QString>(), key_vec, "RTC::TimedLong");

	_createButton = new QPushButton(_("Create"));
	QObject::connect(_createButton, SIGNAL(clicked()),this, SLOT(createButtonSlot()));

	subLayouts.back()->addWidget(_createButton);
	mainLayout->addStretch();
	

}



/**
 * @brief データポート検索
 * @param name ポート名
 * @param ret データポートプロファイルオブジェクト
 * @param return true：指定ポート名のデータポートが存在した false:存在しなかった
 */
bool addDataPortTab::searchPort(QString name, RTC_XML::DataPorts &ret)
{
	QVector<RTC_XML::DataPorts> ports = _comp->get_dataports();
	for (QVector<RTC_XML::DataPorts>::iterator itr = ports.begin(); itr != ports.end(); itr++)
	{
		if ((*itr).get_name() == name)
		{
			ret = (*itr);
			return true;
		}
	}
	return false;
}

/**
 * @brief データポート追加
 * @param profile データポートプロファイルオブジェクト
 */
void addDataPortTab::addPort(RTC_XML::DataPorts profile)
{

	if (_comp != NULL)
	{
		
		if (!searchPort(profile.get_name(), profile))
		{
			
			_comp->addDataPort(profile);
			_viewWidget->getRenderRTC()->addDataPort(profile);
			_listWidget->list_update(_comp->get_dataports());

			sigAddPort(profile);
		}
		
	}
}


/**
 * @brief 生成ボタン押下時のスロット
 */
void addDataPortTab::createButtonSlot()
{
	RTC_XML::DataPorts profile;
	QString name = _portNameTextbox.getText();
	name = name.replace(" ", "");
	name = name.replace("\t", "");
	if (name.isEmpty())
	{
		QMessageBox::question(this, _("Creation Faild"), _("Please Input Name"), QMessageBox::Ok);
		return;
	}
	profile.set_name(name);
	profile.set_portType(_portTypeCombox.getItemText());
	profile.set_type(_dataTypeCombox.getItemText());

	addPort(profile);
}