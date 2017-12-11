/*!
 * @file  RTCViewWidget.h
 * @brief RTC�\���E�B�W�F�b�g
 *
 */

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


/**
 * @class RenderPath
 * @brief �}�`�`��x�[�X�I�u�W�F�N�g
 */
class RenderPath : public QObject, public QGraphicsItem
{

public:
	/**
	 * @brief �R���X�g���N�^
	 * @param scene �V�[���I�u�W�F�N�g
	 * @param parent �e�E�B�W�F�b�g
	 */
	RenderPath(QGraphicsScene* scene, QWidget *parent);
	/**
	 * @brief �R�s�[�R���X�g���N�^
	 * @param obj �R�s�[��
	 */
	RenderPath(const RenderPath &obj);
	/**
	 * @brief �`��p�X�ݒ�
	 * @param path �`��p�X�ݒ�
	 */
	void setPath(QPainterPath path);
	/**
	 * @brief FillRule�̐ݒ�
	 * @param rule FillRule
	 */
	void setFillRule(Qt::FillRule rule);
	/**
	 * @brief FillGradient�̐ݒ�
	 * @param color1 
	 * @param color2 
	 */
	void setFillGradient(QColor color1, QColor color2);
	/**
	 * @brief �y�������̐ݒ�
	 * @param width ����
	 */
	void setPenWidth(int width);
	/**
	 * @brief �y���̐F�ݒ�
	 * @param color �F
	 */
	void setPenColor(QColor color);
	/**
	 * @brief ��]�p�x�ݒ�
	 * @param degrees �p�x
	 */
	void setRotationAngle(int degrees);
	/**
	 * @brief ���S�ʒu�ݒ�
	 * @param x �ʒu(X)
	 * @param y �ʒu(Y)
	 */
	void setCenterPoint(int x, int y);
	/**
	 * @brief �ʒu�ݒ�
	 * @param x �ʒu(X)
	 * @param y �ʒu(Y)
	 */
	void setPosition(int x, int y);
	/**
	 * @brief �T�C�Y�ݒ�
	 * @param width ��
	 * @param height ����
	 */
	void setSize(int width, int height);
	/**
	 * @brief ��`�擾
	 * @param obj �R�s�[��
	 */
	QRectF boundingRect() const;
	/**
	 * @brief �`����s
	 * @param painter 
	 * @param option 
	 * @param widget 
	 */
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	/**
	 * @brief �`��X�V
	 * @param painter 
	 */
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

/**
 * @class RTCViewWidgetBase
 * @brief RTC�\���x�[�X�N���X
 */
class RTCViewWidgetBase: public QWidget
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param parent �e�E�B�W�F�b�g
	 */
	RTCViewWidgetBase(QWidget *parent = Q_NULLPTR);
	/**
	 * @brief �`��RTC�I�u�W�F�N�g�擾
	 * @return �`��RTC�I�u�W�F�N�g
	 */
	RenderRTC *getRenderRTC();
protected:
	QGraphicsScene *_scene;
	QVBoxLayout *_mainLayout;
	GraphicsView *_view;
	RenderRTC *_renderWindow;
};

/**
 * @class RTCViewWidget
 * @brief RTC�\���N���X
 */
class RTCViewWidget : public RTCViewWidgetBase
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param profile RTC�v���t�@�C��
	 * @param parent �e�E�B�W�F�b�g
	 */
	RTCViewWidget(RTC_XML::RTC_Profile* profile, QWidget *parent = Q_NULLPTR);
protected:



};

/**
 * @class RTCViewWidgetRTP
 * @brief RTC�\���N���X(���I�ҏW)
 */
class RTCViewWidgetRTP : public RTCViewWidget
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param comp RTC�v���t�@�C��
	 * @param parent �e�E�B�W�F�b�g
	 */
	RTCViewWidgetRTP(RTC_XML::RTC_ProfileRTP* comp, QWidget *parent = Q_NULLPTR);
	/**
	 * @brief �`��RTC�I�u�W�F�N�g�擾
	 * @return �`��RTC�I�u�W�F�N�g
	 */
	RenderRTCRTP* getRenderRTC();
private:

};

/**
 * @class GraphicsView
 * @brief �}�`�\���I�u�W�F�N�g
 */
class GraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param scene �V�[���I�u�W�F�N�g
	 * @param parent �e�E�B�W�F�b�g
	 */
	GraphicsView(QGraphicsScene * scene, QWidget * parent = Q_NULLPTR);
};

/**
 * @class Port
 * @brief Port�`��x�[�X�N���X
 */
