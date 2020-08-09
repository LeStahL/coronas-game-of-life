#pragma once

#include <QWidget>

namespace Ui { class MainMenu; }

class MainMenu : public QWidget
{
    Q_OBJECT

    public:
    MainMenu(QWidget *parent = nullptr);
    explicit ~MainMenu();

    Ui::MainMenu *ui;
}
