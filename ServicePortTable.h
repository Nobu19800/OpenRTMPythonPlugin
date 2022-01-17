/*!
 * @file  ServicePortTable.h
 * @brief サービスポート一覧表示クラス
 *
 */

#ifndef SERVICEPORTTABLE_H
#define SERVICEPORTTABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QDialog>
#include <QPushButton>

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
	 * @class ServicePortOperationDialog
	 * @brief サービスポート設定ダイアログ
	 */
	class ServicePortOperationDialog : public QDialog
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param parent 親ウィジェット
		 */
		ServicePortOperationDialog(QWidget* parent = Q_NULLPTR);
	private:
		QVBoxLayout* _mainLayout;

	};


	/**
	 * @class ServicePortSettingButton
	 * @brief サービスポート設定ボタン
	 */
	class ServicePortSettingButton : QPushButton
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param name 表示名
		 */
		ServicePortSettingButton(QString name);
	protected Q_SLOTS:
		/**
		 * @brief ボタン押下時スロット
		 */
		void pushSlot();
	private:
		ServicePortOperationDialog* _dialog;
	};

	/**
	 * @class ServicePortTable
	 * @brief サービスポート一覧表示ウィジェット
	 */
	class ServicePortTable : public QTableWidget
	{
		Q_OBJECT

	public:
		/**
		 * @brief コンストラクタ
		 */
		ServicePortTable();
		/**
		 * @brief リスト更新
		 * @param ports データポート一覧
		 */
		void list_update(QVector<RTC_XML::ServicePorts> ports);

		//    void fileNew();

	protected:



	private Q_SLOTS:

		//    void fileOpen();


	private:



	};
}

#endif // SERVICEPORTTABLE_H
