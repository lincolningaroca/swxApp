#pragma once

#include "helperdatabase/helperdb.hpp"
#include <QList>
#include <QString>

class QTableView;

namespace SW {

class DataImporterExporter {

public:

  enum class ExportFormat {
	Xlsx,
	Csv,
	Tsv,
	Txt
  };

  explicit DataImporterExporter() = default;

  // --- MÉTODOS DE EXPORTACIÓN ---
  static bool exportTableView(QTableView *tableView, const QString &filePath);

  // --- MÉTODOS DE IMPORTACIÓN ---
  static QList<SW::UrlImportData> importFromFile(const QString &filePath);

  // --- MANEJO DE ERRORES ---
  static const QString& lastError() { return lastError_; }

private:
  // Auxiliares de Exportación
  static bool exportToXlsx(QTableView *tableView, const QString &filePath);
  static bool exportToTextFormat(QTableView *tableView, const QString &filePath, QChar delimiter);
  static QString escapeCsvField(const QString &field, QChar delimiter);

  // Auxiliares de Importación
  static QList<SW::UrlImportData> importFromXlsx(const QString &filePath);
  static QList<SW::UrlImportData> importFromTextFormat(const QString &filePath);

  inline static QString lastError_{};
};

} // namespace SW