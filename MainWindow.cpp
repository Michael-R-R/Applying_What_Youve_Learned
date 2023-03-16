#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTextCursor>
#include <QTextCharFormat>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fileMenu(new QMenu("File", this)),
    runFileAction(new QAction("Run", fileMenu)),
    openFileAction(new QAction("Open", fileMenu)),
    saveFileAction(new QAction("Save", fileMenu)),
    delimiterLineEdit(new QLineEdit(this)),
    contentEditor(new QPlainTextEdit(this)),
    logEditor(new QPlainTextEdit(this)),
    vSplitter(new QSplitter(Qt::Orientation::Vertical, this))
{
    ui->setupUi(this);

    ui->menubar->addMenu(fileMenu);

    fileMenu->addAction(runFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);

    ui->vMainLayout->addWidget(delimiterLineEdit);
    ui->vMainLayout->addWidget(vSplitter);

    vSplitter->addWidget(contentEditor);
    vSplitter->addWidget(logEditor);

    logEditor->setReadOnly(true);

    connect(runFileAction, &QAction::triggered, this, &MainWindow::runFile);
    connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveFileAction, &QAction::triggered, this, &MainWindow::saveFile);
    connect(this, &MainWindow::fileOpened, this, &MainWindow::processNewContent);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Open File...",
                                                    ".",
                                                    "Text Files (*.txt)");
    if(filePath.isEmpty())
        return;

    QFile inFile(filePath);
    if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    emit fileOpened(inFile.readAll());

    inFile.close();
}

void MainWindow::saveFile()
{
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Save File...",
                                                    ".",
                                                    "Text Files (*.txt)");
    if(filePath.isEmpty())
        return;

    QFile outFile(filePath);
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream outStream(&outFile);
    outStream << contentEditor->toPlainText();

    outFile.close();
}

void MainWindow::runFile()
{
    processNewContent(contentEditor->toPlainText());
}

void MainWindow::processNewContent(const QString& content)
{
    contentEditor->clear();
    logEditor->clear();

    QString line = "";
    int lineNum = 1;
    int prevIndex = 0;
    int currIndex = content.indexOf("\n") + 1;

    while(currIndex > 0)
    {
        line = content.mid(prevIndex, (currIndex - prevIndex));

        contentEditor->insertPlainText(line);

        processLineDelimiter(lineNum, line);

        prevIndex = currIndex;
        currIndex = content.indexOf("\n", currIndex) + 1;

        lineNum++;
    }
}

void MainWindow::processLineDelimiter(const int lineNum, const QString& line)
{
    const QString delimiter = delimiterLineEdit->text();
    if(delimiter.isEmpty())
        return;

    if(!line.contains(delimiter))
        return;

    QTextCharFormat normalFormat;
    normalFormat.setForeground(Qt::black);

    QTextCharFormat highlightFormat;
    highlightFormat.setForeground(Qt::red);

    QTextCursor logCursor = logEditor->textCursor();
    logCursor.insertText(QString("%1: ").arg(QString::number(lineNum)), normalFormat);

    int prevIndex = 0;
    int currIndex = line.indexOf(delimiter);

    while(currIndex > -1)
    {
        QString tempLine = line.mid(prevIndex, (currIndex - prevIndex));
        QString delimiterLine = line.mid(currIndex, delimiter.size());

        logCursor.insertText(tempLine, normalFormat);
        logCursor.insertText(delimiterLine, highlightFormat);

        prevIndex = currIndex + delimiter.size();
        currIndex = line.indexOf(delimiter, currIndex + 1);
    }

    if(prevIndex < line.size())
        logCursor.insertText(line.mid(prevIndex), normalFormat);
}











