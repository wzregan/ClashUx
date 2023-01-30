#include <iostream>
#include <QString>
#include <QApplication>
#include "inc/ClashUx.h"
#include <stdio.h>
#include <unistd.h>
#include <spdlog/spdlog.h>
#include <QFile>
int main(int argc,char ** args) {
    QApplication app(argc,args);
    ClashUx ux;
    ux.startService();
    ux.init();
    ux.show();
    return app.exec();
}
