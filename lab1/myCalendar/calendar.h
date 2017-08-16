#ifndef CALENDAR_H
#define CALENDAR_H

#include<QCalendarWidget>
#include <QPainter>
#include <qcolor>
#include <qdate>
#include <qpen>
#include <qbrush>
#include <QVector>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class calendar: public QCalendarWidget
{
    Q_OBJECT
public:
    calendar();
    ~calendar();

    void setColor(QColor& color);
    QColor getColor();
protected:
    virtual void paintCell(QPainter * painter, const QRect & rect, const QDate & date) const;

private slots:
    void addNote( const QDate & );

private:
    QDate m_currentDate;
    QPen m_outlinePen;
    QBrush m_transparentBrush;

    QVector<QDate> dates;
    QVector<QString> todolist;

};

#endif // CALENDAR_H
