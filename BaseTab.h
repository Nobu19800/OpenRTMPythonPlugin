

#ifndef BASETAB_H
#define BASETAB_H

#include <QMap>
#include <QWidget>



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


enum WidgetType
{
	TextBox = 1,
	Combox = 2,
	TextCombox = 3,
	SpinBox = 4,
	DoubleSpinBox = 5
};

class BaseWidget
{
public:
	BaseWidget(QWidget *widget=NULL, QLayout *layout = NULL, WidgetType t= TextBox)
	: _widget(widget),
	  _layout(layout),
	  _type(t)
	{
		
	};
	QWidget *_widget;
	QLayout *_layout;
	WidgetType _type;

	void setText(QString text);
	QString getText();
	QString getItemText();
};


class BaseTab : public QWidget
{
    Q_OBJECT

public:
    BaseTab(QWidget *parent = 0);


	BaseWidget apendWidget(QWidget *wid, QString name, QString label, WidgetType t=TextBox);
	BaseWidget addCombox(QString name, QString label, QVector<QString> value, QVector<QString> ls, QString default_s);
	BaseWidget addTextBox(QString name, QString label, QVector<QString> value, QString default_s);
	
public Q_SLOTS:
//    void fileNew();

protected:



//    void fileOpen();


protected:

	QVBoxLayout *mainLayout;
	QMap<QString, BaseWidget> WidList;
	QVector<QVBoxLayout*> subLayouts;
	int widNum;
	
	

};

#endif // TEXTEDIT_H
