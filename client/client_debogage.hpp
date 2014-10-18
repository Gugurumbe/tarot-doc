#ifndef CLIENT_DEBOGAGE_DEFINI
#define CLIENT_DEBOGAGE_DEFINI

#include "client.hpp"

class ClientDebogage : public Client
{
  Q_OBJECT;
public:
  ClientDebogage(QObject * parent = 0);
public slots:
  void traiter_connexion();
  void traiter_deconnexion();
  void traiter_message(Message);
  void demander_ordres();
};

#endif
