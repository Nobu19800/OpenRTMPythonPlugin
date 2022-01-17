/*!
 * @file  PyRTCItem.h
 * @brief PyRTCアイテム
 *
 */

#ifndef PYRTCITEM_H
#define PYRTCITEM_H

#include <cnoid/Item>
#include <cnoid/ItemManager>


#include <cnoid/BodyItem>
#include <cnoid/ControllerItem>
#include <cnoid/Body>
#include <cnoid/Light>
#include <cnoid/Archive>
#include <cnoid/PutPropertyFunction>





#include "exportdecl.h"





namespace rtmiddleware {

	/**
	 * @class PyRTCItemBase
	 * @brief PyRTCアイテムベースクラス
	 */
	class CNOID_EXPORT PyRTCItemBase : public cnoid::ControllerItem
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		PyRTCItemBase();

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
		/**
		* @brief 実行コンテキスト設定
		* @param which 実行コンテキストID
		*/
		void setExecContextType(int which);

		enum RelativePathBaseType {
			RTC_DIRECTORY,
			PROJECT_DIRECTORY,
			N_RELATIVE_PATH_BASE_TYPES
		};
		enum ExecContextType {
			PERIODIC_EXECUTION_CONTEXT,
			CHOREONOID_EXECUTION_CONTEXT,
			N_EXEC_CONTEXT_TYPES
		};

	protected:
		/**
		 * @brief 初期化時実行関数
		 * @param ext 
		 */
		virtual bool initialize(cnoid::ControllerIO* io) override;
		cnoid::BodyItem* body_item;
		std::string comp_name;

		std::string moduleNameProperty;

		cnoid::Selection relativePathBaseType;
		cnoid::Selection execContextType;
	};
	
	/**
	 * @class PyRTCItem
	 * @brief PyRTCアイテムクラス
	 */
	class CNOID_EXPORT PyRTCItem : public PyRTCItemBase
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		PyRTCItem();
		/**
		 * @brief コピーコンストラクタ
		 * @param org コピー元
		 */
		PyRTCItem(const PyRTCItem& org);
		/**
		 * @brief デストラクタ
		 */
		virtual ~PyRTCItem();
		/**
		 * @brief 初期化関数
		 * @param ext 
		 */
		static void initialize(cnoid::ExtensionManager* ext);

		/**
		 * @brief RTC生成
		 * @param name 名前
		 */
		void createComp(std::string name);
		/**
		 * @brief 相対パス設定
		 * @param which ID
		 */
		void setRelativePathBaseType(int which);

		

		
	private:
		//controlLink m_crl;
		
		
		


#ifdef ENABLE_SIMULATION_PROFILING
		/**
		 * @brief 
		 * @param profilingNames 
		 */
		virtual void getProfilingNames(std::vector<std::string>& profilingNames){};
		/**
		 * @brief 
		 * @param profilingNames 
		 */
		virtual void getProfilingTimes(std::vector<double>& profilingTimes){};
#endif
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
		


	};

};


#endif //PYRTCITEM_H