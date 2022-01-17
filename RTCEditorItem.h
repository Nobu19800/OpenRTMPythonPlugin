/*!
 * @file  RTCEditorItem.h
 * @brief RTCEditorアイテム
 *
 */

#ifndef RTCEDITORITEM_H
#define RTCEDITORITEM_H

#include <cnoid/Item>
#include <cnoid/ItemManager>
#include <cnoid/CorbaUtil>
#include <cnoid/ControllerItem>



#include <cnoid/OpenRTMPlugin>
#include <mutex>



#include "PyRTCItem.h"
#include "RTC_MainWindow.h"
#include "RTC_XML.h"

#include "exportdecl.h"










namespace rtmiddleware {
	
	/**
	 * @class RTCEditorItem
	 * @brief RTCEditorアイテム
	 */
	class CNOID_EXPORT RTCEditorItem : public PyRTCItemBase
	{
		
	public:
		/**
		 * @brief コンストラクタ
		 */
		RTCEditorItem();
		/**
		 * @brief コピーコンストラクタ
		 * @param org コピー元
		 */
		RTCEditorItem(const RTCEditorItem& org);
		/**
		 * @brief デストラクタ
		 */
		virtual ~RTCEditorItem();
		/**
		 * @brief 初期化関数
		 * @param ext 
		 */
		static void initialize(cnoid::ExtensionManager* ext);
		/**
		 * @brief RTCダイアグラム上の選択アイテム変更時実行関数
		 * @param item RTCダイアグラム上で選択中のRTC
		 */
		void onItemSelectionChanged(cnoid::RTSComp* item);
		/**
		 * @brief RTC生成
		 * @param name RTC名
		 */
		void createEditComp(const char* name);
		/**
		 * @brief RTCのファイル更新
		 * @param filename Pythonファイルのパス
		 */
		void update_comp(const char *filename);
		/**
		 * @brief RTCのアクティブ化
		 */
		void activate_comp();
		/**
		 * @brief RTCの非アクティブ化
		 */
		void deactivate_comp();
		/**
		 * @brief RTCのリセット
		 */
		void reset_comp();
		/**
		 * @brief RTCの状態取得
		 * @param status RTCプロファイル
		 */
		void get_status(RTC_XML::RTC_ProfileRTP::RTC_State& status);
		/**
		 * @brief データポート追加
		 * @param port データポートプロファイル
		 */
		void add_dataport(RTC_XML::DataPorts port);
		/**
		* @brief ウインドウ表示
		*/
		void showWindows();
		/**
		* @brief ビュー追加時実行関数
		* @param item RTCダイアグラム上で選択中のRTC
		*/
		void onVeiwAdded(cnoid::View* view);

	private:
		cnoid::Connection selectionChangedConnection;
		cnoid::Connection viewAddConnection;
		RTC_MainWindow *mwin;
		std::mutex m_mutex;
	
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
		 * @brief 初期化時実行関数
		 * @param ext 
		 */
		virtual bool initialize(cnoid::ControllerIO* io) override;
		/**
		 * @brief 
		 */
		virtual void onPositionChanged();


	};

};


#endif //RTCEDITORITEM_H