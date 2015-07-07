#include "WebView.h"
#include <QDebug>
#include <iostream>
#include <QTextCodec>
using namespace std;
WebView::WebView(QWidget *parent):
    QWebView(parent)
{
    sdhtml_renderer (&m_callbacks, &m_options, 0);
    m_pmarkdown = sd_markdown_new (0, 16, &m_callbacks, &m_options);

    this->settings ()->setDefaultTextEncoding ("utf-8");

    QTextCodec::setCodecForLocale (QTextCodec::codecForName("UTF-8"));
}

WebView::~WebView()
{

}

void WebView::setMarkDownString (QString code){
    m_pOutBuf = bufnew(64);
    m_pInBuf = bufnew(64);
    code = code.trimmed ();

//    char* data = code.toLocal8Bit ().data ();
//    char* data = code.toUtf8 ().data ();
//    const char* data = code.toUtf8 ().constData ();
//    const char* data = code.toLocal8Bit ().constData ();
    QByteArray byteArray = code.toLocal8Bit ();
    const char* data = byteArray.constData ();

    m_pInBuf->size = strlen(data);

    qDebug() << "=================origin start====================";
    for(auto i=0u;i < code.size () ;i++){
        qDebug() << code.at (i);
    }

    qDebug() << "=================std start====================";
    std::string str = code.toStdString ();
    for(auto i=0u;i < str.size () ;i++){
        qDebug() << str.at (i);
    }

    data = str.c_str ();

    qDebug() << "=================data start====================";
    for(auto i=0u;i < m_pInBuf->size;i++){
        qDebug() << data[i];
    }


    bufgrow(m_pInBuf, m_pInBuf->size+1);

    m_pInBuf->data = (uint8_t*)strdup(data);
    m_pInBuf->data[ strlen( (char*)m_pInBuf->data) ] = '\0';

    sd_markdown_render (m_pOutBuf, m_pInBuf->data, m_pInBuf->size, m_pmarkdown);
    qDebug() << m_pInBuf->size << "===" << strlen( (char*)m_pInBuf->data );

qDebug() << m_pOutBuf->size << "===" << strlen( (char*)m_pOutBuf->data );

    char* buffer = new char[m_pOutBuf->size+1];
    strncpy ( buffer, (char*)m_pInBuf->data, m_pInBuf->size);
    buffer[m_pOutBuf->size] = '\0';

    QString html( buffer );

    this->setContent ("");
    this->setContent ( html.toUtf8 () );

    qDebug() << "=================buffer start====================";
    for(auto i=0u;i < m_pOutBuf->size;i++){
        qDebug() << buffer[i];
    }

    qDebug() << "=================start====================";
    for(int i=0;i < html.size ();i++){
        qDebug() << html.at (i);
    }
qDebug() << "raw:"<< (char*)m_pOutBuf->data << "!!!!";
    bufrelease(m_pInBuf);
    bufrelease(m_pOutBuf);
    m_pInBuf = NULL;
    m_pOutBuf = NULL;

    delete[] buffer;
}

