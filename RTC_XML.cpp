/*!
 * @file  RTC_XML.cpp
 * @brief RTCプロファイルオブジェクトクラス
 *
 */

#include "RTC_XML.h"


using namespace RTC_XML;

/**
 * @brief コンストラクタ
 */
BasicInfo::BasicInfo()
{
}

/**
 * @brief コピーコンストラクタ
 * @param obj コピー元
 */
BasicInfo::BasicInfo(const BasicInfo &obj)
{
	_properties = obj._properties;
	_docs = obj._docs;
}

/**
 * @brief デストラクタ
 */
BasicInfo::~BasicInfo()
{
}

/**
 * @brief XMLファイルからプロファイル取得
 * @param reader XMLリーダー
 */
void BasicInfo::getXMLData(QXmlStreamReader &reader)
{
	{
		//std::cout << reader.name().toString().toStdString() << std::endl;
		QXmlStreamAttributes attributes = reader.attributes();
		Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
			//std::cout << attribute.name().toLocal8Bit().toStdString() << "\t" << attribute.value().toLocal8Bit().toStdString() << std::endl;
			_properties[attribute.name().toString()] = attribute.value().toString();
		}
	}

	while (reader.readNextStartElement()) {
		//std::cout << reader.name().toString().toStdString() << std::endl;
		if (reader.name() == "Doc")
		{
			QXmlStreamAttributes attributes = reader.attributes();
			Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
				//std::cout << attribute.name().toLocal8Bit().toStdString() << "\t" << attribute.value().toLocal8Bit().toStdString() << std::endl;
				_docs[attribute.name().toString()] = attribute.value().toString();
			}
		}
		else
		{
			reader.skipCurrentElement();
		}
		reader.readNext();
	}
}

/**
 * @brief カテゴリ名取得
 * @return カテゴリ名
 */
QString BasicInfo::getCategory()
{
	return _properties["category"];
}

/**
 * @brief モジュール名取得
 * @return モジュール名
 */
QString BasicInfo::getName()
{
	return _properties["name"];
}

/**
 * @brief コンストラクタ
 */
RTC_Action::RTC_Action()
{

}

/**
 * @brief コピーコンストラクタ
 * @param obj コピー元
 */
RTC_Action::RTC_Action(const RTC_Action &obj)
{
	_docs = obj._docs;
	_properties = obj._properties;
}

/**
 * @brief デストラクタ
 */
RTC_Action::~RTC_Action()
{

}

/**
 * @brief XMLファイルからプロファイル取得
 * @param reader XMLリーダー
 */
void RTC_Action::getXMLData(QXmlStreamReader &reader)
{
	{
		//std::cout << reader.name().toString().toStdString() << std::endl;
		QXmlStreamAttributes attributes = reader.attributes();
		Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
			//std::cout << attribute.name().toLocal8Bit().toStdString() << "\t" << attribute.value().toLocal8Bit().toStdString() << std::endl;
			_properties[attribute.name().toString()] = attribute.value().toString();
		}
	}

	while (reader.readNextStartElement()) {
		//std::cout << reader.name().toString().toStdString() << std::endl;
		if (reader.name() == "Doc")
		{
			QXmlStreamAttributes attributes = reader.attributes();
			Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
				//std::cout << attribute.name().toLocal8Bit().toStdString() << "\t" << attribute.value().toLocal8Bit().toStdString() << std::endl;
				_docs[attribute.name().toString()] = attribute.value().toString();
			}
		}
		else
		{
			reader.skipCurrentElement();
		}
		reader.readNext();
	}
}

/**
 * @brief コンストラクタ
 */
ConfigurationSet::ConfigurationSet()
{

}

/**
 * @brief コピーコンストラクタ
 * @param obj コピー元
 */
ConfigurationSet::ConfigurationSet(const ConfigurationSet &obj)
{
	_properties = obj._properties;
	_docs = obj._docs;
	_ext = obj._ext;
}

/**
 * @brief デストラクタ
 */
ConfigurationSet::~ConfigurationSet()
{

}

/**
 * @brief XMLファイルからプロファイル取得
 * @param reader XMLリーダー
 */
