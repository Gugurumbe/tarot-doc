#include "journal.hpp"
#include "label_nom.hpp"
#include "config.hpp"
#include <sstream>

#define NOM_CLASSE "Journal"

#include "ne_pas_deboguer.hpp"

#define S(texte) QString::fromUtf8(texte)

Journal::Journal(QWidget * parent):
  QTextBrowser(parent)
{
  ENTER("Journal(QWidget * parent)");
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
  header+=S("<body>");
  header+=S("<p>");
  footer+=S("</p></body></html>");
}

void Journal::afficher_connexion()
{
  ENTER("afficher_connexion()");
  header+=S("<p class=\"connexion\">Connecté.</p>");
  setHtml(header + footer);
}

void Journal::afficher_deconnexion()
{
  ENTER("afficher_deconnexion()");
  header+=S("<p class=\"deconnexion\">Déconnecté.</p>");
  setHtml(header + footer);
}

void Journal::afficher_numero(unsigned int n)
{
  ENTER("afficher_numero(unsigned int n)");
  ADD_ARG("n", n);
  header+=S("<p class=\"numero\">Vous êtes ");
  header+=LabelNom::nom_de(n);
  header+=S(".</p>");
  setHtml(header + footer);
}

void Journal::afficher_changement_jeu(std::vector<Carte> gagnees,
				      std::vector<Carte> perdues)
{
  ENTER("afficher_changement_jeu(vector<Carte> gagnees, vector<Carte> perdues)");
  ADD_ARG("gagnees", gagnees);
  ADD_ARG("perdues", perdues);
  std::stringstream str;
  str<<"<p class=\"changement_jeu\"> Vous avez <strong>gagné</strong> : "
     <<"<ul class=\"gagne\">";
  for(unsigned int i = 0 ; i < gagnees.size() ; i++)
    {
      str<<"<li class=\""
	 <<gagnees[i].couleur_simple()
	 <<"\">"<<gagnees[i]<<"</li>";
    }
  str<<"<li>(c'est tout)</li></ul>Vous avez <strong>perdu</strong> : "
     <<"<ul class=\"perdu\">";
  for(unsigned int i = 0 ; i < perdues.size() ; i++)
    {
      str<<"<li class=\""
	 <<gagnees[i].couleur_simple()
	 <<"\">"<<gagnees[i]<<"</li>";
    }
  str<<"<li>(c'est tout)</li></ul>";
  header+=S(str.str().c_str());
  setHtml(header + footer);
}

void Journal::afficher_doit_priser()
{
  std::stringstream str;
  str<<"<p class=\"a_vous\">Vous devez priser";
  str<<".</p>";
  header+=S(str.str().c_str());
  setHtml(header + footer);
}

void Journal::afficher_doit_priser(Enchere meilleure)
{
  std::stringstream str;
  str<<"<p class=\"a_vous\">Vous devez priser";
  str<<" : <strong>passer</strong> ou faire mieux que <span class=\"joueur\">"
     <<LabelNom::nom_de(meilleure.joueur()).toUtf8().data()
     <<"</span> qui a fait une Prise de niveau <span class=\"prise\">";
  str<<meilleure.prise()<<"</span>";
  str<<".</p>";
  header+=S(str.str().c_str());
  setHtml(header + footer);
}

void Journal::afficher_contrat_invalide()
{
  header+=S("<p class=\"erreur\">Votre enchère a été refusée.</p>");
}

void Journal::afficher_contrat_intermediaire(Enchere contrat)
{
  std::stringstream str;
  str<<"<p class=\"enchere\"><span class=\"joueur\">"
     <<LabelNom::nom_de(contrat.joueur()).toUtf8().data()
     <<"</span> fait l'enchere : <span class=\"prise\">"
     <<contrat.prise()<<"</span>";
  header+=S(str.str().c_str());
  setHtml(header + footer);
}

void Journal::afficher_doit_appeler(std::vector<Carte> possibles)
{
  std::stringstream str;
  str<<"<p class=\"appeler\">Vous devez <strong>appeler</strong>"
     <<" une carte. Les cartes acceptées sont : <ul class=\"valide\">";
  for(unsigned int i = 0 ; i < possibles.size() ; i++)
    {
      str<<"<li class=\""
	 <<possibles[i].couleur_simple()
	 <<"\">"<<possibles[i]<<"</li>";
    }
  str<<"</ul></p>";
  header+=S(str.str().c_str());
  setHtml(header + footer);
}

void Journal::afficher_appel_invalide()
{
  header+=S("<p class=\"erreur\">Votre appel a été refusé.</p>");
}

void Journal::afficher_contrat_final(Enchere contrat)
{
  std::stringstream str;
  str<<"<p class=\"contrat_final\">Voici le contrat <strong>final"
     <<"</strong> : <span class=\"joueur\">"
     <<LabelNom::nom_de(contrat.joueur()).toUtf8().data()
     <<"</span> fait un contrat de niveau <span class=\"prise\">"
     <<contrat.prise()<<"</span> en appelant la carte "
     <<"<span class=\""<<contrat.carte_appelee()->couleur_simple()
     <<"\">"<<*(contrat.carte_appelee())<<"</span></p>";
  header+=S(str.str().c_str());
  setHtml(header + footer);  
}

void Journal::afficher_chien_devoile(std::vector<Carte> chien)
{
  std::stringstream str;
  str<<"<p class=\"chien\">Le chien est dévoilé : <ul class=\"valide\">";
  for(unsigned int i = 0 ; i < chien.size() ; i++)
    {
      str<<"<li class=\""<<chien[i].couleur_simple()<<"\">"<<chien[i]
	 <<"</li>";
    }
  header+=S(str.str().c_str());
  setHtml(header + footer);
}
