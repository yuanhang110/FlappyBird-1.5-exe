#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsItem>
#include <QObject>
#include <QPair>


class Score : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Score();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void resetScore();
    int getScore();
    int scoreNumber;
public slots:
    int updateSocre();
private:
    QPair<int,int> picOffset[10];   //图片偏移量
             //标记当前分数
    bool first;                     //标记第一次是否更新
    int time;                       //场景调用更新分数
    QPixmap pixmap;

};

#endif // SCORE_H
