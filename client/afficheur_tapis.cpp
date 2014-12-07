#include "afficheur_tapis.hpp"
#include "label_nom.hpp"

AfficheurTapis::AfficheurTapis(QWidget * parent):
  QTableWidget(parent)
{
}

void AfficheurTapis::recalculer(const Tapis & tapis)
{
  std::vector<Carte> cartes;
  std::vector<unsigned int> numeros;
  tapis.contenu(cartes, numeros);
  clear();
  setRowCount(cartes.size());
  setColumnCount(2);
  QTableWidgetItem * carte = 0;
  QTableWidgetItem * poseur = 0;
  for(unsigned int i = 0 ; i < cartes.size() ; i++)
    {
      carte = new QTableWidgetItem(cartes[i].nom().c_str());
      poseur = new QTableWidgetItem(LabelNom::nom_de(numeros[i]));
      setItem(i, 0, carte);
      setItem(i, 1, poseur);
    }
}