void ConfigurationSet::getXMLData(QXmlStreamReader &reader)
{
	{
		//std::cout << reader.name().toString().toStdString() << std::endl;
		QXmlStreamAttributes attributes = reader.attributes();
		Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
			//std::cout << attribute.name().toLocal8Bit().toStdString() << "\t" << attribute.value().toLocal8Bit().toStdString() << std::endl;
			_properties[attribute.name().toString()] = attribute.value().toString();
		}
	}

	while (reader.readNextStartElement()) {

		if (reader.name() == "Doc")
		{
			//std::cout << reader.name().toString().toStdString() << std::endl;
			QXmlStreamAttributes attributes = reader.attributes();
			Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
				_docs[attribute.name().toString()] = attribute.value().toString();
				//std::cout << attribute.name().toLocal8Bit().toStdString() << "\t" << attribute.value().toLocal8Bit().toStdString() << std::endl;
			}
		}
		else if (reader.name() == "Properties")
		{
			//std::cout << reader.name().toString().toStdString() << std::endl;
			QXmlStreamAttributes attributes = reader.attributes();
			Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
				//std::cout << attribute.name().toLocal8Bit().toStdString() << "\t" << attribute.value().toLocal8Bit().toStdString() << std::endl;
				_ext[attribute.name().toString()] = attribute.value().toString();

			}
		}
		else
		{
			reader.skipCurrentElement();
		}
		reader.readNext();
	}
}

/**
 * @brief 変数名取得
 * @return 変数名
 */
QString ConfigurationSet::get_data_name()
{
	return "_" + _properties["name"];
}

/**
 * @brief パラメータ名取得
 * @return パラメータ名
 */
QString ConfigurationSet::get_name()
{
	return _properties["name"];
}

/**
 * @brief パラメータ名取得
 * @param name パラメータ名
 */
void ConfigurationSet::set_name(QString name)
{
	_properties["name"] = name;
}

/**
 * @brief デフォルト値設定
 * @return デフォルト値
 */
QString ConfigurationSet::get_defaultValue()
{
	return _properties["defaultValue"];
}

/**
 * @brief デフォルト値設定
 * @param val デフォルト値
 */
void ConfigurationSet::set_defaultValue(QString val)
{
	_properties["defaultValue"] = val;
}

/**
 * @brief データ型取得
 * @return データ型
 */
QString ConfigurationSet::get_type()
{
	return _properties["type"];
}

/**
 * @brief データ型設定
 * @param type データ型名
 */
void ConfigurationSet::set_type(QString type)
{
	_properties["type"] = type;
}

/**
 * @brief ウィジェット型取得
 * @return ウィジェット型
 */
QString ConfigurationSet::get_widget()
{
	//return _ext["value"];
	return "";
}

/**
 * @brief ウィジェット型設定
 * @param widget ウィジェット型
 */
void ConfigurationSet::set_widget(QString widget)
{
	//_ext["value"] = widget;
}

/**
 * @brief 制約式取得
 * @return 制約式
 */
QString ConfigurationSet::get_constraint()
{
	//return _properties["defaultValue"];
	return "";
}

/**
 * @brief 制約式設定
 * @param constraits 制約式
 */
void ConfigurationSet::set_constraint(QString constraits)
{
	//_properties["defaultValue"] = constraits;
}

/**
 * @brief ステップ値取得
 * @return ステップ値
 */
QString ConfigurationSet::get_step()
{
	//return _properties["defaultValue"];
	return "";
}

/**
 * @brief ステップ値設定
 * @param step ステップ値
 */
void ConfigurationSet::set_step(QString step)
{
	//_properties["defaultValue"] = step;
}

/**
 * @brief コンストラクタ
 */
DataPorts::DataPorts()
{
	_properties["name"] = "port";
	_properties["portType"] = "DataInPort";
	_properties["type"] = "RTC::TimedDouble";
}

/**
 * @brief コピーコンストラクタ
 * @param obj コピー元
 */
DataPorts::DataPorts(const DataPorts &obj)
{
	_properties = obj._properties;
	_docs = obj._docs;
}

