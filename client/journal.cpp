#include "journal.hpp"
#include "label_nom.hpp"
#include "config.hpp"
#include "option.cpp"
#include <sstream>
#include <QScrollBar>

#define NOM_CLASSE "Journal"

#include "deboguer.hpp"

#define S(texte) QString::fromUtf8(texte)

#define SET_HTML(html) setHtml(html);\
  verticalScrollBar()->setValue(verticalScrollBar()->maximum())

Journal::Journal(QWidget * parent):
  QTextBrowser(parent)
{
  ENTER("Journal(QWidget * parent)");
  ADD_ARG("parent", parent);
  header = S("<!DOCTYPE html><html><head><title>Journal</title>"
	     "<meta charset=\"utf8\"/><link rel=\"stylesheet\" "
	     "type=\"text/css\" href=") + S(STYLE) + 
    S("/></head><body>");
  footer+=S("</body></html>");
}

void Journal::connecte()
{
  ENTER("connecte()");
  body = "";
  p("<p class=\"connexion\">Connecté.</p>");
  SET_HTML(header + body + footer);
}

void Journal::deconnecte()
{
  ENTER("deconnecte()");
  p("<p class=\"deconnexion\">Déconnecté.</p>");
  SET_HTML(header + body + footer);
}

void Journal::numero_change(unsigned int n)
{
  p("<p class=\"information\">Vous jouez en tant que"
    " <span class=\"joueur\">");
  body += LabelNom::nom_de(n);
  p("</span>.</p>");
  SET_HTML(header + body + footer);
}

void Journal::doit_priser(Option<Enchere> max)
{
  p("<p class=\"sollicitation\">Vous devez formuler une"
    " prise. ");
  if(max.aucun())
    {
      p("Personne n'a rien dit pour le moment.</p>");
    }
  else
    {
      p("Vous devez faire mieux que <span class=\"joueur\">");
      body+=LabelNom::nom_de(max.get().joueur());
      p("</span>. ");
      switch(max.get().prise())
	{
	case Enchere::PASSE:
	  p("Il/elle a <span class=\"prise\">passé</span>.");
	  break;
	case Enchere::PRISE:
	  p("Il/elle a <span class=\"prise\">prisé</span>.");
	  break;
	case Enchere::GARDE:
	  p("Il/elle a <span class=\"prise\">gardé</span>.");
	  break;
	case Enchere::GARDE_SANS:
	  p("Il/elle a <span class=\"prise\">gardé <strong>"
	    "sans le chien</strong></span> !");
	  break;
	case Enchere::GARDE_CONTRE:
	  p("Il/elle a <span class=\"prise\">gardé <strong>"
	    "contre le chien</strong></span> !");
	  break;
	default:
	  p("Je n'ai pas réussi à déterminer sa prise.");
	}
      p("</p>");
    }
  SET_HTML(header + body + footer);
}

void Journal::enchere_acceptee(Enchere e)
{
  p("<p class=\"accepte\">Votre enchère a été acceptée. ");
  switch(e.prise())
    {
    case Enchere::PASSE:
      p("Vous avez <span class=\"prise\">passé</span>.");
      break;
    case Enchere::PRISE:
      p("Vous avez <span class=\"prise\">prisé</span>.");
      break;
    case Enchere::GARDE:
      p("Vous avez <span class=\"prise\">gardé</span>.");
      break;
    case Enchere::GARDE_SANS:
      p("Vous avez <span class=\"prise\">gardé <strong>"
	"sans le chien</strong></span> !");
      break;
    case Enchere::GARDE_CONTRE:
      p("Vous avez <span class=\"prise\">gardé <strong>"
	"contre le chien</strong></span> !");
      break;
    default:
      p("Je n'ai pas réussi à déterminer votre prise.");
    }
  p("</p>");
  SET_HTML(header + body + footer);
}

void Journal::enchere_refusee(Enchere e)
{
  p("<p class=\"refuse\">Votre enchère a été refusée. ");
  switch(e.prise())
    {
    case Enchere::PASSE:
      p("Vous aviez <span class=\"prise\">passé</span>.");
      break;
    case Enchere::PRISE:
      p("Vous aviez <span class=\"prise\">prisé</span>.");
      break;
    case Enchere::GARDE:
      p("Vous aviez <span class=\"prise\">gardé</span>.");
      break;
    case Enchere::GARDE_SANS:
      p("Vous aviez <span class=\"prise\">gardé <strong>"
	"sans le chien</strong></span> !");
      break;
    case Enchere::GARDE_CONTRE:
      p("Vous aviez <span class=\"prise\">gardé <strong>"
	"contre le chien</strong></span> !");
      break;
    default:
      p("Je n'ai pas réussi à déterminer la prise que "
	"vous aviez demandée.");
    }
  p("</p>");
  SET_HTML(header + body + footer);
}

