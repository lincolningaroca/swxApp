#include "swlabel.hpp"

#include <QMouseEvent>

SWLabel::SWLabel(QWidget* parent):
  QLabel{parent}
{

}

void SWLabel::mousePressEvent(QMouseEvent* event){

  if(event->button() == Qt::LeftButton){
      emit clicked();
    }

}
