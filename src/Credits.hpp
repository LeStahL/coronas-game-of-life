#pragma once

#include <QWidget>

namespace Ui { class Credits; }

class Credits : public QWidget
{
    Q_OBJECT

    public:
    Credits(QWidget *parent = nullptr);
    ~Credits();

    private slots:
    void backClicked();

    private:
    Ui::Credits *ui;
};
