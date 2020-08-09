#include "ui_mainmenu.h"
#include "MainMenu.hpp"

#include <QFile>
#include <QTextStream>

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    QFile f(":/style/MainMenu.qss");
    if (!f.exists())
        printf("Style sheet for MainMenu is not present in resources.\n");
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        setStyleSheet(ts.readAll());
        f.close();
    }
}

MainMenu::~MainMenu()
{
    delete ui;
}