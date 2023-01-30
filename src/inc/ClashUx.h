//
// Created by regan on 2023/1/24.
//

#ifndef CLASHUX_CLASHUX_H
#define CLASHUX_CLASHUX_H
#include "qtmaterialtabs.h"
#include "qtmaterialtoggle.h"
#include "qtmaterialradiobutton.h"
#include "qtmaterialtextfield.h"
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class ClashUx; }
QT_END_NAMESPACE

class ClashUx : public QMainWindow {
Q_OBJECT

public:
    explicit ClashUx(QWidget *parent = nullptr);
    ~ClashUx() override;

private:
    bool m_proxyClosed;
// menu_action
private:
    QAction *m_switchAction;
    QAction *m_exit;
    QtMaterialTabs *m_tab;
    QtMaterialToggle * m_proxy;
    QtMaterialToggle * m_hide;
    QtMaterialRadioButton * m_global;
    QtMaterialRadioButton * m_rule;
    QtMaterialRadioButton * m_direct;
    QtMaterialTextField *m_proxyport;
    QtMaterialToggle * m_lancon;

private:
    void init_trayIcon();
    void init_tab();
    void init_serverList();
private:
    void addServiceItem(QString s1,QString s2,QString s3);
public:
    void startService();
    void init();
private:
    QSystemTrayIcon * trayicon;
private:
    Ui::ClashUx *ui;
    QMenu * mp_menu;
private slots:
    void switchProxyStatus();
    void switchtab(int idx);
    void importconfig();
    void checkspeed();
    void proxyClick(bool checked);
    void update_config();
    void exit_program();
    void hideWindow(bool);
    void showWindow(bool);

protected:
    void closeEvent(QCloseEvent *event) override;
};


#endif //CLASHUX_CLASHUX_H
