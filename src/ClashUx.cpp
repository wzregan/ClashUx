//
// Created by regan on 2023/1/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ClashUx.h" resolved

#include "inc/ClashUx.h"
#include "ui_ClashUx.h"
#include "qtmaterialtoggle.h"
#include "qtmaterialtextfield.h"
#include "qtmaterialradiobutton.h"
#include "qtmaterialraisedbutton.h"
#include <stdlib.h>
#include <QFile>
#include <QDebug>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <spdlog/spdlog.h>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QListView>
#include "inc/ServiceWidgetItem.h"
#include <yaml-cpp/yaml.h>
#include "SysUtil.h"
#include <stdio.h>
#include <sstream>
int service_pid;
ClashUx::ClashUx(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::ClashUx) {
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/icon.png"));
    m_proxyClosed = true;
}

ClashUx::~ClashUx() {
    delete ui;
}

void ClashUx::init_trayIcon() {
    this->trayicon = new QSystemTrayIcon(this);
    this->trayicon->setIcon(QIcon(":/img/icon.png"));
    mp_menu = new QMenu();
    m_switchAction = new QAction("开启代理",mp_menu);
    mp_menu->addAction(m_switchAction);
    mp_menu->addSeparator();
    connect(m_switchAction,&QAction::triggered,this,&ClashUx::switchProxyStatus);
    m_exit = new QAction("退出", mp_menu);
    connect(m_exit, SIGNAL(triggered(bool)), this, SLOT(exit_program()));
    mp_menu->addAction(m_exit);
    mp_menu->addSeparator();
    QAction *m_show = new QAction("打开面板", mp_menu);
    mp_menu->addAction(m_show);
    connect(m_show, SIGNAL(triggered(bool )),this, SLOT(showWindow(bool )));

    this->trayicon->setContextMenu(mp_menu);
    this->trayicon->show();

    // 关闭代理
    system("export GIO_EXTRA_MODULES=/usr/lib/x86_64-linux-gnu/gio/modules/ && gsettings set org.gnome.system.proxy mode 'none'");
}

void ClashUx::switchProxyStatus() {
    m_proxy->toggle();
}

//
void ClashUx::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    kill(service_pid,SIGKILL);
    if(!m_proxyClosed){
        switchProxyStatus();
    }
    exit(0);
}

void ClashUx::init_tab() {
    m_tab = new QtMaterialTabs(this);
    QAction *log_action = new QAction("日志",m_tab);
    QAction *config_action = new QAction("配置",m_tab);
    QAction *setting_action = new QAction("设置",m_tab);

    this->ui->top->addWidget(m_tab);
    this->ui->centralwidget->setContentsMargins(0,0,0,0);
    this->ui->top->setContentsMargins(0,0,0,0);
    m_tab->addTab("代理",QIcon(":/img/top/jiekoupeizhi.svg"));
    m_tab->addTab("日志",QIcon(":/img/top/icon-rizhi.svg"));
    m_tab->addTab("设置",QIcon(":/img/top/shezhi.svg"));
    m_tab->layout()->setContentsMargins(0,0,0,0);
    connect(m_tab,SIGNAL(currentChanged(int)),this, SLOT(switchtab(int)));

    QtMaterialToggle * sws = new QtMaterialToggle();
    m_lancon = new QtMaterialToggle();
    m_proxy = new QtMaterialToggle();
    m_hide = new QtMaterialToggle();
    connect(m_hide, SIGNAL(toggled(bool)),this, SLOT(hideWindow(bool)));
    connect(m_proxy, SIGNAL(toggled(bool)),this, SLOT(proxyClick(bool)));
    m_hide->setFixedSize(55,40);
    sws->setFixedSize(55,40);
    m_lancon->setFixedSize(55,40);
    m_proxy->setFixedSize(55,40);
    this->ui->gridLayout->addWidget(m_proxy,0,1);
    this->ui->gridLayout->addWidget(sws,1,1);
    this->ui->gridLayout->addWidget(m_lancon,2,1);
    this->ui->gridLayout->addWidget(m_hide,3,1);

    this->ui->gridLayout->setVerticalSpacing(15);
    m_proxyport = new QtMaterialTextField();
    m_proxyport->setLabel("混合代理端口");
    m_proxyport->setText("7890");

//    this->ui->setting_vl->addWidget(proxyport);
    //    sws->setFixedSize(70,50);
//    lancon->setFixedSize(70,50);
//    this->ui->setting_layout->
    m_global = new QtMaterialRadioButton();
    m_global->setText("全局");
    const QFont &qFont = m_global->font();
    m_rule = new QtMaterialRadioButton();
    m_rule->setText("规则");
    m_direct = new QtMaterialRadioButton();
    m_direct->setText("直连");
    auto config = GetConfigMessage();
    std::string mode = config["mode"];
    bool allowlan = config["allow-lan"];
    m_lancon->toggled(allowlan);
    if(mode=="rule"){
        m_rule->setChecked(true);
    }else if(mode=="global"){
        m_global->setChecked(true);
    }else{
        m_direct->setChecked(true);
    }

    connect(m_global, SIGNAL(clicked()),this, SLOT(update_config()));
    connect(m_rule, SIGNAL(clicked()),this, SLOT(update_config()));
    connect(m_direct, SIGNAL(clicked()),this, SLOT(update_config()));
    connect(m_lancon, SIGNAL(toggled(bool)),this, SLOT(update_config()));
    connect(m_proxyport, SIGNAL(editingFinished()),this, SLOT(update_config()));
//    this
//    qhl->addWidget(rule);
//    qhl->addWidget(direct);
    this->ui->verticalLayout->setSpacing(15);
    this->ui->verticalLayout->addWidget(m_global);
    this->ui->verticalLayout->addWidget(m_rule);
    this->ui->verticalLayout->addWidget(m_direct);
    this->ui->verticalLayout->addWidget(m_proxyport);
    QtMaterialRaisedButton *btn_import = new QtMaterialRaisedButton();
    btn_import->setText("导入配置");
    this->ui->configlayout->addWidget(btn_import);
    connect(btn_import, SIGNAL(clicked()),this, SLOT(importconfig()));
    QtMaterialRaisedButton* btn = new QtMaterialRaisedButton();
    btn->setText("一键测速");
    this->ui->verticalLayout_3->addWidget(btn);
    connect(btn, SIGNAL(clicked()),this, SLOT(checkspeed()));
}



