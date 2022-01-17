/*!
 * @file  DataPortTable.cpp
 * @brief データポート一覧表示クラス
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



#include "DataPortTable.h"
#include "gettext.h"

namespace rtmiddleware {
	/**
	 * @brief コンストラクタ
	 */
	DataPortTable::DataPortTable()
		: QTableWidget(5, 3)
	{
		QStringList horzHeaders;
		horzHeaders << _("Name")
			<< _("Variable Name(Data)")
			<< _("Variable Name(Port)");
		setHorizontalHeaderLabels(horzHeaders);
		setSelectionMode(QAbstractItemView::NoSelection);

	}

	/**
	 * @brief リスト更新
	 * @param ports データポート一覧
	 */
	void DataPortTable::list_update(QVector<RTC_XML::DataPorts> ports)
	{
		setRowCount(ports.size());
		int num = 0;
		for (QVector<RTC_XML::DataPorts>::iterator itr = ports.begin(); itr != ports.end(); itr++)
		{
			if ((*itr).get_portType() == "DataOutPort" || (*itr).get_portType() == "DataInPort")
			{
				QString data_variable = "self." + (*itr).get_data_name();
				QString port_variable = "self." + (*itr).get_port_name();
				setItem(num, 0, new QTableWidgetItem((*itr).get_name()));
				setItem(num, 1, new QTableWidgetItem(data_variable));
				setItem(num, 2, new QTableWidgetItem(port_variable));

				num += 1;
			}
		}
	}
}