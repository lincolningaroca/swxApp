#pragma once

#include <QLabel>

class QMouseEvent;

class SWLabel : public QLabel{
  Q_OBJECT
public:
  explicit SWLabel(QWidget* parent = nullptr);

signals:
  void clicked();

  // QWidget interface
protected:
  void mousePressEvent(QMouseEvent* event) override;
};

