#include "liste_cartes.hpp"
#include "config.hpp"

#define NOM_CLASSE "ListeCartes"

#define DEBOGUER_

#ifdef DEBOGUER_
#include "ne_pas_deboguer.hpp"
#else
#include "ne_pas_deboguer.hpp"
#endif

#define S(texte) QString::fromUtf8(texte)

ListeCartes::ListeCartes(QWidget * parent):
  QTextBrowser(parent)
{
  ENTER("ListeCartes(QWidget * parent)");
  ADD_ARG("parent", parent);
  header+=S("<!DOCTYPE html>");
  header+=S("<html>");
  header+=S("<head>");
  header+=S("<title>Journal</title>");
  header+=S("<meta charset=\"utf8\"/>");
  header+=S("<link rel=\"stylesheet\" type=\"text/css\" href=");
  header+=S(STYLE);
  header+=S("/>");
  header+=S("</head>");
  header+=S("<body><p><strong>Vos cartes : </strong><ul>");
  footer+=S("</ul></p></body></html>");
}

QString rendre(std::vector<Carte> & cartes)
{
  //Tri-bulle
  Carte aux(0);
  for(unsigned int taille_triee = 1 ; 
      taille_triee < cartes.size() ; taille_triee++)
    {
      for(unsigned int bulle = taille_triee ;
	  bulle > 0 && cartes[bulle - 1].numero() >= cartes[bulle].numero() ;
	  bulle--)
	{
	  aux = cartes[bulle - 1];
	  cartes[bulle - 1] = cartes[bulle];
	  cartes[bulle] = aux;
	}
    }
  QString res;
  for(unsigned int i = 0 ; i < cartes.size() ; i++)
    {
      res += S("<li class=\"");
      res += S(cartes[i].couleur_simple().c_str());
      res += S("\">");
      res += S(cartes[i].nom().c_str());
      res += S("</li>");
    }
  return res;
}

void ListeCartes::gagner(std::vector<Carte> gagnees, std::vector<Carte> perdues)
{
  ENTER("gagner(vector<Carte> gagnees, vector<Carte> perdues)");
  ADD_ARG("gagnees", gagnees);
  ADD_ARG("perdues", perdues);
  //Traitement des cartes perdues :
  for(unsigned int i = 0 ; i < perdues.size() ; i++)
    {
      for(unsigned int j = 0 ; j < cartes.size() ; j++)
	{
	  if(cartes[j] == perdues[i])
	    {
	      cartes.erase(cartes.begin() + j);
	      j = cartes.size();
	    }
	}
    }
  //Traitement des carte gagnées :
  for(unsigned int i = 0 ; i < gagnees.size() ; i++)
    {
      cartes.push_back(gagnees[i]);
    }
  setHtml(header + rendre(cartes) + footer);
}

void ListeCartes::set(std::vector<Carte> cartes)
{
  this->cartes = cartes;
  setHtml(header + rendre(cartes) + footer);
}
