#define DEBUG
//Commenter si on veut utiliser le ClientJeu.

#include <QApplication>
#include <iostream>
#include <QtNetwork>

#ifdef DEBUG
#include "client_debogage.hpp"
#define CLIENT ClientDebogage
#else
#include "client_jeu.hpp"
#define CLIENT ClientJeu
#endif

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  std::cout<<"Entrez l'adresse du serveur : "<<std::endl;
  std::string addr;
  std::cin>>addr;
  std::cout<<"Entrez le port du serveur : ";
  int port;
  std::cin>>port;
  CLIENT c;
  c.connecter(QHostAddress(QString(addr.c_str())), port);
  return app.exec();
}
