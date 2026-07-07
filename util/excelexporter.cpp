#include "excelexporter.hpp"

#include "xlsxdocument.h"
#include <QAbstractItemModel>

#include <QDir>
#include <QHeaderView>
#include <QFileInfo>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QTableView>

#include <QAbstractItemModel>
#include <QDir>
#include <QFileInfo>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QTableView>

namespace  SW {

bool ExcelExporter::exportTableView(QTableView *tableView, const QString &filePath) {

  lastError_.clear();

  if (!tableView) {
	lastError_ = "Error: El TableView es nulo.";
	return false;
  }

  auto *model = tableView->model();
  if (!model) {
	lastError_ = "Error: La tabla no tiene un modelo de datos asignado.";
	return false;
  }

  QSet<QString> excludedColumns = {"url_id", "categoryid"};
  QString savePath = filePath;
  if (!savePath.endsWith(".xlsx", Qt::CaseInsensitive)) savePath += ".xlsx";

  QXlsx::Document xlsxDocument;

  // Formato para cabeceras
  QXlsx::Format headerFormat;
  headerFormat.setFontBold(true);
  headerFormat.setVerticalAlignment(QXlsx::Format::AlignVCenter);
  headerFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);

  // Formato para datos — sin wrap, alineación superior
  QXlsx::Format dataFormat;
  dataFormat.setVerticalAlignment(QXlsx::Format::AlignTop);

  // 4. Escribir cabeceras y ancho de columnas
  int colExcel = 1;
  for (int col = 0; col < model->columnCount(); ++col) {
	if (tableView->isColumnHidden(col)) continue;

	QString fieldName;
	if (auto sqlModel = qobject_cast<QSqlTableModel*>(model))
	  fieldName = sqlModel->record().fieldName(col).toLower();
	if (excludedColumns.contains(fieldName)) continue;

	// Ancho de columna tomado del QTableView
	const double excelWidth = tableView->columnWidth(col) / 7.0;
	xlsxDocument.setColumnWidth(colExcel, excelWidth);

	xlsxDocument.write(1, colExcel++,
					   model->headerData(col, Qt::Horizontal).toString(),
					   headerFormat);
  }

  // 5. Escribir datos
  for (int row = 0; row < model->rowCount(); ++row) {
	colExcel = 1;
	for (int col = 0; col < model->columnCount(); ++col) {
	  if (tableView->isColumnHidden(col)) continue;

	  QString fieldName;
	  if (auto sqlModel = qobject_cast<QSqlTableModel*>(model))
		fieldName = sqlModel->record().fieldName(col).toLower();
	  if (excludedColumns.contains(fieldName)) continue;

	  QVariant data = model->data(model->index(row, col), Qt::DisplayRole);

	  if (!data.isValid() || data.isNull())
		xlsxDocument.write(row + 2, colExcel++, "", dataFormat);
	  else
		xlsxDocument.write(row + 2, colExcel++, data, dataFormat);
	}
  }

  // 6. Fijar alto de filas igual que en QTableView
  const int rowHeight = tableView->verticalHeader()->defaultSectionSize();
  const double excelRowHeight = rowHeight / 1.33;

  // Cabecera
  xlsxDocument.setRowHeight(1, excelRowHeight);

  // Filas de datos
  for (int row = 0; row < model->rowCount(); ++row){
	xlsxDocument.setRowHeight(row + 2, excelRowHeight);
  }

  return xlsxDocument.saveAs(savePath);
}


}// namespace SW
