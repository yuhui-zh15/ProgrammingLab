#include "mainwindow.h"
#include <QApplication>

#include"calendar.h"
#include<QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();

    calendar* cale = new calendar();
    cale->resize(QSize(screenRect.width()/2, screenRect.height()/2));
    cale->setWindowOpacity(0.5);
    cale->show();

    QObject::connect(cale,SIGNAL(activated(const QDate &)),cale,SLOT(addNote(const QDate &)));

    return a.exec();
}
