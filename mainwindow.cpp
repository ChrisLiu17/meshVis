#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    Node *node;
    ui->setupUi(this);
    graphs = new GraphWidget();
    ui->graphicsView->setScene(graphs->m_scene);


    node = new Node(graphs);
    node->node_id = "1";
    nodeList.append(node);

    node = new Node(graphs);
    node->node_id = "2";
    nodeList.append(node);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    int pos_x = -300;
    int pos_y = -300;
    int sec_diff;
    Node *j_node;
    auto graphics = ui->graphicsView->scene();

    //    for (int i = 0;i <NodeList_sta.size();i++) {
    for (auto &i_node : nodeList)
    {
        pos_x += 100;
        pos_y += 100;

        int j;
        for (j = 0; j < m_nodeList.size(); j++)
        {
            j_node = m_nodeList.at(j);

            if (i_node->node_id == j_node->node_id)
            {
                break;
            }
        }
        if (m_nodeList.size() == j)
        {
            j_node = new Node(graphs);
            j_node->node_id = i_node->node_id;
            m_nodeList.append(j_node);
            graphics->addItem(j_node);
            j_node->setPos(pos_x, pos_y);
            qDebug() << "add" << i_node->node_id;
        }

        //更新时间戳
        j_node->node_time = QDateTime::currentDateTime().toTime_t();
    }

    //划线
    for (auto &i_node: m_nodeList)
    {
        for (auto &j_node: m_nodeList)
        {
            auto edge = new Edge(i_node, j_node);
            edge->Edge_linkquality = 11;            //demo
            graphics->addItem(edge);
        }
    }

    // 删除超时节点
    for (int i = 0; i < m_nodeList.size(); i++)
    {
        sec_diff = QDateTime::currentDateTime().toTime_t() - m_nodeList.at(i)->node_time;

        if (sec_diff > 3)
        {
            //删除该节点的所有线条
            for (int j = 0; j < m_nodeList.at(i)->edgeList.size(); j++)
            {
                graphics->removeItem(m_nodeList.at(i)->edgeList.at(j));
                m_nodeList.at(i)->edgeList.removeAt(j);
                j--;
            }
            qDebug() << "del" << m_nodeList.at(i)->node_id;
            graphics->removeItem(m_nodeList.at(i));
            m_nodeList.removeAt(i);
            i--;
        }
    }

    qDebug() << m_nodeList;
}

// clear
void MainWindow::on_pushButton_clicked()
{
    nodeList.clear();
    m_nodeList.clear();
    ui->graphicsView->scene()->clear();
}

// add a node
void MainWindow::on_pushButton_2_clicked()
{
    static int i = 1;
    auto node = new Node(graphs);
    node->node_id = QString::number(i++);
    nodeList.append(node);

    update();
}