void Journal::contrat_intermediaire(Enchere e)
{
  p("<p class=\"information\"><span class=\"joueur\">");
  body+=LabelNom::nom_de(e.joueur());
  p("</span> ");
  switch(e.prise())
    {
    case Enchere::PASSE:
      p("<span class=\"prise\">passe</span>.");
      break;
    case Enchere::PRISE:
      p("<span class=\"prise\">prise</span>.");
      break;
    case Enchere::GARDE:
      p("<span class=\"prise\">garde</span>.");
      break;
    case Enchere::GARDE_SANS:
      p("<span class=\"prise\">garde <strong>"
	"sans le chien</strong></span> !");
      break;
    case Enchere::GARDE_CONTRE:
      p("<span class=\"prise\">garde <strong>"
	"contre le chien</strong></span> !");
      break;
    default:
      p("Fait une enchère (indéterminée ?!?!).");
    }
  p("</p>");
  SET_HTML(header + body + footer);
}

void Journal::doit_appeler(std::vector<Carte> possibles)
{
  p("<p class=\"sollicitation\">Vous devez appeler une carte. "
    "Les cartes qui seront acceptées sont <ul>");
  for(unsigned int i = 0 ; i < possibles.size() ; i++)
    {
      p("<li class=\"");
      p(possibles[i].couleur_simple());
      p("\">");
      p(possibles[i].nom());
      p("</li>");
    }
  p("</ul></p>");
  SET_HTML(header + body + footer);
}

void Journal::appel_accepte(Carte c)
{
  p("<p class=\"accepte\">L'appel de la carte <span class=\"");
  p(c.couleur_simple());p("\">");p(c.nom());
  p("</span> a réussi.</p>");
  SET_HTML(header + body + footer);
}

void Journal::appel_refuse(Carte c)
{
  p("<p class=\"refuse\">L'appel de la carte <span class=\"");
  p(c.couleur_simple());p("\">");p(c.nom());
  p("</span> a échoué.</p>");
  SET_HTML(header + body + footer);
}

void Journal::contrat_final(Enchere e)
{
  p("<p class=\"information\">Finalement, "
    "<span class=\"joueur\">");
  body+=LabelNom::nom_de(e.joueur());
  p("</span> <span class=\"prise\">");
  switch(e.prise())
    {
    case Enchere::PASSE:
      p("passe");
      break;
    case Enchere::PRISE:
      p("prise");
      break;
    case Enchere::GARDE:
      p("garde");
      break;
    case Enchere::GARDE_SANS:
      p("garde <strong>sans le chien</strong>");
      break;
    case Enchere::GARDE_CONTRE:
      p("garde <strong>contre le chien</strong>");
      break;
    default:
      p("Fait une enchère (indéterminée ?!?!)");
    }
  p("</span> en appelant la carte <span class=\"");
  Carte a = *(e.carte_appelee());
  p(a.couleur_simple());
  p("\">");p(a.nom());p("</span>.");
  p("</p>");
  SET_HTML(header + body + footer);
}

void Journal::chien(Carte c1, Carte c2, Carte c3)
{
  p("<p class=\"information\">Le chien a été dévoilé : <ul>");
  p("<li class=\"");p(c1.couleur_simple());p("\">");
p(c1.nom());p("</li>");
  p("<li class=\"");p(c2.couleur_simple());p("\">");
p(c2.nom());p("</li>");
  p("<li class=\"");p(c3.couleur_simple());p("\">");
p(c3.nom());p("</li>");
  p("</ul></p>");
  SET_HTML(header + body + footer);
}

void Journal::doit_ecarter(std::vector<Carte> possibles,
				    std::vector<Carte> atouts)
{
  p("<p class=\"sollicitation\">Vous devez faire un écart. "
    "Vous pouvez utiliser : <ul>");
  for(unsigned int i = 0 ; i < possibles.size() ; i++)
    {
      p("<li class=\"");p(possibles[i].couleur_simple());
      p("\">");p(possibles[i].nom());p("</li>");
    }
  p("</ul>À la rigueur, vous pouvez taper dans <ul>");
  for(unsigned int i = 0 ; i < atouts.size() ; i++)
    {
      p("<li class=\"");p(atouts[i].couleur_simple());
      p("\">");p(atouts[i].nom());p("</li>");
    }
  p("</ul></p>");
  SET_HTML(header + body + footer);
}

void Journal::ecart_accepte(std::vector<Carte> ecart)
{
  p("<p class=\"accepte\">Votre écart a été accepté : <ul>");
  for(unsigned int i = 0 ; i < ecart.size() ; i++)
    {
      p("<li class=\"");p(ecart[i].couleur_simple());
      p("\">");p(ecart[i].nom());p("</li>");
    }
  p("</ul></p>");
  SET_HTML(header + body + footer);
}

void Journal::ecart_refuse(std::vector<Carte> ecart)
{
  p("<p class=\"refuse\">Votre écart a été refusé : <ul>");
  for(unsigned int i = 0 ; i < ecart.size() ; i++)
    {
      p("<li class=\"");p(ecart[i].couleur_simple());
      p("\">");p(ecart[i].nom());p("</li>");
    }
  p("</ul></p>");
  SET_HTML(header + body + footer);
}

