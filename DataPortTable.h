

#ifndef DATAPORTTABLE_H
#define DATAPORTTABLE_H


#include <QWidget>
#include <QTableWidget>

#include "RTC_XML.h"




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





class DataPortTable : public QTableWidget
{
    Q_OBJECT

public:
	DataPortTable();
	void list_update(QVector<RTC_XML::DataPorts> ports);
public Q_SLOTS:
//    void fileNew();

protected:





//    void fileOpen();


private:

	

};

#endif // TEXTEDIT_H
