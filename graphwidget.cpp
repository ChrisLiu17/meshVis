#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

//! [0]
GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{

    qDebug() << "graphwidget-----";
    m_scene = new QGraphicsScene(this);
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    m_scene->setSceneRect(-400, -400, 800, 800);
    setScene(m_scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);
    setWindowTitle(tr("Elastic Nodes"));
    //! [0]

    //! [1]
//    Node *node1 = new Node(this);
//    Node *node2 = new Node(this);
//    Node *node3 = new Node(this);
//    Node *node4 = new Node(this);
//    centerNode = new Node(this);
//    Node *node6 = new Node(this);
//    Node *node7 = new Node(this);
//    Node *node8 = new Node(this);
//    Node *node9 = new Node(this);

//    int a = 2;
//    Node *node_a;
//    QList<Node *> m_NodeList;
//    int x = 50,y = 50;
//    for (int i =0; i < a; i++) {
//        node_a = new Node(this);
//        m_NodeList.append(node_a);
//        x += 50;
//        y += 50;
//        m_scene->addItem(node_a);
//        node_a->setPos(x,y);
//    }
//    m_scene->addItem(new Edge(m_NodeList.at(0),m_NodeList.at(1)));

//    scene->addItem(node2);
//    scene->addItem(node3);
//    scene->addItem(node4);
//    scene->addItem(centerNode);
//    scene->addItem(node6);
//    scene->addItem(node7);
//    scene->addItem(node8);
//    scene->addItem(node9);

//    scene->addItem(new Edge(node1, node2));             //场景显示连线
//    scene->addItem(new Edge(node2, node3));
//    scene->addItem(new Edge(node2, node1));
//    scene->addItem(new Edge(node2, centerNode));
//    scene->addItem(new Edge(node3, node6));
//    scene->addItem(new Edge(node4, node1));
//    scene->addItem(new Edge(node4, centerNode));
//    scene->addItem(new Edge(centerNode, node6));
//    scene->addItem(new Edge(centerNode, node8));
//    scene->addItem(new Edge(node6, node9));
//    scene->addItem(new Edge(node7, node4));
//    scene->addItem(new Edge(node8, node7));
//    scene->addItem(new Edge(node9, node8));

//    node1->setPos(-50, -50);
//    node2->setPos(0, -50);
//    node3->setPos(50, -50);
//    node4->setPos(-50, 0);
//    centerNode->setPos(0, 0);
//    node6->setPos(50, 0);
//    node7->setPos(-50, 50);
//    node8->setPos(0, 50);
//    node9->setPos(50, 50);

//    qDebug() << node1 << "node1";
//    Sleep(1000);
//    int x = 50,y = 50;
//    int a;
//    a= NodeList_m.size();
//    qDebug() << a << "NodeList_m.at(" << "111111111111" << ")";
//    if(NodeList_m.size() != 0){
//        qDebug() << "graphwidget";
//        for(int i = 0;i < NodeList_m.size();i++){
//            scene->addItem(NodeList_m.at(i));
//            x += 50;
//            y += 50;
//            NodeList_m.at(i)->setPos(x,y);
//            qDebug() << NodeList_m.size() << "aaaaaaaaaaaa";
//            qDebug() << x << "x";
//        }

//    }
}

void GraphWidget::addNode(Node *node)
{
    //Node *node = new Node(this);
    NodeList << node;
}

QList<Node *> GraphWidget::nodes() const
{
    return NodeList;
}
//! [1]
void GraphWidget::json_node(QJsonArray nodearr)
{
    qDebug() << "json_node";
    QJsonObject obj_node1;
    obj_node1.insert("id",41);
    obj_node1.insert("ip","192.168.10.42");
    obj_node1.insert("latitude",-90);
    obj_node1.insert("longitude",-180);
    QJsonObject obj_node2;
    obj_node2.insert("id",42);
    obj_node2.insert("ip","192.168.10.43");
    obj_node2.insert("latitude",-90);
    obj_node2.insert("longitude",-180);

    QJsonArray obj_arr;
    obj_arr.append(obj_node1);
    obj_arr.append(obj_node2);


    QJsonArray node_arr = obj_arr;
//    QString node_str = byte;
//    qDebug() << node_str<< "node_str";
//    QStringList nodeInfos_List = node_str.split("\n");
//    qDebug() << nodeInfos_List << "nodeInfos_List";
//    QList<QString> ::Iterator it = nodeInfos_List.begin(),itend = nodeInfos_List.end();
//    for(int i=0;it != itend;i++){

//    }
    //QJsonArray node_arr = nodearr;
    //Node *node;

    QJsonObject node_obj;

    QList<Node *> NodeList_sta;
    int x = 50,y = 50;
    for (int i=0;i < node_arr.size();i++) {
        qDebug() << node_arr[i].toObject()<< "node_obj" << i <<" toObject ";
        qDebug() << node_arr[i].toObject().value("id") << "node_arr[" << i <<"].toObject().value(id)";
        node_1 = new Node(this);
//        NodeList_sta.append(node1);
        //NodeList_m.append(node1);
        //qDebug() << NodeList_sta.at(i) << "NodeList_sta.at(" << i << ")";
        //qDebug() << NodeList_m.at(i) << "NodeList_m.at(" << i << ")";
        //addNode();
//        addNode(node1);
        //delete node1;

        //scene()->addItem(NodeList_sta.at(i));
        //NodeList_sta.at(i)->setPos(x,y);
        x += 50;
        y += 50;

        m_scene->addItem(node_1);
        node_1->setPos(x, y);
        qDebug() << node_1 << "node_1";

    }

    //x += 50;
    //y += 50;
    //qDebug() << x << "x";
//    qDebug() << NodeList_sta.at(1) << "NodeList_sta.at(1)";
//    qDebug() << NodeList_m.at(1) << "NodeList_m.at(1)";

//    qDebug() << NodeList_sta << "NodeList";
    //QList<Node *> NodeList_a;
    //NodeList_m = NodeList_sta;
//    scene()->addItem();


    //Node_sta = new Node(this);

    //while(1);


}
//! [2]
void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}


//! [2]

//! [3]
void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    //键盘
    switch (event->key()) {
    case Qt::Key_Up:
        centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}
//! [3]

//! [4]
void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

//    for (Node *node : qAsConst(nodes))
//        node->calculateForces();

//    bool itemsMoved = false;
//    for (Node *node : qAsConst(nodes)) {
//        if (node->advancePosition())
//            itemsMoved = true;
//    }

//    if (!itemsMoved) {
//        killTimer(timerId);
//        timerId = 0;
//    }


}
//! [4]

#if QT_CONFIG(wheelevent)
//! [5]
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow(2., -event->angleDelta().y() / 240.0));
}
//! [5]
#endif

//! [6]
void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{

    Q_UNUSED(rect);

    // Shadow
    // 阴影

    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
    /*
    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
                       "wheel or the '+' and '-' keys"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
    */
}
//! [6]

//! [7]
void GraphWidget::scaleView(qreal scaleFactor)
{
    //缩放
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);

}
//! [7]

void GraphWidget::shuffle()
{

    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }

}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
