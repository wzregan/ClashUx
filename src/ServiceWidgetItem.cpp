//
// Created by regan on 2023/1/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ServiceWidgetItem.h" resolved

#include "inc/ServiceWidgetItem.h"
#include "ui_ServiceWidgetItem.h"
#include <thread>

#include "SysUtil.h"
ServiceWidgetItem::~ServiceWidgetItem() {
    delete ui;
}

ServiceWidgetItem::ServiceWidgetItem(QString s1, QString s2, QString s3, QWidget *parent):QWidget(parent), ui(new Ui::ServiceWidgetItem){
    ui->setupUi(this);
    ui->label->setText(s1);
    ui->label_2->setText(s2);
    ui->label_3->setText(s3);
    connect( this, SIGNAL(updateUI(int)),this, SLOT(resetlabel(int)),Qt::BlockingQueuedConnection);
//    std::thread t([&](){
////        qDebug()<<s1.toStdString().c_str();
////        int rrt = ping("www.baidu.com");
////        qDebug()<<rrt;
//    });
//    t.detach();
}

void ServiceWidgetItem::resetlabel(int rrt) {
    if(rrt<100){
        this->ui->label_3->setStyleSheet("color:rgb(37, 174, 16 );");
    }else if(rrt > 100 && rrt < 300){
        this->ui->label_3->setStyleSheet("color:rgb(234, 178, 34);");
    }else if(rrt > 300 && rrt < 1000){
        this->ui->label_3->setStyleSheet("color:rgb(239, 9, 9);");
    }else{
        this->ui->label_3->setStyleSheet("color:red;");
        this->ui->label_3->setText("failed");
        return;
    }
    this->ui->label_3->setText(QString::fromStdString(std::to_string(rrt)));
}

QString ServiceWidgetItem::getServer() {
    return this->ui->label->text();
}
