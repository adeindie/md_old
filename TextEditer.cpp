#include "TextEditer.h"
#include <QDebug>
#include <QTextDocument>
#include <QTextBlock>
#include <QMimeData>
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


    this->acceptDrops ();
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
//    if ( !doc ) return;
//    QTextFrame* rootFrame = doc->rootFrame ();

//    QTextFrameFormat frameFormat;
//    frameFormat.setBorderBrush (Qt::red);
//    frameFormat.setBorder (5);
//    rootFrame->setFrameFormat (frameFormat);
//    auto it = rootFrame->begin ();
//    while( ++it != rootFrame->end () && it != last ){
//        QTextFrame* frame = it.currentFrame ();
//        frame->setFrameFormat (frameFormat);
//    }

}

void TextEditer::dragEnterEvent(QDragEnterEvent *e){
    if (e->mimeData ()->hasUrls ()){
        e->acceptProposedAction ();
    }
}

void TextEditer::dropEvent (QDropEvent *e){

    const QMimeData* mime = e->mimeData ();
    qDebug() << mime->urls ();

    foreach (const QUrl &url, e->mimeData ()->urls ()) {
        qDebug() << url.toLocalFile ();
        url.from
    }
}