class Port : public RenderPath
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param defsize �f�t�H���g�T�C�Y
	 * @param scene �V�[���I�u�W�F�N�g
	 * @param parent �e�E�B�W�F�b�g
	 */
	Port(int defsize, QGraphicsScene* scene, QWidget* parent = Q_NULLPTR);
	/**
	 * @brief �R�s�[�R���X�g���N�^
	 * @param obj �R�s�[��
	 */
	Port(const Port &obj);
	/**
	 * @brief �T�C�Y�ݒ�
	 * @param size �T�C�Y
	 */
	void setBoxSize(int size);
	/**
	 * @brief �`��p�X�擾
	 * @return �`��p�X
	 */
	virtual QPainterPath getPath() = 0;
	/**
	 * @enum PortDir
	 * @brief �|�[�g�����ꗗ
	 */
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

/**
 * @class ServicePortWidget
 * @brief �T�[�r�X�|�[�g�ҏW�E�B�W�F�b�g
 */
class ServicePortWidget : public BaseTab
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param sport �T�[�r�X�|�[�g�v���t�@�C��
	 * @param dialog �T�[�r�X�|�[�g�ݒ�_�C�A���O
	 * @param parent �e�E�B�W�F�b�g
	 */
	ServicePortWidget(ServicePortRTP *sport, ServicePortDialog *dialog, QWidget * parent = Q_NULLPTR);
	BaseWidget _portNameTextbox;
	BaseWidget _interfaceNameTextbox;
	BaseWidget _dinterfaceDirCombox;
	BaseWidget _interfaceDirCombox;
	BaseWidget _IDLTextbox;
	BaseWidget _interfaceTypeCombox;
	BaseWidget _IDLPathTextbox;
private Q_SLOTS :
	/**
	 * @brief �폜�{�^���������X���b�g
	 */
	void deleteButtonSlot();

private:
	ServicePortDialog *_dialog;
	QPushButton *_deleteButton;
};


/**
 * @class ServicePortDialog
 * @brief �T�[�r�X�|�[�g�ݒ�_�C�A���O
 */
class ServicePortDialog : public QDialog
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param sport �T�[�r�X�|�[�g�`��I�u�W�F�N�g
	 * @param parent �e�E�B�W�F�b�g
	 */
	ServicePortDialog(ServicePortRTP *sport, QWidget * parent = Q_NULLPTR);
};

/**
 * @class ServicePort
 * @brief �T�[�r�X�|�[�g�`��
 */
class ServicePort : public Port
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param profile �T�[�r�X�|�[�g�v���t�@�C��
	 * @param defsize �f�t�H���g�T�C�Y
	 * @param scene �V�[���I�u�W�F�N�g
	 * @param parent �e�E�B�W�F�b�g
	 */
	ServicePort(RTC_XML::ServicePorts profile, int defsize, QGraphicsScene* scene, QWidget* parent = Q_NULLPTR);
	/**
	 * @brief �`��p�X�擾
	 * @return �`��p�X
	 */
	virtual QPainterPath getPath();
	/**
	 * @brief �`����s
	 * @param painter 
	 * @param option 
	 * @param widget 
	 */
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	RTC_XML::ServicePorts _profile;
protected:
	QPainterPath _rectPath;
};

/**
 * @class ServicePortRTP
 * @brief �T�[�r�X�|�[�g�`��(���I�ҏW)
 */
class ServicePortRTP : public ServicePort
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param profile �T�[�r�X�|�[�g�v���t�@�C��
	 * @param defsize �f�t�H���g�T�C�Y
	 * @param scene �V�[���I�u�W�F�N�g
	 * @param mainwindow RTCEditor���C���E�C���h�E
	 * @param parent �e�E�B�W�F�b�g
	 */
	ServicePortRTP(RTC_XML::ServicePorts profile, int size, QGraphicsScene* scene, RTC_MainWindow *mainwindow, QWidget* parent = Q_NULLPTR);
protected:
	/**
	 * @brief �}�E�X�_�u���N���b�N���̃X���b�g
	 * @param event �C�x���g���e
	 */
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
private:
	RTC_MainWindow *_mainwindow;
};


/**
 * @class DataPortWidget
 * @brief �f�[�^�|�[�g�ҏW�E�B�W�F�b�g
 */
class DataPortWidget : public BaseTab
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param dport �f�[�^�|�[�g�`��I�u�W�F�N�g
	 * @param dialog �f�[�^�|�[�g�ҏW�_�C�A���O
	 * @param parent �e�E�B�W�F�b�g
	 */
	DataPortWidget(DataPortRTP *dport, DataPortDialog *dialog, QWidget * parent = Q_NULLPTR);
	BaseWidget _portNameTextbox;
	BaseWidget _portTypeCombox;
	BaseWidget _dataTypeCombox;
private Q_SLOTS :
	/**
	 * @brief �폜�{�^���������X���b�g
	 */
	void deleteButtonSlot();

private:
	DataPortDialog *_dialog;
	QPushButton *_deleteButton;


};

/**
 * @class DataPortDialog
 * @brief �f�[�^�|�[�g�ҏW�_�C�A���O
 */
class DataPortDialog : public QDialog
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param dport �f�[�^�|�[�g�`��I�u�W�F�N�g
	 * @param parent �e�E�B�W�F�b�g
	 */
	DataPortDialog(DataPortRTP *dport, QWidget * parent = Q_NULLPTR);
};

/**
 * @class DataPort
 * @brief �f�[�^�|�[�g�`��I�u�W�F�N�g
 */
class DataPort : public Port
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param profile �f�[�^�|�[�g�v���t�@�C��
	 * @param defsize �f�t�H���g�T�C�Y
	 * @param scene �V�[���I�u�W�F�N�g
	 * @param parent �e�E�B�W�F�b�g
	 */
	DataPort(RTC_XML::DataPorts profile, int defsize, QGraphicsScene* scene, QWidget* parent = Q_NULLPTR);
	/**
	 * @brief �R�s�[�R���X�g���N�^
	 * @param obj �R�s�[��
	 */
	DataPort(const DataPort &obj);
	/**
	 * @brief �`��p�X�擾
	 * @return �`��p�X
	 */
	virtual QPainterPath getPath();
	/**
	 * @brief �`����s
	 * @param painter 
	 * @param option 
	 * @param widget 
	 */
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	RTC_XML::DataPorts _profile;
protected:
	QPainterPath _rectPath;

};

/**
 * @class DataPortRTP
 * @brief �f�[�^�|�[�g�`��I�u�W�F�N�g(���I�ҏW)
 */
class DataPortRTP : public DataPort
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param profile �f�[�^�|�[�g�v���t�@�C��
	 * @param defsize �f�t�H���g�T�C�Y
	 * @param scene �V�[���I�u�W�F�N�g
	 * @param mainwindow RTCEditor���C���E�C���h�E
	 * @param parent �e�E�B�W�F�b�g
	 */
	DataPortRTP(RTC_XML::DataPorts profile, int size, QGraphicsScene* scene, RTC_MainWindow *mainwindow, QWidget* parent = Q_NULLPTR);
protected:
	/**
	 * @brief �}�E�X�_�u���N���b�N���̃X���b�g
	 * @param event �C�x���g���e
	 */
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
private:
	RTC_MainWindow *_mainwindow;
};

/**
 * @class RenderRTC
 * @brief RTC�`��I�u�W�F�N�g
 */
class RenderRTC : public RenderPath
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param scene �V�[���I�u�W�F�N�g
	 * @param comp RTC�v���t�@�C��
	 * @param parent �e�E�B�W�F�b�g
	 */
	RenderRTC(QGraphicsScene* scene,  RTC_XML::RTC_Profile* comp, QWidget* parent=0);
	/**
	 * @brief RTC�`��ݒ�X�V
	 */
	void setRTC();
	/**
	 * @brief �f�[�^�|�[�g�ǉ�
	 * @param profile �f�[�^�|�[�g�v���t�@�C��
	 */
	virtual void addDataPort(RTC_XML::DataPorts profile);
	/**
	 * @brief �T�[�r�X�|�[�g�ǉ�
	 * @param profile �T�[�r�X�|�[�g�v���t�@�C��
	 */
	virtual void addServicePort(RTC_XML::ServicePorts profile);
	/**
	 * @brief �|�[�g�폜
	 * @param name �|�[�g��
	 */
	virtual void removePort(QString name);
	/**
	 * @brief �S�|�[�g�폜
	 */
	virtual void removeAllPort();
	/**
	 * @brief RTC�v���t�@�C���ݒ�
	 * @param comp RTC�v���t�@�C��
	 */
	virtual void load(RTC_XML::RTC_Profile* comp);
	const int def_size_x = 50;
	const int def_size_y = 10;
	/**
	 * @brief �|�[�g�����擾
	 * @return �|�[�g����
	 */
	int getPortNum();
	



	int _port_size;

	QMap <QString, Port*> _ports;
private:
	RTC_XML::RTC_Profile* _comp_base;
	//QMap <QString, QString> _config_params;
};


/**
 * @class RenderRTCRTP
 * @brief RTC�`��I�u�W�F�N�g(���I�ҏW)
 */
class RenderRTCRTP : public RenderRTC
{
	Q_OBJECT
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param mainwindow RTC���C���E�C���h�E
	 * @param scene �V�[���I�u�W�F�N�g
	 * @param comp RTC�v���t�@�C��
	 * @param parent �e�E�B�W�F�b�g
	 */
	RenderRTCRTP(QGraphicsScene* scene, RTC_MainWindow *mainwindow, RTC_XML::RTC_ProfileRTP* comp, QWidget* parent = Q_NULLPTR);
	/**
	 * @brief �f�[�^�|�[�g�ǉ�
	 * @param profile �f�[�^�|�[�g�v���t�@�C��
	 */
	virtual void addDataPort(RTC_XML::DataPorts profile);
	/**
	 * @brief �T�[�r�X�|�[�g�ǉ�
	 * @param profile �T�[�r�X�|�[�g�v���t�@�C��
	 */
	virtual void addServicePort(RTC_XML::ServicePorts profile);
	RTC_MainWindow *_mainwindow;
	cnoid::Signal<void(RTC_XML::RTC_ProfileRTP::RTC_State&)>  updateStatus;
private Q_SLOTS :
	/**
	 * @brief RTC��Ԋm�F�X���b�g
	 */
	void check_rtc();
private:
	QTimer *_timer;
	RTC_XML::RTC_ProfileRTP* _comp;
	RTC_XML::RTC_ProfileRTP::RTC_State current_state;
};

#endif