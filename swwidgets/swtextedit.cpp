#include "swtextedit.hpp"
#include <QVBoxLayout>
#include <QTextCharFormat>
#include <QColorDialog>
#include <QColor>
#include <QIcon>
#include <QStyle>
#include <QApplication>
#include <QTextEdit>
#include <QToolBar>
#include <QFontComboBox>
#include <QSpinBox>
#include <QAction>
#include <QFontComboBox>

SWTextEdit::SWTextEdit(QWidget *parent):
  QWidget(parent){

  auto *layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  toolBar_ = new QToolBar(this);
  toolBar_->setIconSize(QSize(16, 16));
  toolBar_->setFixedHeight(28);

  editor_ = new QTextEdit(this);

  layout->addWidget(toolBar_);
  layout->addWidget(editor_);

  initToolBar();

  QObject::connect(editor_, &QTextEdit::textChanged, this, &SWTextEdit::textChanged);
  QObject::connect(editor_, &QTextEdit::cursorPositionChanged, this, &SWTextEdit::on_cursorPositionChanged);
}

void SWTextEdit::initToolBar()
{
  // const auto style = qApp->style();

  // --- Negrita ---
  boldAction_ = toolBar_->addAction("B");
  boldAction_->setCheckable(true);
  boldAction_->setShortcut(QKeySequence::Bold);
  boldAction_->setFont(QFont("Times New Roman", 10, QFont::Bold));
  boldAction_->setToolTip("Negrita (Ctrl+B)");
  QObject::connect(boldAction_, &QAction::triggered, this, &SWTextEdit::on_boldAction);

  // --- Cursiva ---
  italicAction_ = toolBar_->addAction("I");
  italicAction_->setCheckable(true);
  italicAction_->setShortcut(QKeySequence::Italic);
  QFont italicFont("Times New Roman", 10);
  italicFont.setItalic(true);
  italicAction_->setFont(italicFont);
  italicAction_->setToolTip("Cursiva (Ctrl+I)");
  QObject::connect(italicAction_, &QAction::triggered, this, &SWTextEdit::on_italicAction);

  // --- Subrayado ---
  underlineAction_ = toolBar_->addAction("U");
  underlineAction_->setCheckable(true);
  underlineAction_->setShortcut(QKeySequence::Underline);
  QFont underlineFont("Times New Roman", 10);
  underlineFont.setUnderline(true);
  underlineAction_->setFont(underlineFont);
  underlineAction_->setToolTip("Subrayado (Ctrl+U)");
  QObject::connect(underlineAction_, &QAction::triggered, this, &SWTextEdit::on_underlineAction);

  toolBar_->addSeparator();

  // --- Alineación con iconos estándar de Qt ---
  alignLeftAction_ = toolBar_->addAction(QIcon(":/img/leftalign.png"), "");
  alignLeftAction_->setCheckable(true);
  alignLeftAction_->setChecked(true);
  alignLeftAction_->setToolTip("Alinear izquierda");
  QObject::connect(alignLeftAction_, &QAction::triggered, this, [this](){
	editor_->setAlignment(Qt::AlignLeft);
	alignLeftAction_->setChecked(true);
	alignCenterAction_->setChecked(false);
	alignRightAction_->setChecked(false);
  });

  alignCenterAction_ = toolBar_->addAction(QIcon(":/img/center.png"), "");
  alignCenterAction_->setCheckable(true);
  alignCenterAction_->setToolTip("Centrar");
  QObject::connect(alignCenterAction_, &QAction::triggered, this, [this](){
	editor_->setAlignment(Qt::AlignCenter);
	alignLeftAction_->setChecked(false);
	alignCenterAction_->setChecked(true);
	alignRightAction_->setChecked(false);
  });

  alignRightAction_ = toolBar_->addAction(QIcon(":/img/rightalign.png"), "");
  alignRightAction_->setCheckable(true);
  alignRightAction_->setToolTip("Alinear derecha");
  QObject::connect(alignRightAction_, &QAction::triggered, this, [this](){
	editor_->setAlignment(Qt::AlignRight);
	alignLeftAction_->setChecked(false);
	alignCenterAction_->setChecked(false);
	alignRightAction_->setChecked(true);
  });

  toolBar_->addSeparator();

  // --- Color de texto con icono estándar ---
  colorAction_ = toolBar_->addAction(QIcon(":/img/textcolor.png"), "");
  colorAction_->setToolTip("Color de texto");
  QObject::connect(colorAction_, &QAction::triggered, this, &SWTextEdit::on_colorAction);

  toolBar_->addSeparator();
  fontFamily_ = new QFontComboBox(toolBar_);
  fontFamily_->setFixedWidth(150);
  fontFamily_->setToolTip("Tipo de fuente");
  toolBar_->addWidget(fontFamily_);
  toolBar_->addSeparator();

  QObject::connect(fontFamily_, &QFontComboBox::currentFontChanged, this, [this](const QFont &font){
	QTextCharFormat fmt;
	fmt.setFontFamilies({font.family()});
	editor_->mergeCurrentCharFormat(fmt);
  });


  // --- Tamaño de fuente ---
  fontSize_ = new QSpinBox(toolBar_);
  fontSize_->setRange(6, 72);
  fontSize_->setValue(10);
  fontSize_->setFixedWidth(50);
  fontSize_->setToolTip("Tamaño de fuente");
  toolBar_->addWidget(fontSize_);
  QObject::connect(fontSize_, &QSpinBox::valueChanged, this, &SWTextEdit::on_fontSizeChanged);
}
void SWTextEdit::on_boldAction(){
  QTextCharFormat fmt;
  fmt.setFontWeight(boldAction_->isChecked() ? QFont::Bold : QFont::Normal);
  editor_->mergeCurrentCharFormat(fmt);
}

