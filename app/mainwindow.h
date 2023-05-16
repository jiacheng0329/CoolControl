#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mdiareawidget.h"
#include "listbutton.h"
#include "treeProperty.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void createDockWidget();
    void createCentralWidget();

    TreeProperty *controlTree;
    ListButton *controlList;
    MdiAreaWidget *centralWidget;
};
#endif // MAINWINDOW_H
