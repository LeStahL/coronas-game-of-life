#pragma once

#include <QMainWindow>

#include "MainMenu.hpp"
#include "Credits.hpp"

namespace Ui { class GameWindow; }

class GameWindow : public QMainWindow
{
    Q_OBJECT

    public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void showCredits();
    void showGame();
    void showHighScores();
    void showMainMenu();

    Ui::GameWindow *ui;
};
