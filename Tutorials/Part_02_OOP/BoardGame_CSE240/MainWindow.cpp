#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Board.h"
#include "Game.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    board(new Board(8, 8, this)),
    game(new Game(*board, this))
{
    ui->setupUi(this);

    ui->vMainLayout->addWidget(board);

    game->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


