/*!
 * @file  PyRTCItem.h
 * @brief PyRTC�A�C�e��
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




#include "exportdecl.h"










namespace rtmiddleware {

	/**
	 * @class PyRTCItemBase
	 * @brief PyRTC�A�C�e���x�[�X�N���X
	 */
	class CNOID_EXPORT PyRTCItemBase : public cnoid::ControllerItem
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		PyRTCItemBase();

		/**
		 * @brief �V�~�����[�V�����J�n�����s�֐�
		 */
		virtual bool start();
		/**
		 * @brief ���ݕ��擾
		 * @return ���ݕ�
		 */
		virtual double timeStep() const;
		/**
		 * @brief �V�~�����[�V�����X�V�O���s�֐�
		 */
		virtual void input();
		/**
		 * @brief �V�~�����[�V�����X�V�����s�֐�
		 */
		virtual bool control();
		/**
		 * @brief �V�~�����[�V�����X�V����s�֐�
		 */
		virtual void output();
		/**
		 * @brief �V�~�����[�V�����I�������s�֐�
		 */
		virtual void stop();

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
		 * @brief �����������s�֐�
		 * @param ext 
		 */
		virtual bool initialize(cnoid::ControllerItemIO* io) override;
		cnoid::BodyItem* body_item;
		std::string comp_name;

		std::string moduleNameProperty;

		cnoid::Selection relativePathBaseType;
		cnoid::Selection execContextType;
	};
	
	/**
	 * @class PyRTCItem
	 * @brief PyRTC�A�C�e���N���X
	 */
	class CNOID_EXPORT PyRTCItem : public PyRTCItemBase
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		PyRTCItem();
		/**
		 * @brief �R�s�[�R���X�g���N�^
		 * @param org �R�s�[��
		 */
		PyRTCItem(const PyRTCItem& org);
		/**
		 * @brief �f�X�g���N�^
		 */
		virtual ~PyRTCItem();
		/**
		 * @brief �������֐�
		 * @param ext 
		 */
		static void initialize(cnoid::ExtensionManager* ext);
		/**
		 * @brief ���s�R���e�L�X�g�ݒ�
		 * @param which ���s�R���e�L�X�gID 
		 */
		void setExecContextType(int which);
		/**
		 * @brief RTC����
		 * @param name ���O
		 */
		void createComp(std::string name);
		/**
		 * @brief ���΃p�X�ݒ�
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
		 * @brief 
		 */
		virtual void onPositionChanged();
		


	};

};


#endif