/*!
 * @file  RTCViewWidget.h
 * @brief RTC表示ウィジェット
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


namespace rtmiddleware {
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
	 * @brief 図形描画ベースオブジェクト
	 */
	class RenderPath : public QObject, public QGraphicsItem
	{

	public:
		/**
		 * @brief コンストラクタ
		 * @param scene シーンオブジェクト
		 * @param parent 親ウィジェット
		 */
		RenderPath(QGraphicsScene* scene, QWidget* parent);
		/**
		 * @brief コピーコンストラクタ
		 * @param obj コピー元
		 */
		RenderPath(const RenderPath& obj);
		/**
		 * @brief 描画パス設定
		 * @param path 描画パス設定
		 */
		void setPath(QPainterPath path);
		/**
		 * @brief FillRuleの設定
		 * @param rule FillRule
		 */
		void setFillRule(Qt::FillRule rule);
		/**
		 * @brief FillGradientの設定
		 * @param color1
		 * @param color2
		 */
		void setFillGradient(QColor color1, QColor color2);
		/**
		 * @brief ペン太さの設定
		 * @param width 太さ
		 */
		void setPenWidth(int width);
		/**
		 * @brief ペンの色設定
		 * @param color 色
		 */
		void setPenColor(QColor color);
		/**
		 * @brief 回転角度設定
		 * @param degrees 角度
		 */
		void setRotationAngle(int degrees);
		/**
		 * @brief 中心位置設定
		 * @param x 位置(X)
		 * @param y 位置(Y)
		 */
		void setCenterPoint(int x, int y);
		/**
		 * @brief 位置設定
		 * @param x 位置(X)
		 * @param y 位置(Y)
		 */
		void setPosition(int x, int y);
		/**
		 * @brief サイズ設定
		 * @param width 幅
		 * @param height 高さ
		 */
		void setSize(int width, int height);
		/**
		 * @brief 矩形取得
		 * @param obj コピー元
		 */
		QRectF boundingRect() const;
		/**
		 * @brief 描画実行
		 * @param painter
		 * @param option
		 * @param widget
		 */
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
		/**
		 * @brief 描画更新
		 * @param painter
		 */
		void updatePaint(QPainter* painter);

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
	 * @brief RTC表示ベースクラス
	 */
	class RTCViewWidgetBase : public QWidget
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param parent 親ウィジェット
		 */
		RTCViewWidgetBase(QWidget* parent = Q_NULLPTR);
		/**
		 * @brief 描画RTCオブジェクト取得
		 * @return 描画RTCオブジェクト
		 */
		RenderRTC* getRenderRTC();
	protected:
		QGraphicsScene* _scene;
		QVBoxLayout* _mainLayout;
		GraphicsView* _view;
		RenderRTC* _renderWindow;
	};

	/**
	 * @class RTCViewWidget
	 * @brief RTC表示クラス
	 */
	class RTCViewWidget : public RTCViewWidgetBase
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param profile RTCプロファイル
		 * @param parent 親ウィジェット
		 */
		RTCViewWidget(RTC_XML::RTC_Profile* profile, QWidget* parent = Q_NULLPTR);
	protected:



	};

	/**
	 * @class RTCViewWidgetRTP
	 * @brief RTC表示クラス(動的編集)
	 */
	class RTCViewWidgetRTP : public RTCViewWidget
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param comp RTCプロファイル
		 * @param parent 親ウィジェット
		 */
		RTCViewWidgetRTP(RTC_XML::RTC_ProfileRTP* comp, QWidget* parent = Q_NULLPTR);
		/**
		 * @brief 描画RTCオブジェクト取得
		 * @return 描画RTCオブジェクト
		 */
		RenderRTCRTP* getRenderRTC();
	private:

	};

	/**
	 * @class GraphicsView
	 * @brief 図形表示オブジェクト
	 */
	class GraphicsView : public QGraphicsView
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param scene シーンオブジェクト
		 * @param parent 親ウィジェット
		 */
		GraphicsView(QGraphicsScene* scene, QWidget* parent = Q_NULLPTR);
	};

	/**
	 * @class Port
	 * @brief Port描画ベースクラス
	 */
	class Port : public RenderPath
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param defsize デフォルトサイズ
		 * @param scene シーンオブジェクト
		 * @param parent 親ウィジェット
		 */
		Port(int defsize, QGraphicsScene* scene, QWidget* parent = Q_NULLPTR);
		/**
		 * @brief コピーコンストラクタ
		 * @param obj コピー元
		 */
		Port(const Port& obj);
		/**
		 * @brief サイズ設定
		 * @param size サイズ
		 */
		void setBoxSize(int size);
		/**
		 * @brief 描画パス取得
		 * @return 描画パス
		 */
		virtual QPainterPath getPath() = 0;
		/**
		 * @enum PortDir
		 * @brief ポート方向一覧
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
	 * @brief サービスポート編集ウィジェット
	 */
	class ServicePortWidget : public BaseTab
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param sport サービスポートプロファイル
		 * @param dialog サービスポート設定ダイアログ
		 * @param parent 親ウィジェット
		 */
		ServicePortWidget(ServicePortRTP* sport, ServicePortDialog* dialog, QWidget* parent = Q_NULLPTR);
		BaseWidget _portNameTextbox;
		BaseWidget _interfaceNameTextbox;
		BaseWidget _dinterfaceDirCombox;
		BaseWidget _interfaceDirCombox;
		BaseWidget _IDLTextbox;
		BaseWidget _interfaceTypeCombox;
		BaseWidget _IDLPathTextbox;
	private Q_SLOTS:
		/**
		 * @brief 削除ボタン押下時スロット
		 */
		void deleteButtonSlot();

	private:
		ServicePortDialog* _dialog;
		QPushButton* _deleteButton;
	};


	/**
	 * @class ServicePortDialog
	 * @brief サービスポート設定ダイアログ
	 */
	class ServicePortDialog : public QDialog
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param sport サービスポート描画オブジェクト
		 * @param parent 親ウィジェット
		 */
		ServicePortDialog(ServicePortRTP* sport, QWidget* parent = Q_NULLPTR);
	};

	/**
	 * @class ServicePort
	 * @brief サービスポート描画
	 */
	class ServicePort : public Port
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param profile サービスポートプロファイル
		 * @param defsize デフォルトサイズ
		 * @param scene シーンオブジェクト
		 * @param parent 親ウィジェット
		 */
		ServicePort(RTC_XML::ServicePorts profile, int defsize, QGraphicsScene* scene, QWidget* parent = Q_NULLPTR);
		/**
		 * @brief 描画パス取得
		 * @return 描画パス
		 */
		virtual QPainterPath getPath();
		/**
		 * @brief 描画実行
		 * @param painter
		 * @param option
		 * @param widget
		 */
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
		RTC_XML::ServicePorts _profile;
	protected:
		QPainterPath _rectPath;
	};

	/**
	 * @class ServicePortRTP
	 * @brief サービスポート描画(動的編集)
	 */
	class ServicePortRTP : public ServicePort
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param profile サービスポートプロファイル
		 * @param defsize デフォルトサイズ
		 * @param scene シーンオブジェクト
		 * @param mainwindow RTCEditorメインウインドウ
		 * @param parent 親ウィジェット
		 */
		ServicePortRTP(RTC_XML::ServicePorts profile, int size, QGraphicsScene* scene, RTC_MainWindow* mainwindow, QWidget* parent = Q_NULLPTR);
	protected:
		/**
		 * @brief マウスダブルクリック時のスロット
		 * @param event イベント内容
		 */
		void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
	private:
		RTC_MainWindow* _mainwindow;
	};


	/**
	 * @class DataPortWidget
	 * @brief データポート編集ウィジェット
	 */
	class DataPortWidget : public BaseTab
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param dport データポート描画オブジェクト
		 * @param dialog データポート編集ダイアログ
		 * @param parent 親ウィジェット
		 */
		DataPortWidget(DataPortRTP* dport, DataPortDialog* dialog, QWidget* parent = Q_NULLPTR);
		BaseWidget _portNameTextbox;
		BaseWidget _portTypeCombox;
		BaseWidget _dataTypeCombox;
	private Q_SLOTS:
		/**
		 * @brief 削除ボタン押下時スロット
		 */
		void deleteButtonSlot();

	private:
		DataPortDialog* _dialog;
		QPushButton* _deleteButton;


	};

	/**
	 * @class DataPortDialog
	 * @brief データポート編集ダイアログ
	 */
	class DataPortDialog : public QDialog
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param dport データポート描画オブジェクト
		 * @param parent 親ウィジェット
		 */
		DataPortDialog(DataPortRTP* dport, QWidget* parent = Q_NULLPTR);
	};

	/**
	 * @class DataPort
	 * @brief データポート描画オブジェクト
	 */
	class DataPort : public Port
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param profile データポートプロファイル
		 * @param defsize デフォルトサイズ
		 * @param scene シーンオブジェクト
		 * @param parent 親ウィジェット
		 */
		DataPort(RTC_XML::DataPorts profile, int defsize, QGraphicsScene* scene, QWidget* parent = Q_NULLPTR);
		/**
		 * @brief コピーコンストラクタ
		 * @param obj コピー元
		 */
		DataPort(const DataPort& obj);
		/**
		 * @brief 描画パス取得
		 * @return 描画パス
		 */
		virtual QPainterPath getPath();
		/**
		 * @brief 描画実行
		 * @param painter
		 * @param option
		 * @param widget
		 */
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
		RTC_XML::DataPorts _profile;
	protected:
		QPainterPath _rectPath;

	};

	/**
	 * @class DataPortRTP
	 * @brief データポート描画オブジェクト(動的編集)
	 */
	class DataPortRTP : public DataPort
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param profile データポートプロファイル
		 * @param defsize デフォルトサイズ
		 * @param scene シーンオブジェクト
		 * @param mainwindow RTCEditorメインウインドウ
		 * @param parent 親ウィジェット
		 */
		DataPortRTP(RTC_XML::DataPorts profile, int size, QGraphicsScene* scene, RTC_MainWindow* mainwindow, QWidget* parent = Q_NULLPTR);
	protected:
		/**
		 * @brief マウスダブルクリック時のスロット
		 * @param event イベント内容
		 */
		void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
	private:
		RTC_MainWindow* _mainwindow;
	};

	/**
	 * @class RenderRTC
	 * @brief RTC描画オブジェクト
	 */
	class RenderRTC : public RenderPath
	{
	public:
		/**
		 * @brief コンストラクタ
		 * @param scene シーンオブジェクト
		 * @param comp RTCプロファイル
		 * @param parent 親ウィジェット
		 */
		RenderRTC(QGraphicsScene* scene, RTC_XML::RTC_Profile* comp, QWidget* parent = 0);
		/**
		 * @brief RTC描画設定更新
		 */
		void setRTC();
		/**
		 * @brief データポート追加
		 * @param profile データポートプロファイル
		 */
		virtual void addDataPort(RTC_XML::DataPorts profile);
		/**
		 * @brief サービスポート追加
		 * @param profile サービスポートプロファイル
		 */
		virtual void addServicePort(RTC_XML::ServicePorts profile);
		/**
		 * @brief ポート削除
		 * @param name ポート名
		 */
		virtual void removePort(QString name);
		/**
		 * @brief 全ポート削除
		 */
		virtual void removeAllPort();
		/**
		 * @brief RTCプロファイル設定
		 * @param comp RTCプロファイル
		 */
		virtual void load(RTC_XML::RTC_Profile* comp);
		const int def_size_x = 50;
		const int def_size_y = 10;
		/**
		 * @brief ポート総数取得
		 * @return ポート総数
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
	 * @brief RTC描画オブジェクト(動的編集)
	 */
	class RenderRTCRTP : public RenderRTC
	{
		Q_OBJECT
	public:
		/**
		 * @brief コンストラクタ
		 * @param mainwindow RTCメインウインドウ
		 * @param scene シーンオブジェクト
		 * @param comp RTCプロファイル
		 * @param parent 親ウィジェット
		 */
		RenderRTCRTP(QGraphicsScene* scene, RTC_MainWindow* mainwindow, RTC_XML::RTC_ProfileRTP* comp, QWidget* parent = Q_NULLPTR);
		/**
		 * @brief データポート追加
		 * @param profile データポートプロファイル
		 */
		virtual void addDataPort(RTC_XML::DataPorts profile);
		/**
		 * @brief サービスポート追加
		 * @param profile サービスポートプロファイル
		 */
		virtual void addServicePort(RTC_XML::ServicePorts profile);
		RTC_MainWindow* _mainwindow;
		cnoid::Signal<void(RTC_XML::RTC_ProfileRTP::RTC_State&)>  updateStatus;
	private Q_SLOTS:
		/**
		 * @brief RTC状態確認スロット
		 */
		void check_rtc();
	private:
		QTimer* _timer;
		RTC_XML::RTC_ProfileRTP* _comp;
		RTC_XML::RTC_ProfileRTP::RTC_State current_state;
	};
}

#endif //RTCVIEWWIDGET_H