//#define TEST

#include <QApplication>
#include <iostream>
#include <QtNetwork>

#include "config.hpp"

#include "client_jeu.hpp"

#include "client_graphique.hpp"

#include "coquille.hpp"

#ifndef TEST

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  INTERFACE client;
  client.show();
  return app.exec();
}

#else

#include "testeur_client.hpp"

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  PartieClient partie;
  Testeur testeur(&partie);
  testeur.run();
  return 0;
}

#endif
