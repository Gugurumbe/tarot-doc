#ifndef CLIENT_JEU_DEFINI
#define CLIENT_JEU_DEFINI

#include "client.hpp"

//Classe de client de jeu. Il joue avec le serveur.

class ClientJeu : public Client
{
  Q_OBJECT;
public:
  ClientJeu(QObject * parent = 0);
  int numero() const;
public slots:
  void traiter_connexion();
  void traiter_deconnexion();
  void traiter_message(Message);
private:
  int m_numero; //Le client est capable de retenir son numéro.
  //Tant qu'on l'a pas reçu, il vaut -1.
};

#endif
