#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebView>

extern "C"
{
#include <markdown.h>
#include <buffer.h>
#include <html.h>
}

class WebView : public QWebView
{
    Q_OBJECT
public:
    WebView(QWidget* parent=0);
    ~WebView();

    void setMarkDownString(QString mdcode);
private:
    struct sd_markdown *m_pmarkdown;
    struct sd_callbacks m_callbacks;
    struct html_renderopt m_options;
    struct buf          *m_pOutBuf;
    struct buf          *m_pInBuf;
};

#endif // WEBVIEW_H
