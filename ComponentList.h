/*!
 * @file  ComponentList.h
 * @brief RTC�����`���[�\���N���X
 *
 */

#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <QWidget>
#include <QTableWidget>
#include <QDialog>
#include <QPushButton>
#include <QGroupBox>

#include <cnoid/View>
#include <cnoid/CorbaUtil>

#include <rtm/Manager.h>
#include <rtm/ManagerServant.h>

#include "RTC_XML.h"
#include "RTCViewWidget.h"

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

/**
 * @class ComponentWidget
 * @brief RTC�\���E�B�W�F�b�g
 */
class ComponentWidget : public QGroupBox
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param path ���W���[���p�X
	 * @param parent �e�E�B�W�F�b�g
	 */
	ComponentWidget(QString path, QWidget *parent = Q_NULLPTR);
	/**
	 * @brief ���W���[���p�X�ݒ�
	 * @param path ���W���[���p�X
	 */
	void setModulePath(QString path);
	/**
	 * @brief �J�e�S���擾
	 * @return �J�e�S��
	 */
	QString getCategory();
	/**
	* @brief �I������
	*/
	void killprocess();
	/**
	* @brief RTC�v���t�@�C���I�u�W�F�N�g�̎擾
	* @return RTC�v���t�@�C���I�u�W�F�N�g
	*/
	RTC_XML::RTC_Profile get_comp_prof();
	/**
	* @brief �N�����Ă���v���Z�X���̎擾
	* @return �N�����Ă���v���Z�X��
	*/
	int get_process_count();
	/**
	* @brief �}�l�[�W���ŋN�����Ă���R���|�[�l���g���̎擾
	* @return �R���|�[�l���g��
	*/
	int get_rtcd_count();
public Q_SLOTS:
	/**
	 * @brief RTC��ʃv���Z�X�ŋN��
	 */
	void run_process();
	/**
	 * @brief RTC���}�l�[�W���ŋN��
	 */
	void run_rtcd();
	
	

private:
	QString _path;
	RTC_XML::RTC_Profile _comp;
	RTCViewWidget *_vw;
	QVBoxLayout *_mainLayout;
	QPushButton *_processButton;
	QPushButton *_managerButton;
	QVector<QProcess*> _process;
	QVector<RTC::RTObject_impl*> _cpp_modules;
	QVector<std::string> _python_module;
};

/**
 * @class ComponentTabWidget
 * @brief �J�e�S����RTC�\���^�u
 */
class ComponentTabWidget : public QWidget
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	ComponentTabWidget();
	/**
	 * @brief RTC�ǉ�
	 * @param cw RTC�\���E�B�W�F�b�g
	 */
	void addComponent(ComponentWidget *cw);
	/**
	 * @brief ���C�����C�A�E�g�̐L�k���ݒ�
	 * @param v �L�k��
	 */
	void addStretchMain(int v = 0);
	/**
	 * @brief �T�u���C�A�E�g�̐L�k���ݒ�
	 * @param v �L�k��
	 */
	void addStretchSub(int v = 0);
	/**
	* @brief �I������
	*/
	void killprocess();
	/**
	* @brief RTC�E�B�W�F�b�g�ꗗ�擾
	* @return RTC�E�B�W�F�b�g�ꗗ
	*/
	QMap<QString, ComponentWidget *>  getComponents();
private:
	QMap<QString, ComponentWidget *> _complist;
	QVBoxLayout *_mainLayout;
	QVector<QHBoxLayout*> _subLayouts;
};

/**
 * @class ComponentList
 * @brief RTC�����`���[�\���E�B�W�F�b�g
 */
class ComponentList : public QTabWidget
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param parent �e�E�B�W�F�b�g
	 */
	ComponentList(QWidget *parent = Q_NULLPTR);
	/**
	 * @brief RTC�ǉ�
	 * @param path ���W���[���p�X
	 */
	void addComponent(QString path);
	/**
	 * @brief ���W���[���ꗗ�����[�h
	 * @param path ���W���[�����X�g�̃p�X
	 */
	void load(QString path);
	/**
	* @brief �I������
	*/
	void killprocess();
	/**
	* @brief �ۑ�����
	* @param archive
	*/
	void store(cnoid::Archive& archive);
	/**
	* @brief ��������
	* @param archive
	*/
	void restore(const cnoid::Archive& archive);
	/**
	* @brief ��������
	* @param archive
	*/
	void restore_process(const cnoid::Archive& archive);
private:
	QMap<QString, ComponentTabWidget*> tabList;


};

/**
 * @class ScrollArea
 * @brief �X�N���[���G���A
 */
class ScrollArea : public QScrollArea
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param parent �e�E�B�W�F�b�g
	 */
	ScrollArea(QWidget *parent = Q_NULLPTR);
private Q_SLOTS:
	/**
	 * @brief �X�N���[�����̃X���b�g
	 * @param v �ړ���
	 */
	void valueChanged(int v);
};


class ComponentListView : public cnoid::View
{
	Q_OBJECT
public:
	/**
	* @brief �R���X�g���N�^
	*/
	ComponentListView();
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~ComponentListView();
	/**
	* @brief ������
	* @param ext 
	*/
	static void initializeClass(cnoid::ExtensionManager* ext);
	/**
	* @brief �C���X�^���X�擾
	* @return �C���X�^���X
	*/
	static ComponentListView* instance();
	/**
	* @brief �I������
	*/
	void killprocess();
	/**
	* @brief �ۑ�����
	* @param archive 
	*/
	void store(cnoid::Archive& archive);
	/**
	* @brief ��������
	* @param archive
	*/
	void restore(const cnoid::Archive& archive);
private:
	ScrollArea *_area;
	ComponentList *_mwin;
};

#endif // TEXTEDIT_H
