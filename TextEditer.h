#ifndef TEXTEDITER_H
#define TEXTEDITER_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QStack>
#include <QTimer>

class TextEditer: public QPlainTextEdit
{
    Q_OBJECT
public:
    TextEditer(QWidget* parent=0);
    ~TextEditer();

protected slots:
    void onTextChangeInner();
    void onTextColorUpdate();
protected:
    QTimer m_Timer;
    QStack<QColor> m_colorStack;
};

#endif // TEXTEDITER_H
