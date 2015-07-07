#include "TextEditer.h"
#include <QDebug>
#include <QTextDocument>
#include <QTextBlock>

TextEditer::TextEditer(QWidget *parent):
    QPlainTextEdit(parent){

    m_Timer.stop ();

    connect (this, SIGNAL(textChanged()),
             this, SLOT(onTextChangeInner()) );

    connect(&m_Timer, SIGNAL(timeout()),
            this, SLOT(onTextColorUpdate()));

    connect( this->document (), SIGNAL(contentsChange(int,int,int)),
             this, SLOT(onDocumentChange(int,int,int)));

    m_colorStack.push_back ( QColor(0, 0, 0) );
}

TextEditer::~TextEditer()
{
    m_Timer.stop ();
}

void TextEditer::onTextChangeInner(){
    onTextColorUpdate();
}

void TextEditer::onTextColorUpdate(){
    m_Timer.stop ();
    //    QTextDocument* doc = this->document ();
    //    if (!doc) return;
    //    QTextCursor curcor(document ());
    //    QString content = this->toPlainText ();
    //    if (content.size () == 0) return;
    //    bool rs = false;
    //    int cnt=0;
    //    QColor color(0, 0, 0);
    //    do{
    //        int pos = curcor.position ();

    //        if (pos-1 > content.size ()) break;
    //        int idx = pos-1;
    //        if (idx < 0) idx = 0;
    //        QChar chr = content.at (idx);

    //        if (chr == '#'){
    //            color = QColor(255, 0, 0);
    //        }

    //        if ( chr == '\n'){
    //            color = QColor(0, 0, 0);
    //        }
    //        QTextCharFormat fmt;
    //        fmt.setForeground (color);

    //        curcor.mergeCharFormat (fmt);
    //        this->mergeCurrentCharFormat (fmt);

    //        rs = curcor.movePosition ( QTextCursor::Right, QTextCursor::MoveAnchor, 1);
    //    }while( rs && cnt++<10);


}

static QColor _GetRamdomColor()
{
    QColor col;
    int RamdomNum = rand() % 0xffffff;
    char strCol[8];
    sprintf(strCol, "#%06x", RamdomNum);
    col.setNamedColor(QString::fromLocal8Bit(strCol, 8));
    return col;
}

void TextEditer::onDocumentChange (int position, int charsRemoved, int charsAdded){
    if(charsAdded == 0)
        return;

    QTextCursor cursor = this->textCursor();
//    // 随机颜色
//    for (int i = 0; i < charsAdded-1; i++ )
//    {
//        int pos = position + i;
//        // 选择一个字, 随机设定颜色
//        QTextCharFormat fmt;
//        fmt.setForeground(_GetRamdomColor());
//        QTextCursor helper = cursor;
//        helper.setPosition(pos);
//        helper.setPosition(pos+1, QTextCursor::KeepAnchor);
//        helper.setCharFormat(fmt);
//    }

    QTextDocument* doc = this->document ();
    if ( !doc ) return;
    int cnt = doc->blockCount ();
    qDebug() << charsAdded << " block count:" << cnt;
    for (int i=0;i<cnt;i++){
        QTextBlock block = doc->findBlock (i);
        if (block.text ().size () == 0) continue;
        QTextCharFormat fmt;
        fmt.setForeground(_GetRamdomColor());
        QTextCursor helper = cursor;
        helper.clearSelection ();
        helper.setPosition( block.position ()+1 , QTextCursor::KeepAnchor );
        helper.setPosition( block.position ()+block.text ().size () - 2 , QTextCursor::KeepAnchor );
        helper.setCharFormat(fmt);
        QString old = block.text ();
        block.blockFormat ()
        helper.insertText (block.text ());
    }
}


