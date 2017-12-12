/*!
 * @file  RTCViewWidget.cpp
 * @brief RTC表示ウィジェット
 *
 */

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
#include <QTimer>

#include <iostream>
#include <cnoid/MessageView>



#include "RTCViewWidget.h"
#include "CreateDataObject.h"
#include "RTC_MainWindow.h"

#include "gettext.h"


/**
 * @brief コンストラクタ
 * @param scene シーンオブジェクト
 * @param parent 親ウィジェット
 */
RenderPath::RenderPath(QGraphicsScene* scene, QWidget *parent)
    : QGraphicsItem(),
	_penWidth(1),
	_rotationAngle(0),
	_pos_x(0),
	_pos_y(0),
	_width(0),
	_height(0)
{
	
	QColor color("black");
	setPenColor(color);
	QColor color1("black");
	QColor color2("black");
	setFillGradient(color1, color2);
	scene->addItem(this);
}

/**
 * @brief コピーコンストラクタ
 * @param obj コピー元
 */
RenderPath::RenderPath(const RenderPath &obj)
{
	_penWidth = obj._penWidth;
	_rotationAngle = obj._rotationAngle;
	_pos_x = obj._pos_x;
	_pos_y = obj._pos_y;
	_width = obj._width;
	_height = obj._height;
}

/**
 * @brief 描画パス設定
 * @param path 描画パス設定
 */
void RenderPath::setPath(QPainterPath path)
{
	_path = path;
}

/**
 * @brief FillRuleの設定
 * @param rule FillRule
 */
void RenderPath::setFillRule(Qt::FillRule rule)
{
	_path.setFillRule(rule);
}

/**
 * @brief FillGradientの設定
 * @param color1 
 * @param color2 
 */
void RenderPath::setFillGradient(QColor color1, QColor color2)
{
	_fillColor1 = color1;
	_fillColor2 = color2;
}

/**
 * @brief ペン太さの設定
 * @param width 太さ
 */
void RenderPath::setPenWidth(int width)
{
	_penWidth = width;
}

/**
 * @brief ペンの色設定
 * @param color 色
 */
void RenderPath::setPenColor(QColor color)
{
	_penColor = color;
}

/**
 * @brief 回転角度設定
 * @param degrees 角度
 */
void RenderPath::setRotationAngle(int degrees)
{
	_rotationAngle = degrees;
}

/**
 * @brief 中心位置設定
 * @param x 位置(X)
 * @param y 位置(Y)
 */
void RenderPath::setCenterPoint(int x, int y)
{
	_centerPoint_x = x;
	_centerPoint_y = y;
}

/**
 * @brief 位置設定
 * @param x 位置(X)
 * @param y 位置(Y)
 */
void RenderPath::setPosition(int x, int y)
{
	_pos_x = x;
	_pos_y = y;
}

/**
 * @brief サイズ設定
 * @param width 幅
 * @param height 高さ
 */
void RenderPath::setSize(int width, int height)
{
	_width = width;
	_height = height;
}

/**
 * @brief 矩形取得
 * @param obj コピー元
 */
QRectF RenderPath::boundingRect() const
{
	int pos_x = _pos_x*scene()->width() / 100.0;
	int pos_y = _pos_y*scene()->height() / 100.0;

	int width = _width*scene()->width() / 100.0;
	int height = _height*scene()->height() / 100.0;

	if (width < 0)
	{
		pos_x += width;
		width = -width;
	}

	if (height < 0)
	{
		pos_y += height;
		height = -height;
	}
	//std::cout << pos_x << "\t" << pos_y << "\t" << width << "\t" << height << std::endl;
	//std::cout << _width*scene()->width() << "\t" << _height*scene()->height() << std::endl;
	return QRectF(pos_x, pos_y, width, height);
}

/**
 * @brief 描画実行
 * @param painter 
 * @param option 
 * @param widget 
 */
void RenderPath::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	updatePaint(painter);
}

/**
 * @brief 描画更新
 * @param painter 
 */
