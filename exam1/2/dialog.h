#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QList>
#include <QRect>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    bool event(QEvent *event);
    bool eventFilter(QObject *object, QEvent *event);

private:
    Ui::Dialog *ui;
    QPoint dropPos;
    QList<QRect> rects;
    QList<QColor> colors;
    QList<bool> focus;
    QList<bool> deleted;

};

#endif // DIALOG_H
