#ifndef APP_EVENTS_H
#define APP_EVENTS_H

#include <QEvent>

const QEvent::Type ADD_RESULT_EVENT = static_cast<QEvent::Type>(QEvent::User + 1);

// Define your custom event subclass
class AddResultEvent : public QEvent
{
 public:
   AddResultEvent(const int &result)
      : QEvent(ADD_RESULT_EVENT)
      , _result(result)
   {}

   int result() const
   {
      return _result;
   }

 private:
   int _result;
};

#endif
