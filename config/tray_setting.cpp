//
// Created by wangyz38535 on 2023/10/12.
//
#include <QDialog>

#include "tray_setting.h"

#include "ui_tray_settings.h"

SettingDlg::SettingDlg(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)  {
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::Tool | Qt::FramelessWindowHint);



}

SettingDlg::~SettingDlg() = default;
