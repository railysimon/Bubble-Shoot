#include <bubble.h>

bubble::bubble(QObject *parent): QObject(parent), QGraphicsItem()
{

}

bubble::bubble(int x, int y, int w, int h)
{
    posX = x;
    posY = y;
    width = w;
    height = h;
}

bubble::~bubble()
{

}

void bubble::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signal();
    QGraphicsItem::mousePressEvent(event);
}

QRectF bubble::boundingRect() const
{
    return QRectF(posX, posY, width, height);
}

void bubble::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    srand(time(NULL));
    QRectF rect = boundingRect();
    painter->setBrush(QColor(rand() % 200, rand() % 200, rand() % 200));
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter->drawEllipse(rect);

        Q_UNUSED(option);
        Q_UNUSED(widget);
}


