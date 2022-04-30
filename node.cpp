#include "edge.h"
#include "node.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

//! [0]
Node::Node(GraphWidget *graphWidget)
    : graph(graphWidget)
{

    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}
//! [0]

//! [1]
void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}
//! [1]
/*
//! [2]
void Node::calculateForces()
{
    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }
//! [2]

//! [3]
// Sum up all forces pushing this item away
//总结所有将这个物体推开的力
qreal xvel = 0;
qreal yvel = 0;
const QList<QGraphicsItem *> items = scene()->items();
for (QGraphicsItem *item : items) {
    Node *node = qgraphicsitem_cast<Node *>(item);
    if (!node)
        continue;

    QPointF vec = mapToItem(node, 0, 0);
    qreal dx = vec.x();
    qreal dy = vec.y();
    double l = 2.0 * (dx * dx + dy * dy);
    if (l > 0) {
        xvel += (dx * 150.0) / l;
        yvel += (dy * 150.0) / l;
    }
}
//! [3]

//! [4]
// Now subtract all forces pulling items together
//现在减去所有拉物体的力
double weight = (edgeList.size() + 1) * 10;
for (const Edge *edge : qAsConst(edgeList)) {
    QPointF vec;
    if (edge->sourceNode() == this)
        vec = mapToItem(edge->destNode(), 0, 0);
    else
        vec = mapToItem(edge->sourceNode(), 0, 0);
    xvel -= vec.x() / weight;
    yvel -= vec.y() / weight;
}
//! [4]

//! [5]
if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
    xvel = yvel = 0;
//! [5]

//! [6]
QRectF sceneRect = scene()->sceneRect();
newPos = pos() + QPointF(xvel, yvel);
newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + 10), sceneRect.right() - 10));
newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + 10), sceneRect.bottom() - 10));
}
//! [6]
*/
    //! [7]
    bool Node::advancePosition()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}
//! [7]

//! [8]
QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -20 - adjust, -20 - adjust, 43 + adjust, 43 + adjust);
}
//! [8]

//! [9]
QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-20, -20, 40, 40);
    return path;
}
//! [9]

//! [10]
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    qDebug() << 11111111111111111<<endl;
//        painter->setPen(Qt::NoPen);
//        painter->setBrush(Qt::darkGray);
//        painter->drawEllipse(-7, -7, 30, 30);

//        QRadialGradient gradient(-3, -3, 10);

//        if (option->state & QStyle::State_Sunken) {
//            gradient.setCenter(3, 3);
//            gradient.setFocalPoint(3, 3);
//            gradient.setColorAt(1, QColor(Qt::yellow).lighter(120));
//            gradient.setColorAt(0, QColor(Qt::darkYellow).lighter(120));
//        } else {
//            gradient.setColorAt(0, Qt::yellow);
//            gradient.setColorAt(1, Qt::darkYellow);
//        }

//        painter->setBrush(gradient);
    //从这里记录新的位置，在原来链表上找到这个节点下标，把原来的节点位置覆盖，进行重画,

    //时间戳
    QDateTime time = QDateTime::currentDateTime();   //获取当前时间

    int timeT = time.toTime_t();
    int time_a =timeT - node_time;
    qDebug() << time_a << "time-a";

        painter->setPen(QPen(Qt::black, 0));                        //绘制网络节点
        QRect node(-20,-20,40,40);
        painter->drawEllipse(node);
        flags = Qt::AlignHCenter | Qt::AlignVCenter;                //水平和垂直居中
        qDebug() << node_id << "id_a";


    //用find去找到NodeList_sta里面的id和node_id相同，然后把NodeList_sta里的X,Y换成新的坐标点
    //用槽函数，将数据传到mainwidows里的nodelist链表，

        painter->drawText(node,flags,node_id);

}
//! [10]

//! [11]
QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{

    switch (change) {
    case ItemPositionHasChanged:
        for (Edge *edge : qAsConst(edgeList))
            edge->adjust();
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);

}
//! [11]

//! [12]
void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

//void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    auto ics = graph->m_scene;
//    qDebug() << event->scenePos() << "event->scenePos()";

//    //获取每次鼠标在场景坐标系下的平移量
//    QPointF mouseDelta = mapToScene(event->pos()) - mapToScene(this->);
//    QPointF offset = event->scenePos();
//    const QList<QGraphicsItem *> itemsa = scene()->items();

//    qDebug() << itemsa.size() << "list.size()";
//    for(int index = 0;index < itemsa.size(); index++)
//    {
//        qDebug() << "mouseMove";
//        itemsa.at(index)->moveBy(offset.x(),offset.y());
//        qDebug() << itemsa.at(index) << "list.at(index)";
//    }

//}
//! [12]
