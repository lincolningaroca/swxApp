#include "systemthemewatcher.hpp"

#ifdef Q_OS_WIN
#include <windows.h>
#endif

namespace SW {


SystemThemeWatcher::SystemThemeWatcher(QObject *parent)
  : QObject{parent}
{}

bool SystemThemeWatcher::nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result){
  Q_UNUSED(result)

#ifdef Q_OS_WIN

  if(eventType == "windows_generic_MSG"){

    const MSG *msg = static_cast<MSG*>(message);
    if(msg->message == WM_SETTINGCHANGE){

      emit systemThemeChanged();

    }
  }
#else

  Q_UNUSED(eventType)
  Q_UNUSED(message)
  Q_UNUSED(result)
#endif

  return false;
}
} // namespace SW
