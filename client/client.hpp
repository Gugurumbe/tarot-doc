/**
   @file client/client.hpp
   @brief Définit le moteur "réseau" du client et de l'IA.
 */

#ifndef CLIENT_DEFINI

/**
   Empêche les inclusions récursives.
 */
#define CLIENT_DEFINI

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include "protocole.hpp"

/**
   @brief Définit une classe communiquant avec un serveur sur le
   réseau.
   
   La classe Client utilise les outils Qt pour établir une
   transmission en mode connecté (Tcp), grâce à laquelle il peut
   envoyer et recevoir des Messages tels que définis dans
   shared/protocole.hpp. 
   
   Telle quelle, cette classe ne sait pas quoi faire des Messages
   reçus et de la déconnexion du serveur, et ne sait pas quand envoyer
   des Messages au serveur. Il y a pour l'instant 2 comportements :
   ClientDebogage, qui demande à l'utilisateur d'entrer un message
   puis qui attend de recevoir un message, redemande à l'utilisateur
   d'entrer un message et ainsi de suite jusqu'à la déconnexion, et
   ClientJeu, en construction, qui va réagir dans un environnement de
   tarot. 

   Cette classe peut être utilisée aussi bien pour un client graphique
   que pour un client autonome (IA).

   Il existe une symétrie de construction entre le Client et le
   Serveur : une classe générale qui relaye des Message à une classe
   spécialisée pour le débogage ou à une classe spécialisée pour le
   jeu, qui utilise une spécialisation de Partie.
 */
class Client: public QObject
{
  Q_OBJECT;
public:

  /**
     @brief Constructeur par défaut.
     
     N'ouvre aucune connexion pour l'instant.
   */
  Client(QObject * parent = 0);
public slots:

  /**
     @brief Tente de se reconnecter.
     
     Utilise les informations de la précédente connexion.
     
     @note La connexion échouera si on n'a pas établi une première
     connexion avec Client::connecter(QHostAddress, unsigned int).
   */
  void reconnecter();

  /**
     @brief Tente d'établir une connexion.

     Tente d'établir une connexion à une certaine adresse sur un
     certain port. 

     @param hote : l'adresse IP (selon Qt) de l'hôte. La façon la plus
     simple de construire une QHostAddress valide est : 
     QHostAddress("123.45.67.89"); si votre adresse IP est
     123.45.67.89. Dans tous les cas, l'adresse de votre machine
     depuis cette même machine est 127.0.0.1, ou "localhost".

     @param port : le port de listage. Celui retourné par la méthode
     Serveur::ouvrir_global() ou Serveur::ouvrir_local().
   */
  void connecter(QHostAddress hote, unsigned int port);

  /**
     @brief Quitte la connexion.

     En fin d'exécution, ce n'est pas nécessaire.

     @warning En cours d'exécution, il faut vérifier que le signal
     Client::deconnecte() ne soit pas connecté au slot
     Client::reconnecter(), car sinon la connexion est immédiatement
     rétablie.
   */
  void deconnecter();

  /**
     @brief Envoie un message au serveur.
     
     @param m : le message à envoyer.
     
     Ce slot est à préférer à Client::envoyer(QByteArray).
   */
  void envoyer(Protocole::Message m);

  /**
     @brief Envoie un paquet au serveur.

     @note Sauf en cas de débogage, il est préférable d'utiliser la
     méthode Client::envoyer(Message).
     
     @param p : le paquet brut à envoyer.
   */
  void envoyer(QByteArray p);
  
signals:

  /**
     @brief Émis lorsque le client est connecté.
     
     Détermine également le moment où le client à finalement réussi à
     se connecter au serveur.
   */
  void connecte();

  /**
     @brief Émis lorsque le client est déconnecté.

     Également émis lorsque le client est déconnecté par
     Client::deconnecter(). 
   */
  void deconnecte();

  /**
     @brief Émis lorsqu'un message est reçu du serveur.

     Il n'y a pas d'équivalent « Client::recu_brut(QByteArray) ». Si
     cela manque vraiment, je le rajouterai.

     @param m : le Message reçu du serveur.
   */
  void recu(Protocole::Message m);
		      
private slots:

  /**
     @brief Vérifie si de nouvelles données sont disponibles.

     Ce slot est déclenché automatiquement.
   */
  void recevoir();
  
private:
  
  /**
     @brief Objet Qt pour représenter une socket.
  */
  QTcpSocket sock;

  /**
     @brief Utilisé pour la reconnexion.
   */
  QHostAddress hote;

  /**
     @brief Utilisé pour la reconnexion.
   */
  unsigned int port;
};

#endif