void RenderPath::updatePaint(QPainter *painter)
{
	painter->setRenderHint(QPainter::Antialiasing);
	painter->scale(scene()->width() / 100.0, scene()->height() / 100.0);
	painter->translate(_centerPoint_x, _centerPoint_y);
	painter->rotate(-_rotationAngle);
	painter->translate(-_centerPoint_x, -_centerPoint_y);

	painter->translate(_pos_x, _pos_y);

	painter->setPen(QPen(_penColor, _penWidth,
		Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	QLinearGradient gradient(0, 0, 0, 100);
	gradient.setColorAt(0.0, _fillColor1);
	gradient.setColorAt(1.0, _fillColor2);
	painter->setBrush(QBrush(gradient));
	painter->drawPath(_path);

	

}

/**
 * @brief コンストラクタ
 * @param parent 親ウィジェット
 */
RTCViewWidgetBase::RTCViewWidgetBase(QWidget *parent)
	: QWidget(parent)
{
	_scene = new QGraphicsScene(0, 0, 600, 600);
	_mainLayout = new QVBoxLayout();
	setLayout(_mainLayout);
	_view = new GraphicsView(_scene);
	_view->scale(0.25, 0.25);
	_view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	_view->setBackgroundBrush(QColor(255, 255, 255));
	_mainLayout->addWidget(_view);
}

/**
 * @brief コンストラクタ
 * @param profile RTCプロファイル
 * @param parent 親ウィジェット
 */
RTCViewWidget::RTCViewWidget(RTC_XML::RTC_Profile* profile,  QWidget *parent) :
	RTCViewWidgetBase(parent)
{

	//_renderWindow = RenderRTC(NULL, _scene, this->parent());
	_renderWindow = new RenderRTC(_scene, profile, this);
	_scene->update();
}

/**
 * @brief コンストラクタ
 * @param comp RTCプロファイル
 * @param parent 親ウィジェット
 */
RTCViewWidgetRTP::RTCViewWidgetRTP(RTC_XML::RTC_ProfileRTP* profile, QWidget *parent)
	: RTCViewWidget(profile, parent)
{
	_renderWindow = new RenderRTCRTP(_scene, (RTC_MainWindow*)this->parent(), profile);
	_scene->update();
}


/**
 * @brief コンストラクタ
 * @param scene シーンオブジェクト
 * @param parent 親ウィジェット
 */
GraphicsView::GraphicsView(QGraphicsScene * scene, QWidget * parent):
	QGraphicsView(scene, parent)
{

}

/**
 * @brief コンストラクタ
 * @param scene シーンオブジェクト
 * @param comp RTCプロファイル
 * @param parent 親ウィジェット
 */
RenderRTC::RenderRTC(QGraphicsScene* scene, RTC_XML::RTC_Profile* comp, QWidget* parent)
	: RenderPath(scene, parent),
	_port_size(10),
	_comp_base(comp)
{
	

	//this->scene()->update();
	//setRTC();
	load(_comp_base);

}

/**
 * @brief RTC描画設定更新
 */
void RenderRTC::setRTC()
{
	int num = getPortNum();
	int size_x = def_size_x;
	int size_y = def_size_y + _port_size*2*num;
	int pos_x = (100 - size_x) / 2;
	int pos_y = (100 - size_y) / 2;

	double l_num = 0.5;
	double r_num = 0.5;

	

	for (QMap<QString, Port*>::iterator itr = _ports.begin(); itr != _ports.end(); itr++)
	{
		if ((*itr)->_position == Port::PORT_LEFT)
		{
		
			(*itr)->setPosition(pos_x, pos_y+size_y/num*l_num - (*itr)->_size/2);
			l_num += 1.0;

		}
		else if ((*itr)->_position == Port::PORT_RIGHT)
		{
			(*itr)->setPosition(pos_x + size_x, pos_y + size_y / num*r_num - (*itr)->_size / 2);
			r_num += 1.0;
		}
	}

	setPosition(pos_x, pos_y);
	setSize(size_x, size_y);


	_path = QPainterPath();
	_path.moveTo(0, 0);
	_path.lineTo(size_x, 0);
	_path.lineTo(size_x, size_y);
	_path.lineTo(0, size_y);
	_path.closeSubpath();
}

/**
 * @brief データポート追加
 * @param profile データポートプロファイル
 */
void RenderRTC::addDataPort(RTC_XML::DataPorts profile)
{
	
	DataPort *dp = new DataPort(profile, _port_size, scene());
	dp->setBoxSize(_port_size);

	_ports[profile.get_name()] = dp;
	/*std::cout << profile._properties["name"].toStdString() << std::endl;
	for (int i = 0; i < profile._properties.keys().size(); i++)
	{
		std::cout << profile._properties.keys()[i].toStdString() << std::endl;
		std::cout << profile._properties[profile._properties.keys()[i]].toStdString() << std::endl;
	}*/
	

	setRTC();
	scene()->update();
}

/**
 * @brief サービスポート追加
 * @param profile サービスポートプロファイル
 */
void RenderRTC::addServicePort(RTC_XML::ServicePorts profile)
{
	ServicePort *sp = new ServicePort(profile, _port_size, scene());
	sp->setBoxSize(_port_size);

	_ports[profile.get_name()] = sp;


	setRTC();
	scene()->update();
}

/**
 * @brief ポート削除
 * @param name ポート名
 */
void RenderRTC::removePort(QString name)
{
	if (_ports.keys().indexOf(name) >= 0)
	{
		scene()->removeItem(_ports[name]);
		_ports.remove(name);
		setRTC();
		scene()->update();
	}
}

/**
 * @brief 全ポート削除
 */
void RenderRTC::removeAllPort()
{
	for (QMap <QString, Port*>::iterator itr = _ports.begin(); itr != _ports.end(); itr++)
	{
		scene()->removeItem((*itr));
	}
	_ports.clear();

	setRTC();
	scene()->update();

}

/**
 * @brief ポート総数取得
 * @return ポート総数
 */
int RenderRTC::getPortNum()
{
	int l_count = 0;
	int r_count = 0;

	for (QMap<QString, Port*>::iterator itr = _ports.begin(); itr != _ports.end(); itr++)
	{
		if ((*itr)->_position == Port::PORT_LEFT)
		{
			l_count += 1;
		}
		else if ((*itr)->_position == Port::PORT_RIGHT)
		{
			r_count += 1;
		}
	}
	if (l_count > r_count)
	{
		return l_count;
	}
	else
	{
		return r_count;
	}
}

/**
 * @brief RTCプロファイル設定
 * @param comp RTCプロファイル
 */
void RenderRTC::load(RTC_XML::RTC_Profile* comp)
{
	removeAllPort();

	QVector<RTC_XML::DataPorts> data_ports = comp->get_dataports();
	for (QVector<RTC_XML::DataPorts>::iterator itr = data_ports.begin(); itr != data_ports.end(); itr++)
	{
		addDataPort((*itr));
	}

	QVector<RTC_XML::ServicePorts> svc_ports = comp->get_svcports();
	for (QVector<RTC_XML::ServicePorts>::iterator itr = svc_ports.begin(); itr != svc_ports.end(); itr++)
	{
		addServicePort((*itr));
	}

	QVector<RTC_XML::ConfigurationSet> configsets = comp->get_confsets();
	for (QVector<RTC_XML::ConfigurationSet>::iterator itr = configsets.begin(); itr != configsets.end(); itr++)
	{
		//addDataPort((*itr));
	}
}

/**
 * @brief コンストラクタ
 * @param mainwindow RTCメインウインドウ
 * @param scene シーンオブジェクト
 * @param comp RTCプロファイル
 * @param parent 親ウィジェット
 */
RenderRTCRTP::RenderRTCRTP(QGraphicsScene* scene, RTC_MainWindow *mainwindow, RTC_XML::RTC_ProfileRTP* comp, QWidget* parent)
	: RenderRTC(scene, comp, parent),
	current_state(RTC_XML::RTC_ProfileRTP::RTP_Created),
	_comp(comp)
{
	_mainwindow = mainwindow;
	

	/*
	RTC_XML::RTC_Profile prof;
	prof.loadXML("RTC.xml");
	
	//addDataPort(prof._dataports[0]);
	
	//std::cout << prof._svrports.size() << std::endl;
	addServicePort(prof._svrports[0]);
	*/
	_timer = new QTimer();
	_timer->setInterval(100);
	QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(check_rtc()));
	_timer->start();
	
}

/**
 * @brief データポート追加
 * @param profile データポートプロファイル
 */
void RenderRTCRTP::addDataPort(RTC_XML::DataPorts profile)
{

	DataPortRTP *dp = new DataPortRTP(profile, _port_size, scene(), _mainwindow);
	dp->setBoxSize(_port_size);

	_ports[profile.get_name()] = dp;


	setRTC();
	scene()->update();
}

/**
 * @brief サービスポート追加
 * @param profile サービスポートプロファイル
 */
void RenderRTCRTP::addServicePort(RTC_XML::ServicePorts profile)
{
	
	ServicePortRTP *sp = new ServicePortRTP(profile, _port_size, scene(), _mainwindow);
	
	sp->setBoxSize(_port_size);
	
	_ports[profile.get_name()] = sp;


	setRTC();
	scene()->update();
	
	
}

/**
 * @brief コンストラクタ
 * @param defsize デフォルトサイズ
 * @param scene シーンオブジェクト
 * @param parent 親ウィジェット
 */
Port::Port(int defsize, QGraphicsScene* scene, QWidget* parent)
	: RenderPath(scene, parent)
{
	_size = defsize;
}

/**
 * @brief コピーコンストラクタ
 * @param obj コピー元
 */
Port::Port(const Port &obj)
	: RenderPath(obj)
{

}

/**
 * @brief サイズ設定
 * @param size サイズ
 */
void Port::setBoxSize(int size)
{
	_size = size;
	QPainterPath path = getPath();
	setPath(path);
}


/**
 * @brief コンストラクタ
 * @param dport データポート描画オブジェクト
 * @param dialog データポート編集ダイアログ
 * @param parent 親ウィジェット
 */
DataPortWidget::DataPortWidget(DataPortRTP *dport, DataPortDialog *dialog, QWidget * parent)
	: BaseTab(parent)
{
	_dialog = dialog;
	QList<QString> key_list = dataTypeList.keys();
	key_list.sort();

	QVector<QString> key_vec = QVector<QString>::fromList(key_list);
	_portNameTextbox = addTextBox("portNameTextbox", _("Port Name"), QVector<QString>(), dport->_profile.get_name());
	_portTypeCombox = addCombox("portTypeCombox", _("Port Type"), QVector<QString>(), QVector<QString>({ "DataOutPort", "DataInPort" }), dport->_profile.get_portType());
	_dataTypeCombox = addCombox("dataTypeCombox ", _("Data Type"), QVector<QString>(), key_vec, dport->_profile.get_type());
	//std::cout << dport->_profile.get_type().toStdString() << std::endl;

	_deleteButton = new QPushButton(_("Create"));
	QObject::connect(_deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonSlot()));

	subLayouts.back()->addWidget(_deleteButton);
	mainLayout->addStretch();
}

