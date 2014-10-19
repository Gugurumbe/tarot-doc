#include "serveur.hpp"
#include <iostream>

Serveur::Serveur(QObject * parent) : QObject(parent), ppl(0)
{
  QObject::connect(&listener, SIGNAL(newConnection()), 
		   this, SLOT(accepter()));
  //listener est la socket permettant d'accepter des connexions.
}

unsigned int Serveur::push(QTcpSocket * sock)
{
  unsigned int i = 0; //Sert à retenir la position occupée
  while(ppl < clients.size() && clients[ppl]) ppl++; //Cherche un endroit vide
  while(ppl >= clients.size()) clients.push_back(0); 
  //Rajoute un endroit vide à la fin si tout est plein.
  i = ppl;
  clients[i] = sock;
  while(ppl < clients.size() && clients[ppl]) ppl++;
  while(ppl >= clients.size()) clients.push_back(0);
  return i; //retourne la position occupée.
}

void Serveur::remove(unsigned int i)
{
  clients[i]->disconnect(this); // Déconnecte les signaux émis du serveur
  clients[i] = 0;               // Vide la place
  if(i < ppl) ppl = i ;         // avance la première place libre
  // On ne détruit pas le client.
}

unsigned int Serveur::ouvrir_local()
{
  listener.listen(QHostAddress("127.0.0.1"));
  //On liste sur l'adresse loopback, pour n'accepter que les sockets de la
  //même machine. On peut spécifier le port explicitement, mais rien ne dit
  //qu'il soit déjà pris.
  return listener.serverPort();
}

unsigned int Serveur::ouvrir_global()
{
  listener.listen(QHostAddress::Any);
  // On accepte les connexions venant de n'importe où.
  return listener.serverPort();
}

unsigned int Serveur::find(QObject * sock)
{
  //Retourne la position occupée par la socket sock.
  unsigned int i = 0 ;
  while(i < clients.size() && clients[i] != sock) i++;
  return i;
}

void Serveur::accepter()
{
  //Récupération d'une nouvelle socket.
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
      //Pas besoin de garder une socket si elle est déconnectée.
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
  //Il y a deux solutions : regarder les messages de tout le monde
  // ou regarder les messages de l'émetteur. C'est la même complexité :
  // find() peut potentiellement passer toutes les socket en revue avant
  // d'avoir trouvé l'appelant. Cependant, je préfère ne vérifier les 
  // nouveaux messages que quand le signal readyRead() a été émis.
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
  //Le signal disconnected() sera émis, donc on mettra proprement le client
  //à la poubelle au prochain tour d'événements.
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
