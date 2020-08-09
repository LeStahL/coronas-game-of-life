#pragma once

#include <QWidget>

namespace Ui { class MainMenu; }

class MainMenu : public QWidget
{
    Q_OBJECT

    public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

    private slots:
    void playClicked();
    void highScoresClicked();
    void creditsClicked();

    private:
    Ui::MainMenu *ui;
};
