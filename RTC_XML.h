/*!
 * @file  RTC_XML.h
 * @brief RTC�v���t�@�C���I�u�W�F�N�g�N���X
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



namespace RTC_XML
{
	/**
	 * @class BasicInfo
	 * @brief ��{�v���t�@�C��
	 */
	class BasicInfo
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		BasicInfo();
		/**
		 * @brief �R�s�[�R���X�g���N�^
		 * @param obj �R�s�[��
		 */
		BasicInfo(const BasicInfo &obj);
		/**
		 * @brief �f�X�g���N�^
		 */
		~BasicInfo();
		QMap <QString, QString> _properties;
		QMap <QString, QString> _docs;
		/**
		 * @brief XML�t�@�C������v���t�@�C���擾
		 * @param reader XML���[�_�[
		 */
		void getXMLData(QXmlStreamReader &reader);
		/**
		 * @brief �J�e�S�����擾
		 * @return �J�e�S����
		 */
		QString getCategory();
		/**
		 * @brief ���W���[�����擾
		 * @return ���W���[����
		 */
		QString getName();
	};

	/**
	 * @class RTC_Action
	 * @brief �A�N�e�B�r�e�B�v���t�@�C��
	 */
	class RTC_Action
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		RTC_Action();
		/**
		 * @brief �R�s�[�R���X�g���N�^
		 * @param obj �R�s�[��
		 */
		RTC_Action(const RTC_Action &obj);
		/**
		 * @brief �f�X�g���N�^
		 */
		~RTC_Action();
		/**
		 * @brief XML�t�@�C������v���t�@�C���擾
		 * @param reader XML���[�_�[
		 */
		void getXMLData(QXmlStreamReader &reader);
		


		QMap <QString, QString> _docs;
		QMap <QString, QString> _properties;
	};

	/**
	 * @class ConfigurationSet
	 * @brief �R���t�B�O���[�V�����v���t�@�C��
	 */
	class ConfigurationSet
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		ConfigurationSet();
		/**
		 * @brief �R�s�[�R���X�g���N�^
		 * @param obj �R�s�[��
		 */
		ConfigurationSet(const ConfigurationSet &obj);
		/**
		 * @brief �f�X�g���N�^
		 */
		~ConfigurationSet();
		/**
		 * @brief XML�t�@�C������v���t�@�C���擾
		 * @param reader XML���[�_�[
		 */
		void getXMLData(QXmlStreamReader &reader);
		/**
		 * @brief �p�����[�^���擾
		 * @return �p�����[�^��
		 */
		QString get_name();
		/**
		 * @brief �p�����[�^���擾
		 * @param name �p�����[�^��
		 */
		void set_name(QString name);
		/**
		 * @brief �f�t�H���g�l�ݒ�
		 * @return �f�t�H���g�l
		 */
		QString get_defaultValue();
		/**
		 * @brief �f�t�H���g�l�ݒ�
		 * @param val �f�t�H���g�l
		 */
		void set_defaultValue(QString val);
		/**
		 * @brief �f�[�^�^�擾
		 * @return �f�[�^�^
		 */
		QString get_type();
		/**
		 * @brief �f�[�^�^�ݒ�
		 * @param type �f�[�^�^��
		 */
		void set_type(QString type);
		/**
		 * @brief �E�B�W�F�b�g�^�擾
		 * @return �E�B�W�F�b�g�^
		 */
		QString get_widget();
		/**
		 * @brief �E�B�W�F�b�g�^�ݒ�
		 * @param widget �E�B�W�F�b�g�^
		 */
		void set_widget(QString widget);
		/**
		 * @brief ���񎮎擾
		 * @return ����
		 */
		QString get_constraint();
		/**
		 * @brief ���񎮐ݒ�
		 * @param constraits ����
		 */
		void set_constraint(QString constraits);
		/**
		 * @brief �X�e�b�v�l�擾
		 * @return �X�e�b�v�l
		 */
		QString get_step();
		/**
		 * @brief �X�e�b�v�l�ݒ�
		 * @param step �X�e�b�v�l
		 */
		void set_step(QString step);
		/**
		 * @brief �ϐ����擾
		 * @return �ϐ���
		 */
		QString get_data_name();
		QMap <QString, QString> _properties;
		QMap <QString, QString> _docs;
		QMap <QString, QString> _ext;
	};

	/**
	 * @class DataPorts
	 * @brief �f�[�^�|�[�g�v���t�@�C��
	 */
	class DataPorts
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		DataPorts();
		/**
		 * @brief �R�s�[�R���X�g���N�^
		 * @param obj �R�s�[��
		 */
		DataPorts(const DataPorts &obj);
		/**
		 * @brief �f�X�g���N�^
		 */
		~DataPorts();
		/**
		 * @brief XML�t�@�C������v���t�@�C���擾
		 * @param reader XML���[�_�[
		 */
		void getXMLData(QXmlStreamReader &reader);
		QMap <QString, QString> _properties;
		QMap <QString, QString> _docs;
		/**
		 * @brief �|�[�g���擾
		 * @return �|�[�g��
		 */
		QString get_name();
		/**
		 * @brief �|�[�g�^�擾
		 * @return �|�[�g�^
		 */
		QString get_portType();
		/**
		 * @brief �f�[�^�^�擾
		 * @return �f�[�^�^
		 */
		QString get_type();
		/**
		 * @brief �|�[�g���ݒ�
		 * @param name �|�[�g��
		 */
		void set_name(QString name);
		/**
		 * @brief �|�[�g�^�ݒ�
		 * @param type �|�[�g�^
		 */
		void set_portType(QString type);
		/**
		 * @brief �f�[�^�^�ݒ�
		 * @param type �f�[�^�^
		 */
		void set_type(QString type);
		/**
		 * @brief �f�[�^�ϐ����擾
		 * @return �f�[�^�ϐ���
		 */
		QString get_data_name();
		/**
		 * @brief �|�[�g�ϐ����擾
		 * @return �|�[�g�ϐ���
		 */
		QString get_port_name();
	};

	/**
	 * @class ServiceInterface
	 * @brief �T�[�r�X�C���^�[�t�F�[�X�v���t�@�C��
	 */
	class ServiceInterface
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		ServiceInterface();
		/**
		 * @brief �R�s�[�R���X�g���N�^
		 * @param obj �R�s�[��
		 */
		ServiceInterface(const ServiceInterface &obj);
		/**
		 * @brief �f�X�g���N�^
		 */
		~ServiceInterface();
		/**
		 * @brief XML�t�@�C������v���t�@�C���擾
		 * @param reader XML���[�_�[
		 */
		void getXMLData(QXmlStreamReader &reader);
		/**
		 * @brief �C���^�[�t�F�[�X���擾
		 * @return �C���^�[�t�F�[�X��
		 */
		QString get_name();
		/**
		 * @brief �C���^�[�t�F�[�X���ݒ�
		 * @param name �C���^�[�t�F�[�X��
		 */
		void set_name(QString name);
		/**
		 * @brief �����擾
		 * @return ����
		 */
		QString get_direction();
		/**
		 * @brief �����ݒ�
		 * @param dir ������
		 */
		void set_direction(QString dir);
		/**
		 * @brief IDL�t�@�C���p�X�擾
		 * @return IDL�t�@�C���p�X
		 */
		QString get_idlFile();
		/**
		 * @brief IDL�t�@�C���p�X�ݒ�
		 * @param file IDL�t�@�C���p�X
		 */
		void set_idlFile(QString file);
		/**
		 * @brief �C���^�[�t�F�[�X�^�擾
		 * @return �C���^�[�t�F�[�X�^
		 */
		QString get_type();
		/**
		 * @brief �C���^�[�t�F�[�X�^�ݒ�
		 * @param type �C���^�[�t�F�[�X�^
		 */
		void set_type(QString type);
		/**
		 * @brief IDL�C���N���[�h�p�X�擾
		 * @return IDL�C���N���[�h�p�X
		 */
		QString get_path();
		/**
		 * @brief IDL�C���N���[�h�p�X�ݒ�
		 * @param path IDL�C���N���[�h�p�X
		 */
		void set_path(QString path);
		/**
		 * @brief �C���^�[�t�F�[�X�ϐ����擾
		 * @return �C���^�[�t�F�[�X�ϐ���
		 */
		QString get_data_name();
		QMap <QString, QString> _properties;
		QMap <QString, QString> _docs;
	};

	/**
	 * @class ServicePorts
	 * @brief �T�[�r�X�|�[�g�v���t�@�C��
	 */
	class ServicePorts
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		ServicePorts();
		/**
		 * @brief �R�s�[�R���X�g���N�^
		 * @param obj �R�s�[��
		 */
		ServicePorts(const ServicePorts &obj);
		/**
		 * @brief �f�X�g���N�^
		 */
		~ServicePorts();
		/**
		 * @brief XML�t�@�C������v���t�@�C���擾
		 * @param reader XML���[�_�[
		 */
		void getXMLData(QXmlStreamReader &reader);
		/**
		 * @brief �C���^�[�t�F�[�X�ǉ�
		 * @param svrif �T�[�r�X�C���^�[�t�F�[�X�v���t�@�C��
		 */
		void addInterface(ServiceInterface svrif);
		/**
		 * @brief �|�[�g���擾
		 * @return �|�[�g��
		 */
		QString get_name();
		/**
		 * @brief �|�[�g���ݒ�
		 * @param name �|�[�g��
		 */
		void set_name(QString name);
		/**
		 * @brief �C���^�[�t�F�[�X�擾
		 * @return �T�[�r�X�C���^�[�t�F�[�X�ꗗ
		 */
		QVector<ServiceInterface> get_interfaces();

		QMap <QString, QString> _properties;
		QVector<ServiceInterface> _interfaces;
		QMap <QString, QString> _docs;

	};

	/**
	 * @class Language
	 * @brief ����v���t�@�C��
	 */
	class Language
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		Language();
		/**
		 * @brief �R�s�[�R���X�g���N�^
		 * @param obj �R�s�[��
		 */
		Language(const Language &obj);
		/**
		 * @brief �f�X�g���N�^
		 */
		~Language();
		/**
		 * @brief XML�t�@�C������v���t�@�C���擾
		 * @param reader XML���[�_�[
		 */
		void getXMLData(QXmlStreamReader &reader);
		QMap <QString, QString> _properties;
		QMap <QString, QString> _docs;
		/**
		 * @brief ���ꖼ�擾
		 * @return ���ꖼ
		 */
		QString getKind();
	};

	/**
	 * @class RTC_Profile
	 * @brief RTC�v���t�@�C��
	 */
	class RTC_Profile
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		RTC_Profile();
		/**
		 * @brief �R�s�[�R���X�g���N�^
		 * @param obj �R�s�[��
		 */
		RTC_Profile(const RTC_Profile &obj);
		/**
		 * @brief �f�X�g���N�^
		 */
		~RTC_Profile();
		/**
		 * @brief XML�t�@�C������v���t�@�C���擾
		 * @param name XML�t�@�C���̃p�X
		 */
		void loadXML(QString name);
		/**
		 * @brief �|�[�g�̑����擾
		 * @return �|�[�g�̑���
		 */
		int getPortNum();
		/**
		 * @brief �f�[�^�|�[�g�ǉ�
		 * @param port �f�[�^�|�[�g�v���t�@�C��
		 */
		void addDataPort(DataPorts port);
		/**
		 * @brief �T�[�r�X�|�[�g�ǉ�
		 * @param port �T�[�r�X�|�[�g�v���t�@�C��
		 */
		void addServicePort(ServicePorts port);
		/**
		 * @brief �R���t�B�O���[�V�����p�����[�^�ǉ�
		 * @param conf �R���t�B�O���[�V�����p�����[�^
		 */
		void addConfigurationSet(ConfigurationSet conf);
		/**
		 * @brief �f�[�^�|�[�g�폜
		 * @param name �|�[�g��
		 */
		void removeDataPort(QString name);
		/**
		 * @brief �T�[�r�X�|�[�g�폜
		 * @param name �|�[�g��
		 */
		void removeServicePort(QString name);
		/**
		 * @brief �R���t�B�O���[�V�����p�����[�^�폜
		 * @param name �R���t�B�O���[�V�����p�����[�^��
		 */
		void removeConfigurationSet(QString name);
		/**
		 * @brief �A�N�e�B�r�e�B�擾
		 * @return �A�N�e�B�r�e�B�ꗗ
		 */
		QMap <QString, RTC_Action> get_actions();
		/**
		 * @brief �R���t�B�O���[�V�����p�����[�^�擾
		 * @return �R���t�B�O���[�V�����p�����[�^�ꗗ
		 */
		QVector<ConfigurationSet> get_confsets();
		/**
		 * @brief �f�[�^�|�[�g�擾
		 * @return �f�[�^�|�[�g�ꗗ
		 */
		QVector<DataPorts> get_dataports();
		/**
		 * @brief �T�[�r�X�|�[�g�擾
		 * @return �T�[�r�X�|�[�g�ꗗ
		 */
		QVector<ServicePorts> get_svcports();
		QMap <QString, QString> _properties;
		/**
		 * @brief ��{�v���t�@�C���擾
		 * @return ��{�v���t�@�C���ꗗ
		 */
		BasicInfo get_info();
		BasicInfo _info;
		QMap <QString, RTC_Action> _actions;
		QVector<ConfigurationSet> _confsets;
		QVector<DataPorts> _dataports;
		QVector<ServicePorts> _svrports;
		/**
		 * @brief ����v���t�@�C���擾
		 * @return ����v���t�@�C���ꗗ
		 */
		Language get_language();
		Language _language;


	};

	/**
	 * @class RTC_Profile(���I�ҏW)
	 * @brief RTC�v���t�@�C��
	 */
	class RTC_ProfileRTP : public RTC_Profile
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		RTC_ProfileRTP();
		/**
		 * @enum RTC_State
		 * @brief RTC��Ԉꗗ
		 */
		enum RTC_State
		{
			RTP_Created = 0,
			RTP_InActive = 1,
			RTP_Acitve = 2,
			RTP_Error = 3,
		};
		/**
		 * @brief RTC��Ԏ擾
		 * @param ec_num ���s�R���e�L�X�gID
		 * @return RTC��Ԏ擾
		 */
		RTC_State getState(int ec_num);
		/**
		 * @brief RTC��Ԑݒ�
		 * @param state RTC���
		 * @param ec_num ���s�R���e�L�X�gID
		 */
		void setState(RTC_ProfileRTP::RTC_State state, int ec_num);
	private:
		QMap<int, RTC_State> _state;
	};
	

}



#endif // TEXTEDIT_H