#pragma once

#include <QObject>
#include <QStyledItemDelegate>


class SWItemDelegate : public QStyledItemDelegate
{
  Q_OBJECT
public:
  explicit SWItemDelegate(QObject *parent = nullptr);

  // QAbstractItemDelegate interface
public:
  virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

  virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
