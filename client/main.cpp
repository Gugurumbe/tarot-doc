#include <QApplication>
#include <iostream>
#include <QtNetwork>
#include "client_jeu.hpp"

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  std::cout<<"Entrez le port du serveur : ";
  int port;
  std::cin>>port;
  ClientJeu c;
  c.connecter(QHostAddress("127.0.0.1"), port);
  return app.exec();
}
