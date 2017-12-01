

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





class ControlCompWidget : public BaseTab
{
    Q_OBJECT

public:
	ControlCompWidget(QWidget *parent = 0);

	int getECNum();
	cnoid::Signal<void()>  sigActiveButton;
	cnoid::Signal<void()>  sigDeactiveButton;
	cnoid::Signal<void()>  sigResetButton;

	


public Q_SLOTS:
	void activeButtonSlot();
	void deactiveButtonSlot();
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
