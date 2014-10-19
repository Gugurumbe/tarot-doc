#define DEBUG
//Commenter pour passer en mode jeu

#include <iostream>
#include <QApplication>

#ifdef DEBUG
#include "serveur_debogage.hpp"
#define SERVEUR ServeurDebogage
#else
#include "serveur_jeu.hpp"
#define SERVEUR ServeurJeu
#endif

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  SERVEUR s;
  std::cout<<"Ouverture du port "<<s.ouvrir_global()<<std::endl;
  return app.exec();
}
