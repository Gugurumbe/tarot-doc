//Le nom de ce fichier est risqué...

#include "main.hpp"

#include <iostream>

Main::Main()
{
  m_cartes.reserve(18);
  //15 plus 3 pour le chien
}

Main::Main(const Main & m): m_cartes(m.m_cartes)
{}

Main::Main(const Protocole::Msg_distribution & m)
{
  m_cartes.reserve(18);
  for(unsigned int i = 0 ; i < 15 ; i++)
    {
      m_cartes.push_back(m.cartes[i]);
    }
}

void Main::enlever(const Carte & carte)
{
  for(std::vector<Carte>::iterator i = m_cartes.begin();
      i != m_cartes.end(); i++)
    {
      if(*i == carte)
	{
	  m_cartes.erase(i);
	  i=m_cartes.end();
	}
    }
}

bool Main::possede(const Carte & carte) const
{
  std::vector<Carte>::const_iterator i = m_cartes.begin();
  for(i = m_cartes.begin();
      i != m_cartes.end() && *i != carte; i++);
  return i != m_cartes.end();
}

void Main::ajouter(const Carte & carte)
{
  m_cartes.push_back(carte);
}

bool Main::peut_appeler(const Carte & carte) const
{
  std::cout<<"->bool Main::peut_appeler(const Carte & carte) const";
  std::cout<<", given carte.numero() = "<<carte.numero()<<std::endl;
  //Si le joueur n'a pas tous les rois, il ne peut pas appeler
  //une dame.
  Carte::Valeur valeur_incomplete = Carte::ROI; //La première valeur pour laquelle
  // il manque une carte dans la main du joueur.
  while(valeur_incomplete > carte.valeur() &&
	(
	 possede(Carte(Carte::PIQUE * 14 + valeur_incomplete)) &&
	 possede(Carte(Carte::TREFLE * 14 + valeur_incomplete))&&
	 possede(Carte(Carte::CARREAU* 14 + valeur_incomplete))&&
	 possede(Carte(Carte::COEUR * 14 + valeur_incomplete))))
    {
      std::cout<<"Le joueur possède toutes les valeurs "<<valeur_incomplete;
      std::cout<<std::endl;
      valeur_incomplete = (Carte::Valeur)((int)valeur_incomplete - 1);
    }
  bool b = carte.tete() && valeur_incomplete <= carte.valeur();
  if(!b)
    {
      if(!carte.tete())
	std::cout<<"Erreur : ce n'est même pas une tête."<<std::endl;
      if(valeur_incomplete > carte.valeur())
	std::cout<<"Erreur : avant d'appeler une Carte de valeur "
		 <<carte.valeur()
		 <<", il faut avoir toutes les Cartes de valeur "
		 <<valeur_incomplete<<std::endl;
    }
  std::cout<<"<-bool Main::peut_appeler(const Cate & carte) const"
	   <<", given carte.numero() = "<<carte.numero()
	   <<" : return "<<(std::string)(b?"true":"false")<<std::endl;
  return b;
}

bool Main::peut_declarer(const std::vector<Carte> & poignee) const
{
  if(poignee.size() == 8 || poignee.size() == 10 || poignee.size() == 13)
    {
      //On possède toutes ces cartes ?
      bool possession = true;
      for(unsigned int i = 0 ; i < poignee.size() ; i++)
	{
	  if(!possede(poignee[i]))
	    {
	      possession = false;
	      i = poignee.size();
	    }
	}
      if(possession)
	{
	  //Sont-elles différentes ?
	  bool differentes = true;
	  for(unsigned int i = 0 ; i < poignee.size() ; i++)
	    for(unsigned int j = i + 1 ; j < poignee.size() ; j++)
	      {
		if(poignee[i] == poignee[j])
		  {
		    differentes = false;
		    i = poignee.size();
		    j = poignee.size();
		  }
	      }
	  if(differentes)
	    {
	      //Y a-t-il l'excuse ?
	      bool excuse = false;
	      for(unsigned int i = 0 ; i < poignee.size() ; i++)
		{
		  if(poignee[i]==EXCUSE)
		    {
		      excuse = true;
		      i = poignee.size();
		    }
		}
	      if(excuse)
		{
		  //Le joueur doit posséder exactement poignee.size() atouts,
		  //puisque l'excuse est un atout.
		  unsigned int nombre_atouts = 0;
		  for(unsigned int i = 0 ; i < m_cartes.size() ; i++)
		    {
		      if(m_cartes[i].atout())nombre_atouts++;
		    }
		  return nombre_atouts == poignee.size();
		}
	      return true;
	    }
	  return false;
	}
      return false;
    }
  return false;
}

const Main & Main::operator=(const Main & m)
{
  m_cartes = m.m_cartes;
  return *this;
}

void Main::distribution(Protocole::Msg_distribution & m)
{
  for(unsigned int i = 0 ; i < 15 && i < m_cartes.size() ; i++)
    {
      m.cartes[i] = m_cartes[i].numero();
    }
}

std::vector<Carte::ModaliteEcart> Main::peut_ecarter(const std::vector<Carte> & ecart) const
{
  std::vector<Carte::ModaliteEcart> resultat(ecart.size());
  std::vector<Carte> cartes_restantes = m_cartes;
  // On commence par traiter les cartes qui ne sont pas des atouts
  for(unsigned int i = 0 ; i < ecart.size() ; i++)
    {
      if(ecart[i].ecartable() == Carte::ECARTABLE)
	{
	  if(possede(ecart[i]))
	    resultat[i] = Carte::ECARTABLE;
	  else
	    resultat[i] = Carte::NON_ECARTABLE;
	}
      else if(ecart[i].ecartable() == Carte::NON_ECARTABLE)
	{
	  resultat[i] = Carte::NON_ECARTABLE;
	}
    }
  //On regarde s'il reste des cartes écartables dans la main du bonhomme
  bool peut_atout = true;
  for(unsigned int i = 0 ; i < m_cartes.size() && peut_atout ; i++)
    {
      if(m_cartes[i].ecartable() == Carte::ECARTABLE)
	{
	  peut_atout = false;
	  //... sauf si on a déjà prévu d'écarter m_cartes[i]
	  for(unsigned int j = 0 ; j < ecart.size() ; j++)
	    {
	      if(ecart[j] == m_cartes[i])
		{
		  peut_atout = true;
		  j = ecart.size();
		}
	    }
	}
    }
  // On traite le cas des atouts
  for(unsigned int i = 0 ; i < ecart.size() ; i++)
    {
      if(ecart[i].ecartable() == Carte::MONTRER_CARTE)
	{
	  if(peut_atout)resultat[i] = Carte::MONTRER_CARTE;
	  else resultat[i] = Carte::NON_ECARTABLE;
	}
    }
  // On vérifie si on possède bien ces 3 cartes
  for(unsigned int i = 0 ; i < ecart.size() ; i++)
    {
      if(!possede(ecart[i])) resultat[i] = Carte::NON_ECARTABLE;
    }
  //On vérifie si elles sont toutes différentes
  for(unsigned int i = 0 ; i < ecart.size() ; i++)
    {
      for(unsigned int j = i + 1 ; j < ecart.size() ; j++)
	{
	  if(ecart[i] == ecart[j]) resultat[j] = Carte::NON_ECARTABLE;
	}
    }
  return resultat;
}
