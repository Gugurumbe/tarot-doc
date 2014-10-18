#include "client.hpp"
#include <QtNetwork>
#include <iostream>

Client::Client(QObject * parent): QObject(parent)
{
  QObject::connect(&sock, SIGNAL(connected()), 
		   this, SIGNAL(connecte()));
  QObject::connect(&sock, SIGNAL(disconnected()),
		   this, SIGNAL(deconnecte()));
  QObject::connect(&sock, SIGNAL(readyRead()),
		   this, SLOT(recevoir()));
}

void Client::connecter(QHostAddress addr, unsigned int port)
{
  sock.connectToHost(addr, port);
  hote = addr;
  Client::port = port;
}

void Client::reconnecter()
{
  sock.connectToHost(hote, port);
}

void Client::deconnecter()
{
  sock.disconnectFromHost();
}

void Client::envoyer(Message m)
{
  QByteArray paquet;
  QDataStream out(&paquet, QIODevice::WriteOnly);
  ::ecrire(m, out);
  sock.write(paquet);
  sock.flush();
}

void Client::envoyer(QByteArray p)
{
  sock.write(p);
  sock.flush();
}

void Client::recevoir()
{
  QDataStream in(&sock);
  Message m;
  ::lire(in, m); 
  emit recu(m);
}
