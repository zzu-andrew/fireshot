//
// Created by wangyz38535 on 2023/9/17.
//

#ifndef TEST_MAINWINDOW_H
#define TEST_MAINWINDOW_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <QDialog>

#include "config/tray_setting.h"

class ScreenShot;

class FireShot : public QDialog {
Q_OBJECT

public:
    explicit FireShot(QWidget *parent = nullptr);
    int32_t CreateActions();
    int32_t CreateTrayWithIcon();
    void ConstructSignal();


    ~FireShot() override;

signals:
    void SatrtShot();
    void ShotDone(FireShot* starer);
    void CheckHotKey(uint32_t value);
    void StopShot(FireShot* starter);

private slots:
    void OnStartShot();
    void OnShotDone(ScreenShot* starer);
    void OnExitShot();
    void OnShowSetting();

    void OnIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    QSystemTrayIcon* m_lpTrayIcon; // 放置一个系统托盘图标
    QMenu* m_lpTrayIconMenu;
    QAction* m_lpSettingAction;  // 系统托盘上的设置按钮
    QAction* m_lpShotAction;  // 截图按钮
    QAction* m_lpQuitAction; // 退出按钮
    SettingDlg *m_lpSettingDlg; // tray settings
    bool m_bShotting; // 是否正在截图

};


#endif //TEST_MAINWINDOW_H
