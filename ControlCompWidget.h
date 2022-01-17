/*!
 * @file  ControlCompWidget.h
 * @brief コンポーネント監視ウィジェット
 *
 */

#ifndef CONTROLCOMPWIDGET_H
#define CONTROLCOMPWIDGET_H


#include <QWidget>
#include <cnoid/Signal>
#include "BaseTab.h"
#include "PythonEditor.h"
#include "highlighter.h"
#include "ActivityCode.h"




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
class QPushButton;
QT_END_NAMESPACE



namespace rtmiddleware {
	/**
	 * @class ControlCompWidget
	 * @brief コンポーネント監視ウィジェット
	 */
	class ControlCompWidget : public BaseTab
	{
		Q_OBJECT

	public:
		/**
		 * @brief コンストラクタ
		 * @param parent 親ウィジェット
		 */
		ControlCompWidget(QWidget* parent = Q_NULLPTR);
		/**
		 * @brief 設定している実行コンテキストのID取得
		 * @retuen 実行コンテキストのID
		 */
		int getECNum();
		cnoid::Signal<void()>  sigActiveButton;
		cnoid::Signal<void()>  sigDeactiveButton;
		cnoid::Signal<void()>  sigResetButton;




	public Q_SLOTS:
		/**
		 * @brief アクティブボタンのスロット
		 */
		void activeButtonSlot();
		/**
		 * @brief 非アクティブボタンのスロット
		 */
		void deactiveButtonSlot();
		/**
		 * @brief リセットボタンのスロット
		 */
		void resetButtonSlot();

	protected:





		//    void fileOpen();


	private:
		QPushButton* _activeButton;
		QPushButton* _deactiveButton;
		QPushButton* _resetButton;
		BaseWidget _ECCombox;
	};
}
#endif // CONTROLCOMPWIDGET_H
