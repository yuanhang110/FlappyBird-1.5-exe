#ifndef MYVIEW_H
#define MYVIEW_H

#include<QtWidgets/QApplication>
#include <QtGui>
//#include <QApplication>
#include <QtCore>
#include <QString>
#include <QGraphicsView>
#include <QLabel>
#include <QKeyEvent>
#include <QObject>
class ScoreFontMini;
class WhiteMask;
class BlackMask;
class StartBtn;
class RankBtn;
class ScoreBoard;
class Bird;
class Ground;
class PipeTop;
class PipeBottom;
class Score;
class skills;
class Hint;
class GameOverLabel;
class QPropertyAnimation;
class QParallelAnimationGroup;

namespace Ui {
class MainWindow;
}
class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyView(QWidget *parent = 0);
signals:
    void birdFly();
    void HintHide();
    void start();
    void newScoreNumber(int);
    void birdtrigger();
    void birdchange();
    //void _slowdowntrigger();
public slots:
    void needPipe();
    void birdDie_();
    void gameOver();
    void hintOpacity(); //逐渐消失效果
    void GolShow();     //死亡组合动画
    void _start();
    void removeWhiteMark();
    //void slowdowntrigger();
protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    //void paintEvent(QPaintEvent *);
private:
    void initView();
    void initScene();
    void initHintPA();//初始化hint动画
    void initDieFrames();//初始化死亡用并行框架
    void initConnectTimer();//初始化信号链接和计时器
    void hideItems();
    void createGround();
    void createPipe();
    void createBird();
    void createScore();
    void createskills();
    void createMusic();
    void createHint();
    void hideItem();
    void createDieFrames();
    void resetPipe();
    void whiteMaskAnimation();
    void blackMaskAnimation();
private:
//场景需要的各种Item
    PipeTop *pipeTop1;
    PipeTop *pipeTop2;
    PipeTop *pipeTop3;
    PipeBottom *pipeBottom1;
    PipeBottom *pipeBottom2;
    PipeBottom *pipeBottom3;

    Ground *ground;
    Score *score;
    Bird *bird;
    Hint *hint;
    StartBtn *startBtn;
    RankBtn *rankBtn;
    ScoreBoard *scoreBoard;
    GameOverLabel *gameOverLabel;
    ScoreFontMini *scoreFontMini;
//场景需要的定时器
    QTimer *timer;
    QTimer *timerPipeScore;
    QTimer *timerBird;
    bool StartOver;
    int PipeNumber;
//场景需要的动画框架
    QPropertyAnimation *hintAnimation;
    QPropertyAnimation *startBtnAnimation;
    QPropertyAnimation *rankBtnAnimation;
    QPropertyAnimation *scoreBoardAnimation;
    QPropertyAnimation *gameOverLabelAnimation;
    QPropertyAnimation *scoreFontMiniAnimation;
    QParallelAnimationGroup *dieGroup;//死亡用并行动画组
//场景需要的mask
    WhiteMask *whiteMask;
//场景需要的音效
     QLabel *picLabel;
     Ui::MainWindow *ui;
};

#endif // MYVIEW_H