/**
 * @brief 削除ボタン押下時スロット
 */
void DataPortWidget::deleteButtonSlot()
{
	_dialog->accept();
}


/**
 * @brief コンストラクタ
 * @param dport データポート描画オブジェクト
 * @param parent 親ウィジェット
 */
DataPortDialog::DataPortDialog(DataPortRTP *dport, QWidget * parent)
{
	setWindowTitle(_("Edit DataPort Dialog"));
	QVBoxLayout *mainLayout = new QVBoxLayout();
	setLayout(mainLayout);
	DataPortWidget *dpwidget = new DataPortWidget(dport, this, parent);
	mainLayout->addWidget(dpwidget);



}


/**
 * @brief コンストラクタ
 * @param profile データポートプロファイル
 * @param defsize デフォルトサイズ
 * @param scene シーンオブジェクト
 * @param parent 親ウィジェット
 */
DataPort::DataPort(RTC_XML::DataPorts profile, int defsize, QGraphicsScene* scene, QWidget* parent)
	:Port(defsize, scene, parent)
{
	_rectPath = getPath();
	QColor color("black");
	setPenColor(color);
	_profile = profile;

	QColor color1("yellow");
	QColor color2("yellow");

	setFillGradient(color1, color2);

	setCenterPoint(0, 0);

}

