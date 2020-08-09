#include "ui_gamewindow.h"
#include "GameWindow.hpp"

#include <QFile>
#include <QTextStream>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setCentralWidget((QWidget*)&mainMenu);

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

    update();
}

GameWindow::~GameWindow()
{
    delete ui;
}
