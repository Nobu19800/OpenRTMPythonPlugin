/*!
 * @file  ActivityTab.h
 * @brief �e�R�[���o�b�N�֐��ҏW�^�u
 *
 */


#ifndef ACTIVITYTAB_H
#define ACTIVITYTAB_H


#include <QWidget>
#include "BaseTab.h"
#include "PythonEditor.h"
#include "highlighter.h"
#include "ActivityCode.h"




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
QT_END_NAMESPACE




/**
 * @class ActivityTab
 * @brief �e�R�[���o�b�N�֐��ҏW�^�u
 */
class ActivityTab : public BaseTab
{
    Q_OBJECT

public:
	/**
	 * @brief �R���X�g���N�^
	 * @param name �A�N�e�B�r�e�B��ID
	 * @param text �e�L�X�g
	 * @param parent �e�E�B�W�F�b�g
	 */
	ActivityTab(ActivityCode name, QString text, QWidget *parent = Q_NULLPTR);
	/**
	 * @brief �R���X�g���N�^
	 * @param name �A�N�e�B�r�e�B��
	 * @param text �e�L�X�g
	 * @param parent �e�E�B�W�F�b�g
	 */
	ActivityTab(QString name, QString text, QWidget *parent = Q_NULLPTR);

	/**
	 * @brief �e�L�X�g�擾
	 * @return �e�L�X�g
	 */
	QString getText();
	/**
	 * @brief �t�H���g�T�C�Y�ݒ�
	 * @param s �t�H���g�T�C�Y
	 */
	void setFontSize(int s);
	


public Q_SLOTS:


protected:





//    void fileOpen();


private:
	ActivityCode _name;
	QString _text;
	
	PythonEditor *_editor;
	Highlighter *_highlight;
};

#endif // TEXTEDIT_H
