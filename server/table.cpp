#include "table.hpp"

#include <cstdlib>

#include <iostream>

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
  QObject::connect(&partie, SIGNAL(doit_emettre(unsigned int, Protocole::Message)),
		   this, SLOT(doit_transmettre(unsigned int, Protocole::Message)));
}

void Table::ajouter(unsigned int sock)
{
  unsigned int i = 0;
  while(i < joueurs.size() && joueurs[i] >= 0) i++;
  if(i < joueurs.size())
    {
      joueurs[i] = sock;
      Protocole::Message m;
      m.type = Protocole::NUMERO;
      m.m.numero.n = ordre[i];
      emit doit_emettre(sock, m);
      //Si on est complet, on lance la partie
      i = 0 ;
      while(i < joueurs.size() && joueurs[i] >= 0) i++;
      if(i >= joueurs.size())
	{
	  std::cout<<"La partie commence..."<<std::endl;
	  partie.distribuer();
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

void Table::comprendre(unsigned int sock, Protocole::Message m)
{
  //Attention : je ne suis pas sûr que sock fasse partie de la table !
  for(unsigned int i = 0 ; i < joueurs.size() ; i++)
    {
      if(joueurs[i] == (int)sock)
	{
	  Protocole::Message reponse;
	  switch(partie.tester(sock, m))
	    {
	    case 1 :
	      reponse.type = Protocole::ERREUR_PROTOCOLE;
	      emit doit_emettre(sock, reponse);
	      break;
	    case 2 :
	      reponse.type = Protocole::REFUSE;
	      emit doit_emettre(sock, reponse);
	      break;
	    default :
	      partie.assimiler(m);
	    }
	}
    }
}

void Table::enlever(unsigned int sock)
{
  //Attention : sock ne fait peut-être pas partie de la table !
  unsigned int i = 0 ;
  while(i < joueurs.size() && 
	(joueurs[i] < 0 || (unsigned int)joueurs[i] != sock)) i++;
  if(i == joueurs.size() - 1)
    {
      joueurs[i] = -1 ;
      emit incomplet(this);
    }
  // Si on a 5 joueurs et qu'on en perd 3, on ne va pas émettre 3 fois 
  // incomplet(), car le ServeurJeu ajouterait 3 fois la même.
}
void Table::doit_transmettre(unsigned int j, Protocole::Message m)
{
  emit doit_emettre(joueurs[j], m);
}
