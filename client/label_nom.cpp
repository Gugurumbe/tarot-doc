#include "label_nom.hpp"

LabelNom::LabelNom(QWidget * parent): 
  QLabel("???", parent)
{
}

QString LabelNom::nom_de(unsigned int j)
{
  QString str = "???";
  switch(j)
    {
    case 0:str="Agathe";break;
    case 1:str="Emmanuel";break;
    case 2:str="Isidore";break;
    case 3:str="Olivier";break;
    case 4:str="Ursula";break;
    default:break;
    }
  return str;
}

void LabelNom::set_num(unsigned int j)
{
  setText(nom_de(j));
}
