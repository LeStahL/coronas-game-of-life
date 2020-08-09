#include "ui_credits.h"
#include "Credits.hpp"
#include "GameWindow.hpp"

#include <QFile>
#include <QTextStream>

Credits::Credits(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Credits)
{
    ui->setupUi(this);

    QFile f(":/style/Credits.qss");
    if (!f.exists())
        printf("Style sheet for Credits is not present in resources.\n");
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        setStyleSheet(ts.readAll());
        f.close();
    }
}

Credits::~Credits()
{
    delete ui;
}

void Credits::backClicked()
{
    GameWindow *gameWindow = (GameWindow*) parent();
    gameWindow->showMainMenu();
}