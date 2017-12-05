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
	ComponentWidget(QString path, QWidget *parent = 0);
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
private Q_SLOTS:
	/**
	 * @brief RTCを別プロセスで起動
	 */
	void run_process();
	/**
	 * @brief RTCをマネージャで起動
	 */
	void run_rtcd();

private:
	QString _path;
	RTC_XML::RTC_Profile _comp;
	RTCViewWidget *_vw;
	QVBoxLayout *_mainLayout;
	QPushButton *_processButton;
	QPushButton *_managerButton;
	QProcess *_process;
};

/**
 * @class ComponentTabWidgwt
 * @brief カテゴリ別RTC表示タブ
 */
class ComponentTabWidgwt : public QWidget
{
	Q_OBJECT
public:
	/**
	 * @brief コンストラクタ
	 */
	ComponentTabWidgwt();
	/**
	 * @brief RTC追加
	 * @param cw RTC表示ウィジェット
	 */
	void addComponent(ComponentWidget *cw);
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
private:
	QVector<ComponentWidget *> _complist;
	QVBoxLayout *_mainLayout;
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
	ComponentList(QWidget *parent = 0);
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
private:
	QMap<QString, ComponentTabWidgwt*> tabList;


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
	ScrollArea(QWidget *parent = 0);
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
private:
	ScrollArea *_area;
	ComponentList *_mwin;
};

#endif // TEXTEDIT_H
