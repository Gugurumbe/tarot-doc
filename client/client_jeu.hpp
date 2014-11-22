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
  
  void numero_change(unsigned int);
  void jeu_change();
  void doit_priser();
  void enchere_refusee();
  void contrat_intermediaire(unsigned int, Enchere);
  void doit_appeler();
  void appel_refuse();
  void contrat_final(Enchere);
  void chien_devoile(Carte, Carte, Carte);
  void doit_ecarter();
  void ecart_accepte();
  void ecart_refuse();
  void atout_au_chien(std::vector<Carte>);
  void doit_jouer();
  void requete_refusee();
  void requete_acceptee();
  void carte_jouee(unsigned int, Carte);
  void score(std::vector<int>);
  void carte_gagnee(Carte, unsigned int, unsigned int);
  void pli(unsigned int);
  void maitre(unsigned int);
private:
  PartieClient partie;
};

#endif
