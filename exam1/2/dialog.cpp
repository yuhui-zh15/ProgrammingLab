#include "dialog.h"
#include "ui_dialog.h"
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
//    setFixedSize(400,300);
    ui->setupUi(this);
    this->installEventFilter(this);
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::eventFilter(QObject *object, QEvent *event) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (mouseEvent->button() == Qt::RightButton && keyEvent->modifiers() == Qt::ShiftModifier) {
        dropPos = mouseEvent->pos();

        for (int i = 0; i < rects.count(); i++) {
            if (rects.at(i).contains(dropPos)) {
                focus[i] = true;
            }
        }
        repaint();
        return true;
    }
    return false;
}

bool Dialog::event(QEvent *event) {
    return QDialog::event(event);
}

void Dialog::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {
        int flag = 0;
        dropPos = event->pos();
        for (int i = 0; i < rects.count(); i++) {
            if (rects.at(i).contains(dropPos)) {
                //TODO
                flag = 1;
            }
        }
        if (!flag) {
            if (dropPos.x() > 10 && dropPos.x() < width() - 10 && dropPos.y() > 10 && dropPos.y() < height() - 10) {
                rects.append(QRect(dropPos.x()-10, dropPos.y()-10, 20,20));
                focus.append(false);
                deleted.append(false);
            }
        }
        repaint();
    }
    else if(event->button() == Qt::RightButton) {
        dropPos = event->pos();

            for (int i = 0; i < rects.count(); i++) {
                if (rects.at(i).contains(dropPos)) {
                    focus[i] = !focus[i];
                }
                else {
                    focus[i] = false;
                }
            }
        repaint();
    }
}

void Dialog::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Up) {
        for (int i = 0; i < rects.count(); i++) {
            if (focus.at(i)) {
                if (rects.at(i).y()-1 < 0) return;
                QRect new_rect(rects.at(i).x(), rects.at(i).y()-1, 20, 20);
                rects[i] = new_rect;
            }
        }
        repaint();
    }
    else if (event->key() == Qt::Key_Down) {
        for (int i = 0; i < rects.count(); i++) {
            if (focus.at(i)) {
                if (rects.at(i).y()+1 > height()-20) return;
                QRect new_rect(rects.at(i).x(), rects.at(i).y()+1, 20, 20);
                rects[i] = new_rect;
            }
        }
        repaint();
    }
    else if (event->key() == Qt::Key_Left) {
        for (int i = 0; i < rects.count(); i++) {
            if (focus.at(i)) {
                if (rects.at(i).x()-1 < 0) return;
                QRect new_rect(rects.at(i).x()-1, rects.at(i).y(), 20, 20);
                rects[i] = new_rect;
            }
        }
        repaint();
    }
    else if (event->key() == Qt::Key_Right) {
        for (int i = 0; i < rects.count(); i++) {
            if (focus.at(i)) {
                if (rects.at(i).x()+1 > width()-20) return;
                QRect new_rect(rects.at(i).x()+1, rects.at(i).y(), 20, 20);
                rects[i] = new_rect;
            }
        }
        repaint();
    }
    else if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace) {
        for (int i = 0; i < rects.count(); i++) {
            if (focus.at(i)) {
                deleted[i] = true;
            }
        }
        repaint();
    }
}

void Dialog::paintEvent(QPaintEvent *event) {
    QPainter* painter = new QPainter(this);
    painter->setPen(Qt::transparent);
    for (int i = 0; i < rects.count(); i++) {
        if (focus.at(i)) painter->setBrush(Qt::red);
        else painter->setBrush(Qt::blue);
        if(!deleted.at(i)) painter->drawRect(rects.at(i));
    }
}
