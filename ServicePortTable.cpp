/*!
 * @file  ServicePortTable.cpp
 * @brief サービスポート一覧表示クラス
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



#include "ServicePortTable.h"
#include "gettext.h"

namespace rtmiddleware {
	/**
	 * @brief コンストラクタ
	 * @param parent 親ウィジェット
	 */
	ServicePortOperationDialog::ServicePortOperationDialog(QWidget* parent)
	{
		setWindowTitle(_("Function List"));

		_mainLayout = new QVBoxLayout();
		setLayout(_mainLayout);
	}


	/**
	 * @brief コンストラクタ
	 * @param name 表示名
	 */
	ServicePortSettingButton::ServicePortSettingButton(QString name)
		:QPushButton(name),
		_dialog(0)
	{
		QObject::connect(this, SIGNAL(clicked()), this, SLOT(pushSlot()));
	}

	/**
	 * @brief ボタン押下時スロット
	 */
	void ServicePortSettingButton::pushSlot()
	{
		_dialog = new ServicePortOperationDialog();
		_dialog->show();
	}


	/**
	 * @brief コンストラクタ
	 */
	ServicePortTable::ServicePortTable()
		: QTableWidget(5, 3)
	{
		QStringList horzHeaders;
		horzHeaders << _("Name")
			<< _("Variable Name")
			<< _("Function");
		setHorizontalHeaderLabels(horzHeaders);
		setSelectionMode(QAbstractItemView::NoSelection);
	}


	/**
	 * @brief リスト更新
	 * @param ports データポート一覧
	 */
	void ServicePortTable::list_update(QVector<RTC_XML::ServicePorts> ports)
	{
		setRowCount(ports.size());
		int num = 0;

		for (QVector<RTC_XML::ServicePorts>::iterator itr = ports.begin(); itr != ports.end(); itr++)
		{
			setItem(num, 0, new QTableWidgetItem((*itr).get_name()));
			if ((*itr).get_interfaces().size() > 0)
			{
				QString data_variable = "self." + (*itr).get_interfaces()[0].get_data_name();
				setItem(num, 1, new QTableWidgetItem(data_variable));
			}
			num += 1;

		}
	}
}