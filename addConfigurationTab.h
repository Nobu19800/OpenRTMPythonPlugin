/*!
 * @file  addConfigurationTab.h
 * @brief コンフィギュレーション設定タブ
 *
 */

#ifndef ADDCONFIGURATIONTAB_H
#define ADDCONFIGURATIONTAB_H


#include <QWidget>
#include "BaseTab.h"
#include "RTCViewWidget.h"
#include "ConfigurationTable.h"
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
	 * @class addConfigurationTab
	 * @brief コンフィギュレーション設定タブ
	 */
	class addConfigurationTab : public ConfigParamWidgetBase
	{
		Q_OBJECT

	public:
		/**
		 * @brief コンストラクタ
		 * @param comp コンポーネントプロファイルオブジェクト
		 * @param viewWidget RTC表示ウィジェット
		 * @param listWidget コンフィグレーションパラメータ一覧表示ウィジェット
		 * @param parent 親ウィジェット
		 */
		addConfigurationTab(RTC_XML::RTC_ProfileRTP* comp, RTCViewWidget* viewWidget, ConfigurationTable* listWidget, QWidget* parent = Q_NULLPTR);




	public Q_SLOTS:
		/**
		 * @brief コンフィギュレーションパラメータ追加
		 * @param profile コンフィグレーションパラメータプロファイルオブジェクト
		 */
		void addConfiguration(RTC_XML::ConfigurationSet profile);
		/**
		 * @brief 作成ボタン押下時のスロット
		 */
		void createButtonSlot();
		//    void fileNew();

	protected:





		//    void fileOpen();


	private:
		RTCViewWidget* _viewWidget;
		ConfigurationTable* _listWidget;
		QPushButton* _createButton;
		RTC_XML::RTC_ProfileRTP* _comp;

		BaseWidget _paramNameTextbox;
		BaseWidget _paramTypeCombox;
		BaseWidget _paramDefaultTextbox;
		BaseWidget _paramConstraintsTextbox;
		BaseWidget _paramWidgetCombox;
		BaseWidget _paramStepTextbox;

	};

}

#endif // ADDCONFIGURATIONTAB_H
