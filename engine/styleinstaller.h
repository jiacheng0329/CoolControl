#ifndef STYLEINSTALLER_H
#define STYLEINSTALLER_H
#include "mainwindow.h"
#include <QWidget>

#define STYLE_INSTALLER StyleInstaller::instance()

struct StyleString {
    QString light;
    QString text;
    QString back;
    QString control;
    QString hover;
    QString windowBack;
};
class StyleInstaller
{
public:
    static StyleInstaller* instance();
    static void deleteInstance();

    void install(const StyleString& s);
    void install(const QString& path);
    void append(const QString &style);

    static StyleString darkOrange;

private:
    //QString m_style;

    StyleInstaller();
    StyleInstaller(const StyleInstaller&)=delete;
    StyleInstaller& operator = (const StyleInstaller&)=delete;
    StyleInstaller(StyleInstaller&&)=delete;
    StyleInstaller& operator = (StyleInstaller&&)=delete;

    static StyleInstaller* uniqueInstance;


};

#endif // STYLEINSTALLER_H
