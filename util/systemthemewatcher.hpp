#pragma once

#include <QObject>
#include <QAbstractNativeEventFilter>

namespace SW {


struct SystemThemeWatcher : public QObject, QAbstractNativeEventFilter
{
  Q_OBJECT
public:
  explicit SystemThemeWatcher(QObject *parent = nullptr);

signals:

  void systemThemeChanged();

  // QAbstractNativeEventFilter interface
public:
  bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;
};


} // namespace SW
