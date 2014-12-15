#include "client.hpp"
#include <iostream>

#define NOM_CLASSE "Client"

#include "deboguer.hpp"
//À des fins de débogage.

//#include <QTimer>

Client::Client(QObject * parent): QObject(parent),
				  taille_paquet(-1)
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
  if(taille_paquet>=0)
    {
      DEBUG<<"J'attends un paquet de taille "
	   <<taille_paquet<<std::endl;
      if(sock.bytesAvailable() >= taille_paquet)
	{
	  DEBUG<<"Je peux lire !"<<std::endl;
	  Protocole::Message m;
	  QDataStream in(&sock);
	  if(Protocole::lire(in, m))
	    {
	      DEBUG<<"J'ai lu : "<<m<<std::endl;
	      taille_paquet = -1;
	      emit recu(m);
	      recevoir();
	    }
	  else
	    {
	      ERROR<<"Erreur : la taille n'est pas convenable."
		   <<std::endl;
	    }
	}
      else
	{
	  DEBUG<<"C'est pas pour tout de suite."
	       <<std::endl;
	}
    }
  else if(sock.bytesAvailable() >= 1)
    {
      DEBUG<<"Je peux lire la taille..."<<std::endl;
      QDataStream in(&sock);
      quint8 tmp;
      in>>tmp;
      taille_paquet = static_cast<int>(tmp) - 1;
      DEBUG<<"Taille : "<<taille_paquet<<std::endl;
      recevoir();
    }
  
  //QTimer::singleShot(1000, this, SLOT(recevoir()));
}

void Client::unread(QByteArray const & paquet)
{
  ENTER("unread(QByteArray const & paquet)");
  ADD_ARG("paquet.toHex()", paquet.toHex().data());
  for(int i = paquet.size() - 1 ; i >= 0 ; i--)
    {
      DEBUG<<"unget de "<<paquet[i]<<"."<<std::endl;
      sock.ungetChar(paquet[i]);
    }
}
