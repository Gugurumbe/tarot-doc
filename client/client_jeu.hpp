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
     @brief Émis lorsque mon numéro change.
     @param n Mon nouveau numéro.
   */
  void numero_change(unsigned int n);

  /**
     @brief Émis lorsque mon jeu change.
   */
  void jeu_change();

  /**
     @brief Émis lorsque je dois priser.
   */
  void doit_priser();
  
  /**
     @brief Émis lorsque mon enchère a été refusée.
  */
  void enchere_refusee();

  /**
     @brief Émis lorsqu'un joueur effectue une enchère.
     @param j Le numéro de ce joueur;
     @param e L'enchère réalisée.

     @note Il y a une redondance : j correspond à e.joueur()
   */
  void contrat_intermediaire(unsigned int j, Enchere e);

  /**
     @brief Émis lorsque je dois appeler une Carte.
   */
  void doit_appeler();

  /**
     @brief Émis lorsque le serveur refuse que j'appelle cette
     Carte.
   */
  void appel_refuse();

  /**
     @brief Émis lorsque le contrat final est divulgué.
     
     @param e L'enchère correspondante.
   */
  void contrat_final(Enchere e);

  /**
     @brief Émis lorsque le Chien est dévoilé.
     
     @param c1 La première carte.
     @param c2 ...
     @param c3 ...
   */
  void chien_devoile(Carte c1, Carte c2, Carte c3);

  /**
     @brief Émis lorsqu'on doit faire un écart.
   */
  void doit_ecarter();

  /**
     @brief Émis lorsque l'écart a été accepté.
   */
  void ecart_accepte();

  /**
     @brief Émis lorsque l'écart a été refusé.
   */
  void ecart_refuse();

  /**
     @brief Émis lorsque des atouts ont été mis au chien.

     @param atouts Les atouts en question.
   */
  void atout_au_chien(std::vector<Carte> atouts);

  /**
     @brief Émis lorsque je dois jouer.
   */
  void doit_jouer();

  /**
     @brief Émis lorsque ma carte a été refusée.
   */
  void requete_refusee();
  
  /**
     @brief Émis lorsque le serveur accepte que je joue ma carte.
   */
  void requete_acceptee();
  
  /**
     @brief Émis lorsqu'une carte a été jouée.
     
     @param joueur Le numéro du joueur qui a joué cette Carte.
     @param carte La carte en question.
   */
  void carte_jouee(unsigned int joueur, Carte carte);

  /**
     @brief Émis à la fin de la manche.

     @param scores Les scores de chacun.
     @note La somme des scores fait 0.
   */
  void score(std::vector<int> scores);

  /**
     @brief Émis lorsqu'un joueur remporte une carte.
     
     @param c La carte en question.
     @param poseur Le joueur qui avait joué cette Carte.
     @param gagnant Le joueur qui a finalement remporté cette carte.
   */
  void carte_gagnee(Carte c, unsigned int poseur, unsigned int gagnant);

  /**
     @brief Émis lorsqu'une levée est terminée.

     @param j Le numéro du joueur qui a remporté cette levée.
   */
  void pli(unsigned int j);

  /**
     @brief Émis lorsque le joueur maître change.
     
     @param m Le nouveau joueur maître.
   */
  void maitre(unsigned int m);
private:
  PartieClient partie;
};

#endif
