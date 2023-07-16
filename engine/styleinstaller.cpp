#include "styleinstaller.h"
#include <QApplication>
#include <QFile>

//QString light;QString text;QString back;QString control;QString hover;
StyleString StyleInstaller::darkOrange = {"rgb(247,105,0)", "rgb(210,210,210)", "rgb(67,68,69)"
                    , "rgb(40,40,40)",  "rgb(50,50,50)",  "rgb(105,105,105)"};


StyleInstaller *StyleInstaller::uniqueInstance = nullptr;

StyleInstaller *StyleInstaller::instance()
{
    if(!uniqueInstance) {
        uniqueInstance = new StyleInstaller;
    }
    return uniqueInstance;
}

void StyleInstaller::deleteInstance()
{
    if (uniqueInstance) {
        delete uniqueInstance;
    }
}

//-----------------------------------------------------------------------------
//自定义样式表
//-----------------------------------------------------------------------------
void StyleInstaller::install(const StyleString& s)
{
    QString style = "QDockWidget{background-color:lightgray;border:2px solid red;}"
              "MainWindow{background:[windowBack];}"
              //"QMdiArea{padding:5px;}"://engineicons/orange-right.svg://Icons/orange-image.svg

              "*{color:[text];background: [back];}"
              "QTreeView::branch{padding:3px;padding-bottom:10px;}"
              "QTreeView::branch:open:has-children{image:url(://engineicons/gray-down.svg);}"
              "QTreeView::branch:closed:has-children{image:url(://engineicons/gray-right.svg);}"
              "QTreeView::branch:open:has-children:hover{image:url(://engineicons/orange-down.svg);}"
              "QTreeView::branch:closed:has-children:hover{image:url(://engineicons/orange-right.svg);}"

              "QTreeWidget{outline:0px;background: [back];border:noe;padding:5px;}"
              "QTreeView::item{height:25px;margin-bottom:5px;color:[text];}"
              "QTreeView::item{border-bottom:1px solid transparent;}"
              "QTreeView::item:hover{color:[text];border-bottom:1px solid [light]"
                                    ";background: [hover];}"
              "QTreeView::item:selected{color:[text];border-bottom:1px solid [hover]"
                                    ";background: [hover];}"

              "QPushButton{background:[control];border:1px solid [windowBack];}"
              "QPushButton:focus{background:[control];border:1px solid [light];}"
              "QLineEdit{background:[control];border:1px solid rgb(105,105,105);}"
              "QLineEdit:hover{background:[control];border:1px solid [light];}"

              "QComboBox{background:[control];border:1px solid [windowBack];}"
              "QComboBox:checked{background:[control];border:1px solid [light];}"
              "QComboBox QAbstractItemView {background:[control];outline: 0px;border:1px solid [light];}"
              "QComboBox QAbstractItemView::item{height:25px;}"
              "QComboBox QAbstractItemView::item:hover{background:[windowBack];}"
              "QComboBox QAbstractItemView::item:selected{background:[windowBack];}"

             "QListWidget{background:[back];outline:0px;}"
             "QListWidget::item{border-bottom:1px solid transparent;height:30px;}"
             "QListWidget::item:hover{border-bottom:1px solid [light];background: [hover];}"
             "QListWidget::item:selected{border-bottom:1px solid transparent;background: [hover];}"

             "QLineEdit{background:[control];border:1px solid [windowBack];}"
             "QLineEdit:hover{background:[control];border:1px solid [light];}"

              "QScrollBar:vertical{margin-left:8px;width:14px;}"
              "QScrollBar::handle:vertical{background:[windowBack];border-radius:6px;}"
              "QScrollBar::sub-line:vertical{background:transparent;}"
              "QScrollBar::add-line:vertical{background:transparent;}"
              "QScrollBar::sub-page:vertical{background:transparent;}"
              "QScrollBar::add-page:vertical{background:transparent;}"

              "QLabel{background:transparent;}";

    style.replace("[light]", s.light);
    style.replace("[text]", s.text);
    style.replace("[back]", s.back);
    style.replace("[control]", s.control);
    style.replace("[hover]", s.hover);
    style.replace("[windowBack]", s.windowBack);

    qApp->setStyleSheet(style);
}

//-----------------------------------------------------------------------------
//加载已有样式
//-----------------------------------------------------------------------------
void StyleInstaller::install(const QString &path)
{
    QString qss;
    QFile file(path);

    if (file.open(QFile::ReadOnly)) {
        qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        file.close();
    }

}

void StyleInstaller::append(const QString &style)
{
    Q_UNUSED(style);
    //m_style.append(style);
    //m_window->setStyleSheet(m_style);
}

StyleInstaller::StyleInstaller()
{

}


