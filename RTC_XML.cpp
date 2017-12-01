#include "RTC_XML.h"


using namespace RTC_XML;


BasicInfo::BasicInfo()
{
}

BasicInfo::BasicInfo(const BasicInfo &obj)
{
	_properties = obj._properties;
	_docs = obj._docs;
}

BasicInfo::~BasicInfo()
{
}

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


QString BasicInfo::getCategory()
{
	return _properties["category"];
}

QString BasicInfo::getName()
{
	return _properties["name"];
}

RTC_Action::RTC_Action()
{

}

RTC_Action::RTC_Action(const RTC_Action &obj)
{
	_docs = obj._docs;
	_properties = obj._properties;
}

RTC_Action::~RTC_Action()
{

}

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

ConfigurationSet::ConfigurationSet()
{

}

ConfigurationSet::ConfigurationSet(const ConfigurationSet &obj)
{
	_properties = obj._properties;
	_docs = obj._docs;
	_ext = obj._ext;
}

ConfigurationSet::~ConfigurationSet()
{

}

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

QString ConfigurationSet::get_data_name()
{
	return "_" + _properties["name"];
}

QString ConfigurationSet::get_name()
{
	return _properties["name"];
}

void ConfigurationSet::set_name(QString name)
{
	_properties["name"] = name;
}


QString ConfigurationSet::get_defaultValue()
{
	return _properties["defaultValue"];
}
void ConfigurationSet::set_defaultValue(QString val)
{
	_properties["defaultValue"] = val;
}
QString ConfigurationSet::get_type()
{
	return _properties["type"];
}
void ConfigurationSet::set_type(QString type)
{
	_properties["type"] = type;
}
QString ConfigurationSet::get_widget()
{
	//return _ext["value"];
	return "";
}
void ConfigurationSet::set_widget(QString widget)
{
	//_ext["value"] = widget;
}
QString ConfigurationSet::get_constraint()
{
	//return _properties["defaultValue"];
	return "";
}
void ConfigurationSet::set_constraint(QString constraits)
{
	//_properties["defaultValue"] = constraits;
}
QString ConfigurationSet::get_step()
{
	//return _properties["defaultValue"];
	return "";
}
void ConfigurationSet::set_step(QString step)
{
	//_properties["defaultValue"] = step;
}


DataPorts::DataPorts()
{
	_properties["name"] = "port";
	_properties["portType"] = "DataInPort";
	_properties["type"] = "RTC::TimedDouble";
}

DataPorts::DataPorts(const DataPorts &obj)
{
	_properties = obj._properties;
	_docs = obj._docs;
}

DataPorts::~DataPorts()
{

}

QString DataPorts::get_name()
{
	return _properties["name"];
}

QString DataPorts::get_portType()
{
	return _properties["portType"];
}

QString DataPorts::get_type()
{
	return _properties["type"];
}






void DataPorts::set_name(QString name)
{
	_properties["name"] = name;
}
void DataPorts::set_portType(QString type)
{
	_properties["portType"] = type;
}
void DataPorts::set_type(QString type)
{
	_properties["type"] = type;
}


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



QString DataPorts::get_data_name()
{
	return "_d_" + get_name();
}
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




ServiceInterface::ServiceInterface()
{
	_properties["name"] = "port";
}


ServiceInterface::ServiceInterface(const ServiceInterface &obj)
{
	_properties = obj._properties;
	_docs = obj._docs;
}


ServiceInterface::~ServiceInterface()
{

}

QString ServiceInterface::get_name()
{
	return _properties["name"];
}

void ServiceInterface::set_name(QString name)
{
	_properties["name"] = name;
}

QString ServiceInterface::get_data_name()
{
	return "_i_" + _properties["name"];
}


QString ServiceInterface::get_direction()
{
	return _properties["direction"];
}

void ServiceInterface::set_direction(QString dir)
{
	_properties["direction"] = dir;
}


QString ServiceInterface::get_idlFile()
{
	return _properties["idlFile"];
}

void ServiceInterface::set_idlFile(QString file)
{
	_properties["idlFile"] = file;
}


QString ServiceInterface::get_type()
{
	return _properties["type"];
}

void ServiceInterface::set_type(QString type)
{
	_properties["type"] = type;
}


QString ServiceInterface::get_path()
{
	return _properties["path"];
}

void ServiceInterface::set_path(QString path)
{
	_properties["path"] = path;
}



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

ServicePorts::ServicePorts()
{

}

ServicePorts::ServicePorts(const ServicePorts &obj)
{
	_properties = obj._properties;
	_interfaces = obj._interfaces;
	_docs = obj._docs;
}

ServicePorts::~ServicePorts()
{

}

void ServicePorts::addInterface(ServiceInterface svrif)
{
	_interfaces.push_back(svrif);
}

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


QString ServicePorts::get_name()
{
	return _properties["name"];
}

void ServicePorts::set_name(QString name)
{
	_properties["name"] = name;
}


QVector<ServiceInterface> ServicePorts::get_interfaces()
{
	return _interfaces;
}

Language::Language()
{

}

Language::Language(const Language &obj)
{
	_docs = obj._docs;
	_properties = obj._properties;
}

Language::~Language()
{

}

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


QString Language::getKind()
{
	return  _properties["kind"];
}


RTC_Profile::RTC_Profile()
{

}

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

RTC_Profile::~RTC_Profile()
{

}

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

int RTC_Profile::getPortNum()
{
	return _dataports.size() + _svrports.size();
}


RTC_ProfileRTP::RTC_ProfileRTP()
{
	_state[0] = RTP_Created;
}

RTC_ProfileRTP::RTC_State RTC_ProfileRTP::getState(int ec_num)
{
	if (_state.keys().indexOf(ec_num) >= 0)
	{
		return _state[ec_num];
	}
	return RTP_Created;
}

void RTC_ProfileRTP::setState(RTC_ProfileRTP::RTC_State state, int ec_num)
{
	_state[ec_num] = state;
}


QMap <QString, RTC_Action> RTC_Profile::get_actions()
{
	return _actions;
}



QVector<ConfigurationSet> RTC_Profile::get_confsets()
{
	return _confsets;
}


QVector<DataPorts> RTC_Profile::get_dataports()
{
	return _dataports;
}


void RTC_Profile::addDataPort(DataPorts port)
{
	_dataports.push_back(port);
}


void RTC_Profile::addServicePort(ServicePorts port)
{
	_svrports.push_back(port);
}


QVector<ServicePorts>  RTC_Profile::get_svcports()
{
	return _svrports;
}


void RTC_Profile::addConfigurationSet(ConfigurationSet conf)
{
	_confsets.push_back(conf);
}


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

BasicInfo RTC_Profile::get_info()
{
	return _info;
}

Language RTC_Profile::get_language()
{
	return _language;
}