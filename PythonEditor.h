/*!
 * @file  PythonEditor.h
 * @brief Python用エディタ
 *
 */

#ifndef PYTHONEDITOR_H
#define PYTHONEDITOR_H

#include <QTextEdit>

QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
class QPrinter;
QT_END_NAMESPACE

namespace rtmiddleware {
	/**
	 * @class PythonEditor
	 * @brief Python用エディタ
	 */
	class PythonEditor : public QTextEdit
	{
		Q_OBJECT

	public:
		/**
		 * @brief コンストラクタ
		 * @param parent 親ウィジェット
		 */
		PythonEditor(QWidget* parent = Q_NULLPTR);

		/**
		 * @brief フォントサイズ設定
		 * @param s フォントサイズ
		 */
		void setFontSize(const int s);
		static const int tab_keywords_size;
		static const char* tab_keywords[];
	public Q_SLOTS:
		//    void fileNew();

	protected:
		/**
		 * @brief
		 * @param source
		 */
		void insertFromMimeData(const QMimeData* source) override;
		/**
		 * @brief キー押下時のイベント
		 * @param e イベント内容
		 */
		void keyPressEvent(QKeyEvent*) override;



		//    void fileOpen();


	private:
		/**
		 * @brief フォント設定
		 * @param fontSize フォントサイズ
		 * @param wrapColumn 行の文字数
		 */
		void createFont(const int fontSize, const int wrapColumn);
		int fontSize;
		int wrapColumn;


	};
}

#endif // PYTHONEDITOR_H
