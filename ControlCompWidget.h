/*!
 * @file  ControlCompWidget.h
 * @brief �R���|�[�l���g�Ď��E�B�W�F�b�g
 *
 */

#ifndef CONTROLCOMPWIDGET_H
#define CONTROLCOMPWIDGET_H


#include <QWidget>
#include <cnoid/Signal>
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
 * @class ControlCompWidget
 * @brief �R���|�[�l���g�Ď��E�B�W�F�b�g
 */
class ControlCompWidget : public BaseTab
{
    Q_OBJECT

public:
	/**
	 * @brief �R���X�g���N�^
	 * @param parent �e�E�B�W�F�b�g
	 */
	ControlCompWidget(QWidget *parent = Q_NULLPTR);
	/**
	 * @brief �ݒ肵�Ă�����s�R���e�L�X�g��ID�擾
	 * @retuen ���s�R���e�L�X�g��ID
	 */
	int getECNum();
	cnoid::Signal<void()>  sigActiveButton;
	cnoid::Signal<void()>  sigDeactiveButton;
	cnoid::Signal<void()>  sigResetButton;

	


public Q_SLOTS:
	/**
	 * @brief �A�N�e�B�u�{�^���̃X���b�g
	 */
	void activeButtonSlot();
	/**
	 * @brief ��A�N�e�B�u�{�^���̃X���b�g
	 */
	void deactiveButtonSlot();
	/**
	 * @brief ���Z�b�g�{�^���̃X���b�g
	 */
	void resetButtonSlot();

protected:





//    void fileOpen();


private:
	QPushButton *_activeButton;
	QPushButton *_deactiveButton;
	QPushButton *_resetButton;
	BaseWidget _ECCombox;
};

#endif // TEXTEDIT_H
