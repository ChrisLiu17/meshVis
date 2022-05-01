#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

class Node;

//! [0]
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr);

    void addNode(Node *node);    //
    QList<Node *> nodes() const; //

    void itemMoved();
    void json_node(QJsonArray nodearr);
public slots:
    void shuffle(); //拖动
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    //画板背景
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);

public:
    QGraphicsScene *m_scene = nullptr;

private:
    int timerId = 0;
    Node *centerNode = nullptr;
    // Node *Node_sta;
    QList<Node *> NodeList;
    GraphWidget *graphswidget_m = nullptr;
    Node *node_1 = nullptr;
    // QList<Node *> m_NodeList;
    // QGraphicsWidget *gra_item;
};
//! [0]

#endif // GRAPHWIDGET_H
