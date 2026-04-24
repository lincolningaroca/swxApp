#pragma once


#include <QWidget>

// Forward declarations
// class QTextEdit;
class QToolBar;
class QAction;
class QSpinBox;
class QTextCharFormat;
class QFontComboBox;

#include <QTextEdit>

class SWInnerEdit : public QTextEdit {
  Q_OBJECT
public:
  explicit SWInnerEdit(QWidget *parent = nullptr) : QTextEdit(parent) {}
  void setDefaultColor(const QColor &color) { defaultColor_ = color; }

protected:
  void keyPressEvent(QKeyEvent *event) override {
	QTextEdit::keyPressEvent(event);
	// Después de procesar la tecla, si quedó vacío restaurar el color
	if(document()->isEmpty()) {
	  QTextCharFormat fmt;
	  fmt.setForeground(defaultColor_);
	  // Aplicar sin señales para no interferir con placeholder
	  QTextCursor cursor = textCursor();
	  cursor.select(QTextCursor::Document);
	  cursor.setCharFormat(fmt);
	  setTextCursor(cursor);
	}
  }

private:
  QColor defaultColor_{Qt::black};
};

class SWTextEdit : public QWidget
{
  Q_OBJECT

public:

  explicit SWTextEdit( QWidget *parent = nullptr);

  QString toPlainText() const;
  QString toHtml() const;
  void setPlainText(const QString &text);
  void clear();
  void setPlaceholderText(const QString &text);
  void setReadOnly(bool ro);
  bool isReadOnly() const;
  SWInnerEdit* editor() const { return editor_; }
  void setHtml(const QString &html);

  QString currentFont() const;
  int currentFontSize() const;

  void restoreFont(const QString &family, int size, const QColor &color) noexcept;

  void applyIcons(Qt::ColorScheme scheme) noexcept;


signals:
  void textChanged();

private slots:
  void on_boldAction();
  void on_italicAction();
  void on_underlineAction();
  void on_colorAction();
  void on_fontSizeChanged(int size);
  void on_cursorPositionChanged();

private:
  void initToolBar();
  void updateToolBarState();

  QToolBar    *toolBar_{nullptr};
  SWInnerEdit   *editor_{nullptr};

  QAction     *boldAction_{nullptr};
  QAction     *italicAction_{nullptr};
  QAction     *underlineAction_{nullptr};
  QAction     *alignLeftAction_{nullptr};
  QAction     *alignCenterAction_{nullptr};
  QAction     *alignRightAction_{nullptr};
  QAction     *colorAction_{nullptr};
  QSpinBox    *fontSize_{nullptr};
  QFontComboBox *fontFamily_{nullptr};

  QColor defaultColor_{Qt::black};



};
