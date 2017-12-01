

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





class ActivityTab : public BaseTab
{
    Q_OBJECT

public:
	ActivityTab(ActivityCode name, QString text, QWidget *parent = 0);
	ActivityTab(QString name, QString text, QWidget *parent = 0);

	QString getText();
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
