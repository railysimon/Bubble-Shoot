#ifndef WINDOW_H
#define WINDOW_H

#include "bubble.h"

#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLinearGradient>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QIcon>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <ctime>

class bubble;

class Window : public QDialog
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
        int score, size; // counter, bubbble array size
        QGraphicsTextItem *text; // score
        QGraphicsScene *scene;
        QGraphicsView *view;
        QTimer *system; // system-timer
        bubble **bubs; // bubble array
        QCursor *target;

        void Layout();
        void Settings();
        void Score();
        void Timer();

        void BubsCreate();
        void BubsDelete();

private slots:
                void Game();
                void Move();
                void LevelUp();
                void SlotPlay();

signals:
                void Lose(int&);
};

#endif // WINDOW_H
