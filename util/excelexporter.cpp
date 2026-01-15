#include "excelexporter.hpp"

#include <QAbstractItemModel>
#include <QTableView>
#include <QFileInfo>
#include <QDir>
#include <QSqlTableModel>
#include <QSqlRecord>

#include "xlsxdocument.h"

namespace  SW {

bool ExcelExporter::exportTableView(QTableView *tableView, const QString &filePath) {

  lastError_.clear();

  // 1. Verificación inicial de seguridad
  if (!tableView) {
    lastError_ = "Error: El TableView es nulo.";
    return false;
  }

  // Comprobación recomendada antes de extraer el modelo
  auto *model = tableView->model();
  if (!model) {
    lastError_ = "Error: La tabla no tiene un modelo de datos asignado.";
    return false;
  }

  // 2. Preparación del archivo
  QSet<QString> excludedColumns = {"url_id", "categoryid"};
  QString savePath = filePath;
  if (!savePath.endsWith(".xlsx", Qt::CaseInsensitive)) savePath += ".xlsx";

  // ... (Mantener validaciones de QFileInfo y QFile::remove que ya tienes)

  // 3. Creación del documento
  // IMPORTANTE: Constructor vacío para evitar el error de "invalid type id"
  QXlsx::Document xlsxDocument;

  // 4. Escribir Cabeceras
  int colExcel = 1;
  for (int col = 0; col < model->columnCount(); ++col) {
    // Omitir si la columna está oculta en la UI
    if (tableView->isColumnHidden(col)) continue;

    QString fieldName;
    if (auto sqlModel = qobject_cast<QSqlTableModel*>(model)) {
      fieldName = sqlModel->record().fieldName(col).toLower();
    }

    if (excludedColumns.contains(fieldName)) continue;

    xlsxDocument.write(1, colExcel++, model->headerData(col, Qt::Horizontal).toString());
  }

  // 5. Escribir Datos
  for (int row = 0; row < model->rowCount(); ++row) {
    colExcel = 1;
    for (int col = 0; col < model->columnCount(); ++col) {
      if (tableView->isColumnHidden(col)) continue;

      QString fieldName;
      if (auto sqlModel = qobject_cast<QSqlTableModel*>(model)) {
        fieldName = sqlModel->record().fieldName(col).toLower();
      }
      if (excludedColumns.contains(fieldName)) continue;

      // SOLUCIÓN AL ERROR DE TIPO:
      // Usamos Qt::DisplayRole para asegurar que recibimos el valor "limpio"
      QVariant data = model->data(model->index(row, col), Qt::DisplayRole);

      if (!data.isValid() || data.isNull()) {
        xlsxDocument.write(row + 2, colExcel++, "");
      } else {
        // QXlsx maneja mejor QVariant cuando el documento se inició vacío
        xlsxDocument.write(row + 2, colExcel++, data);
      }
    }
  }

  return xlsxDocument.saveAs(savePath);
}


}// namespace SW