/**
 * @brief コピーコンストラクタ
 * @param obj コピー元
 */
DataPort::DataPort(const DataPort &obj)
	: Port(obj)
{
	_rectPath = obj._rectPath;

}

/**
 * @brief 描画パス取得
 * @return 描画パス
 */
QPainterPath DataPort::getPath()
{
	QPainterPath rectPath;
	/*int spx = _pos_x;
	int spy = _pos_y;
	int epx = _pos_x;
	int epy = _pos_y;
	int cofx = 0;
	int cofy = 0;*/
	
	if (_profile.get_portType() == "DataInPort")
	{
		rectPath.moveTo(0, 0);
		rectPath.lineTo(-_size, 0);
		rectPath.lineTo(-_size/2.0, _size/2.0);
		rectPath.lineTo(-_size, _size);
		rectPath.lineTo(0, _size);
		rectPath.closeSubpath();

		_position = PORT_LEFT;
		_width = -_size;
		_height = _size;
	}
	else if(_profile.get_portType() == "DataOutPort")
	{
		rectPath.moveTo(0, 0);
		rectPath.lineTo(_size, _size / 2.0);
		rectPath.lineTo(0, _size);
		rectPath.closeSubpath();

		_position = PORT_RIGHT;
		_width = _size;
		_height = _size;
	}


	
	return rectPath;
}



