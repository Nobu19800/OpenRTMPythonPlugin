

#ifndef PYTHONEDITOR_H
#define PYTHONEDITOR_H

#include <QTextEdit>

QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
class QPrinter;
QT_END_NAMESPACE

class PythonEditor : public QTextEdit
{
    Q_OBJECT

public:
    PythonEditor(QWidget *parent = 0);

	void setFontSize(const int s);
	static const int tab_keywords_size;
	static const char *tab_keywords[];
public Q_SLOTS:
//    void fileNew();

protected:
	void insertFromMimeData(const QMimeData * source) override;

	void keyPressEvent(QKeyEvent *) override;



//    void fileOpen();


private:
	void createFont(const int fontSize, const int wrapColumn);
	int fontSize;
	int wrapColumn;


};

#endif // TEXTEDIT_H
