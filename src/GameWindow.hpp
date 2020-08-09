#pragma once

#include <QMainWindow>

#include "MainMenu.hpp"

namespace Ui { class GameWindow; }

class GameWindow : public QMainWindow
{
    Q_OBJECT

    public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    MainMenu mainMenu;
    Ui::GameWindow *ui;
};