/**
 * @brief デストラクタ
 */
DataPorts::~DataPorts()
{

}

/**
 * @brief ポート名取得
 * @return ポート名
 */
QString DataPorts::get_name()
{
	return _properties["name"];
}


/**
 * @brief ポート型取得
 * @return ポート型
 */
QString DataPorts::get_portType()
{
	return _properties["portType"];
}

/**
 * @brief データ型取得
 * @return データ型
 */
QString DataPorts::get_type()
{
	return _properties["type"];
}





/**
 * @brief ポート名設定
 * @param name ポート名
 */
void DataPorts::set_name(QString name)
{
	_properties["name"] = name;
}

/**
 * @brief ポート型設定
 * @param type ポート型
 */
void DataPorts::set_portType(QString type)
{
	_properties["portType"] = type;
}

/**
 * @brief データ型設定
 * @param type データ型
 */
void DataPorts::set_type(QString type)
{
	_properties["type"] = type;
}

/**
 * @brief XMLファイルからプロファイル取得
 * @param reader XMLリーダー
 */
void DataPorts::getXMLData(QXmlStreamReader &reader)
{
	{
		//std::cout << reader.name().toString().toStdString() << std::endl;
		QXmlStreamAttributes attributes = reader.attributes();
		Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
			_properties[attribute.name().toString()] = attribute.value().toString();
			//std::cout << attribute.name().toLocal8Bit().toStdString() << "\t" << attribute.value().toLocal8Bit().toStdString() << std::endl;
		}
	}

	while (reader.readNextStartElement()) {

		if (reader.name() == "Doc")
		{
			//std::cout << reader.name().toString().toStdString() << std::endl;
			QXmlStreamAttributes attributes = reader.attributes();
			Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
				_docs[attribute.name().toString()] = attribute.value().toString();
				//std::cout << attribute.name().toLocal8Bit().toStdString() << "\t" << attribute.value().toLocal8Bit().toStdString() << std::endl;
			}
		}
		else
		{
			reader.skipCurrentElement();
		}
		reader.readNext();
	}
}


/**
 * @brief データ変数名取得
 * @return データ変数名
 */
QString DataPorts::get_data_name()
{
	return "_d_" + get_name();
}

/**
 * @brief ポート変数名取得
 * @return ポート変数名
 */
QString DataPorts::get_port_name()
{
	if (get_portType() == "DataInPort")
	{
		return "_" + get_name() + "In";
	}
	else if (get_portType() == "DataOutPort")
	{
		return "_" + get_name() + "Out";
	}
	return "";
}



/**
 * @brief コンストラクタ
 */
ServiceInterface::ServiceInterface()
{
	_properties["name"] = "port";
}

/**
 * @brief コピーコンストラクタ
 * @param obj コピー元
 */
ServiceInterface::ServiceInterface(const ServiceInterface &obj)
{
	_properties = obj._properties;
	_docs = obj._docs;
}

/**
 * @brief デストラクタ
 */
ServiceInterface::~ServiceInterface()
{

}

/**
 * @brief インターフェース名取得
 * @return インターフェース名
 */
QString ServiceInterface::get_name()
{
	return _properties["name"];
}

/**
 * @brief インターフェース名設定
 * @param name インターフェース名
 */
void ServiceInterface::set_name(QString name)
{
	_properties["name"] = name;
}

/**
 * @brief インターフェース変数名取得
 * @return インターフェース変数名
 */
QString ServiceInterface::get_data_name()
{
	return "_i_" + _properties["name"];
}

/**
 * @brief 方向取得
 * @return 方向
 */
QString ServiceInterface::get_direction()
{
	return _properties["direction"];
}

/**
 * @brief 方向設定
 * @param dir 方向名
 */
void ServiceInterface::set_direction(QString dir)
{
	_properties["direction"] = dir;
}

/**
 * @brief IDLファイルパス取得
 * @return IDLファイルパス
 */
QString ServiceInterface::get_idlFile()
{
	return _properties["idlFile"];
}

/**
 * @brief IDLファイルパス設定
 * @param file IDLファイルパス
 */
