/*!
 * @file  RTC_XML.h
 * @brief RTCプロファイルオブジェクトクラス
 *
 */

#ifndef RTC_XML_H
#define RTC_XML_H


#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QXmlStreamReader>

#include <iostream>
//#include <QtXml>
#include <map>

#include <mutex>



namespace RTC_XML
{
	/**
	 * @class BasicInfo
	 * @brief 基本プロファイル
	 */
	class BasicInfo
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		BasicInfo();
		/**
		 * @brief コピーコンストラクタ
		 * @param obj コピー元
		 */
		BasicInfo(const BasicInfo &obj);
		/**
		 * @brief デストラクタ
		 */
		~BasicInfo();
		QMap <QString, QString> _properties;
		QMap <QString, QString> _docs;
		/**
		 * @brief XMLファイルからプロファイル取得
		 * @param reader XMLリーダー
		 */
		void getXMLData(QXmlStreamReader &reader);
		/**
		 * @brief カテゴリ名取得
		 * @return カテゴリ名
		 */
		QString getCategory();
		/**
		 * @brief モジュール名取得
		 * @return モジュール名
		 */
		QString getName();

		std::mutex *m_mutex;
	};

	/**
	 * @class RTC_Action
	 * @brief アクティビティプロファイル
	 */
	class RTC_Action
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		RTC_Action();
		/**
		 * @brief コピーコンストラクタ
		 * @param obj コピー元
		 */
		RTC_Action(const RTC_Action &obj);
		/**
		 * @brief デストラクタ
		 */
		~RTC_Action();
		/**
		 * @brief XMLファイルからプロファイル取得
		 * @param reader XMLリーダー
		 */
		void getXMLData(QXmlStreamReader &reader);
		


		QMap <QString, QString> _docs;
		QMap <QString, QString> _properties;

		std::mutex *m_mutex;
	};

	/**
	 * @class ConfigurationSet
	 * @brief コンフィグレーションプロファイル
	 */
	class ConfigurationSet
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		ConfigurationSet();
		/**
		 * @brief コピーコンストラクタ
		 * @param obj コピー元
		 */
		ConfigurationSet(const ConfigurationSet &obj);
		/**
		 * @brief デストラクタ
		 */
		~ConfigurationSet();
		/**
		 * @brief XMLファイルからプロファイル取得
		 * @param reader XMLリーダー
		 */
		void getXMLData(QXmlStreamReader &reader);
		/**
		 * @brief パラメータ名取得
		 * @return パラメータ名
		 */
		QString get_name();
		/**
		 * @brief パラメータ名取得
		 * @param name パラメータ名
		 */
		void set_name(QString name);
		/**
		 * @brief デフォルト値設定
		 * @return デフォルト値
		 */
		QString get_defaultValue();
		/**
		 * @brief デフォルト値設定
		 * @param val デフォルト値
		 */
		void set_defaultValue(QString val);
		/**
		 * @brief データ型取得
		 * @return データ型
		 */
		QString get_type();
		/**
		 * @brief データ型設定
		 * @param type データ型名
		 */
		void set_type(QString type);
		/**
		 * @brief ウィジェット型取得
		 * @return ウィジェット型
		 */
		QString get_widget();
		/**
		 * @brief ウィジェット型設定
		 * @param widget ウィジェット型
		 */
		void set_widget(QString widget);
		/**
		 * @brief 制約式取得
		 * @return 制約式
		 */
		QString get_constraint();
		/**
		 * @brief 制約式設定
		 * @param constraits 制約式
		 */
		void set_constraint(QString constraits);
		/**
		 * @brief ステップ値取得
		 * @return ステップ値
		 */
		QString get_step();
		/**
		 * @brief ステップ値設定
		 * @param step ステップ値
		 */
		void set_step(QString step);
		/**
		 * @brief 変数名取得
		 * @return 変数名
		 */
		QString get_data_name();
		QMap <QString, QString> _properties;
		QMap <QString, QString> _docs;
		QMap <QString, QString> _ext;

		std::mutex *m_mutex;
	};

	/**
	 * @class DataPorts
	 * @brief データポートプロファイル
	 */
	class DataPorts
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		DataPorts();
		/**
		 * @brief コピーコンストラクタ
		 * @param obj コピー元
		 */
		DataPorts(const DataPorts &obj);
		/**
		 * @brief デストラクタ
		 */
		~DataPorts();
		/**
		 * @brief XMLファイルからプロファイル取得
		 * @param reader XMLリーダー
		 */
		void getXMLData(QXmlStreamReader &reader);
		QMap <QString, QString> _properties;
		QMap <QString, QString> _docs;
		/**
		 * @brief ポート名取得
		 * @return ポート名
		 */
		QString get_name();
		/**
		 * @brief ポート型取得
		 * @return ポート型
		 */
		QString get_portType();
		/**
		 * @brief データ型取得
		 * @return データ型
		 */
		QString get_type();
		/**
		 * @brief ポート名設定
		 * @param name ポート名
		 */
		void set_name(QString name);
		/**
		 * @brief ポート型設定
		 * @param type ポート型
		 */
		void set_portType(QString type);
		/**
		 * @brief データ型設定
		 * @param type データ型
		 */
		void set_type(QString type);
		/**
		 * @brief データ変数名取得
		 * @return データ変数名
		 */
		QString get_data_name();
		/**
		 * @brief ポート変数名取得
		 * @return ポート変数名
		 */
		QString get_port_name();

		std::mutex *m_mutex;
	};

	/**
	 * @class ServiceInterface
	 * @brief サービスインターフェースプロファイル
	 */
	class ServiceInterface
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		ServiceInterface();
		/**
		 * @brief コピーコンストラクタ
		 * @param obj コピー元
		 */
		ServiceInterface(const ServiceInterface &obj);
		/**
		 * @brief デストラクタ
		 */
		~ServiceInterface();
		/**
		 * @brief XMLファイルからプロファイル取得
		 * @param reader XMLリーダー
		 */
		void getXMLData(QXmlStreamReader &reader);
		/**
		 * @brief インターフェース名取得
		 * @return インターフェース名
		 */
		QString get_name();
		/**
		 * @brief インターフェース名設定
		 * @param name インターフェース名
		 */
		void set_name(QString name);
		/**
		 * @brief 方向取得
		 * @return 方向
		 */
		QString get_direction();
		/**
		 * @brief 方向設定
		 * @param dir 方向名
		 */
		void set_direction(QString dir);
		/**
		 * @brief IDLファイルパス取得
		 * @return IDLファイルパス
		 */
		QString get_idlFile();
		/**
		 * @brief IDLファイルパス設定
		 * @param file IDLファイルパス
		 */
		void set_idlFile(QString file);
		/**
		 * @brief インターフェース型取得
		 * @return インターフェース型
		 */
		QString get_type();
		/**
		 * @brief インターフェース型設定
		 * @param type インターフェース型
		 */
		void set_type(QString type);
		/**
		 * @brief IDLインクルードパス取得
		 * @return IDLインクルードパス
		 */
		QString get_path();
		/**
		 * @brief IDLインクルードパス設定
		 * @param path IDLインクルードパス
		 */
		void set_path(QString path);
		/**
		 * @brief インターフェース変数名取得
		 * @return インターフェース変数名
		 */
		QString get_data_name();
		QMap <QString, QString> _properties;
		QMap <QString, QString> _docs;

		std::mutex *m_mutex;
	};

	/**
	 * @class ServicePorts
	 * @brief サービスポートプロファイル
	 */
	class ServicePorts
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		ServicePorts();
		/**
		 * @brief コピーコンストラクタ
		 * @param obj コピー元
		 */
		ServicePorts(const ServicePorts &obj);
		/**
		 * @brief デストラクタ
		 */
		~ServicePorts();
		/**
		 * @brief XMLファイルからプロファイル取得
		 * @param reader XMLリーダー
		 */
		void getXMLData(QXmlStreamReader &reader);
		/**
		 * @brief インターフェース追加
		 * @param svrif サービスインターフェースプロファイル
		 */
		void addInterface(ServiceInterface svrif);
		/**
		 * @brief ポート名取得
		 * @return ポート名
		 */
		QString get_name();
		/**
		 * @brief ポート名設定
		 * @param name ポート名
		 */
		void set_name(QString name);
		/**
		 * @brief インターフェース取得
		 * @return サービスインターフェース一覧
		 */
		QVector<ServiceInterface> get_interfaces();

		QMap <QString, QString> _properties;
		QVector<ServiceInterface> _interfaces;
		QMap <QString, QString> _docs;

		std::mutex *m_mutex;

	};

	/**
	 * @class Language
	 * @brief 言語プロファイル
	 */
	class Language
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		Language();
		/**
		 * @brief コピーコンストラクタ
		 * @param obj コピー元
		 */
		Language(const Language &obj);
		/**
		 * @brief デストラクタ
		 */
		~Language();
		/**
		 * @brief XMLファイルからプロファイル取得
		 * @param reader XMLリーダー
		 */
		void getXMLData(QXmlStreamReader &reader);
		QMap <QString, QString> _properties;
		QMap <QString, QString> _docs;
		/**
		 * @brief 言語名取得
		 * @return 言語名
		 */
		QString getKind();

		std::mutex *m_mutex;
	};

	/**
	 * @class RTC_Profile
	 * @brief RTCプロファイル
	 */
	class RTC_Profile
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		RTC_Profile();
		/**
		 * @brief コピーコンストラクタ
		 * @param obj コピー元
		 */
		RTC_Profile(const RTC_Profile &obj);
		/**
		 * @brief デストラクタ
		 */
		~RTC_Profile();
		/**
		 * @brief XMLファイルからプロファイル取得
		 * @param name XMLファイルのパス
		 */
		void loadXML(QString name);
		/**
		 * @brief ポートの総数取得
		 * @return ポートの総数
		 */
		int getPortNum();
		/**
		 * @brief データポート追加
		 * @param port データポートプロファイル
		 */
		void addDataPort(DataPorts port);
		/**
		 * @brief サービスポート追加
		 * @param port サービスポートプロファイル
		 */
		void addServicePort(ServicePorts port);
		/**
		 * @brief コンフィグレーションパラメータ追加
		 * @param conf コンフィグレーションパラメータ
		 */
		void addConfigurationSet(ConfigurationSet conf);
		/**
		 * @brief データポート削除
		 * @param name ポート名
		 */
		void removeDataPort(QString name);
		/**
		 * @brief サービスポート削除
		 * @param name ポート名
		 */
		void removeServicePort(QString name);
		/**
		 * @brief コンフィグレーションパラメータ削除
		 * @param name コンフィグレーションパラメータ名
		 */
		void removeConfigurationSet(QString name);
		/**
		 * @brief アクティビティ取得
		 * @return アクティビティ一覧
		 */
		QMap <QString, RTC_Action> get_actions();
		/**
		 * @brief コンフィグレーションパラメータ取得
		 * @return コンフィグレーションパラメータ一覧
		 */
		QVector<ConfigurationSet> get_confsets();
		/**
		 * @brief データポート取得
		 * @return データポート一覧
		 */
		QVector<DataPorts> get_dataports();
		/**
		 * @brief サービスポート取得
		 * @return サービスポート一覧
		 */
		QVector<ServicePorts> get_svcports();
		QMap <QString, QString> _properties;
		/**
		 * @brief 基本プロファイル取得
		 * @return 基本プロファイル一覧
		 */
		BasicInfo get_info();
		BasicInfo _info;
		QMap <QString, RTC_Action> _actions;
		QVector<ConfigurationSet> _confsets;
		QVector<DataPorts> _dataports;
		QVector<ServicePorts> _svrports;
		/**
		 * @brief 言語プロファイル取得
		 * @return 言語プロファイル一覧
		 */
		Language get_language();
		Language _language;

		std::mutex *m_mutex;


	};

	/**
	 * @class RTC_Profile(動的編集)
	 * @brief RTCプロファイル
	 */
	class RTC_ProfileRTP : public RTC_Profile
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		RTC_ProfileRTP();
		/**
		 * @enum RTC_State
		 * @brief RTC状態一覧
		 */
		enum class RTC_State
		{
			RTP_Created = 0,
			RTP_InActive = 1,
			RTP_Acitve = 2,
			RTP_Error = 3,
		};
		/**
		 * @brief RTC状態取得
		 * @param ec_num 実行コンテキストID
		 * @return RTC状態取得
		 */
		RTC_State getState(int ec_num);
		/**
		 * @brief RTC状態設定
		 * @param state RTC状態
		 * @param ec_num 実行コンテキストID
		 */
		void setState(RTC_ProfileRTP::RTC_State state, int ec_num);
	private:
		QMap<int, RTC_State> _state;
	};
	

}



#endif // RTC_XML_H