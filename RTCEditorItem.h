/*!
 * @file  RTCEditorItem.h
 * @brief RTCEditor�A�C�e��
 *
 */

#ifndef RTCEDITORITEM_H
#define RTCEDITORITEM_H

#include <cnoid/Item>
#include <cnoid/ItemManager>
#include <cnoid/CorbaUtil>
#include <cnoid/ControllerItem>



#include <src/OpenRTMPlugin/RTSItem.h>


#include "PyRTCItem.h"
#include "RTC_MainWindow.h"
#include "RTC_XML.h"

#include "exportdecl.h"










namespace rtmiddleware {
	
	/**
	 * @class RTCEditorItem
	 * @brief RTCEditor�A�C�e��
	 */
	class CNOID_EXPORT RTCEditorItem : public PyRTCItemBase
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		RTCEditorItem();
		/**
		 * @brief �R�s�[�R���X�g���N�^
		 * @param org �R�s�[��
		 */
		RTCEditorItem(const RTCEditorItem& org);
		/**
		 * @brief �f�X�g���N�^
		 */
		virtual ~RTCEditorItem();
		/**
		 * @brief �������֐�
		 * @param ext 
		 */
		static void initialize(cnoid::ExtensionManager* ext);
		/**
		 * @brief RTC�_�C�A�O������̑I���A�C�e���ύX�����s�֐�
		 * @param item RTC�_�C�A�O������őI�𒆂�RTC
		 */
		void onItemSelectionChanged(cnoid::RTSComp* item);
		/**
		 * @brief RTC����
		 * @param name RTC��
		 */
		void createEditComp(const char* name);
		/**
		 * @brief RTC�̃t�@�C���X�V
		 * @param filename Python�t�@�C���̃p�X
		 */
		void update_comp(const char *filename);
		/**
		 * @brief RTC�̃A�N�e�B�u��
		 */
		void activate_comp();
		/**
		 * @brief RTC�̔�A�N�e�B�u��
		 */
		void deactivate_comp();
		/**
		 * @brief RTC�̃��Z�b�g
		 */
		void reset_comp();
		/**
		 * @brief RTC�̏�Ԏ擾
		 * @param status RTC�v���t�@�C��
		 */
		void get_status(RTC_XML::RTC_ProfileRTP::RTC_State& status);
		/**
		 * @brief �f�[�^�|�[�g�ǉ�
		 * @param port �f�[�^�|�[�g�v���t�@�C��
		 */
		void add_dataport(RTC_XML::DataPorts port);


	private:
		cnoid::Connection selectionChangedConnection;
		RTC_MainWindow *mwin;
	protected:
		/**
		 * @brief �v���p�e�B�ݒ�
		 * @param putProperty �v���p�e�B 
		 */
		virtual void doPutProperties(cnoid::PutPropertyFunction& putProperty);
		/**
		 * @brief ��������
		 * @return �����I�u�W�F�N�g
		 */
		virtual cnoid::Item* doDuplicate() const override;
		/**
		 * @brief �ۑ�����
		 * @param archive 
		 */
		virtual bool store(cnoid::Archive& archive) override;
		/**
		 * @brief ��������
		 * @param archive 
		 */
		virtual bool restore(const cnoid::Archive& archive) override;

		/**
		 * @brief �����������s�֐�
		 * @param ext 
		 */
		virtual bool initialize(cnoid::ControllerItemIO* io) override;
		/**
		 * @brief 
		 */
		virtual void onPositionChanged();


	};

};


#endif