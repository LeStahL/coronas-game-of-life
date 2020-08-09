#include "ui_mainmenu.h"
#include "MainMenu.hpp"
#include "GameWindow.hpp"
#include "Map.hpp"

#include <QFile>
#include <QTextStream>
#include <QDebug>

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    QFile f(":/style/MainMenu.qss");
    if (!f.exists())
        qDebug() << "Style sheet for MainMenu is not present in resources.\n";
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        setStyleSheet(ts.readAll());
        f.close();
    }

    QList<QString> availableMaps = Map::listMaps(":/maps");
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::playClicked()
{
    GameWindow *gameWindow = (GameWindow*) parent();
    gameWindow->showGame();
}

void MainMenu::highScoresClicked()
{
    GameWindow *gameWindow = (GameWindow*) parent();
    gameWindow->showHighScores();
}

void MainMenu::creditsClicked()
{
    GameWindow *gameWindow = (GameWindow*) parent();
    gameWindow->showCredits();
}