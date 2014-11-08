/**
   @file server/serveur.hpp
   @brief Définit le moteur "réseau" du serveur.
 */

#ifndef SERVEUR_DEFINI

/**
   Empêche les inclusions récursives.
 */
#define SERVEUR_DEFINI

#include "protocole.hpp"
#include "config.hpp"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <vector>

/**
   @brief Définit une classe communiquant sur le réseau.
   
   La classe Serveur utilise les outils Qt pour établir des
   transmissions en mode connecté (Tcp), grâce auxquelles il peut
   envoyer et recevoir des Protocole::Messages tels que définis dans
   shared/protocole.hpp.

   Telle quelle, cette classe ne sait pas quoi faire des Protocole::Messages
   reçus et des déconnexions des clients, et ne sait pas quand envoyer
   des Protocole::Messages aux clients. Il y a pour l'instant 2 comportements :
   ServeurDebogage, qui répète inlassablement tous les Protocole::Messages reçus,
   en envoyant ERREUR_PROTOCOLE en cas de besoin, et ServeurJeu, en
   construction, qui va réagir selon les règles du tarot.

   L'interaction entre les classes ServeurJeu / ServeurDebogage, Table
   et les joueurs ne se fait pas avec des QTcpSocket, mais avec un
   numéro d'identification unique des clients, utilisé pour envoyer un
   message, pour forcer une déconnexion, pour savoir d'où vient un
   message et pour savoir qui s'est déconnecté.
   
   Les identifiants des clients déconnectés sont réutilisés.

   Il existe une symétrie de construction entre le Client et le
   Serveur : une classe générale qui relaye des Protocole::Message à une classe
   spécialisée pour le débogage ou à une classe spécialisée pour le
   jeu, qui utilise une spécialisation de Partie.
 */
class Serveur : public QObject
{
  Q_OBJECT;
 public:

  /**
     @brief Constructeur par défaut.

     Constructeur par défaut "à la Qt". N'ouvre aucune partie pour
     l'instant. 
   */
  Serveur(QObject * parent = 0);

  /**
     @brief Ouvre une partie 1 joueur.
     
     Lance le serveur sur l'adresse loopback, c'est-à-dire que seuls
     les programmes utilisant le même ordi peuvent jouer sur ce
     serveur. L'avantage, c'est qu'on n'accède absolument pas à
     Internet. 

     @return Le port de listage.
   */
  unsigned int ouvrir_local();

  /**
     @brief Ouvre une partie multijoueur.
     
     Lance le serveur sur toutes les interfaces. N'importe qui peut
     jouer sur ce serveur, mais il faut préparer le routeur (ouvrir le
     pare-feu et rediriger les paquets reçus vers le serveur) et le
     pare-feu que vous pouvez peut-être utiliser sur votre ordi.

     @return Le port de listage. Communiquez-le à vos clients.
   */
  unsigned int ouvrir_global();

public slots:

  /**
     @brief Vérifie les nouvelles connexions.

     En cas de nouvelle connexion, émet le signal
     Serveur::connexion(unsigned int) avec l'identification qui lui a
     été attribuée.

     Le déclenchement de ce slot est automatique.
   */
  void accepter();

  /**
     @brief Nettoie la liste des socket.
     
     Envoie le message deconnexion(unsigned int) si l'objet sock est
     une socket de la liste.

     Le déclenchement de ce slot est automatique.

     @param sock : la QTcpSocket à enlever de la liste.
   */
  void enlever(QObject * sock);

  /**
     @brief Enlève l'objet appelant de la liste des sockets.

     Le déclenchement de ce slot est automatique.

     @see Serveur::enlever(QObject *)
   */
  void enlever();

  /**
     @brief Regarde si on peut lire un Protocole::Message.

     Au besoin, émet message(unsigned int, Protocole::Message) et
     message_brut(unsigned int, QByteArray) ou 
     deconnexion(unsigned int).

     Le déclenchement de ce slot est automatique.
   */
  void lire();

  /**
     @brief Élimine le client.

     Déconnecte sans scrupule le client.
     @param c : le client à déconnecter.
   */
  void deconnecter(unsigned int c);

  /**
     @brief Envoie au client un paquet brut.
     
     @note Il est plus intéressant d'envoyer un Protocole::Message avec
     Serveur::envoyer(unsigned int, Protocole::Message), pour utiliser les
     fonctions de lecture/écriture de shared/protocole.hpp.

     À des fins de débogage, on peut avoir envie d'envoyer un paquet
     qui ne respecte pas le protocole.
     @param c : le numéro du destinataire.
     @param p : le paquet d'octets à envoyer.
     
     @see Serveur::envoyer(unsigned int, Protocole::Message)
   */
  void envoyer(unsigned int c, QByteArray p);

  /**
     @brief Envoie au client un Protocole::Message.

     @param c : le numéro du destinataire.
     @param m : le Protocole::Message respectant le protocole.

     @see Serveur::envoyer(unsigned int, QByteArray)
   */
  void envoyer(unsigned int c, Protocole::Message m); 

 signals:

  /**
     @brief Émis lorsqu'un client se connecte.

     @param c : l'identification qui lui a été attribuée.
   */
  void connexion(unsigned int c);

  /**
     @brief Émis lorsqu'un client envoie un paquet.
     
     @note Le signal Serveur::message(unsigned int, Protocole::Message) est
     simultanément émis, il n'y a pas besoin de tenir compte de ce
     signal (sauf à des fins de débogage).
     
     @param c : l'identification de l'émetteur.
     @param p : le paquet reçu.

     @see Serveur::message(unsigned int, Protocole::Message)
   */
  void message_brut(unsigned int c, QByteArray p);

  /**
     @brief Émis lorsqu'un client se déconnecte.
     
     @param c : l'identification du client sortant.
   */
  void deconnexion(unsigned int c);

  /**
     @brief Émis lorsqu'un Protocole::Message est reçu.

     @param c : l'identification du client.
     @param m : le Message reçu.
     
     @see Serveur::message(unsigned int, QByteArray)
   */
  void message(unsigned int c, Protocole::Message m);

 private:

  /**
     @brief Ajoute une socket.
     
     @note Aucun signal n'est connecté à aucun slot.
     
     @param sock : l'objet Qt qui correspond.
     @return L'identification du nouveau client.
   */
  unsigned int push(QTcpSocket * sock);

  /**
     @brief Enlève le client.
     
     Déconnecte les signaux liés à l'objet Qt correspondant. De cette
     façon, l'objet peut être détruit sereinement.

     @param i : l'identification du client.
   */
  void remove(unsigned int i);

  /**
     @brief Retrouve une identification.

     À partir de l'objet Qt, retrouve l'identification du client.
     
     @param sock : la QTcpSocket.
     @return Le numéro d'identification.
   */
  unsigned int find(QObject * sock);

  /**
     @brief Socket de listage.
     
     Permet d'ouvrir des parties réseau et d'accepter les connexions
     entrantes.
   */
  QTcpServer listener;

  /**
     @brief Tableau des clients.

     Ce tableau est indexé par les numéros d'identifications. Il
     contient les objets Qt de socket.
   */
  std::vector<QTcpSocket *> clients;

  /**
     @brief Première place libre.

     La plus petite identification non utilisée.
   */
  unsigned int ppl;
};

#endif
