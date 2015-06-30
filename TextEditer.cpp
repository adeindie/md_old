#include "TextEditer.h"
#include <QDebug>

TextEditer::TextEditer(QWidget *parent):
    QPlainTextEdit(parent){

    m_Timer.stop ();

  connect (this, SIGNAL(textChanged()),
    this, SLOT(onTextChangeInner()) );

  connect(&m_Timer, SIGNAL(timeout()),
          this, SLOT(onTextColorUpdate()));

  m_colorStack.push_back ( QColor(0, 0, 0) );
}

TextEditer::~TextEditer()
{
    m_Timer.stop ();
}

void TextEditer::onTextChangeInner(){
//    QTextCursor curcor = this->textCursor ();
//    int pos = curcor.position () - 1 ;

//    QString content = this->toPlainText ();

//    if (pos > content.size () || pos < 0 ) {
//        qDebug() << "error" << pos << "," << content.size ();
//        return;
//    }

//    QChar chr= content.at (pos);
//    QColor color(0, 0, 0);



//    qDebug() << "Char:" << chr;
//    if(chr == '#') {
//        if ( pos == 0 || (pos > 0 && content.at (pos - 1) == '\n' ) ){
//            color = QColor(255, 0, 0);
//        }
//        QTextCharFormat fmt;
//        fmt.setForeground (color);
//bool rs = curcor.movePosition (QTextCursor::Left, QTextCursor::MoveAnchor, 1);
//qDebug() << "rs" << rs;
//        curcor.mergeCharFormat (fmt);
//        this->mergeCurrentCharFormat (fmt);
//    }

//    if(chr == '\n'){
//        QTextCharFormat fmt;
//        fmt.setForeground (color);

//        curcor.mergeCharFormat (fmt);
//        this->mergeCurrentCharFormat (fmt);
//    }


//    if (m_Timer.isActive ()) m_Timer.stop ();

//    m_Timer.setInterval ( 500 );
//    m_Timer.start ();
onTextColorUpdate();
}

void TextEditer::onTextColorUpdate(){
    m_Timer.stop ();
    QTextDocument* doc = this->document ();
    if (!doc) return;
    QTextCursor curcor(document ());
    QString content = this->toPlainText ();
    if (content.size () == 0) return;
    bool rs = false;
    int cnt=0;
    QColor color(0, 0, 0);
    do{
        int pos = curcor.position ();

        if (pos-1 > content.size ()) break;
        int idx = pos-1;
        if (idx < 0) idx = 0;
        QChar chr = content.at (idx);

        if (chr == '#'){
            color = QColor(255, 0, 0);
        }

        if ( chr == '\n'){
            color = QColor(0, 0, 0);
        }
        QTextCharFormat fmt;
        fmt.setForeground (color);

        curcor.mergeCharFormat (fmt);
        this->mergeCurrentCharFormat (fmt);

        rs = curcor.movePosition ( QTextCursor::Right, QTextCursor::MoveAnchor, 1);
    }while( rs && cnt++<10);
}

