#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>

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
    m_pWebView = new WebView(this);
    m_pTextEditer = new TextEditer(this);

    m_pTextEditer->setFocus ();

    QRect rect = this->rect ();
    m_pTextEditer->setGeometry (0, 0, rect.width () / 2 , rect.height () );
    m_pWebView->setGeometry (rect.width ()/2, 0, rect.width () / 2, rect.height () );

    this->setWindowTitle ("md");

    connect( m_pTextEditer, SIGNAL(textChanged()),
             this, SLOT(onTextChange()) );

    connect(&m_Timer, SIGNAL(timeout()),
            this, SLOT(onUpdateText()));

    connect(ui->actionRevert, SIGNAL(triggered()),
            this, SLOT(onConvert()));

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

    m_pWebView->setMarkDownString ( code );
}

void MainWindow::onConvert (){

}

