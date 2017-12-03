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
	ComponentWidget(QString path, QWidget *parent = 0);
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
private Q_SLOTS:
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
	QProcess *_process;
};

/**
 * @class ComponentTabWidgwt
 * @brief �J�e�S����RTC�\���^�u
 */
class ComponentTabWidgwt : public QWidget
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	ComponentTabWidgwt();
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
private:
	QVector<ComponentWidget *> _complist;
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
	ComponentList(QWidget *parent = 0);
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
private:
	QMap<QString, ComponentTabWidgwt*> tabList;


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
	ScrollArea(QWidget *parent = 0);
private Q_SLOTS:
	/**
	 * @brief �X�N���[�����̃X���b�g
	 * @param v �ړ���
	 */
	void valueChanged(int v);
};


#endif // TEXTEDIT_H
