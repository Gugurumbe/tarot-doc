/**
   @file client/ai/ia.hpp
 */
#ifndef IA_DEFINIE
/**
   @brief Empêche les inclusions récursives.
 */
#define IA_DEFINIE
#include "client_jeu.hpp"
/**
   @brief Classe d'intelligence artificielle.
   
   Même fonctionnement qu'un client graphique, à ceci près qu'elle
   prend elle-même ses décisions.
 */
class IA : public QObject
{
  Q_OBJECT;
public:
  /**
     @brief Constructeur par défaut.
     @param parent Le parent Qt.
   */
  IA(QObject * parent = 0);
public slots:
  /**
     @brief Initie une connexion à un serveur.
     @param hote L'adresse du serveur.
     @param port Le port d'écoute.
   */
  void connecter(QHostAddress hote, quint16 port);
  void connecte();
  void deconnecte();
  void numero_change(unsigned int numero);
  void doit_priser(Option<Enchere> plus_forte);
  void enchere_acceptee(Enchere e);
  void enchere_refusee(Enchere e);
  void contrat_intermediaire(Enchere contrat);
  void doit_appeler(std::vector<Carte> appelables);
  void appel_accepte(Carte appelee);
  void appel_refuse(Carte c);
  void contrat_final(Enchere finale);
  void chien(Carte c1, Carte c2, Carte c3);
  void doit_ecarter(std::vector<Carte> possibles,
		    std::vector<Carte> atouts);
  void ecart_accepte(std::vector<Carte> ecart);
  void ecart_refuse(std::vector<Carte> invalide);
  void atout_au_chien(std::vector<Carte> atouts);
  void maitre_change(unsigned int maitre);
  void jeu_change(std::vector<Carte> gagnees, 
		  std::vector<Carte> perdues);
  void doit_jouer();
  void requete_acceptee(Carte c);
  void requete_refusee(Carte c);
  void carte_jouee(unsigned int joueur, Carte c);
  void carte_gagnee(Carte c, unsigned int poseur, 
		    unsigned int gagnant);
  void pli_termine(unsigned int maitre);
  void tapis_change(Tapis tapis);
  void partie_terminee(std::vector<int> scores);
private:
  ClientJeu jeu;
};
#endif