void SWTextEdit::on_italicAction(){
  QTextCharFormat fmt;
  fmt.setFontItalic(italicAction_->isChecked());
  editor_->mergeCurrentCharFormat(fmt);
}

void SWTextEdit::on_underlineAction(){
  QTextCharFormat fmt;
  fmt.setFontUnderline(underlineAction_->isChecked());
  editor_->mergeCurrentCharFormat(fmt);
}

void SWTextEdit::on_colorAction(){
  const auto color = QColorDialog::getColor(editor_->textColor(), this, "Color de texto");
  if(color.isValid()){
	QTextCharFormat fmt;
	fmt.setForeground(color);
	editor_->mergeCurrentCharFormat(fmt);
  }
}

void SWTextEdit::on_fontSizeChanged(int size){
  QTextCharFormat fmt;
  fmt.setFontPointSize(size);
  editor_->mergeCurrentCharFormat(fmt);
}

void SWTextEdit::on_cursorPositionChanged(){
  updateToolBarState();
}

void SWTextEdit::updateToolBarState(){
  const auto fmt = editor_->currentCharFormat();
  boldAction_->setChecked(fmt.fontWeight() == QFont::Bold);
  italicAction_->setChecked(fmt.fontItalic());
  underlineAction_->setChecked(fmt.fontUnderline());

  QSignalBlocker blocker(fontSize_);
  fontSize_->setValue(static_cast<int>(fmt.fontPointSize() > 0 ? fmt.fontPointSize() : 10));

  const auto align = editor_->alignment();
  alignLeftAction_->setChecked(align == Qt::AlignLeft);
  alignCenterAction_->setChecked(align == Qt::AlignHCenter);
  alignRightAction_->setChecked(align == Qt::AlignRight);
}

// --- Métodos públicos ---
QString SWTextEdit::toPlainText() const { return editor_->toPlainText(); }
QString SWTextEdit::toHtml() const { return editor_->toHtml(); }
void SWTextEdit::setPlainText(const QString &text) { editor_->setPlainText(text); }
void SWTextEdit::clear() { editor_->clear(); }
void SWTextEdit::setPlaceholderText(const QString &text) { editor_->setPlaceholderText(text); }
void SWTextEdit::setReadOnly(bool ro) { editor_->setReadOnly(ro); }
bool SWTextEdit::isReadOnly() const { return editor_->isReadOnly(); }

void SWTextEdit::setHtml(const QString &html){

  editor_->setHtml(html);

}
