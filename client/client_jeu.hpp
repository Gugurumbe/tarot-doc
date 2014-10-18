#ifndef CLIENT_JEU_DEFINI
#define CLIENT_JEU_DEFINI

#include "client.hpp"

class ClientJeu : public Client
{
  Q_OBJECT;
public:
  ClientJeu(QObject * parent = 0);
public slots:
  void traiter_connexion();
  void traiter_deconnexion();
  void traiter_message(Message);
private:
  int numero;
};

#endif
