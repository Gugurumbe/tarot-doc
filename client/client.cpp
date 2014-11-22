#include "client.hpp"
#include <iostream>

#define NOM_CLASSE "Client"

#include "deboguer.hpp"
//À des fins de débogage.

Client::Client(QObject * parent): QObject(parent)
{
  ENTER("Client(QObject * parent)");
  ADD_ARG("parent", parent);
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
  ENTER("connecter(QHostAddress addr, unsigned int port)");
  ADD_ARG("addr.toString().toStdString()", 
	  addr.toString().toStdString());
  ADD_ARG("port", port);
  sock.connectToHost(addr, port);
  //Connexion
  hote = addr;
  Client::port = port;
  //Préparation de la reconnexion
}

void Client::reconnecter()
{
  ENTER("reconnecter()");
  sock.connectToHost(hote, port);
}

void Client::deconnecter()
{
  ENTER("deconnecter()");
  sock.disconnectFromHost();
}

void Client::envoyer(Protocole::Message m)
{
  ENTER("envoyer(Message m)");
  ADD_ARG("m", m);
  QByteArray paquet;
  QDataStream out(&paquet, QIODevice::WriteOnly);
  Protocole::ecrire(m, out);
  sock.write(paquet.prepend((quint8)(1 + paquet.size())));
  sock.flush();
  //On envoie.
  emit emis(m);
}

void Client::envoyer(QByteArray p)
{
  ENTER("envoyer(QByteArray p)");
  ADD_ARG("p.toHex().data", p.toHex().data());
  sock.write(p);
  //On envoie le paquet tel quel.
  sock.flush();
}

void Client::recevoir()
{
  ENTER("recevoir()");
  QByteArray paquet = sock.readAll();
  QDataStream in(paquet);
  quint8 taille = 0;
  in>>taille;
  if(paquet.size() >= taille)
    {
      Protocole::Message m; 
      if(Protocole::lire(in, m))
	{
	  emit recu(m);
	  QByteArray non_lu;
	  while(!in.atEnd())
	    {
	      quint8 c ;
	      in>>c ;
	      non_lu.append(c);
	    }
	  unread(non_lu);
	  recevoir();
	}
    }
}

void Client::unread(QByteArray const & paquet)
{
  for(int i = paquet.size() - 1 ; i >= 0 ; i--)
    {
      sock.ungetChar(paquet[i]);
    }
}