/**
 * @brief 描画実行
 * @param painter 
 * @param option 
 * @param widget 
 */
void DataPort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	updatePaint(painter);
}


/**
 * @brief コンストラクタ
 * @param profile データポートプロファイル
 * @param defsize デフォルトサイズ
 * @param scene シーンオブジェクト
 * @param mainwindow RTCEditorメインウインドウ
 * @param parent 親ウィジェット
 */
DataPortRTP::DataPortRTP(RTC_XML::DataPorts profile, int size, QGraphicsScene* scene, RTC_MainWindow *mainwindow, QWidget* parent)
	: DataPort(profile, size, scene, parent)
{
	_mainwindow = mainwindow;
	
}

/**
 * @brief マウスダブルクリック時のスロット
 * @param event イベント内容
 */
void DataPortRTP::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	//std::cout << "mouseDoubleClickEvent" << std::endl;
	DataPortDialog dialog(this);
	dialog.show();
	dialog.exec();

	if (dialog.result())
	{

	}

}




/**
 * @brief コンストラクタ
 * @param sport サービスポートプロファイル
 * @param dialog サービスポート設定ダイアログ
 * @param parent 親ウィジェット
 */
ServicePortWidget::ServicePortWidget(ServicePortRTP *sport, ServicePortDialog *dialog, QWidget * parent)
{
	_dialog = dialog;

	_portNameTextbox = addTextBox("portNameTextbox", _("Port Name"), QVector<QString>(), sport->_profile.get_name());
	_interfaceNameTextbox = addTextBox("interfaceName", _("Interface Name"), QVector<QString>(), "");
	_dinterfaceDirCombox = addCombox("interfaceDir ", _("Direction"), QVector<QString>(), QVector<QString>({ "Required","Provided" }), "Required");

	_IDLTextbox = addTextBox("interfaceName", _("IDL File"), QVector<QString>(), "");



	_interfaceTypeCombox = addCombox("interfaceType ", _("Interface type"), QVector<QString>(), QVector<QString>(), "");
	_IDLPathTextbox = addTextBox("IDLPath", _("IDL Path"), QVector<QString>(), "");

	_deleteButton = new QPushButton(_("Create"));
	QObject::connect(_deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonSlot()));

	subLayouts.back()->addWidget(_deleteButton);
	mainLayout->addStretch();

}

/**
 * @brief 削除ボタン押下時スロット
 */
void ServicePortWidget::deleteButtonSlot()
{
	_dialog->accept();
}

/**
 * @brief コンストラクタ
 * @param sport サービスポート描画オブジェクト
 * @param parent 親ウィジェット
 */
ServicePortDialog::ServicePortDialog(ServicePortRTP *sport, QWidget * parent)
{
	setWindowTitle(_("Edit ServicePort Dialog"));
	QVBoxLayout *mainLayout = new QVBoxLayout();
	setLayout(mainLayout);
	ServicePortWidget *dpwidget = new ServicePortWidget(sport, this, parent);
	mainLayout->addWidget(dpwidget);



}



/**
 * @brief コンストラクタ
 * @param profile サービスポートプロファイル
 * @param defsize デフォルトサイズ
 * @param scene シーンオブジェクト
 * @param parent 親ウィジェット
 */
