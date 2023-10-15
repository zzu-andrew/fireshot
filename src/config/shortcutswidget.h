// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2020 Yurii Puchkov at Namecheap & Contributors

#ifndef HOTKEYSCONFIG_H
#define HOTKEYSCONFIG_H

#include "src/utils/confighandler.h"
#include <QStringList>
#include <QVector>
#include <QWidget>

class SetShortcutDialog;
class QTableWidget;
class QVBoxLayout;

class ShortcutsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShortcutsWidget(QWidget* parent = nullptr);

private:
    void initInfoTable();

private slots:
    void populateInfoTable();
    void onShortcutCellClicked(int, int);

private:

    ConfigHandler m_config;
    QTableWidget* m_table;
    QVBoxLayout* m_layout;
    QList<QStringList> m_shortcuts;

    void loadShortcuts();
    void appendShortcut(const QString& shortcutName,
                        const QString& description);
};

#endif // HOTKEYSCONFIG_H
