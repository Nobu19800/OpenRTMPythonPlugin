/*!
 * @file  ConfigurationTable.h
 * @brief コンフィギュレーションパラメータ一覧表示クラス
 *
 */

#ifndef CONFIGURATIONTABLE_H
#define CONFIGURATIONTABLE_H


#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QDialog>

#include "BaseTab.h"
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
	class ConfigParamDialog;
	class RTC_MainWindow;
	/**
	 * @class ConfigParamWidgetBase
	 * @brief コンフィギュレーションパラメータ設定ウィンドウベースクラス
	 */
	class ConfigParamWidgetBase : public BaseTab
	{
		Q_OBJECT

	public:
		/**
		 * @brief コンストラクタ
		 * @param parent 親ウィジェット
		 */
		ConfigParamWidgetBase(QWidget* parent = Q_NULLPTR);



	private:
		BaseWidget _paramNameTextbox;
		BaseWidget _paramTypeCombox;
		BaseWidget _paramDefaultTextbox;
		BaseWidget _paramConstraintsTextbox;
		BaseWidget _paramWidgetCombox;
		BaseWidget _paramStepTextbox;
		QPushButton* _createButton;

	};


	/**
	 * @class ConfigParamWidget
	 * @brief コンフィギュレーションパラメータ編集ウィジェット
	 */
	class ConfigParamWidget : public ConfigParamWidgetBase
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param dialog コンフィグレーションパラメータ編集ダイアログ
		 * @param parent 親ウィジェット
		 */
		ConfigParamWidget(ConfigParamDialog* dialog, QWidget* parent = Q_NULLPTR);
	private:
		ConfigParamDialog* _dialog;

	};

	/**
	 * @class ConfigParamDialog
	 * @brief コンフィグレーションパラメータ編集ダイアログ
	 */
	class ConfigParamDialog : public QDialog
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param parent 親ウィジェット
		 */
		ConfigParamDialog(QWidget* parent = Q_NULLPTR);
	private Q_SLOTS:
		/**
		 * @brief 削除ボタン押下時のスロット
		 */
		void deleteButtonSlot();
	private:
		QVBoxLayout* _mainLayout;
		ConfigParamWidget* _cfwidget;

	};


	/**
	 * @class ConfigSettingButton
	 * @brief コンフィグレーションパラメータ編集ダイアログ起動ボタン
	 */
	class ConfigSettingButton : public QPushButton
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param name 表示名
		 * @param profile コンフィグレーションパラメータプロファイルオブジェクト
		 * @param parent 親ウィジェット
		 */
		ConfigSettingButton(QString name, RTC_XML::ConfigurationSet profile, RTC_MainWindow* parent = Q_NULLPTR);
	private Q_SLOTS:
		/**
		 * @brief ボタン押下時のスロット
		 */
		void pushSlot();
	private:
		RTC_MainWindow* _mainwindow;
		RTC_XML::ConfigurationSet _profile;

	};


	/**
	 * @class ConfigurationTable
	 * @brief コンフィグレーションパラメータ一覧表示ウィジェット
	 */
	class ConfigurationTable : public QTableWidget
	{
		Q_OBJECT

	public:
		/**
		 * @brief コンストラクタ
		 * @param parent 親ウィジェット
		 */
		ConfigurationTable(RTC_MainWindow* parent = Q_NULLPTR);
		/**
		 * @brief リスト更新
		 * @param confsets コンフィグレーションパラメータ一覧
		 */
		virtual void list_update(QVector<RTC_XML::ConfigurationSet> confsets);
	public Q_SLOTS:
		//    void fileNew();

	protected:





		//    void fileOpen();


	private:
		RTC_MainWindow* _mainLayout;


	};

	/**
	 * @class ConfigurationTableRTP
	 * @brief コンフィグレーションパラメータ一覧表示ウィジェット(動的編集対応)
	 */
	class ConfigurationTableRTP : public ConfigurationTable
	{
		Q_OBJECT

	public:
		/**
		 * @brief コンストラクタ
		 * @param parent 親ウィジェット
		 */
		ConfigurationTableRTP(RTC_MainWindow* mainwindow, RTC_MainWindow* parent = Q_NULLPTR);
		/**
		 * @brief リスト更新
		 * @param confsets コンフィグレーションパラメータ一覧
		 */
		virtual void list_update(QVector<RTC_XML::ConfigurationSet> confsets);
	private:
		RTC_MainWindow* _mainwindow;
	};
}

#endif // CONFIGURATIONTABLE_H