ServicePort::ServicePort(RTC_XML::ServicePorts profile, int defsize, QGraphicsScene* scene, QWidget* parent)
	: Port(defsize, scene, parent)
{
	
	_rectPath = getPath();
	
	QColor color("black");
	setPenColor(color);
	_profile = profile;

	QColor color1("yellow");
	QColor color2("yellow");

	setFillGradient(color1, color2);

	setCenterPoint(0, 0);
	
}

/**
 * @brief 描画パス取得
 * @return 描画パス
 */
QPainterPath ServicePort::getPath()
{
	QPainterPath rectPath;
	
	/*int spx = _pos_x;
	int spy = _pos_y;
	int epx = _pos_x;
	int epy = _pos_y;
	int cofx = 0;
	int cofy = 0;*/
	
	rectPath.moveTo(0, 0);
	rectPath.lineTo(_size, 0);
	rectPath.lineTo(_size, _size);
	rectPath.lineTo(0, _size);
	rectPath.closeSubpath();

	_position = PORT_RIGHT;
	_width = _size;
	_height = _size;
	

	
	return rectPath;
}

/**
 * @brief 描画実行
 * @param painter 
 * @param option 
 * @param widget 
 */
void ServicePort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	updatePaint(painter);
}


/**
 * @brief コンストラクタ
 * @param profile サービスポートプロファイル
 * @param defsize デフォルトサイズ
 * @param scene シーンオブジェクト
 * @param mainwindow RTCEditorメインウインドウ
 * @param parent 親ウィジェット
 */
ServicePortRTP::ServicePortRTP(RTC_XML::ServicePorts profile, int size, QGraphicsScene* scene, RTC_MainWindow *mainwindow, QWidget* parent)
	: ServicePort(profile, size, scene, parent)
{
	_mainwindow = mainwindow;
	

}

/**
 * @brief マウスダブルクリック時のスロット
 * @param event イベント内容
 */
void ServicePortRTP::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	//std::cout << "mouseDoubleClickEvent" << std::endl;
	ServicePortDialog dialog(this);
	dialog.show();
	dialog.exec();

	if (dialog.result())
	{

	}

}

/**
 * @brief 描画RTCオブジェクト取得
 * @return 描画RTCオブジェクト
 */
RenderRTC *RTCViewWidgetBase::getRenderRTC()
{
	return _renderWindow;
}

/**
 * @brief RTC状態確認スロット
 */
void RenderRTCRTP::check_rtc()
{
	//cnoid::MessageView::instance()->putln(0, _("test1"));
	
	/*
	std::cout << "test1" << std::endl;
	static int count = 0;
	count += 1;
	if (count % 20 == 0)
	{
		_comp->setState((RTC_XML::RTC_ProfileRTP::RTC_State)(_comp->getState(0)+1), 0);
	}
	*/
	if (_comp != NULL)
	{
		int ec_num = _mainwindow->_controlCompWidget->getECNum();
		RTC_XML::RTC_ProfileRTP::RTC_State status = RTC_XML::RTC_ProfileRTP::RTP_Created;
		updateStatus(status);
		_comp->setState(status, ec_num);
		RTC_XML::RTC_ProfileRTP::RTC_State state = _comp->getState(ec_num);
		if (current_state != state)
		{
			current_state = state;
			if (state == RTC_XML::RTC_ProfileRTP::RTP_InActive)
			{


				QColor color1("blue");
				QColor color2("blue");

				setFillGradient(color1, color2);

				
			}
			else if (state == RTC_XML::RTC_ProfileRTP::RTP_Acitve)
			{


				QColor color1("lime");
				QColor color2("lime");

				setFillGradient(color1, color2);

				
			}
			else if (state == RTC_XML::RTC_ProfileRTP::RTP_Error)
			{


				QColor color1("red");
				QColor color2("red");

				setFillGradient(color1, color2);

				
			}
			scene()->update();
		}


	}
}

/**
 * @brief 描画RTCオブジェクト取得
 * @return 描画RTCオブジェクト
 */
RenderRTCRTP* RTCViewWidgetRTP::getRenderRTC()
{
	return dynamic_cast<RenderRTCRTP *>(_renderWindow);
	
}