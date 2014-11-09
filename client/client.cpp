#include "client.hpp"
#include <iostream>
//À des fins de débogage.

Client::Client(QObject * parent): QObject(parent)
{
  QObject::connect(&sock, SIGNAL(connected()), 
		   this, SIGNAL(connecte()));
  QObject::connect(&sock, SIGNAL(disconnected()),
		   this, SIGNAL(deconnecte()));
  QObject::connect(&sock, SIGNAL(readyRead()),
		   this, SLOT(recevoir()));
  //Connexion de la socket pour transmettre les signaux connected() et
  //disconnected(), et pour vérifier la présence d'un message.
}

void Client::connecter(QHostAddress addr, unsigned int port)
{
  sock.connectToHost(addr, port);
  //Connexion
  hote = addr;
  Client::port = port;
  //Préparation de la reconnexion
}

void Client::reconnecter()
{
  sock.connectToHost(hote, port);
}

void Client::deconnecter()
{
  sock.disconnectFromHost();
}

void Client::envoyer(Protocole::Message m)
{
  QDataStream out(&sock);
  //le QDataStream écrit directement sur la socket.
  Protocole::ecrire(m, out);
  //On écrit le message dans le QDataStream, grâce au protocole.
  sock.flush();
  //On envoie.
}

void Client::envoyer(QByteArray p)
{
  sock.write(p);
  //On envoie le paquet tel quel.
  sock.flush();
}

void Client::recevoir()
{
  QDataStream in(&sock);
  //Le QDataStream lit directement depuis la socket.
  Protocole::Message m; //À remplir.
  while(Protocole::lire(in, m))
    emit recu(m);
}
