#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <node.h>
#include <edge.h>
#include <graphwidget.h>
#include<windows.h> //Sleep

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void update();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    GraphWidget *graphs = nullptr;
    Node *node_main = nullptr;
    QList<Node *> m_nodeList;
    QList<Node *> nodeList;
    QGraphicsScene *m_scene = nullptr;
};
#endif // MAINWINDOW_H
