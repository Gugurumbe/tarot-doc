#include "serveur.hpp"
#include "config.hpp"
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
  while(ppl >= clients.size())
    {
      clients.push_back(0);
      en_attente.push_back(std::queue<QByteArray>());
      taille_restante.push_back(0);
    }
  //Rajoute un endroit vide à la fin si tout est plein.
  i = ppl;
  clients[i] = sock;
  while(ppl < clients.size() && clients[ppl]) ppl++;
  while(ppl >= clients.size())
    {
      clients.push_back(0);
      en_attente.push_back(std::queue<QByteArray>());
      taille_restante.push_back(0);
    }
  return i; //retourne la position occupée.
}

void Serveur::remove(unsigned int i)
{
  clients[i]->disconnect(this); // Déconnecte les signaux émis du serveur
  clients[i] = 0;               // Vide la place
  if(i < ppl) ppl = i ;         // avance la première place libre
  // On ne détruit pas le client.
  //On vide la file d'attente
  en_attente[i] = std::queue<QByteArray>();
  taille_restante[i] = 0;
}

unsigned int Serveur::ouvrir_local()
{
  listener.listen(QHostAddress("127.0.0.1"), PORT);
  //On liste sur l'adresse loopback, pour n'accepter que les sockets de la
  //même machine. On peut spécifier le port explicitement, mais rien ne dit
  //qu'il soit déjà pris.
  return listener.serverPort();
}

unsigned int Serveur::ouvrir_global()
{
  listener.listen(QHostAddress::Any, PORT);
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
      QObject::connect(sock, SIGNAL(bytesWritten(qint64)),
		       this, SLOT(envoyer_suivant(qint64)));
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
      Protocole::Message m;
      Protocole::lire(in, m);
      if(m.compris)
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
#if DEBUG_WRITESTACK == 1
  std::cout<<"Envoi à "<<i<<" un paquet de taille "<<
    paquet.size()<<std::endl;
#endif
  if(i < clients.size()) 
    {
#if DEBUG_WRITESTACK == 1
      std::cout<<(en_attente[i].empty()?"La file d'attente est vide. "
		  :"Il reste des paquets à envoyer. ")
	       << "Il reste "<<taille_restante[i]
	       << " octets du paquet précédent à envoyer."
	       << std::endl;
#endif
      if(en_attente[i].empty() && taille_restante[i] == 0)
	{
	  taille_restante[i] = paquet.size();
	  clients[i]->write(paquet);  
	  //clients[i]->flush();
#if DEBUG_WRITESTACK == 1
	  std::cout<< "Envoi direct du paquet. "
		   <<(en_attente[i].empty()?"La file d'attente est vide. "
		      :"Il reste des paquets à envoyer. ")
		   << "Il reste "<<taille_restante[i]
		   << " octets du paquet précédent à envoyer."
		   << std::endl;
#endif
	}
      else
	{
	  en_attente[i].push(paquet);
#if DEBUG_WRITESTACK == 1
	  std::cout<<"Envoi différé du paquet."<<std::endl;
#endif
	}
    }
}

void Serveur::envoyer(unsigned int i, Protocole::Message m)
{
  QByteArray paquet;
  QDataStream out(&paquet, QIODevice::WriteOnly);
  ecrire(m, out);
  envoyer(i, paquet);
}

void Serveur::envoyer_suivant(qint64 t)
{
  unsigned int i = find(sender());
  if(i < clients.size())
    {
#if DEBUG_WRITESTACK == 1
      std::cout<<"Envoi d'un morceau du paquet de "<<i<<" de taille "<<t<<std::endl;
      std::cout<<"Il restait "<<taille_restante[i]<<" octets à écrire."<<std::endl;
#endif
      taille_restante[i] -= t ;
      if(taille_restante[i] <= 0)
	{
	  if(taille_restante[i] < 0)
	    std::cerr<<"Taille négative."<<std::endl;
	  if(en_attente[i].empty())
	    {
#if DEBUG_WRITESTACK == 1
	      std::cout<<"On n'a plus rien à écrire."<<std::endl;
#endif
	    }
	  else
	    {
	      QByteArray to_send = en_attente[i].front();
	      en_attente[i].pop();
	      taille_restante[i] = to_send.size();
	      clients[i]->write(to_send);
	      //clients[i]->flush();
#if DEBUG_WRITESTACK == 1
	      std::cout<<"On envoie le paquet suivant de taille "<<
		to_send.size()<<std::endl;
#endif
	    }
	}
    }
}
