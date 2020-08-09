#include "ui_gamewindow.h"
#include "GameWindow.hpp"

#include <QFile>
#include <QTextStream>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    QFile f(":/style/GameWindow.qss");
    if (!f.exists())
        printf("Style sheet for GameWindow is not present in resources.\n");
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        setStyleSheet(ts.readAll());
        f.close();
    }
    showMainMenu();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::showHighScores()
{
    // TODO: show high score widget
}

void GameWindow::showGame()
{
    // TODO: show game widget
}

void GameWindow::showMainMenu()
{
    setCentralWidget(new MainMenu(this));
    update();
}

void GameWindow::showCredits()
{
    setCentralWidget(new Credits(this));
    update();
}