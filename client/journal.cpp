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
  p("<!DOCTYPE html>");
  p("<html>");
  p("<head>");
  p("<title>Journal</title>");
  p("<meta charset=\"utf8\"/>");
  p("<link rel=\"stylesheet\" type=\"text/css\" href=");
  p(STYLE);
  p("/>");
  p("</head>");
  p("<body>");
  p("<p>");
  footer+=S("</p></body></html>");
}

void Journal::afficher_connexion()
{
  ENTER("afficher_connexion()");
  p("<p class=\"connexion\">Connecté.</p>");
  setHtml(header + footer);
}

void Journal::afficher_deconnexion()
{
  ENTER("afficher_deconnexion()");
  p("<p class=\"deconnexion\">Déconnecté.</p>");
  setHtml(header + footer);
}

void Journal::afficher_numero_change(unsigned int n)
{
  p("<p class=\"information\">Vous jouez en tant que"
    " <span class=\"joueur\">");
  header += LabelNom::nom_de(n);
  p("</span>.</p>");
  setHtml(header + footer);
}

void Journal::afficher_doit_priser(Option<Enchere> max)
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
      header+=LabelNom::nom_de(max.get().joueur());
      p("</span>.");
      switch(max.get().prise())
	{
	case Enchere::PASSE:
	  p("Il a <span class=\"prise\">passé</span>.");
	  break;
	case Enchere::PRISE:
	  p("Il a <span class=\"prise\">prisé</span>.");
	  break;
	case Enchere::GARDE:
	  p("Il a <span class=\"prise\">gardé</span>.");
	  break;
	case Enchere::GARDE_SANS:
	  p("Il a <span class=\"prise\">gardé <strong>"
	    "sans le chien</strong></span> !");
	  break;
	case Enchere::GARDE_CONTRE:
	  p("Il a <span class=\"prise\">gardé <strong>"
	    "contre le chien</strong></span> !");
	  break;
	default:
	  p("Je n'ai pas réussi à déterminer sa prise.");
	}
      p("</p>");
    }
}

void Journal::afficher_enchere_acceptee(Enchere e)
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
}

void Journal::p(std::string const & utf8)
{
  header += (QString::fromUtf8(utf8.c_str()));
}
