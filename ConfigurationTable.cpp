/*!
 * @file  ConfigurationTable.cpp
 * @brief コンフィギュレーションパラメータ一覧表示クラス
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



#include "ConfigurationTable.h"
#include "RTC_MainWindow.h"

#include "gettext.h"


/**
 * @brief コンストラクタ
 * @param parent 親ウィジェット
 */
ConfigParamWidgetBase::ConfigParamWidgetBase(QWidget *parent)
	: BaseTab(parent)
{
	QVector<QString> type_list({ "short","long", "double", "float", "string" });
	QVector<QString> widget_list({ "text","slider","spin","radio","checkbox","ordered_list" });


	_paramNameTextbox = addTextBox("paramNameTextbox", _("Parameter Name"), QVector<QString>(), "param");
	_paramTypeCombox = addCombox("paramTypeCombox", _("Parameter Type"), QVector<QString>(), type_list, "string");
	_paramDefaultTextbox = addTextBox("paramDefaultTextbox", _("Default Value"), QVector<QString>(), "1");
	_paramConstraintsTextbox = addTextBox("paramConstraintsTextbox", _("Constraints"), QVector<QString>(), "");
	
	_paramWidgetCombox = addCombox("paramNameTextbox ", _("Widget"), QVector<QString>(), widget_list, "text");
	_paramStepTextbox = addTextBox("paramStepTextbox", _("Step"), QVector<QString>(), "");

}

/**
 * @brief コンストラクタ
 * @param dialog コンフィグレーションパラメータ編集ダイアログ
 * @param parent 親ウィジェット
 */
ConfigParamWidget::ConfigParamWidget(ConfigParamDialog *dialog, QWidget *parent)
	: ConfigParamWidgetBase(parent)
{
	_dialog = dialog;
}

/**
 * @brief コンストラクタ
 * @param parent 親ウィジェット
 */
ConfigParamDialog::ConfigParamDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(_("Edit Configuration Parameter Dialog"));
	_mainLayout = new QVBoxLayout();
	setLayout(_mainLayout);
	_cfwidget = new ConfigParamWidget(this);
	_mainLayout->addWidget(_cfwidget);
}

/**
 * @brief 削除ボタン押下時のスロット
 */
void ConfigParamDialog::deleteButtonSlot()
{

}

/**
 * @brief コンストラクタ
 * @param name 表示名
 * @param profile コンフィグレーションパラメータプロファイルオブジェクト
 * @param parent 親ウィジェット
 */
ConfigSettingButton::ConfigSettingButton(QString name, RTC_XML::ConfigurationSet profile, RTC_MainWindow *parent)
	: QPushButton(),
	_profile(profile)
{
	_mainwindow = parent;
	QObject::connect(this, SIGNAL(clicked()), this, SLOT(pushSlot()));
}

/**
 * @brief ボタン押下時のスロット
 */
void ConfigSettingButton::pushSlot()
{
	ConfigParamDialog dialog;
	dialog.show();
	dialog.exec();
	if (dialog.result())
	{
		_mainwindow->deleteConfig(_profile.get_name());
	}
}

/**
 * @brief コンストラクタ
 * @param parent 親ウィジェット
 */
ConfigurationTableRTP::ConfigurationTableRTP(RTC_MainWindow *mainwindow, RTC_MainWindow *parent)
	: ConfigurationTable(parent)
{
	_mainwindow = mainwindow;
}

/**
 * @brief コンストラクタ
 * @param parent 親ウィジェット
 */
ConfigurationTable::ConfigurationTable(RTC_MainWindow *parent)
	: QTableWidget(5, 3)
{
	_mainLayout = parent;

	QStringList horzHeaders;
	horzHeaders << _("Name")
		<< _("Variable Name");
	setHorizontalHeaderLabels(horzHeaders);
	setSelectionMode(QAbstractItemView::NoSelection);
}

void ConfigurationTable::list_update(QVector<RTC_XML::ConfigurationSet> confsets)
{
	setRowCount(confsets.size());
	int num = 0;
	for (QVector<RTC_XML::ConfigurationSet>::iterator itr = confsets.begin(); itr != confsets.end(); itr++)
	{

			QString data_variable = "self." + (*itr).get_data_name();
			setItem(num, 0, new QTableWidgetItem((*itr).get_name()));
			setItem(num, 1, new QTableWidgetItem(data_variable));
			
			num += 1;
	}
}

/**
 * @brief リスト更新
 * @param confsets コンフィグレーションパラメータ一覧
 */
void ConfigurationTableRTP::list_update(QVector<RTC_XML::ConfigurationSet> confsets)
{
	setRowCount(confsets.size());
	int num = 0;
	for (QVector<RTC_XML::ConfigurationSet>::iterator itr = confsets.begin(); itr != confsets.end(); itr++)
	{

		QString data_variable = "self." + (*itr).get_data_name();
		setItem(num, 0, new QTableWidgetItem((*itr).get_name()));
		setItem(num, 1, new QTableWidgetItem(data_variable));
		setCellWidget(num, 2, new ConfigSettingButton(_("Setting"), (*itr), _mainwindow));

		num += 1;
	}
}