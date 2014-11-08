#include "./config.hpp"
#include <iostream>
#include <QApplication>

#include "serveur_debogage.hpp"
#include "serveur_jeu.hpp"

#include <cstdlib>
#include <ctime>

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  srand(time(NULL));
  SERVEUR s;
  std::cout<<"Ouverture du port "<<s.ouvrir_global()<<std::endl;
  return app.exec();
}
