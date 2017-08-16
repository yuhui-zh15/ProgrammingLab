#include "dialog.h"
#include "ui_dialog.h"
#include <QTimer>
#include <QInputDialog>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    m_finished = 0;
    m_seconds = 1500;
    m_left = m_seconds;
    ui->setupUi(this);
    ui->label_1->setText("");
    ui->progressBar->setMaximum(m_seconds);
    ui->progressBar->setValue(m_seconds);
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeOut()));
}

void Dialog::timeOut() {
    m_left--;
    ui->progressBar->setValue(m_left);
    if (m_left == 0) {
        m_timer->stop();
        m_finished++;
        QVariant finished = m_finished;
        ui->label_1->setText("You have finished " + finished.toString() + " tomatoes.");
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_startButton_clicked()
{
     if (m_left) {
        ui->label_1->setText("");
        m_timer->start(1000);
    }
}

void Dialog::on_stopButton_clicked()
{
    m_left = m_seconds;
    ui->progressBar->setValue(m_left);
    m_timer->stop();
}


void Dialog::on_setButton_clicked()
{
    QString line = ui->lineEdit->text();
    m_seconds = line.toInt();
    m_left = m_seconds;
    m_timer->stop();
    ui->progressBar->setMaximum(m_seconds);
    ui->progressBar->setValue(m_seconds);
    qDebug() << "m_seconds = " << m_seconds;
}
