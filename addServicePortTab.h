/*!
 * @file  addServicePortTab.h
 * @brief サービスポート設定タブ
 *
 */

#ifndef ADDSERVICEPORTTAB_H
#define ADDSERVICEPORTTAB_H


#include <QWidget>
#include "BaseTab.h"
#include "RTCViewWidget.h"
#include "ServicePortTable.h"




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
	 * @brief サービスポート設定タブ
	 */
	class addServicePortTab : public BaseTab
	{
		Q_OBJECT

	public:
		/**
		 * @brief コンストラクタ
		 * @param comp コンポーネントプロファイルオブジェクト
		 * @param viewWidget RTC表示ウィジェット
		 * @param listWidget サービスポート一覧表示ウィジェット
		 * @param parent 親ウィジェット
		 */
		addServicePortTab(RTC_XML::RTC_ProfileRTP* comp, RTCViewWidget* viewWidget, ServicePortTable* listWidget, QWidget* parent = Q_NULLPTR);
		/**
		 * @brief サービスポート検索
		 * @param name ポート名
		 * @param ret サービスタポートプロファイルオブジェクト
		 * @param return true：指定ポート名のサービスポートが存在した false:存在しなかった
		 */
		bool searchPort(QString name, RTC_XML::ServicePorts& ret);
		/**
		 * @brief サービスポート追加
		 * @param profile サービスポートプロファイルオブジェクト
		 */
		void addPort(RTC_XML::ServicePorts profile);



	public Q_SLOTS:
		/**
		 * @brief IDLファイル設定ボタン押下時のスロット
		 */
		void IDLFileButtonSlot();
		/**
		 * @brief IDLインクルードパス設定ボタン押下時のスロット
		 */
		void IDLPathButtonSlot();
		/**
		 * @brief 生成ボタン押下時のスロット
		 */
		void createButtonSlot();
		//    void fileNew();

	protected:





		//    void fileOpen();


	private:
		RTCViewWidget* _viewWidget;
		ServicePortTable* _listWidget;
		BaseWidget _portNameTextbox;
		BaseWidget _interfaceNameTextbox;
		BaseWidget _dinterfaceDirCombox;
		BaseWidget _interfaceDirCombox;
		BaseWidget _IDLTextbox;
		BaseWidget _interfaceTypeCombox;
		BaseWidget _IDLPathTextbox;
		QPushButton* _IDLFileButton;
		QPushButton* _IDLPathButton;
		QPushButton* _createButton;
		RTC_XML::RTC_ProfileRTP* _comp;

	};
}
#endif // ADDSERVICEPORTTAB_H
