/*!
 * @file  DataPortTable.h
 * @brief �f�[�^�|�[�g�ꗗ�\���N���X
 *
 */


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





/**
 * @class DataPortTable
 * @brief �f�[�^�|�[�g�ꗗ�\���E�B�W�F�b�g
 */
class DataPortTable : public QTableWidget
{
    Q_OBJECT

public:
	/**
	 * @brief �R���X�g���N�^
	 */
	DataPortTable();
	/**
	 * @brief ���X�g�X�V
	 * @param ports �f�[�^�|�[�g�ꗗ
	 */
	void list_update(QVector<RTC_XML::DataPorts> ports);
public Q_SLOTS:
//    void fileNew();

protected:





//    void fileOpen();


private:

	

};

#endif // TEXTEDIT_H
