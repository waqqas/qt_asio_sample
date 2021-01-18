#ifndef APP_EVENTS_H
#define APP_EVENTS_H

#include <QEvent>

const QEvent::Type ADD_RESULT_EVENT = static_cast<QEvent::Type>(QEvent::User + 1);

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

const QEvent::Type ADD_REQUEST_EVENT = static_cast<QEvent::Type>(QEvent::User + 2);

class AddRequestEvent : public QEvent
{
 public:
   AddRequestEvent(const int &param1, const int &param2)
      : QEvent(ADD_REQUEST_EVENT)
      , _param1(param1)
      , _param2(param2)
   {}

   int param1() const
   {
      return _param1;
   }

   int param2() const
   {
      return _param2;
   }

 private:
   int _param1;
   int _param2;
};

#endif
