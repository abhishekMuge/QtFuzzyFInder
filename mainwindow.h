#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QVector>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QDirIterator>
#include <QSettings>
#include <QMenu>
#include <QAction>
#include "searchworker.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_SelectFolderBtnClick();
    void selectDirectory();
    void performSearch();
    void showContextMenu(const QPoint &pos);
    void selectAllFiles();
    void deselectAllFiles();
    void displayMatch(const QString &filePath);
private:
    int levenshteinDistance(const QString &str1, const QString &str2);
    void scanFiles(const QString &directory);
    bool fileContainsQuery(const QString &filePath, const QString &query);
    bool fuzzyMatch(const QString &text, const QString &query);
    void LoadAppInfoSetting();
    void SetAppInfoSetting(QString &dirInfo);

private:
    Ui::MainWindow *ui;
private:
    QLineEdit *searchInput;
    QListWidget *fileList;
    QTextEdit *resultDisplay;
};
#endif // MAINWINDOW_H
