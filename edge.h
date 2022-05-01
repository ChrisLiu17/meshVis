#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

//! [0]
class Edge : public QGraphicsItem
{
public:
    int Edge_linkquality;

public:
    Edge(Node *sourceNode, Node *destNode);

    Node *sourceNode() const;
    Node *destNode() const;

    void adjust();

    enum
    {
        Type = UserType + 2
    };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Node *source = nullptr, *dest = nullptr;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 10;

    QList<QPointF *> breakPoints; // 贝塞尔曲线端点的坐标

    int flags; // 文本显示的参数
};
//! [0]

#endif // EDGE_H
