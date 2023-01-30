//
// Created by regan on 2023/1/27.
//

#ifndef CLASHUX_SERVICEWIDGETITEM_H
#define CLASHUX_SERVICEWIDGETITEM_H

#include <QWidget>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class ServiceWidgetItem; }
QT_END_NAMESPACE

class ServiceWidgetItem : public QWidget {
Q_OBJECT

public:
    explicit ServiceWidgetItem(QString s1,QString s2,QString s3,QWidget *parent = nullptr);

    ~ServiceWidgetItem() override;
signals:
    void updateUI(int);
public slots:
    void resetlabel(int);
public:
    QString getServer();
private:
    Ui::ServiceWidgetItem *ui;
};


#endif //CLASHUX_SERVICEWIDGETITEM_H
