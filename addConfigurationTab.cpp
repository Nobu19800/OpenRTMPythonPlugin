

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



#include "addConfigurationTab.h"

#include "gettext.h"



/**
 * @brief コンストラクタ
 * @param comp コンポーネントプロファイルオブジェクト
 * @param viewWidget RTC表示ウィジェット
 * @param listWidget コンフィグレーションパラメータ一覧表示ウィジェット
 * @param parent 親ウィジェット
 */
addConfigurationTab::addConfigurationTab(RTC_XML::RTC_ProfileRTP *comp, RTCViewWidget *viewWidget, ConfigurationTable *listWidget, QWidget *parent)
	: ConfigParamWidgetBase(parent)
{
	_comp = comp;
	_viewWidget = viewWidget;
	_listWidget = listWidget;

	QVector<QString> type_list({ "short","long", "double", "float", "string" });
	QVector<QString> widget_list({ "text","slider","spin","radio","checkbox","ordered_list" });
	_paramNameTextbox = addTextBox("paramNameTextbox", _("Parameter Name"), QVector<QString>(), "param");

	_paramTypeCombox = addCombox("paramTypeCombox", _("Parameter Type"), QVector<QString>(), type_list, "string");
	_paramDefaultTextbox = addTextBox("paramTypeCombox", _("Default Value"), QVector<QString>(), "1");
	_paramConstraintsTextbox = addTextBox("paramConstraintsTextbox", _("Constraints"), QVector<QString>(), "");
	_paramWidgetCombox = addCombox("paramWidgetCombox", _("Widget"), QVector<QString>(), widget_list, "text");
	_paramStepTextbox = addTextBox("paramStepTextbox", _("Step"), QVector<QString>(), "");
	


	_createButton = new QPushButton(_("Create"));
	QObject::connect(_createButton, SIGNAL(clicked()),this, SLOT(createButtonSlot()));

	subLayouts.back()->addWidget(_createButton);
	mainLayout->addStretch();
	

}

/**
 * @brief コンフィギュレーションパラメータ追加
 * @param profile コンフィグレーションパラメータプロファイルオブジェクト
 */
void addConfigurationTab::addConfiguration(RTC_XML::ConfigurationSet profile)
{
	if (_comp != NULL)
	{
		_comp->addConfigurationSet(profile);
		_listWidget->list_update(_comp->get_confsets());


	}
}

/**
 * @brief 作成ボタン押下時のスロット
 */
void addConfigurationTab::createButtonSlot()
{
	RTC_XML::ConfigurationSet profile;

	QString name = _paramNameTextbox.getText();
	name = name.replace(" ", "");
	name = name.replace("\t", "");
	if (name.isEmpty())
	{
		QMessageBox::question(this, _("Creation Faild"), _("Please Input Name"), QMessageBox::Ok);
		return;
	}
	profile.set_name(name);
	profile.set_type(_paramTypeCombox.getItemText());


	QString default_val = _paramDefaultTextbox.getText();
	default_val = default_val.replace(" ", "");
	default_val = default_val.replace("\t", "");
	if (default_val.isEmpty())
	{
		QMessageBox::question(this, _("Creation Faild"), _("Please Input Default Value"), QMessageBox::Ok);
		return;
	}

	profile.set_defaultValue(default_val);

	profile.set_constraint(_paramConstraintsTextbox.getText());
	profile.set_widget(_paramWidgetCombox.getItemText());
	profile.set_step(_paramStepTextbox.getText());

	addConfiguration(profile);
}