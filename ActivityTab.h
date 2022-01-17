/*!
 * @file  ActivityTab.h
 * @brief 各コールバック関数編集タブ
 *
 */


#ifndef ACTIVITYTAB_H
#define ACTIVITYTAB_H


#include <QWidget>
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
QT_END_NAMESPACE


namespace rtmiddleware {

	/**
	 * @class ActivityTab
	 * @brief 各コールバック関数編集タブ
	 */
	class ActivityTab : public BaseTab
	{
		Q_OBJECT

	public:
		/**
		 * @brief コンストラクタ
		 * @param name アクティビティのID
		 * @param text テキスト
		 * @param parent 親ウィジェット
		 */
		ActivityTab(ActivityCode name, QString text, QWidget* parent = Q_NULLPTR);
		/**
		 * @brief コンストラクタ
		 * @param name アクティビティ名
		 * @param text テキスト
		 * @param parent 親ウィジェット
		 */
		ActivityTab(QString name, QString text, QWidget* parent = Q_NULLPTR);

		/**
		 * @brief テキスト取得
		 * @return テキスト
		 */
		QString getText();
		/**
		 * @brief フォントサイズ設定
		 * @param s フォントサイズ
		 */
		void setFontSize(int s);
		/**
		* @brief テキスト設定
		* @return テキスト
		*/
		void setText(QString code);


	public Q_SLOTS:


	protected:





		//    void fileOpen();


	private:
		ActivityCode _name;
		QString _text;

		PythonEditor* _editor;
		Highlighter* _highlight;
	};

}

#endif // ACTIVITYTAB_H

