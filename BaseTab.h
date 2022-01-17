/*!
 * @file  BaseTab.h
 * @brief タブの基本クラス
 *
 */


#ifndef BASETAB_H
#define BASETAB_H

#include <QMap>
#include <QWidget>



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
	 * @enum WidgetType
	 * @brief ウィジェットの種別一覧
	 */
	enum WidgetType
	{
		TextBox = 1,
		Combox = 2,
		TextCombox = 3,
		SpinBox = 4,
		DoubleSpinBox = 5
	};

	/**
	 * @class BaseWidget
	 * @brief ウィジェット格納クラス
	 */
	class BaseWidget
	{
	public:
		/**
		 * @brief コンストラクタ
		 * @param widget ウィジェット
		 * @param layout レイアウト
		 * @param t ウィジェット種別
		 */
		BaseWidget(QWidget* widget = NULL, QLayout* layout = NULL, WidgetType t = TextBox);
		QWidget* _widget;
		QLayout* _layout;
		WidgetType _type;

		/**
		 * @brief ラインテキストボックスにテキスト設定
		 * @param text テキスト
		 */
		void setText(QString text);
		/**
		 * @brief ラインテキストボックスのテキスト取得
		 * @return テキスト
		 */
		QString getText();
		/**
		 * @brief コンボボックスのテキスト取得
		 * @return テキスト
		 */
		QString getItemText();
	};

	/**
	 * @class BaseTab
	 * @brief タブのベースクラス
	 */
	class BaseTab : public QWidget
	{
		Q_OBJECT

	public:
		/**
		 * @brief コンストラクタ
		 * @param parent 親ウィジェット
		 */
		BaseTab(QWidget* parent = Q_NULLPTR);

		/**
		 * @brief ウィジェット追加
		 * @param wid 追加ウィジェット
		 * @param name 名前
		 * @param label ラベル名
		 * @param t ウィジェットの種別
		 * @return ウィジェット格納クラス
		 */
		BaseWidget apendWidget(QWidget* wid, QString name, QString label, WidgetType t = TextBox);
		/**
		 * @brief コンボボックス追加
		 * @param name 名前
		 * @param label ラベル名
		 * @param value 初期の値
		 * @param ls アイテムリスト
		 * @param default_s デフォルト値
		 * @return ウィジェット格納クラス
		 */
		BaseWidget addCombox(QString name, QString label, QVector<QString> value, QVector<QString> ls, QString default_s);
		/**
		 * @brief ラインテキストボックス追加
		 * @param name 名前
		 * @param label ラベル名
		 * @param value 初期の値
		 * @param default_s デフォルト値
		 * @return ウィジェット格納クラス
		 */
		BaseWidget addTextBox(QString name, QString label, QVector<QString> value, QString default_s);

	public Q_SLOTS:
		//    void fileNew();

	protected:



		//    void fileOpen();


	protected:

		QVBoxLayout* mainLayout;
		QMap<QString, BaseWidget> WidList;
		QVector<QVBoxLayout*> subLayouts;
		int widNum;



	};
}
#endif // BASETAB_H
