#include "calendar.h"
#include <QtWidgets>
#include <QInputDialog>
#include <QTextCharFormat>
#include <QDebug>
#include <QtGlobal>
#include "draglabel.h"


calendar::calendar()
{
    m_outlinePen.setColor(Qt::red);
    m_transparentBrush.setColor(Qt::transparent);
    setAcceptDrops(true);
}

calendar::~calendar()
{

}


void calendar::addNote( const QDate &date )
{
    qDebug()<<"come in addNote"<<endl;
    QString memo = QInputDialog::getText( this,
            "Memo", "Description:" );

    if( !memo.isEmpty() ){
        QBrush brush;
        brush.setColor(Qt::yellow);

        QTextCharFormat cf = this->dateTextFormat(date);
        cf.setBackground(brush);
        this->setDateTextFormat(date, cf);
        if(dates.contains(date))
        {
            int index = dates.indexOf(date);
            todolist.replace(index, memo);
        }
        else
        {
            dates.append(date);
            todolist.append(memo);
        }
    }

}

void calendar::setColor(QColor& color)
{
   m_outlinePen.setColor(color);
}

QColor calendar::getColor()
{
   return (m_outlinePen.color());
}

void calendar::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
   //qDebug()<<"come in paintCell"<<endl;
   QCalendarWidget::paintCell(painter, rect, date);
   Q_ASSERT(dates.size()==todolist.size());
   for (int i = 0; i < dates.size(); i++)
   {
       if (date == dates.at(i))
       {
           painter->setPen(m_outlinePen);
           painter->setBrush(m_transparentBrush);
           painter->drawRect(rect.adjusted(0, 0, -1, -1));
           painter->drawText(rect,todolist.at(i));
       }
   }

}






