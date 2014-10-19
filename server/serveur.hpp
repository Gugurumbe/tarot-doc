#ifndef SERVEUR_DEFINI
#define SERVEUR_DEFINI

#include "protocole.hpp"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <vector>

//Définit une classe de Serveur qui ne sait pas réagir.

class Serveur : public QObject
{
  Q_OBJECT;
  //C'est un abject QObject
 public:
  Serveur(QObject * parent = 0);
  unsigned int ouvrir_local();
  // Ouvre une partie "solo"
  unsigned int ouvrir_global();
  //Ouvre une partie sur internet.

public slots:
  void accepter();
  // Regarde si par hasard il n'y aurait pas des connexions à accepter.
  void enlever(QObject * sock); // Enlève ce client de la liste des clients.
  void enlever(); //Enlève l'objet appelant.
  void lire(); //Regarde s'il n'y aurait pas des nouveaux messages 
  void deconnecter(unsigned int); //Vire sans scrupule un client.
  void envoyer(unsigned int, QByteArray); //Envoie au client un paquet brut.
  void envoyer(unsigned int, Message); //Envoie au client un message.

 signals:
  void connexion(unsigned int); //émis lorsqu'un client s'est connecté.
  void message_brut(unsigned int, QByteArray); //.......envoie un paquet
  //(il n'est pas conseillé d'en tenir compte, un signal Message() est 
  //simultanément émis)
  void deconnexion(unsigned int);
  //émis lorsqu'un client se déconnecte.
  void message(unsigned int, Message);
  //émis lorsqu'un client envoie un message.

 private:
  unsigned int push(QTcpSocket * sock); 
  // Rajoute la socket à la liste des clients.
                               // Ne connecte aucun signal à aucun slot !
  void remove(unsigned int i);          
  // Enlève le client. Déconnecte les signaux.
  unsigned int find(QObject * sock);
  //Retrouve la socket à partir de son adresse
  QTcpServer listener;         // Sert à accepter les connexions entrantes.
  std::vector<QTcpSocket *> clients;// Tableau des clients
  unsigned int ppl; //Première Place Libre : 
  //dans le tableau, premier pointeur nul.
};

#endif
