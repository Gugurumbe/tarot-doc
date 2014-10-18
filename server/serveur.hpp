#ifndef SERVEUR_DEFINI
#define SERVEUR_DEFINI

#include "protocole.hpp"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <vector>

class Serveur : public QObject
{
  Q_OBJECT;
 public:
  Serveur(QObject * parent = 0);
  virtual ~Serveur();

public slots:
  unsigned int ouvrir_local();
  unsigned int ouvrir_global();
  void accepter();
  void enlever(QObject * sock);
  void enlever();
  void lire();
  void deconnecter(unsigned int);
  void envoyer(unsigned int, QByteArray);
  void envoyer(unsigned int, Message);

 signals:
  void connexion(unsigned int);
  void message_brut(unsigned int, QByteArray);
  void deconnexion(unsigned int);
  void message(unsigned int, Message);

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
