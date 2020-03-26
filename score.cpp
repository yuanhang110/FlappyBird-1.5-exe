#include "score.h"
#include "define.h"
#include <QPainter>
#include <QPair>
#include<QDebug>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include "myview.h"
Score::Score()
{
    for(int i=0; i<10; ++i) {
            picOffset[i].first = (i%5) * SCORE_WIDTH;
            picOffset[i].second = (i>4)? SCORE_HEIGHT : 0;
    }
    scoreNumber = 0;
    time = 0;
    first = false;

    pixmap.load(":/Images/ScoreFont.png");
}

QRectF Score::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(0 - penWidth/2, 0 - penWidth/2,
                  80 + penWidth/2, 60 + penWidth/2);
}

void Score::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(SCORE_WIDTH,0,SCORE_WIDTH,SCORE_HEIGHT,pixmap,
                        picOffset[scoreNumber%10].first,picOffset[scoreNumber%10].second,
                        SCORE_WIDTH,SCORE_HEIGHT);
    if(scoreNumber/10)
        painter->drawPixmap(0,0,SCORE_WIDTH,SCORE_HEIGHT,pixmap,
                            picOffset[scoreNumber/10].first,picOffset[scoreNumber/10].second,
                SCORE_WIDTH,SCORE_HEIGHT);

}

void Score::resetScore()
{
    //return scoreNumber;
    scoreNumber = 0;
    time = 0;
    first = false;
}

int Score::getScore()
{

    //qDebug() <<  scoreNumber;
    return this->scoreNumber;
}

int Score::updateSocre()
{
    if (!first)
    {
        first = true;
        time -= 3;
    }else if(time!=-2 && time) {
        ++scoreNumber;
        update();
        QGraphicsScene *scene = new QGraphicsScene;
        time = 0;
    }
        ++time;
    return scoreNumber;
}

