#include "bird.h"
#include "define.h"
#include <QTimer>
#include <QPainter>
#include <Qdebug>

int trigger = 0;
int change=0;
Bird::Bird()
{
    pixmap1.load(":/Images/bird1.png");
    pixmap2.load(":/Images/bird2.png");
    pixmap3.load(":/Images/bird3.png");
    //pixmap4.load(":/Images/background.jpg");
    oldAngle = 0;
    downFly = BIRD_DOWN;
    angle = 1;
    index = 0;
    dy = 1;
    FlyAngle = false;
    aliveDie = BIRD_ALIVE;
    dieAngle = false;
    dieMove = false;
    pictureRate = 0;
    prepareOrStart = PREPARE;
}

QRectF Bird::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(0 - penWidth/2, 0 - penWidth/2,
                  35 + penWidth/2, 28 + penWidth/2);

}

void Bird::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(pictureRate%BIRD_RATE == 0){
        pictureRate = 0;
        index = (index==2)? 0 : ++index;
    }
    ++pictureRate;
        //painter->drawPixmap(0,280,100,100,pixmap4);
    if(index == 1)
        painter->drawPixmap(0,0,35,28,pixmap1);
    else if(index == 2)
        painter->drawPixmap(0,0,35,28,pixmap2);
    else
        painter->drawPixmap(0,0,35,28,pixmap3);
}

void Bird::resetBird()
{
    oldAngle = 0;
    downFly = BIRD_DOWN;
    angle = 1;
    index = 0; //编号
    dy = 1;    //哨兵值
    FlyAngle = false;
    aliveDie = BIRD_ALIVE;
    dieAngle = false;
    dieMove = false;
    pictureRate = 0;
    prepareOrStart = PREPARE;//false表示没开始，true表示开始
    change=0;
    pixmap1.load(":/Images/bird1.png");
    pixmap2.load(":/Images/bird2.png");
    pixmap3.load(":/Images/bird3.png");
    update();
}

void Bird::upFly()
{
    downFly = BIRD_FLY;
    dy = FLY_COEFFICIENT;
    angle = 1;
    prepareOrStart = START;
}

void Bird::birdtrigger()
{
    int x=5;
    if(change==1)
    {
            x=11;
    }
    else if(change==2)
    {
        x=17;
    }
        qDebug() << x;
        if(trigger<=x){
        ++trigger;
        if (( trigger % 2 == 1) &&(trigger <= x)) {
            pixmap1.load(":/Images/bird4.png");
            pixmap2.load(":/Images/bird5.png");
            pixmap3.load(":/Images/bird6.png");
            triggertime();
            update();
        }
        else if (trigger %2==0){
            if (change==0)
            {
            pixmap1.load(":/Images/bird1.png");
            pixmap2.load(":/Images/bird2.png");
            pixmap3.load(":/Images/bird3.png");
            update();
            }
            else if(change==1)
            {
            pixmap1.load(":/Images/goldbird1.png");
            pixmap2.load(":/Images/goldbird2.png");
            pixmap3.load(":/Images/goldbird3.png");
            update();
            }
            else if(change==2)
            {
            pixmap1.load(":/Images/blackbird1.png");
            pixmap2.load(":/Images/blackbird2.png");
            pixmap3.load(":/Images/blackbird3.png");
            update();
            }
         }
    else if(trigger>x){}
    }}

void Bird::triggertime()
{
    QTimer *Mytimer=new QTimer();
    QTimer::singleShot( 1000,this, SLOT(birdtrigger()) );
    //qDebug() <<  trigger;
    Mytimer ->start();
    //return trigger;
}

int Bird::birdchange()
{
    ++change;
    if (change==3)
    {
        change=0;
        pixmap1.load(":/Images/bird1.png");
        pixmap2.load(":/Images/bird2.png");
        pixmap3.load(":/Images/bird3.png");
        update();
        return change;
        //qDebug()<<change;
    }
    //if(change==)
    if(change==1)
    {
    pixmap1.load(":/Images/goldbird1.png");
    pixmap2.load(":/Images/goldbird2.png");
    pixmap3.load(":/Images/goldbird3.png");
    update();
    return change;
    //qDebug()<<change;
    }
    else if(change==2)
    {
    pixmap1.load(":/Images/blackbird1.png");
    pixmap2.load(":/Images/blackbird2.png");
    pixmap3.load(":/Images/blackbird3.png");
    update();
    return change;
    //qDebug()<<change;
    }
    //}


//    change++;
//    if(change%2==1)
//    {
//      painter->drawPixmap(0,0,15,14,pixmap1);
//      painter->drawPixmap(0,0,15,14,pixmap2);
//      painter->drawPixmap(0,0,15,14,pixmap3);
//    }

}

void Bird::moveBird()
{
    if(prepareOrStart == PREPARE) {
        update();
        return;
    }
    if(trigger % 2 == 0) {
    //如果活着且发生碰撞
      if(aliveDie && !collidingItems().isEmpty()){
          emit this->birdDie();
          aliveDie = BIRD_DIE;
          pixmap1.load(":/Images/bird1.png");
          pixmap2.load(":/Images/bird2.png");
          pixmap3.load(":/Images/bird3.png");
          trigger = 0;
      }
    }
  else if(trigger % 2 == 1) {
      if(this->pos().ry() > SCENE_LOW) {     //如果还未达到地面
          emit this->birdDie();
          aliveDie = BIRD_DIE;
          pixmap1.load(":/Images/bird1.png");
          pixmap2.load(":/Images/bird2.png");
          pixmap3.load(":/Images/bird3.png");
          trigger = 0;
          update();
      }
    }
    //如果死了
    if (!aliveDie){
        if(!dieMove) {
            moveBy(DIE_SCENE_DX,0);
            dieMove = true;
        }
        if(!dieAngle) {//先更新bird死亡的角度
            moveBy(0,dy);
            setRotation(-oldAngle+DIE_PERFECT_ANGLE);//先会水平状态再旋转到最佳死亡角度
            dieAngle = true;
            dy = 4;
        }
        if(this->pos().ry() <= SCENE_LOW) {     //如果还未达到地面
            moveBy(0,dy);
            update();
        } else{
            emit this->downOk();
            this->setRotation(CORRECT_ANGLE);
        }
    }

    //如果是下降
    if(aliveDie && downFly) {
        if(oldAngle <= DOWN_LOWER) {
            setRotation(angle);
            oldAngle += angle;
        }
        dy += DROP_COEFFICIENT;
        moveBy(0,dy);
        update();
    }
    else if(aliveDie) {//如果是上升
        if(oldAngle) {
            setRotation(-oldAngle);//先旋转回水平
            oldAngle = 0;
        } else if(!FlyAngle) {//如果还未更新
            setRotation(RISEZ_PERFECT);        //更新最佳的上升角度
            FlyAngle = true;
        }

        if (dy > 0){//如果上升数值已用完，标记哨兵为下落
            dy = 1;
            downFly = BIRD_DOWN;
        } else {
            if(this->pos().ry()>=SCENE_HIGH) {//没到顶
                dy += DOWN_COEFFICIENT;
                moveBy(0,dy);
                update();
            } else {//到顶
                update();
                downFly = BIRD_DOWN;
                dy = 1;
            }
        }
    }
}






