#ifndef MOUSEFILTER_H
#define MOUSEFILTER_H

#include <qobject.h>
#include <QEvent>
#include <QMouseEvent>
#include "chartshow.h"

class ChartShow;

class MouseFilter : public QObject
{
      Q_OBJECT
public:
       MouseFilter( QObject *pobj = 0 );

private:
       virtual bool eventFilter( QObject *, QEvent* );

};

#endif
