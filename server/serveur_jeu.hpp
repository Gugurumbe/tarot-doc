#ifndef SERVEUR_JEU_DEFINI
#define SERVEUR_JEU_DEFINI

#include "serveur.hpp"
#include "table.hpp"
#include <vector>

//Une classe qui pourra réagir aux messages du client selon les règles du tarot.
class ServeurJeu : public Serveur
{
  Q_OBJECT;
public:
  ServeurJeu(QObject * parent = 0);
public slots :
  void reagir_connexion(unsigned int);
  //La table est pleine : on ne cherche plus à la remplir.
  void detacher_table(Table *);
  //La table n'est plus pleine : il faut trouver un candidat.
  void rattacher_table(Table *);
private:
  std::vector<Table *> incompletes;
};

#endif
