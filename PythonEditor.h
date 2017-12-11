/*!
 * @file  PythonEditor.h
 * @brief Python�p�G�f�B�^
 *
 */

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

/**
 * @class PythonEditor
 * @brief Python�p�G�f�B�^
 */
class PythonEditor : public QTextEdit
{
    Q_OBJECT

public:
	/**
	 * @brief �R���X�g���N�^
	 * @param parent �e�E�B�W�F�b�g
	 */
	PythonEditor(QWidget *parent = Q_NULLPTR);

	/**
	 * @brief �t�H���g�T�C�Y�ݒ�
	 * @param s �t�H���g�T�C�Y
	 */
	void setFontSize(const int s);
	static const int tab_keywords_size;
	static const char *tab_keywords[];
public Q_SLOTS:
//    void fileNew();

protected:
	/**
	 * @brief 
	 * @param source 
	 */
	void insertFromMimeData(const QMimeData * source) override;
	/**
	 * @brief �L�[�������̃C�x���g
	 * @param e �C�x���g���e  
	 */
	void keyPressEvent(QKeyEvent *) override;



//    void fileOpen();


private:
	/**
	 * @brief �t�H���g�ݒ�
	 * @param fontSize �t�H���g�T�C�Y
	 * @param wrapColumn �s�̕�����
	 */
	void createFont(const int fontSize, const int wrapColumn);
	int fontSize;
	int wrapColumn;


};

#endif // TEXTEDIT_H
