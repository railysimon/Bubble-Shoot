#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>

#include <fstream>

class Menu : public QDialog
{
    Q_OBJECT
public:
        Menu(QWidget *parent = 0);
        ~Menu();

private:
        QLabel *label(QString title, int size);
        QPushButton *button(QString title);
        void Layout();
        QLabel *score, *hscore;

        int scr;
        std::fstream file;
        void Readfile();

private slots:
                void ButtonClicked();
                void LoseSlot(int&);
signals:
                void Play();
                void Exit();
};

#endif // MENU_H
