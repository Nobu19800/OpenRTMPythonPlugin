/*!
 * @file  highlighter.h
 * @brief エディタのハイライト機能クラス
 *        Qtのサンプル(http://doc.qt.io/qt-5/qtwidgets-richtext-syntaxhighlighter-example.html)を一部変更
 *
 */

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE


namespace rtmiddleware {
	/**
	 * @class Highlighter
	 * @brief エディタのハイライト機能クラス
	 */
	class Highlighter : public QSyntaxHighlighter
	{
		Q_OBJECT

	public:
		/**
		 * @brief コンストラクタ
		 * @param parent 親ウィジェット
		 */
		Highlighter(QTextDocument* parent = Q_NULLPTR);

	protected:
		/**
		 * @brief
		 * @param text
		 */
		void highlightBlock(const QString& text) override;

	private:
		struct HighlightingRule
		{
			QRegExp pattern;
			QTextCharFormat format;
		};
		QVector<HighlightingRule> highlightingRules;

		QRegExp commentStartExpression;
		QRegExp commentEndExpression;

		QTextCharFormat keywordFormat;
		QTextCharFormat classFormat;
		QTextCharFormat singleLineCommentFormat;
		QTextCharFormat multiLineCommentFormat;
		QTextCharFormat quotationFormat;
		QTextCharFormat functionFormat;
	};
}

#endif // HIGHLIGHTER_H
