//
// Created by wangyz38535 on 2023/10/12.
//

#ifndef QT_CLION_TRY_SETTING_H
#define QT_CLION_TRY_SETTING_H

#include <QDialog>

#include <QPushButton>
#include <QLabel>
#include <QCheckBox>

#include "ui_tray_settings.h"

class SettingDlg : public QDialog {
Q_OBJECT
public:
    SettingDlg(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~SettingDlg() override;

signals:
    void SaveHotKeyConfig();
    void UpdateHotKeyText(uint32_t value);
    void UpdateHotKeyResult(bool success);
    void InitHotKeyValue(uint32_t value);

private:
    Ui::Settings * ui;
};


#endif //QT_CLION_TRY_SETTING_H
