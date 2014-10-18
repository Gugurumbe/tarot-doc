#include "table.hpp"

#include <cstdlib>

#include <iostream>

#define DEBUG

Table::Table(QObject * parent) : QObject(parent)
{
  //Création des ordres :
  for(int i = 0 ; i < 5 ; i++)
    {
      joueurs.push_back(-1); // -1 : pas de joueur
      ordre.push_back(i);
    }
  //Mélange de ordre :
  int r = 0 ;
  int tmp;
  for(unsigned int i = 1 ; i < ordre.size() ; i++)
    {
      r = rand() % i ;
      //échange des cases i et r
      tmp = ordre[r];
      ordre[r] = ordre[i];
      ordre[i] = tmp;
    }
}

void Table::ajouter(unsigned int sock)
{
  unsigned int i = 0;
  while(i < joueurs.size() && joueurs[i] >= 0) i++;
  if(i < joueurs.size())
    {
      joueurs[i] = sock;
      Message m;
      m.type = NUMERO;
      m.m.numero.n = ordre[i];
      emit doit_emettre(sock, m);
      //Si on est complet, on lance la partie
      i = 0 ;
      while(i < joueurs.size() && joueurs[i] >= 0) i++;
      if(i >= joueurs.size())
	{
	  std::cout<<"La partie commence..."<<std::endl;
	  emit complet(this);
	}
    }
  else
    {
      //En fait, la table était déjà pleine !
      std::cerr << "Erreur : la table est pleine."<<std::endl;
      emit complet(this);
      emit doit_deconnecter(sock);
      //Sinon, la socket sera perdue
    }
}

void Table::comprendre(unsigned int sock, Message m)
{
  //Attention : je ne suis pas sûr que sock fasse partie de la table !
  //Ben, je suis bien embêté tant que je n'ai pas les règles...
#ifdef DEBUG
  std::cout<<"Message de "<<sock<<std::endl;
#endif
}

void Table::enlever(unsigned int sock)
{
  //Attention : sock ne fait peut-être pas partie de la table !
  unsigned int i = 0 ;
  while(i < joueurs.size() && 
	(joueurs[i] < 0 || (unsigned int)joueurs[i] != sock)) i++;
  if(i < joueurs.size())
    {
      joueurs[i] = -1 ;
      emit incomplet(this);
#ifdef DEBUG
      std::cout<<"Déconnexion de "<<sock<<" (joueur "<<ordre[i]<<")"<<std::endl;
#endif
    }
}
