#include "ia.hpp"
IA::IA(QObject * parent): QObject(parent),
			  jeu(this)
{
#define C(signal) \
  QObject::connect(&jeu, SIGNAL(signal), this, SLOT(signal));
  C(connecte());
  C(deconnecte());
  C(numero_change(unsigned int));
  C(doit_priser(Option<Enchere>));
  C(enchere_acceptee(Enchere));
  C(enchere_refusee(Enchere));
  C(contrat_intermediaire(Enchere));
  C(doit_appeler(std::vector<Carte>));
  C(appel_accepte(Carte));
  C(appel_refuse(Carte));
  C(contrat_final(Enchere));
  C(chien(Carte, Carte, Carte));
  C(doit_ecarter(std::vector<Carte>, std::vector<Carte>));
  C(ecart_accepte(std::vector<Carte>));
  C(ecart_refuse(std::vector<Carte>));
  C(atout_au_chien(std::vector<Carte>));
  C(maitre_change(unsigned int));
  C(jeu_change(std::vector<Carte>, std::vector<Carte>));
  C(doit_jouer());
  C(requete_acceptee(Carte));
  C(requete_refusee(Carte));
  C(carte_jouee(unsigned int, Carte));
  C(carte_gagnee(Carte, unsigned int, unsigned int));
  C(pli_termine(unsigned int));
  C(tapis_change(Tapis));
  C(partie_terminee(std::vector<int>));
}
void IA::connecter(QHostAddress hote, quint16 port)
{
  jeu.connecter(hote, port);
}
void IA::connecte()
{
  //C'est très bien...
}
void IA::deconnecte()
{
}
void IA::numero_change(unsigned int)
{
}
void IA::doit_priser(Option<Enchere>)
{
  //Je passe
  jeu.formuler_prise(Enchere::PASSE);
}
void IA::enchere_acceptee(Enchere)
{
}
void IA::enchere_refusee(Enchere)
{
  //doit_priser est réémis.
}
void IA::contrat_intermediaire(Enchere)
{
}
void IA::doit_appeler(std::vector<Carte> appelables)
{
  //J'appelle npqui
  jeu.formuler_appel(appelables[rand() % appelables.size()]);
}
void IA::appel_accepte(Carte)
{
}
void IA::appel_refuse(Carte)
{
}
void IA::contrat_final(Enchere)
{
}
void IA::chien(Carte,Carte,Carte)
{
}
void IA::doit_ecarter(std::vector<Carte> possibles, 
		      std::vector<Carte> atouts)
{
  //J'écarte dans l'ordre
  std::vector<Carte> ecart = possibles;
  ecart.insert(ecart.end(), atouts.begin(), atouts.end());
  std::vector<Carte> retenu;
  retenu.push_back(ecart[0]);
  retenu.push_back(ecart[1]);
  retenu.push_back(ecart[2]);
  jeu.formuler_ecart(retenu);
}
void IA::ecart_accepte(std::vector<Carte>)
{
}
void IA::ecart_refuse(std::vector<Carte>)
{
}
void IA::atout_au_chien(std::vector<Carte>)
{
}
void IA::maitre_change(unsigned int)
{
}
void IA::jeu_change(std::vector<Carte>,
		    std::vector<Carte>)
{
}
void IA::doit_jouer()
{
  //La première fois, on tente de jouer npq. Après, on essaye la carte
  //suivante lorsqu'elle est refusée.
  jeu.formuler_requete(Carte(rand() % 78));
}
void IA::requete_acceptee(Carte)
{
}
void IA::requete_refusee(Carte refusee)
{
  if(jeu.partie().mon_tour() && 
     jeu.partie().phase() == Partie::PHASE_JEU)
    {
      jeu.formuler_requete(Carte((refusee.numero() + 1) % 78));
    }
}
void IA::carte_jouee(unsigned int, Carte)
{
}
void IA::carte_gagnee(Carte, unsigned int, unsigned int)
{
}
void IA::pli_termine(unsigned int)
{
}
void IA::tapis_change(Tapis)
{
}
void IA::partie_terminee(std::vector<int>)
{
  deleteLater();
}
