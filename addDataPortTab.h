/*!
 * @file  addDataPortTab.h
 * @brief データポート設定タブ
 *
 */



#ifndef ADDDATAPORTTAB_H
#define ADDDATAPORTTAB_H


#include <QWidget>
#include <cnoid/Signal>
#include "BaseTab.h"
#include "RTCViewWidget.h"
#include "DataPortTable.h"
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



namespace rtmiddleware {
	/**
	 * @class addDataPortTab
	 * @brief データポート設定タブ
	 */
	class addDataPortTab : public BaseTab
	{
		Q_OBJECT

	public:
		/**
		 * @brief コンストラクタ
		 * @param comp コンポーネントプロファイルオブジェクト
		 * @param viewWidget RTC表示ウィジェット
		 * @param listWidget データポート一覧表示ウィジェット
		 * @param parent 親ウィジェット
		 */
		addDataPortTab(RTC_XML::RTC_ProfileRTP* comp, RTCViewWidget* viewWidget, DataPortTable* listWidget, QWidget* parent = Q_NULLPTR);
		/**
		 * @brief データポート検索
		 * @param name ポート名
		 * @param ret データポートプロファイルオブジェクト
		 * @param return true：指定ポート名のデータポートが存在した false:存在しなかった
		 */
		bool searchPort(QString name, RTC_XML::DataPorts& ret);
		/**
		 * @brief データポート追加
		 * @param profile データポートプロファイルオブジェクト
		 */
		void addPort(RTC_XML::DataPorts profile);
		cnoid::Signal<void(RTC_XML::DataPorts)>  sigAddPort;

	public Q_SLOTS:
		/**
		 * @brief 生成ボタン押下時のスロット
		 */
		void createButtonSlot();
		//    void fileNew();

	protected:





		//    void fileOpen();


	private:
		RTCViewWidget* _viewWidget;
		DataPortTable* _listWidget;
		BaseWidget _portNameTextbox;
		BaseWidget _portTypeCombox;
		BaseWidget _dataTypeCombox;
		QPushButton* _createButton;
		RTC_XML::RTC_ProfileRTP* _comp;

	};
}
#endif // ADDDATAPORTTAB_H
