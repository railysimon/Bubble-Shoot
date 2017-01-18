#ifndef BUBBLE_H
#define BUBBLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

#include <ctime>

class bubble : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit bubble(QObject *parent = 0);
    bubble(int x, int y, int w, int h);
    ~bubble();

signals:
    void signal();

protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
        int posX, posY, width, height;
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // BUBBLE_H
