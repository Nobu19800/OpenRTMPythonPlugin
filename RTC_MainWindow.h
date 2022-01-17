/*!
 * @file  RTC_MainWindow.h
 * @brief RTCEditorメインウィンドウクラス
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTemporaryDir>
#include <cnoid/Signal>
#include "PythonEditor.h"
#include "RTCViewWidget.h"
#include "addDataPortTab.h"
#include "addServicePortTab.h"
#include "addConfigurationTab.h"
#include "ActivityTab.h"
#include "ActivityCode.h"
#include "ControlCompWidget.h"


QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
class QPrinter;
class QHBoxLayout;
class QVBoxLayout;
class QTemporaryDir;
QT_END_NAMESPACE

class ToolBar;
QT_FORWARD_DECLARE_CLASS(QMenu)


namespace rtmiddleware {
	/**
	 * @class ModuleSettingWidget
	 * @brief
	 */
	class ModuleSettingWidget : public QWidget
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param parent 親ウィジェット
		 */
		ModuleSettingWidget(QWidget* parent = Q_NULLPTR);
	private:
		PythonEditor* textEdit;
		QHBoxLayout* mainLayout;
		QHBoxLayout* editLayout;
	};


	/**
	 * @class RTC_MainWindow
	 * @brief RTCEditorメインウィンドウクラス
	 */
	class RTC_MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		/**
		 * @brief コンストラクタ
		 * @param parent 親ウィジェット
		 * @param flags
		 */
		explicit RTC_MainWindow(QWidget* parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
		/**
		 * @brief アクティビティ編集タブ追加
		 * @param name 名前
		 * @param text テキスト
		 */
		void addActivityTab(ActivityCode name, QString text);
		/**
		 * @brief サービスポート削除
		 * @param name サービスポート名
		 */
		void deleteServicePort(QString name);
		/**
		 * @brief データポート削除
		 * @param name データポート名
		 */
		void deleteDataPort(QString name);
		/**
		 * @brief コンフィグレーションパラメータ削除
		 * @param name コンフィグレーションパラメータ名
		 */
		void deleteConfig(QString name);
		/**
		 * @brief メニュー作成
		 */
		void createMenus();
		/**
		 * @brief 編集中のPythonファイルパス取得
		 * @return Pythonファイルのパス
		 */
		QString getFileName();
		/**
		* @brief RTCプロファイルオブジェクト取得
		* @return RTCプロファイルオブジェクト
		*/
		RTC_XML::RTC_ProfileRTP* getRTCProfile();
		/**
		* @brief 実装コード取得
		* @param id コールバックのID
		* @return 実装コード文字列
		*/
		QString get_code(ActivityCode id);
		/**
		* @brief 実装コード設定
		* @param id コールバックのID
		* @param code 実装コード文字列
		*/
		void set_code(ActivityCode id, QString code);
		cnoid::Signal<void(const char*)>  sigSaveButton;

	public Q_SLOTS:
		/**
		 * @brief 保存ボタン押下時のスロット
		 */
		void save_button_slot();
		//public Q_SIGNAL:
		//	void save_button_signal(QString filename);

	public:
		QMap<ActivityCode, ActivityTab*> tab_list;
		QWidget* cw;
		QVBoxLayout* ml;
		QHBoxLayout* subLayout;
		QVBoxLayout* tabLayout;
		QTabWidget* tab_widget;
		QHBoxLayout* rtcLayout;
		RTCViewWidgetRTP* vw;
		QVBoxLayout* viewLayout;
		QTabWidget* rtc_tab_widget;
		addDataPortTab* _addDataPortTab;
		DataPortTable* _dataport_widget;
		addServicePortTab* _addServicePortTab;
		ServicePortTable* _serviceport_widget;
		addConfigurationTab* _addConfigurationTab;
		ConfigurationTable* _config_widget;
		QMap<ActivityCode, QString> activities;
		ControlCompWidget* _controlCompWidget;
		QPushButton* save_button;
		ActivityTab* global_tab;
		RTC_XML::RTC_ProfileRTP* _comp;
		QTemporaryDir _tmp_dir;
		/*
		QMenu *fileMenu;
		QMenu *exportMenu;
		QMenu *editMenu;
		QMenu *fontMenu;
		QMenu *optionMenu;
		QMenu *execMenu;
		QMenu *helpMenu;
		QAction *newAct;
		QAction *openAct;
		QAction *saveAct;
		QAction *saveAsAct;
		*/
	};
}

#endif // MAINWINDOW_H
