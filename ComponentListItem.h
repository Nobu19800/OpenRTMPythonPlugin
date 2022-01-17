/*!
 * @file  ComponentListItem.h
 * @brief コンポーネントリストアイテム
 *
 */

#ifndef COMPONENTLISTITEM_H
#define COMPONENTLISTITEM_H

#include <cnoid/Item>
#include <cnoid/ItemManager>

#include <cnoid/ControllerItem>


#include <QWidget>
#include <QTableWidget>
#include <QDialog>
#include <QPushButton>
#include <QGroupBox>


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







#include "ComponentList.h"
#include "RTC_XML.h"

#include "exportdecl.h"










namespace rtmiddleware {
	/**
	 * @class ComponentListItem
	 * @brief コンポーネントリストアイテム
	 */
	class CNOID_EXPORT ComponentListItem : public cnoid::ControllerItem
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		ComponentListItem();
		/**
		 * @brief コピーコンストラクタ
		 * @param org コピー元
		 */
		ComponentListItem(const ComponentListItem& org);
		/**
		 * @brief デストラクタ
		 */
		virtual ~ComponentListItem();
		/**
		 * @brief 初期化関数
		 * @param ext 
		 */
		static void initialize(cnoid::ExtensionManager* ext);

		/**
		* @brief シミュレーション開始時実行関数
		* @return
		*/
		virtual bool start();
		/**
		* @brief 刻み幅取得
		* @return 刻み幅
		*/
		virtual double timeStep() const;
		/**
		* @brief シミュレーション更新前実行関数
		*/
		virtual void input();
		/**
		* @brief シミュレーション更新中実行関数
		*/
		virtual bool control();
		/**
		* @brief シミュレーション更新後実行関数
		*/
		virtual void output();
		/**
		* @brief シミュレーション終了時実行関数
		*/
		virtual void stop();

	protected:
		/**
		 * @brief プロパティ設定
		 * @param putProperty プロパティ 
		 */
		virtual void doPutProperties(cnoid::PutPropertyFunction& putProperty);
		/**
		 * @brief 複製する
		 * @return 複製オブジェクト
		 */
		virtual cnoid::Item* doDuplicate() const override;
		/**
		 * @brief 保存する
		 * @param archive 
		 */
		virtual bool store(cnoid::Archive& archive) override;
		/**
		 * @brief 復元する
		 * @param archive 
		 */
		virtual bool restore(const cnoid::Archive& archive) override;
		/**
		 * @brief 
		 */
		virtual void onPositionChanged();
		/**
		* @brief
		*/
		virtual void onDisconnectedFromRoot();

		//ScrollArea *_area;
		//ComponentList *_mwin;
	};

};


#endif // COMPONENTLISTITEM_H