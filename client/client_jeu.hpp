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
  void traiter_message(Message m);
private:
};

#endif
