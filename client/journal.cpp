#include "journal.hpp"
#include "label_nom.hpp"
#include "config.hpp"

#define S(texte) QString::fromUtf8(texte)

Journal::Journal(QWidget * parent):
  QTextBrowser(parent)
{
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
  header+=S("<p class=\"connexion\">Connecté.</p>");
  setHtml(header + footer);
}

void Journal::afficher_deconnexion()
{
  header+=S("<p class=\"deconnexion\">Déconnecté.</p>");
  setHtml(header + footer);
}

void Journal::afficher_numero(unsigned int n)
{
  header+=S("<p class=\"numero\">Vous êtes ");
  header+=LabelNom::nom_de(n);
  header+=S(".</p>");
  setHtml(header + footer);
}
