/*!
 * @file  DataPortTable.h
 * @brief データポート一覧表示クラス
 *
 */


#ifndef DATAPORTTABLE_H
#define DATAPORTTABLE_H


#include <QWidget>
#include <QTableWidget>

#include "RTC_XML.h"




QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
class QPrinter;
class QLayout;
class QLabel;
class QVBoxLayout;
QT_END_NAMESPACE




namespace rtmiddleware {
	/**
	 * @class DataPortTable
	 * @brief データポート一覧表示ウィジェット
	 */
	class DataPortTable : public QTableWidget
	{
		Q_OBJECT

	public:
		/**
		 * @brief コンストラクタ
		 */
		DataPortTable();
		/**
		 * @brief リスト更新
		 * @param ports データポート一覧
		 */
		void list_update(QVector<RTC_XML::DataPorts> ports);
	public Q_SLOTS:
		//    void fileNew();

	protected:





		//    void fileOpen();


	private:



	};
}

#endif // DATAPORTTABLE_H
