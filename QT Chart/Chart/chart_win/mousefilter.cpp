
#include <stdio.h>
#include "mousefilter.h"

extern ChartShow *ParentForm;

MouseFilter::MouseFilter( QObject *pobj)
   : QObject(pobj)
{
 ParentForm->thr->send_CN=1;
}

bool MouseFilter::eventFilter( QObject * pobj, QEvent* pe )
{
  if(pe->type() == QEvent::MouseButtonPress)
   {
    if(((QMouseEvent*)pe)->button()==Qt::LeftButton)
      {
        ParentForm->thr->send_CN=1;
        ParentForm->mouseObrab(pobj, 1, NULL);
        //frm->imit_obj = pobj;
        
      }
   }

 return false;
}


