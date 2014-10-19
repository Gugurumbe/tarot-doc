#ifndef CLIENT_DEFINI
#define CLIENT_DEFINI

//Classe de Client. À utiliser dans l'IA et dans le client graphique.

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include "protocole.hpp"
//Penser à bien ajouter le dossier ../shared dans les recherches de répertoire
//d'inclusion.

class Client: public QObject
{
  Q_OBJECT;
  //La classe Client hérite de QObject pour pouvoir lancer des signaux.
public:
  Client(QObject * parent = 0);
public slots:
  void reconnecter();
  //Tente de se connecter à l'adresse et sur le port donnés la dernière fois
  //que connecter() a été appelée. Ne pas utiliser avant d'avoir connecté().
  void connecter(QHostAddress, unsigned int);
  //Initie une tentative de connexion. Lorsqu'elle est réussie,
  //le client émet connecte().
  void deconnecter();
  //Facultatif.
  void envoyer(Message);
  //Envoie le message au serveur.
  void envoyer(QByteArray);
  //Envoie un paquet perso au serveur. Déconseillé, si ce n'est pour tester
  //le serveur.
signals:
  void connecte();
  //émis lorsque l'on est connecté.
  void deconnecte();
  //émis lorsque l'on est déconnecté.
  void recu(Message);
  // émis lorsqu'on a reçu un message.
private slots:
  void recevoir();
  //Ce slot est connecté au signal QAbstractSocket::readyRead().
  //Là, on regarde si on peut lire un message, et si c'est le cas
  //on émet recu().
private:
  QTcpSocket sock;
  //Classe de socket de Qt. Protocole TCP, c'est-à-dire socket connectée.
  //C'est mieux.
  QHostAddress hote;
  unsigned int port;
  //On se souvient de l'adresse de l'hôte pour pouvoir se reconnecter().
};

#endif
