#include "mainwindow.h"
#include "styleinstaller.h"
#include <QApplication>
#include <QTextCodec>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font(QStringLiteral("Microsoft YaHei UI"), 9);
    a.setFont(font);
    MainWindow w;
    STYLE_INSTALLER->install(StyleInstaller::darkOrange);
    w.show();

    return a.exec();
}
