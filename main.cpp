#include "window.h"
#include "menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    Window window;
    Menu menu;

    window.show();
    menu.show();

    QObject::connect(&menu, SIGNAL(Play()), &window, SLOT(SlotPlay()));
    QObject::connect(&menu, SIGNAL(Exit()), &window, SLOT(close()));
    QObject::connect(&window, SIGNAL(Lose(int&)), &menu, SLOT(LoseSlot(int&)));

    return application.exec();
}
