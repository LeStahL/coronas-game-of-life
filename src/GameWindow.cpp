#include "ui_gamewindow.h"
#include "GameWindow.hpp"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setCentralWidget((QWidget*)&mainMenu);

    update();
}

GameWindow::~GameWindow()
{
    delete ui;
}
