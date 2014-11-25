#include <QApplication>
#include <iostream>
#include <QtNetwork>

#include "config.hpp"

#include "client_jeu.hpp"

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  std::string addr;
  int port;
#if AUTO == YES
  addr = "127.0.0.1";
  port = 45678;
#else
  std::cout<<"Entrez l'adresse du serveur : "<<std::endl;
  std::cin>>addr;
  std::cout<<"Entrez le port du serveur : ";
  std::cin>>port;
#endif
  ClientJeu c;
  c.connecter(QHostAddress(QString(addr.c_str())), port);
  return app.exec();
}
