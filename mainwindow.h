#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QDebug>
#include <QTimer>
#include <QWebView>
#include <QPlainTextEdit>
#include <TextEditer.h>
#include <WebView.h>

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
    void onConvert();
private:
    Ui::MainWindow *ui;
    QTimer          m_Timer;
    TextEditer*     m_pTextEditer;
    WebView*       m_pWebView;
};

#endif // MAINWINDOW_H
