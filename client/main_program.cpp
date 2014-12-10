#define TEST "testeur_client.hpp"

#ifndef TEST

#include <QApplication>
#include <iostream>
#include <QtNetwork>

#include "config.hpp"

#include "client_jeu.hpp"

#include "client_graphique.hpp"

#include "coquille.hpp"

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  Coquille client;
  client.show();
  return app.exec();
}

#else

#include TEST

#endif
