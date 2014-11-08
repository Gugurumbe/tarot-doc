/**
   @file client/client_debogage.hpp
   @brief Spécialise le moteur "réseau" pour déboguer un serveur.
 */

#ifndef CLIENT_DEBOGAGE_DEFINI

/**
   Empêche les inclusions récursives.
 */
#define CLIENT_DEBOGAGE_DEFINI

#include "client.hpp"

/**
   @brief Spécialise la classe Client, en adoptant le comportement
   suivant : 
   1. Demander à l'utilisateur où se connecter.
   2. Demander à l'utilisateur d'entrer un Message (ou un paquet brut)
   3. Attendre de recevoir la réponse, puis l'afficher.
   4. Si le client est toujours connecté, retourner à 2. Sinon,
   terminer. 
 */
class ClientDebogage : public Client
{
  Q_OBJECT;
public:
  /**
     @brief Constructeur par défaut.

     Attend que la fonction main() fournisse l'adresse et le port de
     connexion.
   */
  ClientDebogage(QObject * parent = 0);
public slots:
  
  /**
     @brief Réaction personnalisée (connexion).
     
     Lance la boucle principale.
     
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

     @param m : le Message reçu du serveur.
     
     @see Client::recu(Message)
   */
  void traiter_message(Protocole::Message m);

  /**
     @brief Demande à l'utilisateur d'entrer un Message.
   */
  void demander_ordres();
};

#endif
