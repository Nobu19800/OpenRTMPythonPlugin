/*!
 * @file  RTC_XML.cpp
 * @brief RTC�v���t�@�C���I�u�W�F�N�g�N���X
 *
 */


#include "RTC_XML.h"


using namespace RTC_XML;

class Guard
{
public:
	Guard(coil::Mutex *mutex)
	{
		m_mutex = mutex;
		m_mutex->lock();
	};
	~Guard()
	{
		m_mutex->unlock();
	};
private:
	coil::Mutex *m_mutex;
};

/**
 * @brief �R���X�g���N�^
 */
BasicInfo::BasicInfo()
{
	m_mutex = new coil::Mutex;
}

/**
 * @brief �R�s�[�R���X�g���N�^
 * @param obj �R�s�[��
 */
BasicInfo::BasicInfo(const BasicInfo &obj)
{
	_properties = obj._properties;
	_docs = obj._docs;
	m_mutex = obj.m_mutex;
	
}

/**
 * @brief �f�X�g���N�^
 */
BasicInfo::~BasicInfo()
{
}

/**
 * @brief XML�t�@�C������v���t�@�C���擾
 * @param reader XML���[�_�[
 */
void BasicInfo::getXMLData(QXmlStreamReader &reader)
{
	Guard guard(m_mutex);
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
 * @brief �J�e�S�����擾
 * @return �J�e�S����
 */
QString BasicInfo::getCategory()
{
	Guard guard(m_mutex);
	return _properties["category"];
}

/**
 * @brief ���W���[�����擾
 * @return ���W���[����
 */
QString BasicInfo::getName()
{
	Guard guard(m_mutex);
	return _properties["name"];
}

/**
 * @brief �R���X�g���N�^
 */
RTC_Action::RTC_Action()
{
	m_mutex = new coil::Mutex;
}

/**
 * @brief �R�s�[�R���X�g���N�^
 * @param obj �R�s�[��
 */
RTC_Action::RTC_Action(const RTC_Action &obj)
{
	_docs = obj._docs;
	_properties = obj._properties;
	m_mutex = obj.m_mutex;
}

/**
 * @brief �f�X�g���N�^
 */
RTC_Action::~RTC_Action()
{

}

/**
 * @brief XML�t�@�C������v���t�@�C���擾
 * @param reader XML���[�_�[
 */
void RTC_Action::getXMLData(QXmlStreamReader &reader)
{
	Guard guard(m_mutex);
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
 * @brief �R���X�g���N�^
 */
ConfigurationSet::ConfigurationSet()
{
	m_mutex = new coil::Mutex;
}

/**
 * @brief �R�s�[�R���X�g���N�^
 * @param obj �R�s�[��
 */
ConfigurationSet::ConfigurationSet(const ConfigurationSet &obj)
{
	_properties = obj._properties;
	_docs = obj._docs;
	_ext = obj._ext;

	m_mutex = obj.m_mutex;
}

/**
 * @brief �f�X�g���N�^
 */
ConfigurationSet::~ConfigurationSet()
{

}

/**
 * @brief XML�t�@�C������v���t�@�C���擾
 * @param reader XML���[�_�[
 */
void ConfigurationSet::getXMLData(QXmlStreamReader &reader)
{
	Guard guard(m_mutex);
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
 * @brief �ϐ����擾
 * @return �ϐ���
 */
QString ConfigurationSet::get_data_name()
{
	return "_" + _properties["name"];
}

/**
 * @brief �p�����[�^���擾
 * @return �p�����[�^��
 */
QString ConfigurationSet::get_name()
{
	Guard guard(m_mutex);
	return _properties["name"];
}

/**
 * @brief �p�����[�^���擾
 * @param name �p�����[�^��
 */
void ConfigurationSet::set_name(QString name)
{
	Guard guard(m_mutex);
	_properties["name"] = name;
}

/**
 * @brief �f�t�H���g�l�ݒ�
 * @return �f�t�H���g�l
 */
QString ConfigurationSet::get_defaultValue()
{
	Guard guard(m_mutex);
	return _properties["defaultValue"];
}

/**
 * @brief �f�t�H���g�l�ݒ�
 * @param val �f�t�H���g�l
 */
void ConfigurationSet::set_defaultValue(QString val)
{
	Guard guard(m_mutex);
	_properties["defaultValue"] = val;
}

/**
 * @brief �f�[�^�^�擾
 * @return �f�[�^�^
 */
QString ConfigurationSet::get_type()
{
	Guard guard(m_mutex);
	return _properties["type"];
}

/**
 * @brief �f�[�^�^�ݒ�
 * @param type �f�[�^�^��
 */
void ConfigurationSet::set_type(QString type)
{
	Guard guard(m_mutex);
	_properties["type"] = type;
}

/**
 * @brief �E�B�W�F�b�g�^�擾
 * @return �E�B�W�F�b�g�^
 */
QString ConfigurationSet::get_widget()
{
	Guard guard(m_mutex);
	//return _ext["value"];
	return "";
}

/**
 * @brief �E�B�W�F�b�g�^�ݒ�
 * @param widget �E�B�W�F�b�g�^
 */
void ConfigurationSet::set_widget(QString widget)
{
	Guard guard(m_mutex);
	//_ext["value"] = widget;
}

/**
 * @brief ���񎮎擾
 * @return ����
 */
QString ConfigurationSet::get_constraint()
{
	Guard guard(m_mutex);
	//return _properties["defaultValue"];
	return "";
}

/**
 * @brief ���񎮐ݒ�
 * @param constraits ����
 */
void ConfigurationSet::set_constraint(QString constraits)
{
	Guard guard(m_mutex);
	//_properties["defaultValue"] = constraits;
}

/**
 * @brief �X�e�b�v�l�擾
 * @return �X�e�b�v�l
 */
QString ConfigurationSet::get_step()
{
	Guard guard(m_mutex);
	//return _properties["defaultValue"];
	return "";
}

/**
 * @brief �X�e�b�v�l�ݒ�
 * @param step �X�e�b�v�l
 */
void ConfigurationSet::set_step(QString step)
{
	Guard guard(m_mutex);
	//_properties["defaultValue"] = step;
}

/**
 * @brief �R���X�g���N�^
 */
DataPorts::DataPorts()
{
	_properties["name"] = "port";
	_properties["portType"] = "DataInPort";
	_properties["type"] = "RTC::TimedDouble";

	m_mutex = new coil::Mutex;
}

/**
 * @brief �R�s�[�R���X�g���N�^
 * @param obj �R�s�[��
 */
DataPorts::DataPorts(const DataPorts &obj)
{
	_properties = obj._properties;
	_docs = obj._docs;

	m_mutex = obj.m_mutex;
	
}

/**
 * @brief �f�X�g���N�^
 */
DataPorts::~DataPorts()
{

}

/**
 * @brief �|�[�g���擾
 * @return �|�[�g��
 */
QString DataPorts::get_name()
{
	Guard guard(m_mutex);
	return _properties["name"];
}


/**
 * @brief �|�[�g�^�擾
 * @return �|�[�g�^
 */
QString DataPorts::get_portType()
{
	Guard guard(m_mutex);
	return _properties["portType"];
}

/**
 * @brief �f�[�^�^�擾
 * @return �f�[�^�^
 */
QString DataPorts::get_type()
{
	Guard guard(m_mutex);
	return _properties["type"];
}





/**
 * @brief �|�[�g���ݒ�
 * @param name �|�[�g��
 */
void DataPorts::set_name(QString name)
{
	Guard guard(m_mutex);
	_properties["name"] = name;
}

/**
 * @brief �|�[�g�^�ݒ�
 * @param type �|�[�g�^
 */
void DataPorts::set_portType(QString type)
{
	Guard guard(m_mutex);
	_properties["portType"] = type;
}

/**
 * @brief �f�[�^�^�ݒ�
 * @param type �f�[�^�^
 */
void DataPorts::set_type(QString type)
{
	Guard guard(m_mutex);
	_properties["type"] = type;
}

/**
 * @brief XML�t�@�C������v���t�@�C���擾
 * @param reader XML���[�_�[
 */
void DataPorts::getXMLData(QXmlStreamReader &reader)
{
	Guard guard(m_mutex);
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
 * @brief �f�[�^�ϐ����擾
 * @return �f�[�^�ϐ���
 */
QString DataPorts::get_data_name()
{
	return "_d_" + get_name();
}

/**
 * @brief �|�[�g�ϐ����擾
 * @return �|�[�g�ϐ���
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
 * @brief �R���X�g���N�^
 */
ServiceInterface::ServiceInterface()
{
	_properties["name"] = "port";

	m_mutex = new coil::Mutex;
}

/**
 * @brief �R�s�[�R���X�g���N�^
 * @param obj �R�s�[��
 */
ServiceInterface::ServiceInterface(const ServiceInterface &obj)
{
	_properties = obj._properties;
	_docs = obj._docs;

	m_mutex = obj.m_mutex;
}

/**
 * @brief �f�X�g���N�^
 */
ServiceInterface::~ServiceInterface()
{

}

/**
 * @brief �C���^�[�t�F�[�X���擾
 * @return �C���^�[�t�F�[�X��
 */
QString ServiceInterface::get_name()
{
	Guard guard(m_mutex);
	return _properties["name"];
}

/**
 * @brief �C���^�[�t�F�[�X���ݒ�
 * @param name �C���^�[�t�F�[�X��
 */
void ServiceInterface::set_name(QString name)
{
	Guard guard(m_mutex);
	_properties["name"] = name;
}

/**
 * @brief �C���^�[�t�F�[�X�ϐ����擾
 * @return �C���^�[�t�F�[�X�ϐ���
 */
QString ServiceInterface::get_data_name()
{
	return "_i_" + _properties["name"];
}

/**
 * @brief �����擾
 * @return ����
 */
QString ServiceInterface::get_direction()
{
	Guard guard(m_mutex);
	return _properties["direction"];
}

/**
 * @brief �����ݒ�
 * @param dir ������
 */
void ServiceInterface::set_direction(QString dir)
{
	Guard guard(m_mutex);
	_properties["direction"] = dir;
}

/**
 * @brief IDL�t�@�C���p�X�擾
 * @return IDL�t�@�C���p�X
 */
QString ServiceInterface::get_idlFile()
{
	Guard guard(m_mutex);
	return _properties["idlFile"];
}

/**
 * @brief IDL�t�@�C���p�X�ݒ�
 * @param file IDL�t�@�C���p�X
 */
void ServiceInterface::set_idlFile(QString file)
{
	Guard guard(m_mutex);
	_properties["idlFile"] = file;
}

/**
 * @brief �C���^�[�t�F�[�X�^�擾
 * @return �C���^�[�t�F�[�X�^
 */
QString ServiceInterface::get_type()
{
	Guard guard(m_mutex);
	return _properties["type"];
}

/**
 * @brief �C���^�[�t�F�[�X�^�ݒ�
 * @param type �C���^�[�t�F�[�X�^
 */
void ServiceInterface::set_type(QString type)
{
	Guard guard(m_mutex);
	_properties["type"] = type;
}

/**
 * @brief IDL�C���N���[�h�p�X�擾
 * @return IDL�C���N���[�h�p�X
 */
QString ServiceInterface::get_path()
{
	Guard guard(m_mutex);
	return _properties["path"];
}

/**
 * @brief IDL�C���N���[�h�p�X�ݒ�
 * @param path IDL�C���N���[�h�p�X
 */
void ServiceInterface::set_path(QString path)
{
	Guard guard(m_mutex);
	_properties["path"] = path;
}


/**
 * @brief XML�t�@�C������v���t�@�C���擾
 * @param reader XML���[�_�[
 */
void ServiceInterface::getXMLData(QXmlStreamReader &reader)
{
	Guard guard(m_mutex);
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
 * @brief �R���X�g���N�^
 */
ServicePorts::ServicePorts()
{
	m_mutex = new coil::Mutex;
}

/**
 * @brief �R�s�[�R���X�g���N�^
 * @param obj �R�s�[��
 */
ServicePorts::ServicePorts(const ServicePorts &obj)
{
	_properties = obj._properties;
	_interfaces = obj._interfaces;
	_docs = obj._docs;

	m_mutex = obj.m_mutex;
}

/**
 * @brief �f�X�g���N�^
 */
ServicePorts::~ServicePorts()
{

}

/**
 * @brief �C���^�[�t�F�[�X�ǉ�
 * @param svrif �T�[�r�X�C���^�[�t�F�[�X�v���t�@�C��
 */
void ServicePorts::addInterface(ServiceInterface svrif)
{
	Guard guard(m_mutex);
	_interfaces.push_back(svrif);
}

/**
 * @brief XML�t�@�C������v���t�@�C���擾
 * @param reader XML���[�_�[
 */
void ServicePorts::getXMLData(QXmlStreamReader &reader)
{
	Guard guard(m_mutex);
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
 * @brief �|�[�g���擾
 * @return �|�[�g��
 */
QString ServicePorts::get_name()
{
	Guard guard(m_mutex);
	return _properties["name"];
}

/**
 * @brief �|�[�g���ݒ�
 * @param name �|�[�g��
 */
void ServicePorts::set_name(QString name)
{
	Guard guard(m_mutex);
	_properties["name"] = name;
}

/**
 * @brief �C���^�[�t�F�[�X�擾
 * @return �T�[�r�X�C���^�[�t�F�[�X�ꗗ
 */
QVector<ServiceInterface> ServicePorts::get_interfaces()
{
	Guard guard(m_mutex);
	return _interfaces;
}


/**
 * @brief �R���X�g���N�^
 */
Language::Language()
{
	m_mutex = new coil::Mutex;
}

/**
 * @brief �R�s�[�R���X�g���N�^
 * @param obj �R�s�[��
 */
Language::Language(const Language &obj)
{
	_docs = obj._docs;
	_properties = obj._properties;

	m_mutex = obj.m_mutex;
}


/**
 * @brief �f�X�g���N�^
 */
Language::~Language()
{

}

/**
 * @brief XML�t�@�C������v���t�@�C���擾
 * @param reader XML���[�_�[
 */
void Language::getXMLData(QXmlStreamReader &reader)
{
	Guard guard(m_mutex);
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
 * @brief ���ꖼ�擾
 * @return ���ꖼ
 */
QString Language::getKind()
{
	Guard guard(m_mutex);
	return  _properties["kind"];
}

/**
 * @brief �R���X�g���N�^
 */
RTC_Profile::RTC_Profile()
{
	m_mutex = new coil::Mutex;
}

/**
 * @brief �R�s�[�R���X�g���N�^
 * @param obj �R�s�[��
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

	m_mutex = obj.m_mutex;
}


/**
 * @brief �f�X�g���N�^
 */
RTC_Profile::~RTC_Profile()
{

}

/**
 * @brief XML�t�@�C������v���t�@�C���擾
 * @param name XML�t�@�C���̃p�X
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
 * @brief �|�[�g�̑����擾
 * @return �|�[�g�̑���
 */
int RTC_Profile::getPortNum()
{
	Guard guard(m_mutex);
	return _dataports.size() + _svrports.size();
}

/**
 * @brief �R���X�g���N�^
 */
RTC_ProfileRTP::RTC_ProfileRTP()
{
	_state[0] = RTP_Created;
}

/**
 * @brief RTC��Ԏ擾
 * @param ec_num ���s�R���e�L�X�gID
 * @return RTC��Ԏ擾
 */
RTC_ProfileRTP::RTC_State RTC_ProfileRTP::getState(int ec_num)
{
	Guard guard(m_mutex);
	if (_state.keys().indexOf(ec_num) >= 0)
	{
		return _state[ec_num];
	}
	return RTP_Created;
}

/**
 * @brief RTC��Ԑݒ�
 * @param state RTC���
 * @param ec_num ���s�R���e�L�X�gID
 */
void RTC_ProfileRTP::setState(RTC_ProfileRTP::RTC_State state, int ec_num)
{
	Guard guard(m_mutex);
	_state[ec_num] = state;
}

/**
 * @brief �A�N�e�B�r�e�B�擾
 * @return �A�N�e�B�r�e�B�ꗗ
 */
QMap <QString, RTC_Action> RTC_Profile::get_actions()
{
	Guard guard(m_mutex);
	return _actions;
}


/**
 * @brief �R���t�B�O���[�V�����p�����[�^�擾
 * @return �R���t�B�O���[�V�����p�����[�^�ꗗ
 */
QVector<ConfigurationSet> RTC_Profile::get_confsets()
{
	Guard guard(m_mutex);
	return _confsets;
}


QVector<DataPorts> RTC_Profile::get_dataports()
{
	Guard guard(m_mutex);
	return _dataports;
}

/**
 * @brief �f�[�^�|�[�g�擾
 * @return �f�[�^�|�[�g�ꗗ
 */
void RTC_Profile::addDataPort(DataPorts port)
{
	Guard guard(m_mutex);
	_dataports.push_back(port);
}


void RTC_Profile::addServicePort(ServicePorts port)
{
	Guard guard(m_mutex);
	_svrports.push_back(port);
}

/**
 * @brief �T�[�r�X�|�[�g�擾
 * @return �T�[�r�X�|�[�g�ꗗ
 */
QVector<ServicePorts>  RTC_Profile::get_svcports()
{
	Guard guard(m_mutex);
	return _svrports;
}

/**
 * @brief �R���t�B�O���[�V�����p�����[�^�ǉ�
 * @param conf �R���t�B�O���[�V�����p�����[�^
 */
void RTC_Profile::addConfigurationSet(ConfigurationSet conf)
{
	Guard guard(m_mutex);
	_confsets.push_back(conf);
}

/**
 * @brief �f�[�^�|�[�g�폜
 * @param name �|�[�g��
 */
void RTC_Profile::removeDataPort(QString name)
{
	Guard guard(m_mutex);
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
 * @brief �T�[�r�X�|�[�g�폜
 * @param name �|�[�g��
 */
void RTC_Profile::removeServicePort(QString name)
{
	Guard guard(m_mutex);
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
 * @brief �R���t�B�O���[�V�����p�����[�^�폜
 * @param name �R���t�B�O���[�V�����p�����[�^��
 */
void RTC_Profile::removeConfigurationSet(QString name)
{
	Guard guard(m_mutex);
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
 * @brief ��{�v���t�@�C���擾
 * @return ��{�v���t�@�C���ꗗ
 */
BasicInfo RTC_Profile::get_info()
{
	Guard guard(m_mutex);
	return _info;
}

/**
 * @brief ����v���t�@�C���擾
 * @return ����v���t�@�C���ꗗ
 */
Language RTC_Profile::get_language()
{
	Guard guard(m_mutex);
	return _language;
}