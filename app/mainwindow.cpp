#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>
#include <QMdiArea>
#include "pltshower.h"
#include "imagelabel.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createDockWidget();
    createCentralWidget();

    //connect(controlList, SIGNAL(buttonChecked(int)), centralWidget, SLOT(SLOT()));

    setStyleSheet("QDockWidget{background-color:lightgray;border:2px solid red;}"
                  "MainWindow{background:rgb(105,105,105);}");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createDockWidget()
{
    QDockWidget* leftDock = new QDockWidget(this);
    controlTree = new TreeProperty(this);
    leftDock->setWidget(controlTree);
    leftDock->setObjectName(tr("leftDock"));
    leftDock->setWindowTitle(tr("控件选择"));
    this->addDockWidget(Qt::LeftDockWidgetArea, leftDock);
    leftDock->show();

    controlTree->addItem("PLT显示");
    controlTree->insertButtonProperty("PLT显示", "按钮");
    controlTree->insertEditProperty("PLT显示", "编辑框", "测试");
    QStringList list = {"测试1", "测试2", "测试3"};
    controlTree->insertComboProperty("PLT显示", "下拉框", list);

    controlTree->addItem("图片显示");
    controlTree->insertButtonProperty("图片显示", "按钮");
    controlTree->insertEditProperty("图片显示", "编辑框", "测试");
    QStringList list2 = {"测试1", "测试2", "测试3"};
    controlTree->insertComboProperty("图片显示", "下拉框", list2);

    controlTree->addItem("其它");
    controlTree->insertButtonProperty("其它", "按钮");
    controlTree->insertEditProperty("其它", "编辑框", "测试");
    QStringList list3 = {"测试1", "测试2", "测试3"};
    controlTree->insertComboProperty("其它", "下拉框", list3);

    controlTree->addItem("其他");
    controlTree->insertButtonProperty("其他", "按钮");
    controlTree->insertEditProperty("其他", "编辑框", "测试");
    QStringList list4 = {"测试1", "测试2", "测试3"};
    controlTree->insertComboProperty("其他", "下拉框", list4);

    QDockWidget* rightDock = new QDockWidget(this);
    controlList = new ListButton(this);
    rightDock->setWidget(controlList);
    rightDock->setObjectName(tr("rightDock"));
    rightDock->setWindowTitle(tr("右侧"));
    this->addDockWidget(Qt::RightDockWidgetArea, rightDock);
    rightDock->show();

    QDockWidget* bottomDock = new QDockWidget(this);
    bottomDock->setObjectName(tr("bottomDock"));
    bottomDock->setWindowTitle(tr("底部"));
    this->addDockWidget(Qt::BottomDockWidgetArea, bottomDock);
    bottomDock->show();

}

void MainWindow::createCentralWidget()
{
    centralWidget = new MdiAreaWidget(this);
    setCentralWidget(centralWidget);
}

