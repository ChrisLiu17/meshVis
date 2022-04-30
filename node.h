#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>
#include <QTime>

class Edge;
class GraphWidget;


//typedef struct{
//    QString node_ipaddr;
//    QString node_id;
//    QString gps;
//    int node_pso_x;
//    int node_pos_y;

//}NodeInfo_s;
//! [0]
class Node : public QGraphicsItem
{
public:
    QString node_id;
    QString node_ipaddr;
    int node_time;
    int node_pos_x;
    int node_pos_y;                       //


    Node(GraphWidget *graphWidget);


    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

//    void calculateForces();
    bool advancePosition();

    QRectF boundingRect() const override;                                                                           //返回绘制item大概区域
    QPainterPath shape() const override;                                                                            //返回item的精准轮廓
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;                //绘制item内容

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

public:
    QList<Edge *> edgeList;
private:

    QPointF newPos;
    GraphWidget *graph = nullptr;

    int flags;
};



//! [0]

#endif // NODE_H
