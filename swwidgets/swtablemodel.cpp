#include "swtablemodel.hpp"

#include <QSqlRecord>

#include "util/helper.hpp"

SWTableModel::SWTableModel(QObject *parent, const QSqlDatabase &db)
  : QSqlTableModel{parent, db}
{

}

QVariant SWTableModel::data(const QModelIndex& index, int role) const{


  if((role == Qt::DisplayRole || role == Qt::ToolTipRole) && (index.column() == 1 || index.column() == 2) ){

    return SW::Helper_t::decrypt(QSqlTableModel::data(index, Qt::DisplayRole).toString());

  }

  return QSqlTableModel::data(index, role);

}

QVariant SWTableModel::headerData(int section, Qt::Orientation orientation, int role) const{

  Q_UNUSED(section)
  // 1. Si piden el tamaño (SizeHint)
  if (orientation == Qt::Vertical && role == Qt::SizeHintRole) {

    return QSize(0, 0); // Esto colapsa el ANCHO de la numeración lateral

  }

  if (orientation == Qt::Vertical && role == Qt::DisplayRole) {
    return QVariant();
  }


  // 3. PARA TODO LO DEMÁS (incluyendo títulos horizontales), usar la lógica base
  // Esto es lo que faltaba para que se vieran los títulos "URL", "Descripción", etc.
  return QSqlTableModel::headerData(section, orientation, role);


}
