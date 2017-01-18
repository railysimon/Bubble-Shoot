#include "menu.h"

Menu::Menu(QWidget *parent) : QDialog(parent)
{
    this->setFixedSize(180, 140);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setWindowIcon(QIcon(QPixmap("icon.jpeg")));
    this->setWindowTitle("Bubble shoot");

    QPalette pal;
    pal.setColor(this->backgroundRole(), QColor(35, 35, 35));
    this->setPalette(pal);

    Readfile();
    Layout();
}

Menu::~Menu()
{

}

QLabel *Menu::label(QString title, int size)
{
    QLabel *lbl = new QLabel(title);
    lbl->setFont(QFont("Ubuntu", size, QFont::Bold));

    return lbl;
}

QPushButton *Menu::button(QString title)
{
    QPushButton *btn = new QPushButton(title);
    btn->setFont(QFont("Ubuntu", 10, QFont::Bold));
    btn->setCursor(Qt::PointingHandCursor);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(ButtonClicked()));

    return btn;
}

void Menu::Layout()
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignCenter);
    QLabel *title = label("<font color=white>Menu</font>", 20);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    layout->addSpacing(10);
    layout->addWidget(button("Play"));
    layout->addWidget(button("Exit"));
    layout->addSpacing(10);

    QHBoxLayout *bottom = new QHBoxLayout;
    score = label("<font color=white>Score: </font>", 7);
    hscore = label("<font color=white>Height Score: " + QString::number(scr), 7);
    bottom->addWidget(score);
    bottom->addSpacing(32);
    bottom->addWidget(hscore);
    layout->addLayout(bottom);
    this->setLayout(layout);
}

void Menu::Readfile()
{
    file.open("score");
    file >> scr;
    file.close();
}

void Menu::ButtonClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());

    if(btn->text() == "Play")
    {
        this->hide();
        emit Play();
    }

    if(btn->text() == "Exit")
    {
        this->close();
        emit Exit();
    }
}

void Menu::LoseSlot(int &sc)
{
    this->show();
    score->setText("<font color=white>Score: " + QString::number(sc));

    Readfile();

    if(sc > scr)
    {
        file.open("score");
        file << sc;
        file.close();
        hscore->setText("<font color=white>Height Score: " + QString::number(sc));
    }
}
