#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <TextEditer.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    m_Timer.stop ();
    delete ui;
}

void MainWindow::init (){
//    m_pTextEditer   = this->ui->plainTextEdit;
    m_pWebView      = this->ui->webView;

    this->ui->plainTextEdit->resize (0, 0);
    m_pTextEditer = new TextEditer(this);

    m_pTextEditer->setFocus ();

    QRect rect = this->rect ();
    m_pTextEditer->setGeometry (0, 0, rect.width () / 2 , rect.height () );
    m_pWebView->setGeometry (rect.width ()/2, 0, rect.width () / 2, rect.height () );
    m_pWebView->settings ()->setDefaultTextEncoding ("utf-8");

    this->setWindowTitle ("md");

    connect( m_pTextEditer, SIGNAL(textChanged()),
             this, SLOT(onTextChange()) );

    connect(&m_Timer, SIGNAL(timeout()),
            this, SLOT(onUpdateText()));

    sdhtml_renderer (&m_callbacks, &m_options, 0);
    m_pmarkdown = sd_markdown_new (0, 16, &m_callbacks, &m_options);
}

void MainWindow::resizeEvent (QResizeEvent *){
    QRect rect = this->rect ();
    m_pTextEditer->setGeometry (0, 0, rect.width () / 2 , rect.height () );
    m_pWebView->setGeometry (rect.width ()/2, 0, rect.width () / 2, rect.height () );
}

void MainWindow::onTextChange (){
    if (m_Timer.isActive ()) m_Timer.stop ();

    m_Timer.setInterval ( 500 );
    m_Timer.start ();
}

void MainWindow::onUpdateText (){
    m_Timer.stop ();
    QString code = m_pTextEditer->toPlainText ();

    m_pOutBuf = bufnew(64);
    m_pInBuf = bufnew(64);

    char* data = code.toLocal8Bit ().data ();
    m_pInBuf->size = strlen(data);

    bufgrow(m_pInBuf, m_pInBuf->size+1);

    m_pInBuf->data = (uint8_t*)strdup(data);

    sd_markdown_render (m_pOutBuf, m_pInBuf->data, m_pInBuf->size, m_pmarkdown);

    QString html((char*)m_pOutBuf->data);

    m_pWebView ->setContent ( html.toUtf8 () );

    bufrelease(m_pInBuf);
    bufrelease(m_pOutBuf);
    m_pInBuf = NULL;
    m_pOutBuf = NULL;
}

