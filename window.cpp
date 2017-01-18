#include "window.h"

Window::Window(QWidget *parent): QDialog(parent), score(0), size(3)
{
    this->setFixedSize(500, 500);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowIcon(QIcon(QPixmap("icon.jpeg")));
    this->setWindowTitle("Bubble shoot");
    Settings();
}

Window::~Window()
{
}

void Window::Layout() // adding graphicsview to layout; add installing it
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(view);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);
}

void Window::Settings() // creating scene, view, bg
{
    scene = new QGraphicsScene(QRectF(0, 0, width(), height()));
    view = new QGraphicsView(scene);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    QLinearGradient gradient(0, 0, width(), height());
    gradient.setColorAt(0, Qt::green);
    gradient.setColorAt(0.5, Qt::black);
    gradient.setColorAt(1, Qt::yellow);
    QGraphicsRectItem *background = scene->addRect(0, 0, width(), height());
    background->setBrush(gradient);

    Score();
    Layout();
}

void Window::Score() // creating the score
{
   text = new QGraphicsTextItem("Score: " + QString::number(score));
   text->setPos(390, 12);
   text->setFont(QFont("Ubuntu", 10, QFont::Bold));
   text->setDefaultTextColor(Qt::red);
   scene->addItem(text);
}

void Window::Timer() // system timmer
{
    system = new QTimer;
    system->setInterval(10);
    system->start();
    connect(system, SIGNAL(timeout()), this, SLOT(Move()));
    connect(system, SIGNAL(timeout()), this, SLOT(LevelUp()));
}

void Window::BubsCreate() // creating the bubbles
{
    srand(time(NULL));
    bubs = new bubble*[size];
    for(int i=0; i<size; i++)
    {
        bubs[i] = new bubble(rand() % 300, (rand() % 100)*(-1), 30, 30);
        scene->addItem(bubs[i]);
        bubs[i]->setCursor(Qt::PointingHandCursor);
        connect(bubs[i], SIGNAL(signal()), this, SLOT(Game()));
    }
}

void Window::BubsDelete() // deleting the bubbles
{
    for(int i=0; i<size; i++)
        delete bubs[i];
    delete bubs;
}

void Window::LevelUp() // next level
{
    if(score == 20) // 2-nd lvl; 5 bubbles
    {
        BubsDelete();
        size = 5;
        BubsCreate();
        score++;
    }

    if(score == 45) system->setInterval(7); // 3-d lvl; more speed

    if(score == 60) // 4-th lvl; 7 bubbles
    {
        BubsDelete();
        size = 7;
        BubsCreate();
        score++;
    }

    if(score == 100) // 5-th lvl; 10 bubbles
    {
        BubsDelete();
        size = 10;
        BubsCreate();
        score++;
    }
}

void Window::SlotPlay()
{
    score = 0;
    size = 3;
    scene->removeItem(text);
    Score();

    BubsCreate();
    Timer();
}

void Window::Game() // click on the bubble
{
    bubble *bub = qobject_cast<bubble*>(sender());
    bub->setPos(50, (rand() % 100)*(-1)); // ?

    score++;
    scene->removeItem(text);
    Score();
}

void Window::Move() // moving the bubbles
{
    for(int i=0; i<size; i++)
    {
        if(bubs[i]->y() >= height()) // if you lose
        {
            system->stop();
            BubsDelete();
            emit Lose(score);
            break;
        }

        bubs[i]->setPos(bubs[i]->x(), bubs[i]->y()+1);
    }
}
