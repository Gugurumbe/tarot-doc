/**
   @file client/client_jeu.hpp
   @brief Spécialise le moteur "réseau" pour jouer avec un serveur.
 */

#ifndef CLIENT_JEU_DEFINI

/**
   Empêche les inclusions récursives.
 */
#define CLIENT_JEU_DEFINI

#include "client.hpp"
#include "partie.hpp"
#include "partie_client.hpp"

#include <iostream>
#include <iomanip>

/**
   @brief Spécialise la classe Client, en permettant de comprendre
   l'environnement de jeu du tarot.

   Utilisera la classe PartieClient.
 */

class ClientJeu : public Client
{
  Q_OBJECT;
public:
  /**
     @brief Constructeur par défaut.
   */
  ClientJeu(QObject * parent = 0);

  /**
     @brief Présente l'état des cartes.
   */
  void presenter_etat();
public slots:
  
  /**
     @brief Réaction personnalisée (connexion).
     
     @see Client::connecte()
   */
  void traiter_connexion();

  /**
     @brief Réaction personnalisée (déconnexion).

     @see Client::deconnecte()
   */
  void traiter_deconnexion();

  /**
     @brief Réaction personnalisée (message).
     
     @param m : Message reçu du serveur.

     @see Client::recu(Message)
   */
  void traiter_message(Protocole::Message m);

  /**
     @brief Envoie un message pour formuler une Prise.
     
     @param p La prise en question.

     @see PartieClient::formuler_prise(Enchere::Prise);
   */
  void formuler_prise(Enchere::Prise p);

  /**
     @brief Traité lorsqu'un joueur effectue une enchère.
     @param j Le numéro de ce joueur;
     @param e L'enchère réalisée.

     @note Il y a une redondance : j correspond à e.joueur()
   */
  void contrat_intermediaire(unsigned int j, Enchere e);

  /**
     @brief Traité lorsque je dois appeler une Carte.
   */
  void doit_appeler();

  /**
     @brief Traité lorsque le serveur refuse que j'appelle cette
     Carte.
   */
  void appel_refuse();

  /**
     @brief Traité lorsque le contrat final est divulgué.
     
     @param e L'enchère correspondante.
   */
  void contrat_final(Enchere e);

  /**
     @brief Traité lorsque le Chien est dévoilé.
     
     @param c1 La première carte.
     @param c2 ...
     @param c3 ...
   */
  void chien_devoile(Carte c1, Carte c2, Carte c3);

  /**
     @brief Traité lorsqu'on doit faire un écart.
   */
  void doit_ecarter();

  /**
     @brief Traité lorsque l'écart a été accepté.
   */
  void ecart_accepte();

  /**
     @brief Traité lorsque l'écart a été refusé.
   */
  void ecart_refuse();

  /**
     @brief Traité lorsque des atouts ont été mis au chien.

     @param atouts Les atouts en question.
   */
  void atout_au_chien(std::vector<Carte> atouts);

  /**
     @brief Traité lorsque je dois jouer.
   */
  void doit_jouer();

  /**
     @brief Traité lorsque ma carte a été refusée.
   */
  void requete_refusee();
  
  /**
     @brief Traité lorsque le serveur accepte que je joue ma carte.
   */
  void requete_acceptee();
  
  /**
     @brief Traité lorsqu'une carte a été jouée.
     
     @param joueur Le numéro du joueur qui a joué cette Carte.
     @param carte La carte en question.
   */
  void carte_jouee(unsigned int joueur, Carte carte);

  /**
     @brief Traité à la fin de la manche.

     @param scores Les scores de chacun.
     @note La somme des scores fait 0.
   */
  void score(std::vector<int> scores);

  /**
     @brief Traité lorsqu'un joueur remporte une carte.
     
     @param c La carte en question.
     @param poseur Le joueur qui avait joué cette Carte.
     @param gagnant Le joueur qui a finalement remporté cette carte.
   */
  void carte_gagnee(Carte c, unsigned int poseur, unsigned int gagnant);

  /**
     @brief Traité lorsqu'une levée est terminée.

     @param j Le numéro du joueur qui a remporté cette levée.
   */
  void pli(unsigned int j);

  /**
     @brief Traité lorsque le joueur maître change.
     
     @param m Le nouveau joueur maître.
   */
  void maitre(unsigned int m);

signals:
  
  /**
     @brief Émis lorsqu'on m'informe de mon numéro.
     
     @param n Mon numéro, entre 0 inclus et 5 exclus.
   */
  void numero_change(unsigned int n);

  /**
     @brief Émis lorsque je suis le premier et que je dois priser.

     @see PartieClient::doit_priser()
   */
  void doit_priser();

  /**
     @brief Émis lorsque je dois priser.
     
     @param max L'enchère maximale.
     @see PartieClient::doit_priser(Enchere)
   */
  void doit_priser(Enchere max);

  /**
     @brief Émis lorsque mon enchère a été refusée.
  */
  void enchere_refusee();

  /**
     @brief Émis lorsqu'un contrat intermédiaire est formulé.
     
     @param e L'enchère en question.
   */
  void dernier_contrat(Enchere e);

  /**
     @brief Émis lorsque le tapis change.
     
     @param tapis Le tapis.
   */
  void tapis_change(const Tapis & tapis);

  /**
     @brief Émis lorsque le maître du tapis change.
   */
  void maitre_change(unsigned int joueur);

  /**
     @brief Émis lorsque mon jeu change.
     
     @param gagnees Les cartes reçues.
     @param perdues Les cartes perdues.
   */
  void jeu_change(std::vector<Carte> gagnees,
		  std::vector<Carte> perdues);

private:
  PartieClient partie;
};

#endif
