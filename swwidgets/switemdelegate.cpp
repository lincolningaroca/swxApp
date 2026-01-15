#include "switemdelegate.hpp"

SWItemDelegate::SWItemDelegate(QObject *parent):
  QStyledItemDelegate(parent)
{}


QSize SWItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{

  auto size = QStyledItemDelegate::sizeHint(option, index);
  size.setHeight(19);
  return size;
}
