/**
   @file server/table.hpp
   @brief Définit une interface entre le Serveur et la Partie. 
 */

#ifndef TABLE_DEFINIE

/**
   Empêche les inclusions récursives.
 */
#define TABLE_DEFINIE

#include <QObject>

#include "protocole.hpp"

#include <vector>

/**
   @brief Classe de Table.

   Une Table est une réunion de 5 joueurs qui s'envoient des Message. 
   
   La Table a la fonction suivante : à partir du numéro
   d'identification d'un client, elle en déduit le numéro de joueur
   utilisable par la classe Partie et vice versa.

   L'autre fonction est de relayer les Message entre la Partie et le
   Serveur. 
 */
class Table : public QObject
{
  Q_OBJECT;
public:
  /**
     @brief Constructeur par défaut.
   */
  Table(QObject * parent = 0);
signals:
  
  /**
     @brief Relaye le Message.

     Indique au ServeurJeu qu'il doit envoyer ce Message à ce numéro
     d'identification. 
     
     @param c : l'identification du destinataire.
     @param m : le Message à transmettre.

     @see Serveur::envoyer(unsigned int, Message)
   */
  void doit_emettre(unsigned int c, Message m);

  /**
     @brief Relaye l'ordre de déconnexion.
     
     @param c : l'identification à déconnecter.

     @see Serveur::deconnecter(unsigned int)
   */
  void doit_deconnecter(unsigned int c);
  
  /**
     @brief Signale au ServeurJeu que la Table est pleine.
     
     @param t : la Table courante (this).

     @see ServeurJeu::detacher_table(Table *)
   */
  void complet(Table * t);

  /**
     @brief Signale au ServeurJeu que la Table doit être complétée. 
     
     @note Pour l'instant, la Table préfèrera s'autodétruire que
     d'émettre ce signal.

     @param t : la Table courante (this).

     @see ServeurJeu::rattacher_table(Table *)
   */
  void incomplet(Table * t);			 
public slots:

  /**
     @brief Ajoute un joueur à la Table.

     Si la Table est complète, celui-ci est immédiatement déconnecté.

     Peut émettre complet(Table *) avec 'this' en argument.

     @param c : l'identification du nouveau client.

     @see Serveur::connexion(unsigned int)
   */
  void ajouter(unsigned int c);

  /**
     @brief Transmet un Message à la Partie

     @warning Il faut d'abord vérifier que le client dont il est
     question est bien un des joueurs, car ce slot est appelé dans
     chaque Table pour chaque Message.

     @param c : l'identification du client bavard.

     @param m : le Message reçu.

     @see Serveur::message(unsigned int, Message)
   */
  void comprendre(unsigned int c, Message m);

  /**
     @brief Enlève un joueur de la Table.

     Peut émettre le signal Table::incomplet()

     @warning Il faut d'abord vérifier que le client dont il est
     question est bien un des joueurs, car ce slot est appelé dans
     chaque Table pour chaque déconnexion.

     @param c : l'identification du client sortant.
     
     @see Serveur::deconnexion(unsigned int)
   */
  void enlever(unsigned int c);
private:
  
  /**
     @brief Indentifications.
   */
  std::vector<int> joueurs ;

  /**
     @brief Numéros des joueurs.
   */
  std::vector<int> ordre;
};

#endif
