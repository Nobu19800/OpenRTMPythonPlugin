/*!
 * @file  ComponentList.h
 * @brief RTCランチャー表示クラス
 *
 */

#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <QWidget>
#include <QTableWidget>
#include <QDialog>
#include <QPushButton>
#include <QGroupBox>

#include <cnoid/View>
#include <cnoid/CorbaUtil>

#include <rtm/Manager.h>
#include <rtm/ManagerServant.h>

#include "RTC_XML.h"
#include "RTCViewWidget.h"

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
class QHBoxLayout;
class QScrollArea;
class QGroupBox;
class QProcess;
QT_END_NAMESPACE



namespace rtmiddleware {
	class CPPComponentInfo;
	class PythonComponentInfo;
	/**
	 * @class ComponentWidget
	 * @brief RTC表示ウィジェット
	 */
	class ComponentWidget : public QGroupBox
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param path モジュールパス
		 * @param parent 親ウィジェット
		 */
		ComponentWidget(QString path, QWidget* parent = Q_NULLPTR);
		/**
		 * @brief モジュールパス設定
		 * @param path モジュールパス
		 */
		void setModulePath(QString path);
		/**
		 * @brief カテゴリ取得
		 * @return カテゴリ
		 */
		QString getCategory();
		/**
		* @brief 終了処理
		*/
		void killprocess();
		/**
		* @brief RTCプロファイルオブジェクトの取得
		* @return RTCプロファイルオブジェクト
		*/
		RTC_XML::RTC_Profile get_comp_prof();
		/**
		* @brief 起動しているプロセス数の取得
		* @return 起動しているプロセス数
		*/
		int get_process_count();
		/**
		* @brief マネージャで起動しているコンポーネント数の取得(周期実行コンテキスト)
		* @return コンポーネント数
		*/
		int get_rtcd_periodic_count();
		/**
		* @brief マネージャで起動しているコンポーネント数の取得(シミュレーション用実行コンテキスト)
		* @return コンポーネント数
		*/
		int get_rtcd_sim_count();
		/**
		* @enum
		* @brief 実行コンテキストの種別
		*/
		enum ExecContextType {
			PERIODIC_EXECUTION_CONTEXT,
			CHOREONOID_EXECUTION_CONTEXT,
			N_EXEC_CONTEXT_TYPES
		};

		/**
		* @brief RTCをマネージャで起動
		*/
		void run_rtcd(ExecContextType ec_type = CHOREONOID_EXECUTION_CONTEXT);

		/**
		* @brief シミュレーション開始時実行関数
		* @return
		*/
		void start();
		/**
		* @brief シミュレーション更新前実行関数
		*/
		void input();
		/**
		* @brief シミュレーション更新中実行関数
		*/
		void control();
		/**
		* @brief シミュレーション更新後実行関数
		*/
		void output();
		/**
		* @brief シミュレーション終了時実行関数
		*/
		void stop();
	public Q_SLOTS:
		/**
		 * @brief RTCを別プロセスで起動
		 */
		void run_processSlot();
		/**
		 * @brief RTCをマネージャで起動(周期実行コンテキスト)
		 */
		void run_rtcd_periodicSlot();
		/**
		* @brief RTCをマネージャで起動(シミュレーション用コンテキスト)
		*/
		void run_rtcd_simSlot();



