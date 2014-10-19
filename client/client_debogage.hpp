#ifndef CLIENT_DEBOGAGE_DEFINI
#define CLIENT_DEBOGAGE_DEFINI

#include "client.hpp"

//Ce client permet de déboguer le serveur, et de tester sa réaction 
//face à des terroristes qui voudraient nous empêcher de faire progresser
//l'humanité.

class ClientDebogage : public Client
{
  Q_OBJECT;
  //Est un QObject
public:
  ClientDebogage(QObject * parent = 0);
public slots:
  void traiter_connexion();
  void traiter_deconnexion();
  void traiter_message(Message);
  //Ces slots sont connectés aux signaux correspondants de Client. Cela permet
  //de réagir.
  void demander_ordres();
  //À chaque fois qu'on reçoit quelque chose, on demande à l'utilisateur 
  //d'envoyer un paquet.
};

#endif
