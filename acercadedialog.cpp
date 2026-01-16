#include "acercadedialog.hpp"
#include "ui_acercadedialog.h"

#include <QMessageBox>
#include <QFile>
#include <QSettings>

AcercaDeDialog::AcercaDeDialog(Qt::ColorScheme colorMode, QWidget *parent)
  : QDialog(parent), ui(new Ui::AcercaDeDialog), colorMode_(colorMode)
{
  ui->setupUi(this);

  readSettings();

  setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
  setTextToAbout();

  ui->tabWidget->setCurrentIndex(0);

  loadInfo_app();
  ui->lblLicencia->setText(QStringLiteral("<a href='message'>Ver licencia.</a>"));
  ui->lblAcercaQt->setText(QStringLiteral("<a href='message'>Acerca de Qt.</a>"));
  QObject::connect(ui->btnCerrar, &QPushButton::clicked, this, &AcercaDeDialog::close);

  QObject::connect(ui->lblLicencia, &QLabel::linkActivated, this, [this](){
    QDialog licenciaDlg(this);

    QScopedPointer<QVBoxLayout> mainLayOut(new QVBoxLayout(&licenciaDlg));
    QScopedPointer<QTextBrowser> teLicencia(new QTextBrowser(&licenciaDlg));

    QFile fileName(QStringLiteral(":/licencia/licencia.txt"));
    if (!fileName.open(QFile::ReadOnly | QFile::Text)) {
      QMessageBox::warning(this, SW::Helper_t::appName(), tr("Error al abrir el archivo.\n%1").arg(
                                                            fileName.errorString()));
      return;
    }


    teLicencia->setFont(customFont);
    teLicencia->setAcceptRichText(true);
    teLicencia->setOpenExternalLinks(true);
    teLicencia->setHtml(fileName.readAll());
    teLicencia->setReadOnly(true);
    mainLayOut->addWidget(teLicencia.data());
    licenciaDlg.setLayout(mainLayOut.data());
    licenciaDlg.setFixedSize(600, 477);
    licenciaDlg.setWindowTitle(SW::Helper_t::appName().append(" - licencia"));
    licenciaDlg.exec();
    fileName.close();
  });

  QObject::connect(ui->lblAcercaQt, &QLabel::linkActivated, this, [this](){
    QMessageBox::aboutQt(this);
  });

  ui->tbLicencia->setFont(customFont);

}

AcercaDeDialog::~AcercaDeDialog()
{
  delete ui;
}

void AcercaDeDialog::writeSettings() const{

  QSettings settings(qApp->organizationName(), SW::Helper_t::appName());
  settings.beginGroup("abaut_dialog");
  settings.setValue("form_geometry", this->saveGeometry());

  settings.endGroup();

}

void AcercaDeDialog::readSettings()
{
  QSettings settings(qApp->organizationName(), SW::Helper_t::appName());
  settings.beginGroup("abaut_dialog");
  const auto formGeometry = settings.value("form_geometry", QByteArray()).toByteArray();
  this->restoreGeometry(formGeometry);
  settings.endGroup();
}


void AcercaDeDialog::loadInfo_app() const noexcept{
  ui->tbLicencia->setFont(customFont);
  ui->tbLicencia->setAcceptRichText(true);
  ui->tbLicencia->setOpenExternalLinks(true);
  ui->tbLicencia->setHtml(QStringLiteral(
    "<p>xxxApp:<br><br>Es software libre, puede "
    "redistribuirlo y/o modificarlo bajo los términos de la Licencia Pública "
    "General de GNU según se encuentra publicada por la <a "
    "href=\"https://www.fsf.org\">Free Software "
    "Foundation</a>, bien de la versión 3 de dicha Licencia o bien (según su "
    "elección) de cualquier versión posterior.<br><br>"
    "Este programa se distribuye con la esperanza de que sea útil, pero <strong>SIN "
    "NINGUNA "
    "GARANTÍA</strong>, incluso sin la garantía <strong>MERCANTIL</strong> implícita ni la de "
    "garantizar la <strong>ADECUACIÓN A UN PROPÓSITO PARTICULAR.</strong> Véase la <a "
    "href=\"https://www.gnu.org/licenses/\">Licencia "
    "Pública General</a> de GNU para más detalles.</p>"));

}

void AcercaDeDialog::setTextToAbout() const{
  ui->tbAcercaDe->setFont(customFont);
  ui->tbAcercaDe->setOpenExternalLinks(true);
  ui->tbAcercaDe->setHtml(QStringLiteral(
    "<p>Powered by:"
    "<ul>"
    "<li>Lincoln Ingaroca De La Cruz.</li>"
    "<li>SWSystem's.</li>"
    "</ul>"
    "Contacto:"
    "<ul>"
    "<li>lincolningaroca@gmail.com</li>"
    "</ul>"
    "Lincoln Ingaroca:"
    "<ul>"
    "<li>Analista de sistemas informáticos.</li>"
    "<li>Software development.</li>"
    "</ul><br>"
    "Bibliotecas:"
    "<p>xxxApp incluye código fuente de los siguientes proyectos:</p>"
    "<ul>"
    "<li><a href=\"https://www.openssl.org/\">OpenSSL.</a></li>"
    "<li><a href=\"https://www.qt.io//\">QtFrameWork and QtWidgets.</a></li>"
    "<li><a href=\"https://www.sqlite.org/index.html\">SQLite.</a></li>"
    "<li><a href=\"https://github.com/QtExcel/QXlsx\">QXlsx library.</a></li>"
    "</ul>"
    "</p>"
    "<p>Repositorio del programa:"
    "<ul><li><a href=\"https://github.com/lincolningaroca/xxxApp\">xxxApp</a></li></ul>"
    "</p>"));

}

void AcercaDeDialog::setImage(Qt::ColorScheme colorMode){

  const QString logoPath = (colorMode == Qt::ColorScheme::Dark)
  ? ":/img/logoEmpresa_1.png"
  : ":/img/logoEmpresa.png";

  QPixmap logoSw(logoPath);

  if(logoSw.isNull()){
    qWarning() << "Logo no disponible para el tema actual: " << logoPath;
    return;
  }

  const QSize labelSize = ui->lblLogo->size();      // 622x462
  const QSize logoSize = logoSw.size();             // 478x471

  if(logoSize.width() > labelSize.width() || logoSize.height() > labelSize.height()){
    ui->lblLogo->setPixmap(logoSw.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
  }else{
    ui->lblLogo->setPixmap(logoSw);
  }

  ui->lblLogo->setAlignment(Qt::AlignCenter);

}


void AcercaDeDialog::showEvent(QShowEvent *event){

  QDialog::showEvent(event);

  const auto scheme = (colorMode_ == Qt::ColorScheme::Unknown)
                                   ? SW::Helper_t::detectSystemColorScheme()
                                   : colorMode_;

  setImage(scheme);


}


void AcercaDeDialog::closeEvent(QCloseEvent *event){

  writeSettings();
  QDialog::closeEvent(event);

}
