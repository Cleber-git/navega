#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&m_NetWorkM, SIGNAL(finished(QNetworkReply*)), this, SLOT(receiverDatas(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiverDatas(QNetworkReply* _reply){
    if(_reply->error() == QNetworkReply::NoError){
        ui->label->setStyleSheet("font-weight: bold ; color: green ;");
        ui->label->setText(_reply->readAll());
    }else{
        ui->label->setText(_reply->errorString());
        ui->label->setStyleSheet("font-weight: bold ; color: red ;");
    }
    _reply->deleteLater();
}

void MainWindow::on_pushButton_clicked()
{
    QString endPoint = ui->lineEdit->text();
    QUrl url("http://127.0.0.1:5000/"+ endPoint);
    QNetworkRequest request(url);
    m_NetWorkM.get(request);
}
