#include "selecteur_carte.hpp"

SelecteurCarte::SelecteurCarte(QWidget * parent) :
  QComboBox(parent)
{
  connect(this, SIGNAL(currentIndexChanged(int)),
	  this, SLOT(changement_selection(int)));
}

void SelecteurCarte::mise_a_jour()
{
  clear();
  setInsertPolicy(QComboBox::InsertAtBottom);
  for(unsigned int i = 0 ; i < affichees.size() ; i++)
    {
      addItem(QString::fromUtf8(affichees[i].nom().c_str()));
    }
}

void SelecteurCarte::ajouter_carte(const Carte & c)
{
  //On l'insère au bon endroit, bien sûr.
  //Pas de dichotomie.
  //En cas de dichotomie, changer aussi enlever_carte et
  //modifier_cartes
  std::vector<Carte>::iterator i = affichees.begin();
  while(i != affichees.end() && i->numero() < c.numero())i++;
  //Il faut insérer avant i
  affichees.insert(i, c);
  //Mise à jour du combobox
  mise_a_jour();
}

void SelecteurCarte::enlever_carte(const Carte & c)
{
  //cf ajouter_carte
  std::vector<Carte>::iterator i = affichees.begin();
  while(i != affichees.end() && *i != c) i++;
  if(i != affichees.end()) affichees.erase(i);
  mise_a_jour();
}

void SelecteurCarte::modifier_cartes(std::vector<Carte> gagnees,
			    std::vector<Carte> perdues)
{
  //cf ajouter_carte
  for(unsigned int i = 0 ; i < gagnees.size() ; i++)
    {
      std::vector<Carte>::iterator j = affichees.begin();
      while(j != affichees.end() && 
	    j->numero() <  gagnees[i].numero()) j++;
      affichees.insert(j, gagnees[i]);
    }
  for(unsigned int i = 0 ; i < perdues.size() ; i++)
    {
      std::vector<Carte>::iterator j = affichees.begin();
      while(j != affichees.end() && *j != perdues[i]) j++;
      if(j != affichees.end()) affichees.erase(j);
    }
  mise_a_jour();
}

void SelecteurCarte::set_cartes(const std::vector<Carte> & cartes)
{
  affichees = cartes;
  mise_a_jour();
}

void SelecteurCarte::afficher_toutes()
{
  affichees.clear();
  affichees.reserve(78);
  for(unsigned int i = 0 ; i < 78 ; i++)
    {
      affichees.push_back(Carte(i));
    }
  mise_a_jour();
}

const Carte & SelecteurCarte::carte_selectionnee() const
{
  return affichees[currentIndex()];
}

void SelecteurCarte::changement_selection(int i)
{
  if(static_cast<unsigned int>(i) < affichees.size())
    {
      emit carte_change(Carte(affichees[i]));
    }
}
