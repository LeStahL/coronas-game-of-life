#include <QApplication>
#include <QMainWindow>

#include "GameWindow.hpp"

int main(int argc, char **args)
{
    QApplication application(argc, args);
    GameWindow *gameWindow = new GameWindow();
    gameWindow->show();
    return application.exec();
}

