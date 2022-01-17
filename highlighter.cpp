/*!
 * @file  highlighter.cpp
 * @brief エディタのハイライト機能クラス
 *        Qtのサンプル(http://doc.qt.io/qt-5/qtwidgets-richtext-syntaxhighlighter-example.html)を一部変更
 *
 */

#include "highlighter.h"

namespace rtmiddleware {
    /**
     * @brief コンストラクタ
     * @param parent 親ウィジェット
     */
    Highlighter::Highlighter(QTextDocument* parent)
        : QSyntaxHighlighter(parent)
    {
        HighlightingRule rule;

        keywordFormat.setForeground(Qt::darkBlue);
        keywordFormat.setFontWeight(QFont::Bold);
        QStringList keywordPatterns;
        keywordPatterns << "\\band\\b" << "\\bassert\\b" << "\\bbreak\\b"
            << "\\bclass\\b" << "\\bcontinue\\b" << "\\bdef\\b"
            << "\\bdel\\b" << "\\belif\\b" << "\\belse\\b"
            << "\\bexcept\\b" << "\\bexec\\b" << "\\bfinally\\b"
            << "\\bfor\\b" << "\\bfrom\\b" << "\\bglobal\\b"
            << "\\bif\\b" << "\\bimport\\b" << "\\bin\\b"
            << "\\bis\\b" << "\\blambda\\b" << "\\bnot\\b"
            << "\\bor\\b" << "\\bpass\\b" << "\\bprint\\b"
            << "\\braise\\b" << "\\breturn\\b" << "\\btry\\b"
            << "\\bwhile\\b" << "\\byield\\b" << "\\bNone\\b"
            << "\\bTrue\\b" << "\\bFalse\\b";
        Q_FOREACH(const QString & pattern, keywordPatterns) {
            rule.pattern = QRegExp(pattern);
            rule.format = keywordFormat;
            highlightingRules.append(rule);

        }

        classFormat.setFontWeight(QFont::Bold);
        classFormat.setForeground(Qt::darkMagenta);
        rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
        rule.format = classFormat;
        highlightingRules.append(rule);

        singleLineCommentFormat.setForeground(Qt::red);
        rule.pattern = QRegExp("//[^\n]*");
        rule.format = singleLineCommentFormat;
        highlightingRules.append(rule);

        multiLineCommentFormat.setForeground(Qt::red);

        quotationFormat.setForeground(Qt::darkGreen);
        rule.pattern = QRegExp("\".*\"");
        rule.format = quotationFormat;
        highlightingRules.append(rule);

        functionFormat.setFontItalic(true);
        functionFormat.setForeground(Qt::blue);
        rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
        rule.format = functionFormat;
        highlightingRules.append(rule);

        commentStartExpression = QRegExp("/\\*");
        commentEndExpression = QRegExp("\\*/");
    }

    /**
     * @brief
     * @param text
     */
    void Highlighter::highlightBlock(const QString& text)
    {
        Q_FOREACH(const HighlightingRule & rule, highlightingRules) {
            QRegExp expression(rule.pattern);
            int index = expression.indexIn(text);
            while (index >= 0) {
                int length = expression.matchedLength();
                setFormat(index, length, rule.format);
                index = expression.indexIn(text, index + length);
            }
        }

        setCurrentBlockState(0);



        int startIndex = 0;
        if (previousBlockState() != 1)
            startIndex = commentStartExpression.indexIn(text);


        while (startIndex >= 0) {

            int endIndex = commentEndExpression.indexIn(text, startIndex);
            int commentLength;
            if (endIndex == -1) {
                setCurrentBlockState(1);
                commentLength = text.length() - startIndex;
            }
            else {
                commentLength = endIndex - startIndex
                    + commentEndExpression.matchedLength();
            }
            setFormat(startIndex, commentLength, multiLineCommentFormat);
            startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
        }
    }

}