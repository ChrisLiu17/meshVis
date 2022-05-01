#include "edge.h"
#include "node.h"
#include "math.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <complex> //三角函数
#include <QColor>
#define PI 3.14159265
#define LINKQUALITY_A 1
#define LINKQUALITY_B 5
#define LINKQUALITY_C 10
//! [0]
Edge::Edge(Node *sourceNode, Node *destNode)
    : source(sourceNode), dest(destNode)
{
    setAcceptedMouseButtons(Qt::NoButton); //元素拖动
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
}
//! [0]

//! [1]
Node *Edge::sourceNode() const
{
    return source;
}

Node *Edge::destNode() const
{
    return dest;
}
//! [1]

//! [2]

void Edge::adjust()
{

    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0)); //其他图元到本图元
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(10.))
    {
        QPointF edgeOffset((line.dx() * 20) / length, (line.dy() * 20) / length); //曲线顶点
        sourcePoint = line.p1() + edgeOffset;                                     //起始点
        destPoint = line.p2() - edgeOffset;                                       //结束点
    }
    else
    {
        sourcePoint = destPoint = line.p1();
    }
}

//! [2]

//! [3]
QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    QPoint point(400, 400);
    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(), //根据矩形面积重绘
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra - point.x(), -extra - point.y(), extra + point.x(), extra + point.y()); //返回新的矩形
}
//! [3]

