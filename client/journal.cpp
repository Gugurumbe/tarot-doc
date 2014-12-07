#include "journal.hpp"
#include "label_nom.hpp"
#include "config.hpp"
#include <sstream>

#define NOM_CLASSE "Journal"

#include "deboguer.hpp"

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
  header+=S("<p class=\"numero\">Vous êtes <span class=\"joueur\">");
  header+=LabelNom::nom_de(n);
  header+=S("</span>.</p>");
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
	 <<perdues[i].couleur_simple()
	 <<"\">"<<perdues[i]<<"</li>";
    }
  str<<"<li>(c'est tout)</li></ul>";
  header+=S(str.str().c_str());
  setHtml(header + footer);
}

void Journal::afficher_doit_priser()
{
  ENTER("afficher_doit_priser()");
  std::stringstream str;
  str<<"<p class=\"a_vous\">Vous devez priser";
  str<<".</p>";
  header+=S(str.str().c_str());
  setHtml(header + footer);
}

void Journal::afficher_doit_priser(Enchere meilleure)
{
  ENTER("afficher_doit_priser(Enchere meilleure)");
  ADD_ARG("meilleure", meilleure);
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
  ENTER("afficher_contrat_invalide()");
  header+=S("<p class=\"erreur\">Votre enchère a été refusée.</p>");
}

void Journal::afficher_contrat_intermediaire(Enchere contrat)
{
  ENTER("afficher_contrat_intermediaire(Enchere contrat)");
  ADD_ARG("contrat", contrat);
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
  ENTER("afficher_doit_appeler(vector<Carte> possibles)");
  ADD_ARG("possibles",possibles);
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
  ENTER("afficher_appel_invalide()");
  header+=S("<p class=\"erreur\">Votre appel a été refusé.</p>");
  setHtml(header + footer);
}

void Journal::afficher_contrat_final(Enchere contrat)
{
  ENTER("afficher_contrat_final(Enchere contrat)");
  ADD_ARG("contrat", contrat);
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
  ENTER("afficher_chien_devoile(vector<Carte> chien)");
  ADD_ARG("chien", chien);
  std::stringstream str;
  str<<"<p class=\"chien\">Le chien est dévoilé : "
     <<"<ul class=\"valide\">";
  for(unsigned int i = 0 ; i < chien.size() ; i++)
    {
      str<<"<li class=\""<<chien[i].couleur_simple()<<"\">"<<chien[i]
	 <<"</li>";
    }
  str<<"</ul></p>";
  header+=S(str.str().c_str());
  setHtml(header + footer);
}

void Journal::afficher_doit_ecarter(std::vector<Carte> possibles,
				    std::vector<Carte> atouts)
{
  ENTER("afficher_doit_ecarter(vector<Carte> possibles, vector<Carte> atouts)");
  ADD_ARG("possibles", possibles);
  ADD_ARG("atouts", atouts);
  std::stringstream str;
  str<<"<p class=\"ecart\">Vous devez faire un écart de 3 cartes. "
     <<"Voici les cartes possibles : <ul class=\"valide\">";
  for(unsigned int i = 0 ; i < possibles.size() ; i++)
    {
      str<<"<li class=\""<<possibles[i].couleur_simple()
	 <<"\">"<<possibles[i]<<"</li>";
    }
  str<<"</ul> En cas de nécessité, vous pouvez écarter ces atouts"
     <<" en sachant que les autres le sauront : "
     <<"<ul class=\"valide\">";
  for(unsigned int i = 0 ; i < atouts.size() ; i++)
    {
      str<<"<li class=\""<<atouts[i].couleur_simple()
	 <<"\">"<<atouts[i]<<"</li>";
    }
  str<<"</ul></p>";
  header+=S(str.str().c_str());
  setHtml(header + footer);
}
void Journal::afficher_doit_jouer()
{
  ENTER("afficher_doit_jouer()");
  header+=S("<p class=\"jeu\">C'est à vous de jouer.</p>");
  setHtml(header + footer);
}

void Journal::afficher_atout_au_chien(std::vector<Carte> atouts)
{
  ENTER("afficher_atout_au_chien(vector<Carte> atouts)");
  ADD_ARG("atouts", atouts);
  std::stringstream str;
  str<<"<p class=\"atout_au_chien\">Un ou plusieurs "
     <<"<strong>atout(s)</strong> ont été mis au chien : "
     <<"<ul class=\"valide\">";
  for(unsigned int i = 0 ; i < atouts.size() ; i++)
    {
      str<<"<li class=\""<<atouts[i].couleur_simple()
	 <<"\">"<<atouts[i]<<"</li>";
    }
  str<<"</ul></p>";
  header+=S(str.str().c_str());
  setHtml(header + footer);  
}
void Journal::afficher_carte_gagnee(Carte c, unsigned int poseur,
				    unsigned int gagnant)
{
  ENTER("afficher_carte_gagnee(Carte c, unsigned int poseur, unsigned int gagnant)");
  ADD_ARG("c", c);
  ADD_ARG("poseur", poseur);
  ADD_ARG("gagnant", gagnant);
  std::stringstream str;
  str<<"<p class=\"mouvement\">La carte <span class=\""
     <<c.couleur_simple()<<"\">"<<c<<"</span> a été remportée par "
     <<"<span class=\"joueur\">";
  str<<LabelNom::nom_de(gagnant).toUtf8().data();
  str<<"</span> après avoir été posée par <span class=\"joueur\">"
     <<LabelNom::nom_de(poseur).toUtf8().data()
     <<"</span></p>";
  header+=S(str.str().c_str());
  setHtml(header + footer);  
}

void Journal::afficher_nouveau_maitre(unsigned int maitre)
{
  ENTER("afficher_maitre_change(unsigned int maitre)");
  ADD_ARG("maitre", maitre);
  std::stringstream str;
  str<<"<p class=\"maitre\">Le joueur maître est maintenant "
     <<"<span class=\"joueur\">"
     <<LabelNom::nom_de(maitre).toUtf8().data()
     <<"</span></p>";
  header+=S(str.str().c_str());
  setHtml(header + footer);  
}

void Journal::afficher_pli_termine(unsigned int joueur)
{
  ENTER("afficher_pli_termine(unsigned int joueur)");
  ADD_ARG("joueur", joueur);
  std::stringstream str;
  str<<"<p class=\"pli\">Le joueur <span class=\"joueur\">"
     <<LabelNom::nom_de(joueur).toUtf8().data()
     <<"</span> remporte le pli.</p>";
  header+=S(str.str().c_str());
  setHtml(header + footer);  
}

void Journal::afficher_partie_terminee(std::vector<int> scores)
{
  ENTER("afficher_partie_terminee(std::vector<int> scores)");
  ADD_ARG("scores", scores);
  std::stringstream str;
  str<<"<p class=\"fin\">La partie est terminée. Voici les scores : "
     <<"<table><tr><th>Joueur</th><th>Score</th></tr>";
  for(unsigned int i = 0 ; i < scores.size() ; i++)
    {
      str<<"<tr><td class=\"joueur\">"
	 <<LabelNom::nom_de(i).toUtf8().data()
	 <<"</td><td class=\"score\">"<<scores[i]<<"</td></tr>";
    }
  str<<"</table></p>";
  header+=S(str.str().c_str());
  setHtml(header + footer);  
}