void ServiceInterface::set_idlFile(QString file)
{
	_properties["idlFile"] = file;
}

/**
 * @brief インターフェース型取得
 * @return インターフェース型
 */
QString ServiceInterface::get_type()
{
	return _properties["type"];
}

/**
 * @brief インターフェース型設定
 * @param type インターフェース型
 */
void ServiceInterface::set_type(QString type)
{
	_properties["type"] = type;
}

/**
 * @brief IDLインクルードパス取得
 * @return IDLインクルードパス
 */
QString ServiceInterface::get_path()
{
	return _properties["path"];
}

/**
 * @brief IDLインクルードパス設定
 * @param path IDLインクルードパス
 */
void ServiceInterface::set_path(QString path)
{
	_properties["path"] = path;
}


/**
 * @brief XMLファイルからプロファイル取得
 * @param reader XMLリーダー
 */
void ServiceInterface::getXMLData(QXmlStreamReader &reader)
{
	{
		//std::cout << reader.name().toString().toStdString() << std::endl;
		QXmlStreamAttributes attributes = reader.attributes();
		Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
			_properties[attribute.name().toString()] = attribute.value().toString();
			//std::cout << attribute.name().toLocal8Bit().toStdString() << "\t" << attribute.value().toLocal8Bit().toStdString() << std::endl;
		}
	}

	while (reader.readNextStartElement()) {
		//std::cout << reader.name().toString().toStdString() << std::endl;
		if (reader.name() == "Doc")
		{
			QXmlStreamAttributes attributes = reader.attributes();
			Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
				_docs[attribute.name().toString()] = attribute.value().toString();

				//std::cout << attribute.name().toLocal8Bit().toStdString() << "\t" << attribute.value().toLocal8Bit().toStdString() << std::endl;
			}
		}
		else
		{
			reader.skipCurrentElement();
		}
		reader.readNext();
	}
}

/**
 * @brief コンストラクタ
 */
ServicePorts::ServicePorts()
{

}

/**
 * @brief コピーコンストラクタ
 * @param obj コピー元
 */
ServicePorts::ServicePorts(const ServicePorts &obj)
{
	_properties = obj._properties;
	_interfaces = obj._interfaces;
	_docs = obj._docs;
}

/**
 * @brief デストラクタ
 */
ServicePorts::~ServicePorts()
{

}

/**
 * @brief インターフェース追加
 * @param svrif サービスインターフェースプロファイル
 */
void ServicePorts::addInterface(ServiceInterface svrif)
{
	_interfaces.push_back(svrif);
}

/**
 * @brief XMLファイルからプロファイル取得
 * @param reader XMLリーダー
 */
void ServicePorts::getXMLData(QXmlStreamReader &reader)
{
	{
		//std::cout << reader.name().toString().toStdString() << std::endl;
		QXmlStreamAttributes attributes = reader.attributes();
		Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
			_properties[attribute.name().toString()] = attribute.value().toString();
			//std::cout << attribute.name().toLocal8Bit().toStdString() << "\t" << attribute.value().toLocal8Bit().toStdString() << std::endl;
		}
	}

	while (reader.readNextStartElement()) {
		//std::cout << reader.name().toString().toStdString() << std::endl;
		if (reader.name() == "Doc")
		{
			QXmlStreamAttributes attributes = reader.attributes();
			Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
				_docs[attribute.name().toString()] = attribute.value().toString();

				//std::cout << attribute.name().toLocal8Bit().toStdString() << "\t" << attribute.value().toLocal8Bit().toStdString() << std::endl;
			}
		}
		else if (reader.name() == "ServiceInterface")
		{
			ServiceInterface svc_if;
			svc_if.getXMLData(reader);
			_interfaces.push_back(svc_if);
		}
		else
		{
			reader.skipCurrentElement();
		}
		reader.readNext();
	}
}

/**
 * @brief ポート名取得
 * @return ポート名
 */
QString ServicePorts::get_name()
{
	return _properties["name"];
}

/**
 * @brief ポート名設定
 * @param name ポート名
 */
