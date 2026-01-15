#include "acercadedialog.hpp"
#include "ui_acercadedialog.h"

#include <QMessageBox>
#include <QFile>

AcercaDeDialog::AcercaDeDialog(Qt::ColorScheme colorMode, QWidget *parent)
  : QDialog(parent), ui(new Ui::AcercaDeDialog)
{
  ui->setupUi(this);

  setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
  setTextToAbout();
  ui->tabWidget->setCurrentIndex(0);

  if(colorMode == Qt::ColorScheme::Unknown){

    const auto retSyscolorScheme = SW::Helper_t::detectSystemColorScheme();

    setImage(retSyscolorScheme);

  }else{

    setImage(colorMode);
  }

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
  ui->tbAcercaDe->setHtml(QStringLiteral("<p>Powered by:"
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
                          "</ul>"
                          "</p>"
                          "<p>Repositorio del programa:"
                          "<ul><li><a href=\"https://github.com/lincolningaroca/xxxApp\">xxxApp</a></li></ul>"
                          "</p>"));

}

void AcercaDeDialog::setImage(Qt::ColorScheme colorMode){

  (colorMode == Qt::ColorScheme::Dark) ? ui->lblLogo->setPixmap(QPixmap(":/img/logoEmpresa_1.png").scaled(490, 338))
                                 : ui->lblLogo->setPixmap(QPixmap(":/img/logoEmpresa.png").scaled(490, 338));

}
