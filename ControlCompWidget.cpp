

#include <QAction>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QSignalMapper>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QDebug>
#include <QGroupBox>
#include <QTextCodec>

#include <iostream>



#include "ControlCompWidget.h"
#include "gettext.h"



ControlCompWidget::ControlCompWidget(QWidget *parent)
	: BaseTab(parent)
{


	_ECCombox = addCombox("ECCombox", _("Execution Context"), QVector<QString>(), QVector<QString>({ "0" }), "0");

	_activeButton = new QPushButton(_("Activate"));
	QObject::connect(_activeButton, SIGNAL(clicked()),this, SLOT(activeButtonSlot()));

	subLayouts.back()->addWidget(_activeButton);
	subLayouts.back()->addStretch();


	_deactiveButton = new QPushButton(_("Deactivate"));
	QObject::connect(_deactiveButton, SIGNAL(clicked()),this, SLOT(deactiveButtonSlot()));

	subLayouts.back()->addWidget(_deactiveButton);
	subLayouts.back()->addStretch();


	_resetButton = new QPushButton(_("Reset"));
	QObject::connect(_resetButton, SIGNAL(clicked()),this, SLOT(resetButtonSlot()));

	subLayouts.back()->addWidget(_resetButton);
	subLayouts.back()->addStretch();
}


int ControlCompWidget::getECNum()
{
	return _ECCombox.getItemText().toInt();
}

void ControlCompWidget::activeButtonSlot()
{
	sigActiveButton();
}

void ControlCompWidget::deactiveButtonSlot()
{
	sigDeactiveButton();
}

void ControlCompWidget::resetButtonSlot()
{
	sigResetButton();
}