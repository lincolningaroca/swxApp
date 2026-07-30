#pragma once

#include <QSqlQueryModel>

struct SWTableModel : public QSqlQueryModel {

  Q_OBJECT

public:
  explicit SWTableModel(QObject* parent = nullptr);

  // QAbstractItemModel interface
  QVariant data(const QModelIndex& index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};