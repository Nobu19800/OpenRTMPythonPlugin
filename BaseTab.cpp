

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



#include "BaseTab.h"



BaseTab::BaseTab(QWidget *parent)
    : QWidget(parent)
{

	mainLayout = new QVBoxLayout();
	setLayout(mainLayout);
	subLayouts.append(new QVBoxLayout());
	mainLayout->addLayout(subLayouts[subLayouts.size()-1]);
}



BaseWidget BaseTab::apendWidget(QWidget *wid, QString name, QString label, WidgetType t)
{
	QGroupBox *widget = new QGroupBox(label);
	QVBoxLayout *layout = new QVBoxLayout();
	widget->setLayout(layout);

	layout->addWidget(wid);
	subLayouts.back()->addWidget(widget);
	subLayouts.back()->addStretch();


	WidList[name] = BaseWidget(wid, layout, t);

	return WidList[name];
}




BaseWidget BaseTab::addCombox(QString name, QString label, QVector<QString> value, QVector<QString> ls, QString default_s)
{
	QComboBox *wid_combo = new QComboBox();
	QWidget *wid = wid_combo;
	

	for(QVector<QString>::iterator it = ls.begin();it != ls.end(); ++it)
	{
		wid_combo->addItem(*it);
	}

	if(!value.isEmpty())
	{
		if(!value[0].isEmpty())
		{
			wid_combo->setCurrentIndex(wid_combo->findText(value[0]));
		}
		else
		{
			wid_combo->setCurrentIndex(wid_combo->findText(default_s));
		}
	}
	else
	{
		wid_combo->setCurrentIndex(wid_combo->findText(default_s));
	}

	BaseWidget wl = apendWidget(wid, name, label, Combox);

	return wl;


}



BaseWidget BaseTab::addTextBox(QString name, QString label, QVector<QString> value, QString default_s)
{
	QLineEdit *wid_line = new QLineEdit();
	QWidget *wid = wid_line;
	

	

	if(value.isEmpty())
	{
		wid_line->setText(default_s);
	}
	else if(value[0].isEmpty())
	{
		wid_line->setText(default_s);
	}
	else
	{
		wid_line->setText(value[0]);
	}

	BaseWidget wl = apendWidget(wid, name, label, TextBox);

	return wl;


}


void BaseWidget::setText(QString text)
{
	QLineEdit *wid = dynamic_cast<QLineEdit*>(_widget);
	if (wid != NULL)
	{
		wid->setText(text);
	}
}


QString BaseWidget::getText()
{
	QLineEdit *wid = dynamic_cast<QLineEdit*>(_widget);
	if (wid != NULL)
	{
		return wid->text();
	}
	return "";
}
QString BaseWidget::getItemText()
{
	QComboBox *wid = dynamic_cast<QComboBox*>(_widget);
	if (wid != NULL)
	{
		return wid->currentText();
	}
	return "";
}