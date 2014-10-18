#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QObject>
#include "serveur_jeu.hpp"

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  ServeurJeu s;
  std::cout<<"Ouverture du port "<<s.ouvrir_global()<<std::endl;
  return app.exec();
}
