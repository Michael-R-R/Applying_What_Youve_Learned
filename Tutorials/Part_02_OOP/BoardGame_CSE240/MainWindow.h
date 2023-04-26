#pragma once

#include <QMainWindow>

class Board;
class Game;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;

    Board* board;
    Game* game;

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
};

