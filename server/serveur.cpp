#include "serveur.hpp"
#include <iostream>

Serveur::Serveur(QObject * parent) : QObject(parent), ppl(0)
{
  QObject::connect(&listener, SIGNAL(newConnection()), 
		   this, SLOT(accepter()));
}

Serveur::~Serveur()
{
  //Fermer les socket
}

unsigned int Serveur::push(QTcpSocket * sock)
{
  unsigned int i = 0; //Sert à retenir la position occupée
  while(ppl < clients.size() && clients[ppl]) ppl++; //Cherche un endroit vide
  while(ppl >= clients.size()) clients.push_back(0); 
  //Rajoute un endroit vide à la fin
  i = ppl;
  clients[i] = sock;
  while(ppl < clients.size() && clients[ppl]) ppl++;
  while(ppl >= clients.size()) clients.push_back(0);
  return i;
}

void Serveur::remove(unsigned int i)
{
  clients[i]->disconnect(this); // Déconnecte les signaux émis du serveur
  clients[i] = 0;               // Vide la place
  if(i < ppl) ppl = i ;
}

unsigned int Serveur::ouvrir_local()
{
  listener.listen(QHostAddress("127.0.0.1"));
  return listener.serverPort();
}

unsigned int Serveur::ouvrir_global()
{
  listener.listen(QHostAddress::Any);
  return listener.serverPort();
}

unsigned int Serveur::find(QObject * sock)
{
  unsigned int i = 0 ;
  while(i < clients.size() && clients[i] != sock) i++;
  return i;
}

void Serveur::accepter()
{
  QTcpSocket * sock = 0;
  while(listener.hasPendingConnections())
    {
      sock = listener.nextPendingConnection();
      QObject::connect(sock, SIGNAL(destroyed(QObject *)),
		       this, SLOT(enlever(QObject *)));
      QObject::connect(sock, SIGNAL(readyRead()),
		       this, SLOT(lire()));
      QObject::connect(sock, SIGNAL(disconnected()),
		       this, SLOT(enlever()));
      QObject::connect(sock, SIGNAL(disconnected()),
		       sock, SLOT(deleteLater()));
      emit connexion(push(sock));
    }
}

void Serveur::enlever(QObject * sock)
{
  unsigned int i = 0 ;
  while((i=find(sock)) < clients.size()) 
    {
      emit deconnexion(i);
      remove(i);
    }
}

void Serveur::enlever()
{
  enlever(QObject::sender());
}

void Serveur::lire()
{
  unsigned int sock = find(QObject::sender());
  if(sock < clients.size())
    {
      QByteArray paquet = clients[sock]->readAll();
      emit message_brut(sock, paquet);
      QDataStream in(paquet);
      Message m;
      ::lire(in, m);
      emit message(sock, m);
    }
}

void Serveur::deconnecter(unsigned int i)
{
  if(i < clients.size()) clients[i]->close();
}

void Serveur::envoyer(unsigned int i, QByteArray paquet)
{
  if(i < clients.size()) 
    {
      clients[i]->write(paquet);  
      clients[i]->flush();
    }
}

void Serveur::envoyer(unsigned int i, Message m)
{
  QByteArray paquet;
  QDataStream out(&paquet, QIODevice::WriteOnly);
  ecrire(m, out);
  envoyer(i, paquet);
}
