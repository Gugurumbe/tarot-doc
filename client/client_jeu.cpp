#include "client_jeu.hpp"
#include <iostream>

ClientJeu::ClientJeu(QObject * parent) : Client(parent)
{
  QObject::connect(this, SIGNAL(connecte()),
		   this, SLOT(traiter_connexion()));
  QObject::connect(this, SIGNAL(deconnecte()),
		   this, SLOT(traiter_deconnexion()));
  QObject::connect(this, SIGNAL(recu(Message)),
		   this, SLOT(traiter_message(Message)));
}

void ClientJeu::traiter_connexion()
{
  std::cout<<"Prêt à jouer."<<std::endl;
}

void ClientJeu::traiter_deconnexion()
{
  std::cout<<"Reconnexion..."<<std::endl;
  reconnecter();
  //C'est critiquable : si le serveur nous déconnecte délibérément,
  //c'est la boucle infinie. Mais bon, le serveur doit savoir résister
  //à ce genre d'attaque.
}

void ClientJeu::traiter_message(Message m)
{
  switch(m.type)
    {
    case NUMERO:
      std::cout<<"Vous avez le numéro "<<m.m.numero.n<<std::endl;
      break;
    default :
      std::cout<<"Message de type "<<m.type<<"."<<std::endl;
    }
}