void ClashUx::switchtab(int idx) {
    this->ui->stackedWidget->setCurrentIndex(idx);
}

void ClashUx::importconfig() {
   QString filename = QFileDialog::getOpenFileName(this,"选择配置文件", nullptr,"*.yaml");
   if(filename==""){
       return;
   }
   QFile qf(filename);
   QFile oldqf("./.config/config.yaml");
   if(oldqf.exists()){
       oldqf.remove();
       qf.copy("./.config/config.yaml");
   }else{
       qf.copy("./.config/config.yaml");
   }
    QMessageBox::information(this,"提示","请重新启动程序");
    int ret = kill(service_pid,SIGKILL);
    if(!m_proxyClosed){
        switchProxyStatus();
    }
    exit(0);

}
#include <iostream>
#include <QThread>

void ClashUx::init_serverList() {
    YAML::Node cfg = YAML::LoadFile("./.config/config.yaml");
    std::cout<<(cfg["proxies"][0]["server"].as<std::string>())<<std::endl;
    for(int i = 0;i < cfg["proxies"].size(); i++){
        QString  server = cfg["proxies"][i]["server"].as<std::string>().c_str();
        QString  name = cfg["proxies"][i]["name"].as<std::string>().c_str();
        addServiceItem(server,name,"-");
    }
}
#include "SysUtil.h"
void ClashUx::addServiceItem(QString s1, QString s2, QString s3) {
    QListWidgetItem *qi = new QListWidgetItem(this->ui->listWidget);
    qi->setSizeHint(QSize(ui->listWidget->width(),35));
    this->ui->listWidget->setItemWidget(qi,new ServiceWidgetItem(s1,s2,s3));
}
class updatespeedThread:public QThread{
protected:
    void run() override {
    }
};
void ClashUx::checkspeed() {
    std::thread t([&](){
        for(int i = 0;i<this->ui->listWidget->count();i++){
            ServiceWidgetItem* swi =(ServiceWidgetItem*) this->ui->listWidget->itemWidget(this->ui->listWidget->item(i));
            qDebug()<<swi->getServer().toStdString().c_str();
            int s = ping(swi->getServer().toStdString().c_str());
            emit swi->resetlabel(s);
        }
    });
    t.detach();

}

void ClashUx::proxyClick(bool checked) {
    qDebug()<<checked;
    if(checked){
        // 如果代理处于关闭状态
        m_proxyClosed = !checked;
        system("export GIO_EXTRA_MODULES=/usr/lib/x86_64-linux-gnu/gio/modules/ && gsettings set org.gnome.system.proxy mode 'manual'");
        m_switchAction->setText("关闭代理");
    }else{
        // 如果代理处于开启状态
        system("export GIO_EXTRA_MODULES=/usr/lib/x86_64-linux-gnu/gio/modules/ && gsettings set org.gnome.system.proxy mode 'none'");
        m_switchAction->setText("开启代理");
        m_proxyClosed =!checked;
    }
}
void ClashUx::update_config() {
    auto config = GetConfigMessage();
    int port = m_proxyport->text().toInt();
    std::string mode;
    if(m_global->isChecked()){
        mode = "global";
    }else if(m_rule->isChecked()){
        mode = "rule";
    }else if(m_direct->isChecked()){
        mode = "direct";
    }
    bool allow_lan = !m_lancon->isChecked();
    config["mixed-port"] = port;
    config["mode"] = mode;
    config["allow-lan"] = allow_lan;
    updateConfig(config);
    qDebug()<<allow_lan;
}
int fd[2];
void ClashUx::startService() {
    if(pipe(fd)==-1)
        exit(-1);
    int pid = fork();
    if(pid==0){
        // children
        ::close(1);
        ::close(2);
        dup(fd[1]);
        dup(fd[1]);
        system("./clash-service -f ./.config/config.yaml");
    }else{
        service_pid = pid;
        // parents
        std::thread t([&](){
            char buf[512];
            read(fd[0],buf,512);
            QTextDocument *doc = this->ui->textEdit->document();
            QTextCursor cursor(doc);
            std::stringstream  ss;
            while(read(fd[0],buf,512)>=0){
                ss<<"<h4>"<<buf<<"</h4>";
                cursor.insertHtml(ss.str().c_str());
            }
        });
        t.detach();
    }
}

void ClashUx::init() {
    init_trayIcon();
    init_tab();
    init_serverList();
}

void ClashUx::exit_program() {
    kill(service_pid,SIGKILL);
    if(!m_proxyClosed){
        switchProxyStatus();
    }
    exit(0);
}
void ClashUx::hideWindow(bool isok){
    if(isok){
        this->setWindowFlag(Qt::Tool);
        this->setHidden(true);
    }else{
        this->setWindowFlag(Qt::Tool,false);
        this->setHidden(false);
    }
}

void ClashUx::showWindow(bool isok) {
//    this->setWindowFlag(Qt::Tool,false);
//    this->setHidden(false);
    this->m_hide->toggle();
}

