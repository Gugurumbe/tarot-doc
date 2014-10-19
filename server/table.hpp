#ifndef TABLE_DEFINIE
#define TABLE_DEFINIE

#include <QObject>

#include "protocole.hpp"

#include <vector>

//La classe Table est un espace où 5 joueurs sont face à un jeu.

class Table : public QObject
{
  Q_OBJECT;
  //C'est un QObject
public:
  Table(QObject * parent = 0);
signals:
  void doit_emettre(unsigned int, Message);
  void doit_deconnecter(unsigned int);
  // Dit au ServeurJeu de transmettre les messages.
  void complet(Table *);
  //Dans la première version, on n'émettra pas le signal incomplet.
  //On virera tout le monde.
  void incomplet(Table *);			 
public slots:
  void ajouter(unsigned int);
  void comprendre(unsigned int, Message);
  void enlever(unsigned int);
private:
  std::vector<int> joueurs ; 
  std::vector<int> ordre;
};

#endif
