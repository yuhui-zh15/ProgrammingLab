#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "tempconverter.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private slots:
    void on_pushButton_clicked();

    void on_m_configureButton_clicked();

private:
    Ui::Widget *ui;
    TempConverter *tempConverter;
};

#endif // WIDGET_H
