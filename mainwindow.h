#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QDebug>
#include <QTimer>
#include <QWebView>
#include <QPlainTextEdit>

extern "C"
{
#include <markdown.h>
#include <buffer.h>
#include <html.h>
}
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void init();

    void resizeEvent (QResizeEvent* evt);
private slots:
    void onTextChange();
    void onUpdateText();
private:
    Ui::MainWindow *ui;
    QTimer          m_Timer;
    QPlainTextEdit* m_pTextEditer;
    QWebView*       m_pWebView;

    struct sd_markdown *m_pmarkdown;
    struct sd_callbacks m_callbacks;
    struct html_renderopt m_options;
    struct buf          *m_pOutBuf;
    struct buf          *m_pInBuf;
};

#endif // MAINWINDOW_H