void ServicePorts::set_name(QString name)
{
	_properties["name"] = name;
}

/**
 * @brief インターフェース取得
 * @return サービスインターフェース一覧
 */
QVector<ServiceInterface> ServicePorts::get_interfaces()
{
	return _interfaces;
}


/**
 * @brief コンストラクタ
 */
Language::Language()
{

}

/**
 * @brief コピーコンストラクタ
 * @param obj コピー元
 */
Language::Language(const Language &obj)
{
	_docs = obj._docs;
	_properties = obj._properties;
}


/**
 * @brief デストラクタ
 */
Language::~Language()
{

}

/**
 * @brief XMLファイルからプロファイル取得
 * @param reader XMLリーダー
 */
void Language::getXMLData(QXmlStreamReader &reader)
{
	{
		//std::cout << reader.name().toString().toStdString() << std::endl;
		QXmlStreamAttributes attributes = reader.attributes();
		Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
			_properties[attribute.name().toString()] = attribute.value().toString();
			//std::cout << attribute.name().toLocal8Bit().toStdString() << "\t" << attribute.value().toLocal8Bit().toStdString() << std::endl;
		}
	}

	while (reader.readNextStartElement()) {

		if (reader.name() == "Doc")
		{
			//std::cout << reader.name().toString().toStdString() << std::endl;
			QXmlStreamAttributes attributes = reader.attributes();
			Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
				_docs[attribute.name().toString()] = attribute.value().toString();
				//std::cout << attribute.name().toLocal8Bit().toStdString() << "\t" << attribute.value().toLocal8Bit().toStdString() << std::endl;
			}
		}
		else
		{
			reader.skipCurrentElement();
		}
		reader.readNext();
	}
}

/**
 * @brief 言語名取得
 * @return 言語名
 */
QString Language::getKind()
{
	return  _properties["kind"];
}

/**
 * @brief コンストラクタ
 */
RTC_Profile::RTC_Profile()
{

}

/**
 * @brief コピーコンストラクタ
 * @param obj コピー元
 */
RTC_Profile::RTC_Profile(const RTC_Profile &obj)
{
	_properties = obj._properties;
	_info = obj._info;
	_actions = obj._actions;
	_confsets = obj._confsets;
	_dataports = obj._dataports;
	_svrports = obj._svrports;
	_language = obj._language;
}


/**
 * @brief デストラクタ
 */
RTC_Profile::~RTC_Profile()
{

}

/**
 * @brief XMLファイルからプロファイル取得
 * @param name XMLファイルのパス
 */
void RTC_Profile::loadXML(QString name)
{
	QFile inputFile(name);
	if (!QFile::exists(name))
	{
		return;
	}
	else if (!inputFile.open(QIODevice::ReadOnly)) {
		return;
	}
	QXmlStreamReader reader(&inputFile);
	reader.setNamespaceProcessing(false);

	while (reader.readNextStartElement()) {
		if (reader.name() == "RtcProfile")
		{
			{

				QXmlStreamAttributes attributes = reader.attributes();
				Q_FOREACH(QXmlStreamAttribute attribute, attributes) {
					_properties[attribute.name().toString()] = attribute.value().toString();

				}
			}
			while (reader.readNextStartElement()) {
				//std::cout << reader.name().toLocal8Bit().toStdString() << std::endl;

				if (reader.name() == "BasicInfo")
				{
					_info.getXMLData(reader);
					//reader.readNext();
					//reader.skipCurrentElement();
				}
				else if (reader.name() == "Actions")
				{
					
					while (reader.readNextStartElement()) {
						RTC_Action act;
						act.getXMLData(reader);
						_actions[reader.name().toString()] = act;

						reader.readNext();
					}


				}
				else if (reader.name() == "ConfigurationSet")
				{
					
					while (reader.readNextStartElement()) {
						
						ConfigurationSet conf;
						conf.getXMLData(reader);
						_confsets.push_back(conf);

						reader.readNext();
					}
				}
				else if (reader.name() == "DataPorts")
				{
					DataPorts dataport;
					dataport.getXMLData(reader);
					_dataports.push_back(dataport);
				}
				else if (reader.name() == "ServicePorts")
				{
					ServicePorts svcport;
					svcport.getXMLData(reader);
					_svrports.push_back(svcport);
				}
				else if (reader.name() == "Language")
				{
					_language.getXMLData(reader);
					reader.readNext();
				}
				else
				{
					//std::cout << reader.name().toString().toStdString() << std::endl;
					reader.skipCurrentElement();
				}
			}
		}

	}
}