//! [4]
void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    QColor color;
    // 贝塞尔曲线的端点
    breakPoints.append(new QPointF(-50, -50));

    if (!source || !dest)
        return;

    if (Edge_linkquality >= LINKQUALITY_A && Edge_linkquality <= LINKQUALITY_B)
    {
        color.setRgb(204, 51, 51, 255);
    }
    else if (Edge_linkquality >= LINKQUALITY_B && Edge_linkquality <= LINKQUALITY_C)
    {
        color.setRgb(255, 153, 0, 255);
    }
    else if (Edge_linkquality > LINKQUALITY_C)
    {
        color.setRgb(51, 153, 51, 255);
    }
    else
    {
        return;
    }

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;
    //! [4]
    QLineF revline(destPoint, sourcePoint);

    //! [5]
    // Draw the line itself
    //画一条线
    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    double angleline = std::atan2(-line.dy(), line.dx());
    double result = angleline * 180 / PI;
    int control_ver = 40;
    double control_x = control_ver * std::sin(result * PI / 180);
    double control_y = control_ver * std::cos(result * PI / 180);
    //    qDebug() << control_x << "control_x"<< control_y << "control_y";

    //贝塞尔曲线控制点
    QPointF controlPoint;
    // QPointF control(50,50);
    controlPoint.setX((sourcePoint.x() + destPoint.x()) / 2 - control_x);
    controlPoint.setY((sourcePoint.y() + destPoint.y()) / 2 - control_y);
    QPainterPath path;
    path.moveTo(QPointF(sourcePoint));
    path.quadTo(controlPoint, destPoint);
    painter->drawPath(path);
    // qDebug() << controlPoint << "control";
    //    qDebug() << sourcePoint << "soucePoint";
    /*
    QPointF controlPointrev;
    //QPointF control(50,50);
    controlPointrev.setX((sourcePoint.x() + destPoint.x())/2 + control_x);
    controlPointrev.setY((sourcePoint.y() + destPoint.y())/2 + control_y);
    QPainterPath path1;
    path1.moveTo(QPointF(destPoint));
    path1.quadTo(controlPointrev,sourcePoint);
    painter->drawPath(path1);
    //qDebug() << controlPointrev <<"controlPointrev";
    */

    //! [5]

    //! [6]

    // Draw the arrows
    //画箭头
    double angle = std::atan2(-line.dy(), line.dx()); //反正切 [-PI,PI] angle为弧度值
    double angleadd = angle + 30 * PI / 180;

    //    QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angleadd + M_PI / 6) * arrowSize,             //计算对边          //下半部分
    //                                                  cos(angleadd + M_PI / 6) * arrowSize);            //计算临边
    //    QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angleadd + M_PI / 3) * arrowSize,             //上半部分
    //                                                  cos(angleadd + M_PI / 3) * arrowSize);

    QPointF destArrowP1 = destPoint + QPointF(sin(angleadd + M_PI + M_PI / 6) * arrowSize,
                                              cos(angleadd + M_PI + M_PI / 6) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angleadd + M_PI + M_PI / 3) * arrowSize,
                                              cos(angleadd + M_PI + M_PI / 3) * arrowSize);
    painter->setBrush(color);
    //    painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);               //画多边形
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);

    //画节点质量

    int x = (sourcePoint.x() + destPoint.x()) / 2;
    int y = (sourcePoint.y() + destPoint.y()) / 2;
    QRect rect(x - 15, y - 35, 30, 30);
    QRect rectrev(x - 15, y + 5, 30, 30);
    flags = Qt::AlignHCenter | Qt::AlignVCenter; //水平和垂直居中
    painter->setBrush(Qt::lightGray);
    // painter->drawEllipse(rect);
    // painter->drawEllipse(rectrev);
    // painter->drawText(rect,flags,QString("20"));
    // painter->drawText(rectrev,flags,QString("16"));
    QString Edge_linkquality_str;
    Edge_linkquality_str = QString::number(Edge_linkquality);
    painter->drawText(QRect(controlPoint.x(), controlPoint.y() - 10, 30, 30), Edge_linkquality_str);
    //    painter->drawText(QRect(controlPointrev.x(),controlPointrev.y() - 10,30,30),Edge_linkquality);
    //    painter->drawText(QRect(10,200,150,50),"SNR");

    // painter->drawLine(line);
    // painter->drawLine(revline);
    /*
    //painter->drawArc(10,20,80,80,270*16,60*16);
    //painter->drawEllipse(0,0,200,100);

    QPoint startPt(100,100);
    QPoint endPt(100,200);
    QPoint ctrlPt1(120,150);
    QPoint ctrlPt2(150,80);

    QPainterPath path;
    //path.lineTo(100, 0);
    //path.cubicTo(200, 0, 100, 50, 200, 100); // 贝塞尔曲线
    //path.closeSubpath(); // 画一条线到路径的第一个点，闭合路径
    //path.addRect(50, 50, 50, 50);//加一个矩形
    //path.moveTo();
    path.quadTo(sourcePoint, destPoint);
    //path.quadTo(destPoint,sourcePoint);
    //path.quadTo(ctrlPt2,endPt);       //第一个参数是控制点，第二个参数是曲线的终点
    painter->drawPath(path);

    */
    /*
//贝塞尔曲线中垂线斜率计算
double angleline = std::atan2(-line.dy(), line.dx());
double result = angleline*180/PI;
qDebug() << result << "result";
double res = std::tan(result);
double rev = -(1/res);
qDebug() << res << "res";
qDebug() << rev << "rev";
*/
    /*
double param = -line.dy()/line.dx();
double angleline = atan(param);
double result = angleline*180/PI;                       //角度
*/
    /*
double angleline = std::atan2(-line.dy(), line.dx());
double result = angleline*180/PI;


    if(fabs(result) <= 30 || fabs(result) >= 60 ){
    result = 45;
}

if( result <= 30 && result >=0 ){
    result = 30;
}else if(result >= 60 && result < 90 ){
    result = 60;
}else if(result >= -30 && result <= 0 ){
    result = -30;
}else if(result > -90 && result <= -60){
    result = -60;
}else if (result == 90){
    result = 60;
}else if (result == -90) {
    result = -60;
}

qDebug() << result << "result";
double res = std::tan(result*PI/180);
qDebug() << res << "res";

int control_x = 30;
int control_y = control_x*res;
qDebug() << control_x << control_y << "control";
*/
}
//! [6]
