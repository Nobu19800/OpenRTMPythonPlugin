/*!
 * @file  addServicePortTab.cpp
 * @brief サービスポート設定タブ
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



#include "addServicePortTab.h"
#include "CreateDataObject.h"

#include "gettext.h"


namespace rtmiddleware {
	/**
	 * @brief コンストラクタ
	 * @param comp コンポーネントプロファイルオブジェクト
	 * @param viewWidget RTC表示ウィジェット
	 * @param listWidget サービスポート一覧表示ウィジェット
	 * @param parent 親ウィジェット
	 */
	addServicePortTab::addServicePortTab(RTC_XML::RTC_ProfileRTP* comp, RTCViewWidget* viewWidget, ServicePortTable* listWidget, QWidget* parent)
		: BaseTab(parent)
	{

		_comp = comp;

		_viewWidget = viewWidget;
		_listWidget = listWidget;






		_portNameTextbox = addTextBox("portNameTextbox", _("Port Name"), QVector<QString>(), "port");
		_interfaceNameTextbox = addTextBox("interfaceName", _("Interface Name"), QVector<QString>(), "");
		_dinterfaceDirCombox = addCombox("interfaceDir ", _("Direction"), QVector<QString>(), QVector<QString>({ "Required","Provided" }), "Required");

		_IDLTextbox = addTextBox("interfaceName", _("IDL File"), QVector<QString>(), "IDL");

		_IDLFileButton = new QPushButton(_("Open"));
		QObject::connect(_IDLFileButton, SIGNAL(clicked()), this, SLOT(IDLFileButtonSlot()));
		_IDLTextbox._layout->addWidget(_IDLFileButton);

		_interfaceTypeCombox = addCombox("interfaceType ", _("Interface type"), QVector<QString>(), QVector<QString>(), "");
		_IDLPathTextbox = addTextBox("IDLPath", _("IDL Path"), QVector<QString>(), "");

		_IDLPathButton = new QPushButton(_("Open"));
		QObject::connect(_IDLPathButton, SIGNAL(clicked()), this, SLOT(IDLPathButtonSlot()));
		_IDLPathTextbox._layout->addWidget(_IDLPathButton);




		_createButton = new QPushButton(_("Create"));
		QObject::connect(_createButton, SIGNAL(clicked()), this, SLOT(createButtonSlot()));

		subLayouts.back()->addWidget(_createButton);
		mainLayout->addStretch();


	}

	/**
	 * @brief IDLファイル設定ボタン押下時のスロット
	 */
	void addServicePortTab::IDLFileButtonSlot()
	{
		QString fileName = QFileDialog::getOpenFileName(this,
			_("Open"), "",
			tr("IDL File (*.idl);;All Files (*)"));

		if (fileName.isEmpty())
		{
			return;
		}
		_IDLTextbox.setText(fileName);

	}

	/**
	 * @brief IDLインクルードパス設定ボタン押下時のスロット
	 */
	void addServicePortTab::IDLPathButtonSlot()
	{
		QString dirName = QFileDialog::getExistingDirectory(this, _("Open"));

		if (dirName.isEmpty())
		{
			return;
		}
		_IDLPathTextbox.setText(dirName);

	}


	/**
	 * @brief サービスポート検索
	 * @param name ポート名
	 * @param ret サービスタポートプロファイルオブジェクト
	 * @param return true：指定ポート名のサービスポートが存在した false:存在しなかった
	 */
	bool addServicePortTab::searchPort(QString name, RTC_XML::ServicePorts& ret)
	{
		QVector<RTC_XML::ServicePorts> ports = _comp->get_svcports();
		for (QVector<RTC_XML::ServicePorts>::iterator itr = ports.begin(); itr != ports.end(); itr++)
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
	 * @brief サービスポート追加
	 * @param profile サービスポートプロファイルオブジェクト
	 */
	void addServicePortTab::addPort(RTC_XML::ServicePorts profile)
	{
		if (_comp != NULL)
		{

			if (!searchPort(profile.get_name(), profile))
			{

				_comp->addServicePort(profile);
				_viewWidget->getRenderRTC()->addServicePort(profile);
				_listWidget->list_update(_comp->get_svcports());


			}

		}
	}

	/**
	 * @brief 生成ボタン押下時のスロット
	 */
	void addServicePortTab::createButtonSlot()
	{
		RTC_XML::ServicePorts profile;
		QString name = _portNameTextbox.getText();
		name = name.replace(" ", "");
		name = name.replace("\t", "");
		if (name.isEmpty())
		{
			QMessageBox::question(this, _("Creation Faild"), _("Please Input Name"), QMessageBox::Ok);
			return;
		}
		profile.set_name(name);


		RTC_XML::ServiceInterface svrif;

		QString if_name = _interfaceNameTextbox.getText();
		if_name = if_name.replace(" ", "");
		if_name = if_name.replace("\t", "");
		if (if_name.isEmpty())
		{
			QMessageBox::question(this, _("Creation Faild"), _("Please Input Interface Name"), QMessageBox::Ok);
			return;
		}
		svrif.set_name(if_name);

		svrif.set_direction(_interfaceDirCombox.getItemText());

		QString idl_name = _IDLTextbox.getText();
		idl_name = idl_name.replace(" ", "");
		idl_name = idl_name.replace("\t", "");
		if (idl_name.isEmpty())
		{
			QMessageBox::question(this, _("Creation Faild"), _("Please Input IDL File Name"), QMessageBox::Ok);
			return;
		}
		svrif.set_idlFile(idl_name);

		svrif.set_type(_interfaceTypeCombox.getText());

		svrif.set_path(_IDLPathTextbox.getText());

		profile.addInterface(svrif);

		addPort(profile);
	}
}