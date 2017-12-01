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



namespace RTC_XML
{

	class BasicInfo
	{
	public:
		BasicInfo();
		BasicInfo(const BasicInfo &obj);
		~BasicInfo();
		QMap <QString, QString> _properties;
		QMap <QString, QString> _docs;
		void getXMLData(QXmlStreamReader &reader);
		QString getCategory();
		QString getName();
	};

	class RTC_Action
	{
	public:
		RTC_Action();
		RTC_Action(const RTC_Action &obj);
		~RTC_Action();
		void getXMLData(QXmlStreamReader &reader);
		


		QMap <QString, QString> _docs;
		QMap <QString, QString> _properties;
	};

	class ConfigurationSet
	{
	public:
		ConfigurationSet();
		ConfigurationSet(const ConfigurationSet &obj);
		~ConfigurationSet();
		void getXMLData(QXmlStreamReader &reader);
		QString get_name();
		void set_name(QString name);
		QString get_defaultValue();
		void set_defaultValue(QString val);
		QString get_type();
		void set_type(QString type);
		QString get_widget();
		void set_widget(QString widget);
		QString get_constraint();
		void set_constraint(QString constraits);
		QString get_step();
		void set_step(QString step);
		QString get_data_name();
		QMap <QString, QString> _properties;
		QMap <QString, QString> _docs;
		QMap <QString, QString> _ext;
	};


	class DataPorts
	{
	public:
		DataPorts();
		DataPorts(const DataPorts &obj);
		~DataPorts();
		void getXMLData(QXmlStreamReader &reader);
		QMap <QString, QString> _properties;
		QMap <QString, QString> _docs;
		QString get_name();
		QString get_portType();
		QString get_type();
		void set_name(QString name);
		void set_portType(QString type);
		void set_type(QString type);
		QString get_data_name();
		QString get_port_name();
	};

	class ServiceInterface
	{
	public:
		ServiceInterface();
		ServiceInterface(const ServiceInterface &obj);
		~ServiceInterface();
		void getXMLData(QXmlStreamReader &reader);
		QString get_name();
		void set_name(QString name);
		QString get_direction();
		void set_direction(QString dir);
		QString get_idlFile();
		void set_idlFile(QString file);
		QString get_type();
		void set_type(QString type);
		QString get_path();
		void set_path(QString path);
		QString get_data_name();
		QMap <QString, QString> _properties;
		QMap <QString, QString> _docs;
	};

	class ServicePorts
	{
	public:
		ServicePorts();
		ServicePorts(const ServicePorts &obj);
		~ServicePorts();
		void getXMLData(QXmlStreamReader &reader);
		void addInterface(ServiceInterface svrif);

		QString get_name();
		void set_name(QString name);
		QVector<ServiceInterface> get_interfaces();

		QMap <QString, QString> _properties;
		QVector<ServiceInterface> _interfaces;
		QMap <QString, QString> _docs;

	};

	class Language
	{
	public:
		Language();
		Language(const Language &obj);
		~Language();

		void getXMLData(QXmlStreamReader &reader);
		QMap <QString, QString> _properties;
		QMap <QString, QString> _docs;
		QString getKind();
	};

	class RTC_Profile
	{
	public:
		RTC_Profile();
		RTC_Profile(const RTC_Profile &obj);
		~RTC_Profile();
		void loadXML(QString name);
		int getPortNum();
		void addDataPort(DataPorts port);
		void addServicePort(ServicePorts port);
		void addConfigurationSet(ConfigurationSet conf);
		void removeDataPort(QString name);
		void removeServicePort(QString name);
		void removeConfigurationSet(QString name);
		QMap <QString, RTC_Action> get_actions();
		QVector<ConfigurationSet> get_confsets();
		QVector<DataPorts> get_dataports();
		QVector<ServicePorts> get_svcports();
		QMap <QString, QString> _properties;
		BasicInfo get_info();
		BasicInfo _info;
		QMap <QString, RTC_Action> _actions;
		QVector<ConfigurationSet> _confsets;
		QVector<DataPorts> _dataports;
		QVector<ServicePorts> _svrports;
		Language get_language();
		Language _language;


	};

	class RTC_ProfileRTP : public RTC_Profile
	{
	public:
		RTC_ProfileRTP();
		enum RTC_State
		{
			RTP_Created = 0,
			RTP_InActive = 1,
			RTP_Acitve = 2,
			RTP_Error = 3,
		};
		RTC_State getState(int ec_num);
		void setState(RTC_ProfileRTP::RTC_State state, int ec_num);
	private:
		QMap<int, RTC_State> _state;
	};
	

}



#endif // TEXTEDIT_H