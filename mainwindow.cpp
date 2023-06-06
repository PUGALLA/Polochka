#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QPushButton"
#include "QPixmap"
#include "QtMath"
#include "QString"
#include "string"
#include "cmath"
#include "poland.h"
#include "iostream"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 600);
    button = new QPushButton(this);
    button->setGeometry(width() * .85, 10, width() * .14, height() * 0.05);
    button->setText("Build graphic");
    connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    ui -> label -> setGeometry(10, 50, width()* 0.825, height()*0.9);
    ui -> lineEdit -> setGeometry(10, 10, width()* 0.825, height()*0.05);
    ui -> lineEdit_2 -> setGeometry(width() * .85, 70, width() * .14, height() * 0.05);
    ui -> lineEdit_3 -> setGeometry(width() * .85, 130, width() * .14, height() * 0.05);
    ui -> label_2 -> setGeometry(width() * .85, 40, width()* 0.1, height()*0.05);
    ui -> label_3 -> setGeometry(width() * .85, 100, width()* 0.1, height()*0.05);
    //lineEdit = new QLineEdit(this);
    //lineEdit -> setGeometry(width() * .01, 10, width() * .25, height() * .05);
    //ui->lineEdit_2->setText("09");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonClicked() {

    ui -> label -> setGeometry(10, 50, width()* 0.8, height()*0.9);
    QPixmap pm(width()* 0.8, height()*.9);
    QPainter painter;
    painter.begin(&pm);
    pm.fill(Qt::white);
    QPen pen;
    QString s = ui -> lineEdit -> text();
    QString temp = s;
    QString in = ui -> lineEdit_3 -> text();
    QString ax = ui -> lineEdit_2 -> text();
    double xmax = 10;
    double xmin = -10;
    if (ax != "") {
        xmax = ax.toDouble();
    }
    if (in != "") {
         xmin = in.toDouble();
    }
    double ymin = xmin, ymax = xmax;
    double xgmin = 0, xgmax = pm.width();
    double ygmin = 0, ygmax = pm.height();
    double x, y;
    double xg = 0, yg = 0;
    double kx = (xgmax - xgmin)/(xmax - xmin), ky = (ygmin - ygmax)/(ymax - ymin);
    double x0 = xgmin - kx * xmin, y0 = ygmin - ky * ymax;
    x = xmin;
    double stepx = (xmax-xmin)/(xgmax-xgmin);
    double ans = 0;
    painter.setPen(pen);
    pen.setWidth(1);
    pen.setCapStyle(Qt::FlatCap);
    pen.setColor(Qt::black);
    painter.drawLine(x0 - pm.width(), y0, x0 + pm.width(), y0);
    painter.drawLine(x0, y0 - pm.height(), x0, y0 + 2 * pm.height());
    QPainterPath qp;
    painter.setPen(pen);
    pen.setColor(Qt::red);
    x = xmin;
    QString t1 = QString::number(x);
    temp.replace("x", "(" + t1 + ")");
    while (calc(temp.toStdString(), ans) != 0) {
        x += stepx;
        QString t1 = QString::number(x);
        temp.replace("x", "(" + t1 + ")");
    }
    y = ans;
    temp = s;
    qp.moveTo(x0 + kx*x, y0 + ky*y);
    while (x <= xmax) {
        x += stepx;
        QString t1 = QString::number(x);
        temp.replace("x", "(" + t1 + ")");
        if (calc(temp.toStdString(), ans) == -1 || ans > ymax || ans < ymin) {
            x += stepx;
            QString t1 = QString::number(x);
            temp.replace("x", "(" + t1 + ")");
            while (calc(temp.toStdString(), ans) != 0) {
                x += stepx;
                QString t1 = QString::number(x);
                temp.replace("x", "(" + t1 + ")");
            }
            y = ans;
            temp = s;
            qp.moveTo(x0 + kx*x, y0 + ky*y);
            continue;
        }
        y = ans;
        xg = x0 + kx*x;
        yg = y0 + ky*y;
        painter.setPen(pen);
        pen.setColor(Qt::red);
        qp.lineTo(xg, yg);
        temp = s;
    }
    painter.drawPath(qp);

    painter.end();
    ui -> label -> setPixmap(pm);
}