	private:
		QString _path;
		RTC_XML::RTC_Profile _comp;
		RTCViewWidget* _vw;
		QVBoxLayout* _mainLayout;
		QPushButton* _processButton;
		QPushButton* _periodicButton;
		QPushButton* _simButton;
		QVector<QProcess*> _process;
		QVector<CPPComponentInfo> _cpp_modules;
		QVector<PythonComponentInfo> _python_module;
	};


	class CPPComponentInfo
	{
	public:
		CPPComponentInfo(RTC::RTObject_impl* obj = NULL, ComponentWidget::ExecContextType ec = ComponentWidget::ExecContextType::PERIODIC_EXECUTION_CONTEXT);
		CPPComponentInfo(const CPPComponentInfo& obj);
		RTC::RTObject_impl* _obj;
		ComponentWidget::ExecContextType _ec;
	};
	class PythonComponentInfo
	{
	public:
		PythonComponentInfo(std::string name = "", ComponentWidget::ExecContextType ec = ComponentWidget::ExecContextType::PERIODIC_EXECUTION_CONTEXT);
		PythonComponentInfo(const PythonComponentInfo& obj);
		std::string _name;
		ComponentWidget::ExecContextType _ec;
	};

	/**
	 * @class ComponentTabWidget
	 * @brief カテゴリ別RTC表示タブ
	 */
	class ComponentTabWidget : public QWidget
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 */
		ComponentTabWidget();
		/**
		 * @brief RTC追加
		 * @param cw RTC表示ウィジェット
		 */
		void addComponent(ComponentWidget* cw);
		/**
		 * @brief メインレイアウトの伸縮幅設定
		 * @param v 伸縮幅
		 */
		void addStretchMain(int v = 0);
		/**
		 * @brief サブレイアウトの伸縮幅設定
		 * @param v 伸縮幅
		 */
		void addStretchSub(int v = 0);
		/**
		* @brief 終了処理
		*/
		void killprocess();
		/**
		* @brief RTCウィジェット一覧取得
		* @return RTCウィジェット一覧
		*/
		QMap<QString, ComponentWidget*>  getComponents();

	private:
		QMap<QString, ComponentWidget*> _complist;
		QVBoxLayout* _mainLayout;
		QVector<QHBoxLayout*> _subLayouts;
	};

	/**
	 * @class ComponentList
	 * @brief RTCランチャー表示ウィジェット
	 */
	class ComponentList : public QTabWidget
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param parent 親ウィジェット
		 */
		ComponentList(QWidget* parent = Q_NULLPTR);
		/**
		 * @brief RTC追加
		 * @param path モジュールパス
		 */
		void addComponent(QString path);
		/**
		 * @brief モジュール一覧をロード
		 * @param path モジュールリストのパス
		 */
		void load(QString path);
		/**
		* @brief 終了処理
		*/
		void killprocess();
		/**
		* @brief 保存する
		* @param archive
		*/
		void store(cnoid::Archive& archive);
		/**
		* @brief 復元する
		* @param archive
		*/
		void restore(const cnoid::Archive& archive);
		/**
		* @brief 復元する
		* @param archive
		*/
		void restore_process(const cnoid::Archive& archive);
		/**
		* @brief シミュレーション開始時実行関数
		* @return
		*/
		void start();
		/**
		* @brief シミュレーション更新前実行関数
		*/
		void input();
		/**
		* @brief シミュレーション更新中実行関数
		*/
		void control();
		/**
		* @brief シミュレーション更新後実行関数
		*/
		void output();
		/**
		* @brief シミュレーション終了時実行関数
		*/
		void stop();
	private:
		QMap<QString, ComponentTabWidget*> tabList;


	};

	/**
	 * @class ScrollArea
	 * @brief スクロールエリア
	 */
	class ScrollArea : public QScrollArea
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param parent 親ウィジェット
		 */
		ScrollArea(QWidget* parent = Q_NULLPTR);
	private Q_SLOTS:
		/**
		 * @brief スクロール時のスロット
		 * @param v 移動量
		 */
		void valueChanged(int v);
	};


	class ComponentListView : public cnoid::View
	{
		Q_OBJECT
	public:
		/**
		* @brief コンストラクタ
		*/
		ComponentListView();
		/**
		* @brief デストラクタ
		*/
		virtual ~ComponentListView();
		/**
		* @brief 初期化
		* @param ext
		*/
		static void initializeClass(cnoid::ExtensionManager* ext);
		/**
		* @brief インスタンス取得
		* @return インスタンス
		*/
		static ComponentListView* instance();
		/**
		* @brief 終了処理
		*/
		void killprocess();
		/**
		* @brief 保存する
		* @param archive
		*/
		void store(cnoid::Archive& archive);
		/**
		* @brief 復元する
		* @param archive
		*/
		void restore(const cnoid::Archive& archive);
		/**
		* @brief シミュレーション開始時実行関数
		* @return
		*/
		void start();
		/**
		* @brief シミュレーション更新前実行関数
		*/
		void input();
		/**
		* @brief シミュレーション更新中実行関数
		*/
		void control();
		/**
		* @brief シミュレーション更新後実行関数
		*/
		void output();
		/**
		* @brief シミュレーション終了時実行関数
		*/
		void stop();
	private:
		ScrollArea* _area;
		ComponentList* _mwin;
	};
}

#endif // COMPONENTLIST_H
