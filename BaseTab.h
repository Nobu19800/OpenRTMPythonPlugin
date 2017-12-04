/*!
 * @file  BaseTab.h
 * @brief �^�u�̊�{�N���X
 *
 */


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

/**
 * @enum WidgetType
 * @brief �E�B�W�F�b�g�̎�ʈꗗ
 */
enum WidgetType
{
	TextBox = 1,
	Combox = 2,
	TextCombox = 3,
	SpinBox = 4,
	DoubleSpinBox = 5
};

/**
 * @class BaseWidget
 * @brief �E�B�W�F�b�g�i�[�N���X
 */
class BaseWidget
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param widget �E�B�W�F�b�g
	 * @param layout ���C�A�E�g
	 * @param t �E�B�W�F�b�g���
	 */
	BaseWidget(QWidget *widget=NULL, QLayout *layout = NULL, WidgetType t= TextBox);
	QWidget *_widget;
	QLayout *_layout;
	WidgetType _type;

	/**
	 * @brief ���C���e�L�X�g�{�b�N�X�Ƀe�L�X�g�ݒ�
	 * @param text �e�L�X�g
	 */
	void setText(QString text);
	/**
	 * @brief ���C���e�L�X�g�{�b�N�X�̃e�L�X�g�擾
	 * @return �e�L�X�g
	 */
	QString getText();
	/**
	 * @brief �R���{�{�b�N�X�̃e�L�X�g�擾
	 * @return �e�L�X�g
	 */
	QString getItemText();
};

/**
 * @class BaseTab
 * @brief �^�u�̃x�[�X�N���X
 */
class BaseTab : public QWidget
{
    Q_OBJECT

public:
	/**
	 * @brief �R���X�g���N�^
	 * @param parent �e�E�B�W�F�b�g
	 */
	BaseTab(QWidget *parent = 0);

	/**
	 * @brief �E�B�W�F�b�g�ǉ�
	 * @param wid �ǉ��E�B�W�F�b�g
	 * @param name ���O
	 * @param label ���x����
	 * @param t �E�B�W�F�b�g�̎��
	 * @return �E�B�W�F�b�g�i�[�N���X
	 */
	BaseWidget apendWidget(QWidget *wid, QString name, QString label, WidgetType t=TextBox);
	/**
	 * @brief �R���{�{�b�N�X�ǉ�
	 * @param name ���O
	 * @param label ���x����
	 * @param value �����̒l
	 * @param ls �A�C�e�����X�g
	 * @param default_s �f�t�H���g�l
	 * @return �E�B�W�F�b�g�i�[�N���X
	 */
	BaseWidget addCombox(QString name, QString label, QVector<QString> value, QVector<QString> ls, QString default_s);
	/**
	 * @brief ���C���e�L�X�g�{�b�N�X�ǉ�
	 * @param name ���O
	 * @param label ���x����
	 * @param value �����̒l
	 * @param default_s �f�t�H���g�l
	 * @return �E�B�W�F�b�g�i�[�N���X
	 */
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
