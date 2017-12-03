/*!
 * @file  highlighter.h
 * @brief �G�f�B�^�̃n�C���C�g�@�\�N���X
 *        Qt�̃T���v��(http://doc.qt.io/qt-5/qtwidgets-richtext-syntaxhighlighter-example.html)���ꕔ�ύX
 *
 */

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE


/**
 * @class Highlighter
 * @brief �G�f�B�^�̃n�C���C�g�@�\�N���X
 */
class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
	/**
	 * @brief �R���X�g���N�^
	 * @param parent �e�E�B�W�F�b�g
	 */
	Highlighter(QTextDocument *parent = 0);

protected:
	void highlightBlock(const QString &text) override;

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


#endif // HIGHLIGHTER_H
