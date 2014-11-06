/**
   @file server/partie_serveur.hpp
   @brief Spécialise une Partie côté client.
 */

#ifndef PARTIE_SERVEUR_DEFINIE

/**
   Empêche les inclusions récursives.
*/
#define PARTIE_SERVEUR_DEFINIE

#include "partie.hpp"
#include <QObject>

/**
   @brief Précision d'une Partie, côté serveur.

   La classe PartieServeur comprend les messages du point de vue d'un
   arbitre. Ses caractéristiques principales sont :
   1. Une capacité à émettre des Messages, grâce à l'héritage de
   QObject. 
   2. La connaissance de l'ensemble des cartes du jeu, et donc des
   équipes. 
 */
class PartieServeur: public QObject, public Partie
{
public:

  /**
     @brief Constructeur par défaut.

     Lance la distribution des cartes.
   */
  PartieServeur();

  /**
     @brief Réimplémente Partie::assimiler(const Message &).
     
     Met à jour le jeu réel, les cartes gagnées par le camp attaquant.
     @param message : le Message à assimiler. Peut provenir du serveur
     lui-même. 
   */
  void assimiler(const Message & message);

  /**
     @brief Teste une requête.
     
     @param joueur : le joueur effectuant cette requête.
     @param m : la requête en question.
     
     @return 0 si la requête est acceptée.
     @return 1 si la requête est une erreur de protocole.
     @return 2 si la requête est refusée.
   */
  int tester(unsigned int joueur, const Message & m) const;
private:

  /**
     @brief Le jeu réel.
  */
  std::vector<Main> jeu_reel;

  /**
     @brief Les cartes gagnées par l'attaque.
     
     On compte les points à la fin.
  */
  std::vector<std::vector<Carte> > carte_gagnees;

  /**
     @brief Le chien.
   */
  std::vector<Carte> chien;

  /**
     @brief Distribution des cartes.
     
     Émet des signaux doit_emettre(). Est appelée au début. 
   */
  void distribuer();
public slots:
signals:
  
  /**
     @brief Signal à connecter à 
     Table::doit_emettre(unsigned int,Message)

     @param j : le joueur à qui adresser le Message.
     @param m : le Message à adresser.
   */
  void doit_emettre(unsigned int j, Message m);
};

#endif