void Journal::atout_au_chien(std::vector<Carte> atouts)
{
  p("<p class=\"information\">Le preneur a écarté un ou des"
    " atouts : <ul>");
  for(unsigned int i = 0 ; i < atouts.size() ; i++)
    {
      p("<li class=\"");p(atouts[i].couleur_simple());
      p("\">");p(atouts[i].nom());p("</li>");
    }
  p("</ul></p>");
  SET_HTML(header + body + footer);
}

void Journal::maitre_change(unsigned int maitre)
{
  p("<p class=\"information\">Le joueur maître change : "
    "c'est maintenant <span class=\"joueur\">");
  body+=LabelNom::nom_de(maitre);
  p("</span>.</p>");
}

void Journal::jeu_change(std::vector<Carte> gagnees,
				  std::vector<Carte> perdues)
{
  p("<p class=\"information\">Votre jeu change : vous "
    "avez gagné <ul>");
  for(unsigned int i = 0 ; i < gagnees.size() ; i++)
    {
      p("<li class=\"");p(gagnees[i].couleur_simple());
      p("\">");p(gagnees[i].nom());p("</li>");
    }
  p("</ul> et vous avez perdu <ul>");
  for(unsigned int i = 0 ; i < perdues.size() ; i++)
    {
      p("<li class=\"");p(perdues[i].couleur_simple());
      p("\">");p(perdues[i].nom());p("</li>");
    }
  p("</ul></p>");
  SET_HTML(header + body + footer);
}

void Journal::doit_jouer()
{
  p("<p class=\"sollicitation\">Vous devez jouer.</p>");
  SET_HTML(header + body + footer);
}

void Journal::requete_acceptee(Carte jouee)
{
  p("<p class=\"accepte\">Vous avez réussi à jouer "
    "<span class=\"");
  p(jouee.couleur_simple());
  p("\">");p(jouee.nom());p("</span></p>");
  SET_HTML(header + body + footer);
}

void Journal::requete_refusee(Carte jouee)
{
  p("<p class=\"refuse\">Vous n'avez pas réussi à jouer "
    "<span class=\"");
  p(jouee.couleur_simple());
  p("\">");p(jouee.nom());p("</span></p>");
  SET_HTML(header + body + footer);
}

void Journal::carte_jouee(unsigned int joueur,
				   Carte jouee)
{
  p("<p class=\"information\"><span class=\"joueur\">");
  body+=LabelNom::nom_de(joueur);
  p("</span> a joué <span class=\"");
  p(jouee.couleur_simple());p("\">");p(jouee.nom());
  p("</span></p>");
  SET_HTML(header + body + footer);
}

void Journal::carte_gagnee(Carte carte, 
				    unsigned int poseur,
				    unsigned int gagnant)
{
  p("<p class=\"information\"><span class=\"joueur\">");
  body+=LabelNom::nom_de(gagnant);
  p("</span> remporte la carte <span class=\"");
  p(carte.couleur_simple());p("\">");p(carte.nom());
  p("</span> de <span class=\"joueur\">");
  body+=LabelNom::nom_de(poseur);
  p("</span></p>");
  SET_HTML(header + body + footer);
}

void Journal::pli_termine(unsigned int gagnant)
{
  p("<p class=\"information\"><span class=\"joueur\">");
  body+=LabelNom::nom_de(gagnant);
  p("</span> remporte le pli.</p>");
  SET_HTML(header + body + footer);
}

void Journal::tapis_change(Tapis tapis)
{
  p("<p class=\"information\">Le tapis change : ");
  std::vector<Carte> cartes;
  std::vector<unsigned int> poseurs;
  tapis.contenu(cartes, poseurs);
  unsigned int maitre;
  if(tapis.maitre(maitre))
    {
      p("le joueur maître est <span class=\"joueur\">");
      body+=LabelNom::nom_de(maitre);
      p("</span>.");
    }
  else p("le tapis est vide.");
  p("<table><tr><th>Joueur</th><th>Carte</th></tr>");
  for(unsigned int i = 0 ; i < cartes.size() ; i++)
    {
      p("<tr><td class=\"joueur\">");
      body+=LabelNom::nom_de(poseurs[i]);
      p("</td><td class=\"");p(cartes[i].couleur_simple());
      p("\">");p(cartes[i].nom());p("</td></tr>");
    }
  p("</table></p>");
  SET_HTML(header + body + footer);
}

void Journal::partie_terminee(std::vector<int> scores)
{
  p("<p class=\"information\">La partie est terminée : ");
  p("<table><tr><th>Joueur</th><th>Score</th></tr>");
  for(unsigned int i = 0 ; i < scores.size() ; i++)
    {
      p("<tr><td class=\"joueur\">");
      body+=LabelNom::nom_de(i);
      p("</td><td>");body+=scores[i];p("</td></tr>");
    }
  p("</table></p>");
  SET_HTML(header + body + footer);
}

void Journal::p(std::string const & utf8)
{
  body += (QString::fromUtf8(utf8.c_str()));
}
