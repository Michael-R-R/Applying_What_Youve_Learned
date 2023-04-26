#pragma once

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QSplitter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow* ui;

    QMenu* fileMenu;

    QAction* runAction;
    QAction* openFileAction;
    QAction* saveFileAction;

    QLineEdit* delimiterLineEdit;

    QPlainTextEdit* contentEditor;
    QPlainTextEdit* logEditor;

    QSplitter* vSplitter;

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void runFile();
    void openFile();
    void saveFile();
    void processNewContent(const QString& content);
    void processLineDelimiter(const int lineNum, const QString& line);

signals:
    void fileOpened(const QString& content);
};