/**
 * @brief ポートの総数取得
 * @return ポートの総数
 */
int RTC_Profile::getPortNum()
{
	return _dataports.size() + _svrports.size();
}

/**
 * @brief コンストラクタ
 */
RTC_ProfileRTP::RTC_ProfileRTP()
{
	_state[0] = RTP_Created;
}

/**
 * @brief RTC状態取得
 * @param ec_num 実行コンテキストID
 * @return RTC状態取得
 */
RTC_ProfileRTP::RTC_State RTC_ProfileRTP::getState(int ec_num)
{
	if (_state.keys().indexOf(ec_num) >= 0)
	{
		return _state[ec_num];
	}
	return RTP_Created;
}

/**
 * @brief RTC状態設定
 * @param state RTC状態
 * @param ec_num 実行コンテキストID
 */
void RTC_ProfileRTP::setState(RTC_ProfileRTP::RTC_State state, int ec_num)
{
	_state[ec_num] = state;
}

/**
 * @brief アクティビティ取得
 * @return アクティビティ一覧
 */
QMap <QString, RTC_Action> RTC_Profile::get_actions()
{
	return _actions;
}


/**
 * @brief コンフィグレーションパラメータ取得
 * @return コンフィグレーションパラメータ一覧
 */
QVector<ConfigurationSet> RTC_Profile::get_confsets()
{
	return _confsets;
}


QVector<DataPorts> RTC_Profile::get_dataports()
{
	return _dataports;
}

/**
 * @brief データポート取得
 * @return データポート一覧
 */
void RTC_Profile::addDataPort(DataPorts port)
{
	_dataports.push_back(port);
}


void RTC_Profile::addServicePort(ServicePorts port)
{
	_svrports.push_back(port);
}

/**
 * @brief サービスポート取得
 * @return サービスポート一覧
 */
QVector<ServicePorts>  RTC_Profile::get_svcports()
{
	return _svrports;
}

/**
 * @brief コンフィグレーションパラメータ追加
 * @param conf コンフィグレーションパラメータ
 */
void RTC_Profile::addConfigurationSet(ConfigurationSet conf)
{
	_confsets.push_back(conf);
}

/**
 * @brief データポート削除
 * @param name ポート名
 */
void RTC_Profile::removeDataPort(QString name)
{
	for (QVector<DataPorts>::iterator itr = _dataports.begin(); itr != _dataports.end(); itr++)
	{
		if ((*itr).get_name() == name)
		{
			_dataports.erase(itr);
			return;
		}
	}
}

/**
 * @brief サービスポート削除
 * @param name ポート名
 */
void RTC_Profile::removeServicePort(QString name)
{
	for (QVector<ServicePorts>::iterator itr = _svrports.begin(); itr != _svrports.end(); itr++)
	{
		if ((*itr).get_name() == name)
		{
			_svrports.erase(itr);
			return;
		}
	}
}

/**
 * @brief コンフィグレーションパラメータ削除
 * @param name コンフィグレーションパラメータ名
 */
void RTC_Profile::removeConfigurationSet(QString name)
{
	for (QVector<ConfigurationSet>::iterator itr = _confsets.begin(); itr != _confsets.end(); itr++)
	{
		if ((*itr).get_name() == name)
		{
			_confsets.erase(itr);
			return;
		}
	}
}

/**
 * @brief 基本プロファイル取得
 * @return 基本プロファイル一覧
 */
BasicInfo RTC_Profile::get_info()
{
	return _info;
}

/**
 * @brief 言語プロファイル取得
 * @return 言語プロファイル一覧
 */
Language RTC_Profile::get_language()
{
	return _language;
}