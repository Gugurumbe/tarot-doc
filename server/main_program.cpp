#include "./config.hpp"
#include "debogueur.hpp"
#include <iostream>
#include <QCoreApplication>

#include "serveur_debogage.hpp"
#include "serveur_jeu.hpp"

#include <cstdlib>
#include <ctime>

#ifndef TESTER_POINTS

int main(int argc, char * argv[])
{
  ENTER_FUNCTION("main(int argc, char * argv[])");
  Debogueur::arg("argc", argc);
  for(int i = 0 ; i < argc ; i++)
    {
      std::stringstream str;
      str<<"argv["<<i<<"]";
      Debogueur::arg(str.str(), 
		     "\"" + std::string(argv[i]) + "\"");
    }
  QCoreApplication app(argc, argv);
  srand(time(NULL));
  SERVEUR s;
  Debogueur::debug()<<"Ouverture du port "<<s.ouvrir_global()<<std::endl;
  long int ret = app.exec();
  Debogueur::ret(ret);
  return ret;
}

#else

#include "score.hpp"

int main(int argc, char * argv[])
{
  return 0;
}

#endif
