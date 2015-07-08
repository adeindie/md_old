#include "WebView.h"
#include <QDebug>
#include <iostream>
#include <QTextCodec>
#include <QDesktopServices>

using namespace std;
WebView::WebView(QWidget *parent):
    QWebView(parent)
{
    sdhtml_renderer (&m_callbacks, &m_options, 0);
    m_pmarkdown = sd_markdown_new (0, 16, &m_callbacks, &m_options);

    this->settings ()->setDefaultTextEncoding ("utf-8");
    this->page ()->setLinkDelegationPolicy ( QWebPage::DelegateAllLinks );
    this->setContextMenuPolicy(Qt::NoContextMenu);

    connect ( this->page (), SIGNAL(linkClicked(QUrl)),
              this, SLOT(onLinkClicked(QUrl)));



    QTextCodec::setCodecForLocale (QTextCodec::codecForName("UTF-8"));


    m_StyleShellFile = "/Users/ade.li/dev/qt/md/Resources/style/Clearness.css";
}

WebView::~WebView()
{
}

void WebView::onLinkClicked(QUrl url){
    QDesktopServices::openUrl ( url );
}

void WebView::setMarkDownString (QString code){
    m_pOutBuf = bufnew(64);
    m_pInBuf = bufnew(64);
    code = code.trimmed ();

    QByteArray byteArray = code.toLocal8Bit ();
    const char* data = byteArray.constData ();

    m_pInBuf->size = strlen(data);

    bufgrow(m_pInBuf, m_pInBuf->size+1);

    m_pInBuf->data = (uint8_t*)strdup(data);
    m_pInBuf->data[ strlen( (char*)m_pInBuf->data) ] = '\0';

    sd_markdown_render (m_pOutBuf, m_pInBuf->data, m_pInBuf->size, m_pmarkdown);

    const char* temp = "<!DOCTYPE html>"
                       "<html><head>"
                       "<title>MD Preview</title>"
                       "<link rel='stylesheet' type='text/css' href='file://%s'>"
                       "<meta http-equiv='Content-Type'' content='text/html; charset=utf-8' />"
                       "</head>"
                       "<body>"
                       "%s"
                       "</body></html>";
    int size = m_pOutBuf->size + strlen(temp) + strlen(m_StyleShellFile) + 1;

    char* buffer = new char[ size ];
    memset(buffer, 0, size);

    buffer[ size ] = '\0';


    QString content( (char*) m_pOutBuf->data );
    int pos = content.lastIndexOf ('>');
    if (pos != content.size () ){
//        qDebug() << "sub string:" << pos;
        content = content.mid (0, pos).trimmed ();
    }
    snprintf (buffer, size, temp, m_StyleShellFile, content.toUtf8 ().constData () );

    QString html( buffer );
    html = html.trimmed ();


    this->setContent ( html.toUtf8 () );

    bufrelease(m_pInBuf);
    bufrelease(m_pOutBuf);
    m_pInBuf = NULL;
    m_pOutBuf = NULL;

    delete[] buffer;
}

