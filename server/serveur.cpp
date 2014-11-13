#include "serveur.hpp"
#include "config.hpp"
#include "debogueur.hpp"
#include <stack>

Serveur::Serveur(QObject * parent) : QObject(parent), ppl(0)
{
  ENTER("Serveur", "Serveur(QObject * parent)");
  ADD_ARG("parent", (void *)parent);
  QObject::connect(&listener, SIGNAL(newConnection()), 
		   this, SLOT(accepter()));
  //listener est la socket permettant d'accepter des connexions.
}

unsigned int Serveur::push(QTcpSocket * sock)
{
  ENTER("Serveur","push(QTcpSocket * sock");
  ADD_ARG("sock", (void *)sock);
  unsigned int i = 0; //Sert à retenir la position occupée
  while(ppl < clients.size() && clients[ppl]) ppl++; //Cherche un endroit vide
  while(ppl >= clients.size())
    {
      clients.push_back(0);
      //en_attente.push_back(std::queue<QByteArray>());
      //taille_restante.push_back(0);
    }
  //Rajoute un endroit vide à la fin si tout est plein.
  i = ppl;
  clients[i] = sock;
  while(ppl < clients.size() && clients[ppl]) ppl++;
  while(ppl >= clients.size())
    {
      clients.push_back(0);
      //en_attente.push_back(std::queue<QByteArray>());
      //taille_restante.push_back(0);
    }
  EXIT(i);
  return i; //retourne la position occupée.
}

void Serveur::remove(unsigned int i)
{
  ENTER("Serveur", "remove(unsigned int i)");
  ADD_ARG("i", i);
  clients[i]->disconnect(this); // Déconnecte les signaux émis du serveur
  clients[i] = 0;               // Vide la place
  if(i < ppl) ppl = i ;         // avance la première place libre
  // On ne détruit pas le client.
  //On vide la file d'attente
  //en_attente[i] = std::queue<QByteArray>();
  //taille_restante[i] = 0;
}

unsigned int Serveur::ouvrir_local()
{
  ENTER("Serveur", "ouvrir_local()");
  listener.listen(QHostAddress("127.0.0.1"), PORT);
  //On liste sur l'adresse loopback, pour n'accepter que les sockets de la
  //même machine. On peut spécifier le port explicitement, mais rien ne dit
  //qu'il soit déjà pris.
  quint16 port = listener.serverPort();
  EXIT(port);
  return port;
}

unsigned int Serveur::ouvrir_global()
{
  ENTER("Serveur", "ouvrir_global()");
  listener.listen(QHostAddress::Any, PORT);
  // On accepte les connexions venant de n'importe où.
  quint16 port = listener.serverPort();
  EXIT(port);
  return port;
}

unsigned int Serveur::find(QObject * sock)
{
  ENTER("Serveur", "find(QObject * sock)");
  ADD_ARG("sock", (void *)sock);
  //Retourne la position occupée par la socket sock.
  unsigned int i = 0 ;
  while(i < clients.size() && clients[i] != sock) i++;
  EXIT(i);
  return i;
}

void Serveur::accepter()
{
  ENTER("Serveur", "accepter()");
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
      //      QObject::connect(sock, SIGNAL(bytesWritten(qint64)),
      //	       this, SLOT(envoyer_suivant(qint64)));
      emit connexion(push(sock));
    }
}

void Serveur::enlever(QObject * sock)
{
  ENTER("Serveur", "enlever(QObject * sock)");
  ADD_ARG("sock", (void *)sock);
  unsigned int i = 0 ;
  while((i=find(sock)) < clients.size()) 
    {
      emit deconnexion(i);
      remove(i);
    }
}

void Serveur::enlever()
{
  ENTER("Serveur", "enlever()");
  QObject * s = QObject::sender();
  DEBUG<<"L'objet appelant est "<<(void *)s<<std::endl;;
  enlever(s);
}

void Serveur::lire()
{
  ENTER("Serveur", "lire()");
  //Il y a deux solutions : regarder les messages de tout le monde
  // ou regarder les messages de l'émetteur. C'est la même complexité :
  // find() peut potentiellement passer toutes les socket en revue avant
  // d'avoir trouvé l'appelant. Cependant, je préfère ne vérifier les 
  // nouveaux messages que quand le signal readyRead() a été émis.
  unsigned int sock = find(QObject::sender());
  DEBUG<<"C'est la socket "<<sock<<"qui cause."<<std::endl;
  if(sock < clients.size())
    {
      QTcpSocket * s = clients[sock];
      QByteArray paquet = s->readAll();
      DEBUG<<std::cout<<"Lecture de tous les octets : "<<paquet.toHex().data()
	       <<" (taille "<<paquet.size()<<")."<<std::endl;
      emit message_brut(sock, paquet);
      QDataStream in(paquet);
      quint8 taille = 0;
      in>>taille;
      DEBUG<<"Taille attendue : "<<taille<<std::endl;
      if(paquet.size() >= 1 && paquet.size() >= taille)
	{
	  DEBUG<<"On peut lire un Message."<<std::endl;
	  Protocole::Message m;
	  Protocole::lire(in, m);
	  if(m.compris)
	    {
	      DEBUG<<"Le message a été compris. Transmission..."<<std::endl;
	      emit message(sock, m);
	      DEBUG<<"Transmission terminée."<<std::endl;
	    }
	  else DEBUG<<"Le message n'a pas été compris."<<std::endl;
	  //On ravale tous les octets en trop.
	  std::stack<quint8> pile;
	  quint8 octet;
	  while(!in.atEnd())
	    {
	      in>>octet;
	      pile.push(octet);
	      DEBUG<<"On ne s'est pas servi de "<<octet<<std::endl;
	    }
	  while(!pile.empty())
	    {
	      DEBUG<<"On ravale "<<pile.top()<<std::endl;
	      s->ungetChar(pile.top());
	      pile.pop();
	    }
	  DEBUG<<"Appel récursif pour bien vérifier que c'est terminé..."
		   <<std::endl;
	  lire();
	  DEBUG<<"Fin de l'appel récursif."<<std::endl;
	}
      else DEBUG<<"C'est trop tôt."<<std::endl;
    }
}

void Serveur::deconnecter(unsigned int i)
{
  ENTER("Serveur", "deconnecter(unsigned int i)");
  ADD_ARG("i", i);
  if(i < clients.size()) clients[i]->close(); 
  //Le signal disconnected() sera émis, donc on mettra proprement le client
  //à la poubelle au prochain tour d'événements.
}

void Serveur::envoyer(unsigned int i, QByteArray paquet)
{
  ENTER("Serveur", "envoyer(unsigned int i, QByteArray paquet)");
  ADD_ARG("i", i);
  ADD_ARG("paquet.toHex()", paquet.toHex().data());
  if(i < clients.size()) 
    {
      clients[i]->write(paquet);  
      clients[i]->flush();
    }
}

void Serveur::envoyer(unsigned int i, Protocole::Message m)
{
  ENTER("Serveur", "envoyer(unsigned int i, Protocole::Message m)");
  ADD_ARG("i", i);
  ADD_ARG("m.type", m.type);
  QByteArray paquet;
  QDataStream out(&paquet, QIODevice::WriteOnly);
  ecrire(m, out);
  paquet.prepend((quint8)(1 + paquet.size()));
  envoyer(i, paquet);
}
/*
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
*/
