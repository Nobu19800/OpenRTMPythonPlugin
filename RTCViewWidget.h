

#ifndef RTCVIEWWIDGET_H
#define RTCVIEWWIDGET_H

#include <QMap>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QDialog>
#include <cnoid/Signal>

#include "BaseTab.h"
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
class QRectF;
class QGraphicsScene;
class QGraphicsView;
QT_END_NAMESPACE


class RenderRTC;
class RenderRTCRTP;
class RenderPath;
class GraphicsView;
class RTCViewWidget;
class RTC_MainWindow;
class DataPortRTP;
class DataPortDialog;
class ServicePortRTP;
class ServicePortDialog;



class RenderPath : public QObject, public QGraphicsItem
{

public:
    RenderPath(QGraphicsScene* scene, QWidget *parent);
	RenderPath(const RenderPath &obj);

	void setPath(QPainterPath path);
	void setFillRule(Qt::FillRule rule);
	void setFillGradient(QColor color1, QColor color2);
	void setPenWidth(int width);
	void setPenColor(QColor color);
	void setRotationAngle(int degrees);
	void setCenterPoint(int x, int y);
	void setPosition(int x, int y);
	void setSize(int width, int height);
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void updatePaint(QPainter *painter);

public Q_SLOTS:
//    void fileNew();

protected:





protected:

	QPainterPath _path;
	int _penWidth;
	int _rotationAngle;
	int _pos_x;
	int _pos_y;
	int _width;
	int _height;
	QColor _fillColor1;
	QColor _fillColor2;
	QColor _penColor;
	int _centerPoint_x;
	int _centerPoint_y;
	

};


class RTCViewWidgetBase: public QWidget
{
	Q_OBJECT
public:
	RTCViewWidgetBase(QWidget *parent = 0);
	RenderRTC *getRenderRTC();
protected:
	QGraphicsScene *_scene;
	QVBoxLayout *_mainLayout;
	GraphicsView *_view;
	RenderRTC *_renderWindow;
};

class RTCViewWidget : public RTCViewWidgetBase
{
	Q_OBJECT
public:
	RTCViewWidget(RTC_XML::RTC_Profile* profile, QWidget *parent = 0);
protected:



};

class RTCViewWidgetRTP : public RTCViewWidget
{
	Q_OBJECT
public:
	RTCViewWidgetRTP(RTC_XML::RTC_ProfileRTP* comp, QWidget *parent = 0);
	
	RenderRTCRTP* getRenderRTC();
private:

};


class GraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	GraphicsView(QGraphicsScene * scene, QWidget * parent = 0);
};

class Port : public RenderPath
{
	Q_OBJECT
public:
	Port(int defsize, QGraphicsScene* scene, QWidget* parent = 0);
	Port(const Port &obj);
	void setBoxSize(int size);
	virtual QPainterPath getPath() = 0;
	enum PortDir
	{
		PORT_LEFT,
		PORT_RIGHT,
		PORT_TOP,
		PORT_BOTTOM
	};
	PortDir _position;
	int _size;
protected:


};

class ServicePortWidget : public BaseTab
{
	Q_OBJECT
public:
	ServicePortWidget(ServicePortRTP *sport, ServicePortDialog *dialog, QWidget * parent = 0);
	BaseWidget _portNameTextbox;
	BaseWidget _interfaceNameTextbox;
	BaseWidget _dinterfaceDirCombox;
	BaseWidget _interfaceDirCombox;
	BaseWidget _IDLTextbox;
	BaseWidget _interfaceTypeCombox;
	BaseWidget _IDLPathTextbox;
private Q_SLOTS :
	void deleteButtonSlot();

private:
	ServicePortDialog *_dialog;
	QPushButton *_deleteButton;
};


class ServicePortDialog : public QDialog
{
	Q_OBJECT
public:
	ServicePortDialog(ServicePortRTP *sport, QWidget * parent = 0);
};


class ServicePort : public Port
{
	Q_OBJECT
public:
	ServicePort(RTC_XML::ServicePorts profile, int defsize, QGraphicsScene* scene, QWidget* parent = 0);
	virtual QPainterPath getPath();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	RTC_XML::ServicePorts _profile;
protected:
	QPainterPath _rectPath;
};


class ServicePortRTP : public ServicePort
{
	Q_OBJECT
public:
	ServicePortRTP(RTC_XML::ServicePorts profile, int size, QGraphicsScene* scene, RTC_MainWindow *mainwindow, QWidget* parent = 0);
protected:
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
private:
	RTC_MainWindow *_mainwindow;
};


class DataPortWidget : public BaseTab
{
	Q_OBJECT
public:
	DataPortWidget(DataPortRTP *dport, DataPortDialog *dialog, QWidget * parent = 0);
	BaseWidget _portNameTextbox;
	BaseWidget _portTypeCombox;
	BaseWidget _dataTypeCombox;
private Q_SLOTS :
	void deleteButtonSlot();

private:
	DataPortDialog *_dialog;
	QPushButton *_deleteButton;


};


class DataPortDialog : public QDialog
{
	Q_OBJECT
public:
	DataPortDialog(DataPortRTP *dport, QWidget * parent = 0);
};


class DataPort : public Port
{
	Q_OBJECT
public:
	DataPort(RTC_XML::DataPorts profile, int defsize, QGraphicsScene* scene, QWidget* parent = 0);
	DataPort(const DataPort &obj);
	virtual QPainterPath getPath();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	RTC_XML::DataPorts _profile;
protected:
	QPainterPath _rectPath;

};

class DataPortRTP : public DataPort
{
	Q_OBJECT
public:
	DataPortRTP(RTC_XML::DataPorts profile, int size, QGraphicsScene* scene, RTC_MainWindow *mainwindow, QWidget* parent = 0);
protected:
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
private:
	RTC_MainWindow *_mainwindow;
};


class RenderRTC : public RenderPath
{
public:
	RenderRTC(QGraphicsScene* scene,  RTC_XML::RTC_Profile* comp, QWidget* parent=0);
	void setRTC();
	virtual void addDataPort(RTC_XML::DataPorts profile);
	virtual void addServicePort(RTC_XML::ServicePorts profile);
	virtual void removePort(QString name);
	virtual void removeAllPort();
	virtual void load(RTC_XML::RTC_Profile* comp);
	const int def_size_x = 50;
	const int def_size_y = 10;
	int getPortNum();
	
	int _penWidth;
	int _rotationAngle;
	int _centerPoint_x;
	int _centerPoint_y;
	int _pos_x;
	int _pos_y;
	int _width;
	int _height;
	int _port_size;

	QMap <QString, Port*> _ports;
private:
	RTC_XML::RTC_Profile* _comp_base;
	//QMap <QString, QString> _config_params;
};


class RenderRTCRTP : public RenderRTC
{
	Q_OBJECT
public:
	RenderRTCRTP(QGraphicsScene* scene, RTC_MainWindow *mainwindow, RTC_XML::RTC_ProfileRTP* comp, QWidget* parent = 0);
	virtual void addDataPort(RTC_XML::DataPorts profile);
	virtual void addServicePort(RTC_XML::ServicePorts profile);
	RTC_MainWindow *_mainwindow;
	cnoid::Signal<void(RTC_XML::RTC_ProfileRTP::RTC_State&)>  updateStatus;
private Q_SLOTS :
	void check_rtc();
private:
	QTimer *_timer;
	RTC_XML::RTC_ProfileRTP* _comp;
	RTC_XML::RTC_ProfileRTP::RTC_State current_state;
};

#endif