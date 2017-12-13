/*!
 * @file  ComponentListItem.h
 * @brief �R���|�[�l���g���X�g�A�C�e��
 *
 */

#ifndef COMPONENTLISTITEM_H
#define COMPONENTLISTITEM_H

#include <cnoid/Item>
#include <cnoid/ItemManager>

#include <cnoid/ControllerItem>


#include <QWidget>
#include <QTableWidget>
#include <QDialog>
#include <QPushButton>
#include <QGroupBox>


QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
class QPrinter;
class QLayout;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QScrollArea;
class QGroupBox;
class QProcess;
QT_END_NAMESPACE







#include "ComponentList.h"
#include "RTC_XML.h"

#include "exportdecl.h"










namespace rtmiddleware {
	/**
	 * @class ComponentListItem
	 * @brief �R���|�[�l���g���X�g�A�C�e��
	 */
	class CNOID_EXPORT ComponentListItem : public cnoid::ControllerItem
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		ComponentListItem();
		/**
		 * @brief �R�s�[�R���X�g���N�^
		 * @param org �R�s�[��
		 */
		ComponentListItem(const ComponentListItem& org);
		/**
		 * @brief �f�X�g���N�^
		 */
		virtual ~ComponentListItem();
		/**
		 * @brief �������֐�
		 * @param ext 
		 */
		static void initialize(cnoid::ExtensionManager* ext);

		/**
		* @brief �V�~�����[�V�����J�n�����s�֐�
		* @return
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
		/**
		* @brief
		*/
		virtual void onDisconnectedFromRoot();

		//ScrollArea *_area;
		//ComponentList *_mwin;
	};

};


#endif