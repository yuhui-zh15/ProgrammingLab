#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

protected slots:
    void timeOut();

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_setButton_clicked();

private:
    Ui::Dialog *ui;
    int m_seconds;
    int m_finished;
    int m_left;
    QTimer* m_timer;
};

#endif // DIALOG_H
