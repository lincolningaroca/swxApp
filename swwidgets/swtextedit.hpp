#pragma once


#include <QWidget>

// Forward declarations
class QTextEdit;
class QToolBar;
class QAction;
class QSpinBox;
class QTextCharFormat;
class QFontComboBox;

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
  QTextEdit* editor() const { return editor_; }
  void setHtml(const QString &html);

  QString currentFont() const;
  int currentFontSize() const;
  void restoreFont(const QString &family, int size) noexcept;

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
  QTextEdit   *editor_{nullptr};

  QAction     *boldAction_{nullptr};
  QAction     *italicAction_{nullptr};
  QAction     *underlineAction_{nullptr};
  QAction     *alignLeftAction_{nullptr};
  QAction     *alignCenterAction_{nullptr};
  QAction     *alignRightAction_{nullptr};
  QAction     *colorAction_{nullptr};
  QSpinBox    *fontSize_{nullptr};
  QFontComboBox *fontFamily_{nullptr};



};
