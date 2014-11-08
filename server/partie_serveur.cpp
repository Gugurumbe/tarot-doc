#include "partie_serveur.hpp"

#include <iostream>

PartieServeur::PartieServeur(QObject * parent):
  QObject(parent), Partie(), jeu_reel(5)
{
}

void PartieServeur::assimiler(Protocole::Message const & message)
{
  Partie::assimiler(message);
  /* Le serveur met à jour les mains des joueurs et le tapis. */
  switch(message.type)
    {
    default :
      std::cout<<"Penser à assimiler côté serveur.\n";
    }
}

int PartieServeur::tester(unsigned int joueur, Protocole::Message const & message) const
{
  int ok = 0;
  switch(message.type)
    {
    case Protocole::PRISE:
      // Ok si on en est aux enchères, que c'est son tour et qu'il
      // monte
      if(phase() == ENCHERES && tour() == joueur)
	{
	  Enchere e(joueur, message.m.prise);
	  if(!(e.prise()) || tour() == 0
	     || e > enchere_de((tour() + 4) % 5))
	    {
	      //C'est valide, et on n'accèdera pas à encheres[4] au
	      //premier tour.
	    }
	  else ok = 2;
	}
      else ok = 1;
      break;
    case Protocole::APPELER:
      if(phase() == ENCHERES && joueur == attaquant())
	{
	  if(jeu_reel[joueur].peut_appeler
	     (Carte(message.m.appeler.carte)))
	    {
	      //C'est bon !
	    }
	  else ok = 2;
	}
      else ok = 1;
      break;
    case Protocole::ECART:
      if(phase() == CONSTITUTION_ECART &&
	 joueur == attaquant() &&
	 Enchere::GARDE_SANS > enchere_de(joueur).prise())
	{
	  std::vector<Carte> ecart;
	  for(unsigned int i = 0 ; i < 3 ; i ++)
	    {
	      ecart[i] = message.m.ecart.ecart[i];
	    }
	  std::vector<Carte::ModaliteEcart> resultat;
	  resultat = jeu_reel[joueur].peut_ecarter(ecart);
	  for(unsigned int i = 0 ; i < resultat.size() ; i++)
	    {
	      switch(resultat[i])
		{
		case Carte::NON_ECARTABLE :
		  ok = 2 ;
		  i = 3;
		default:
		  break;
		}
	    }
	}
      else ok = 1;
      break;
    case Protocole::CHELEM:
      ok = 1; //Pas encore implémenté.
      break;
    case Protocole::MONTRER_POIGNEE:
      ok = 1;
      break;
    }
  return ok;
}

template <class T>
void swap(unsigned int i, unsigned int j, std::vector<T> & tab)
{
  T temp(tab[i]);
  tab[i] = tab[j];
  tab[j] = temp;
}

template<class T>
void shuffle(std::vector<T> & tab)
{
  for(unsigned int i = 1 ; i < tab.size() ; i++)
    {
      swap(i, rand() % i, tab);
    }
}

void PartieServeur::distribuer()
{
  std::vector<int> nums (78);
  for(unsigned int i = 0 ; i < nums.size() ; i++)
    {
      nums[i] = i;
    }
  shuffle(nums);
  // Les 3 premières cartes sont pour le chien, les autres pour les
  // joueurs.
  chien.clear();
  for(unsigned int i = 0 ; i < 3 ; i++)
    {
      chien.push_back(Carte(nums[i]));
    }
  jeu_reel.clear();
  int nbr_atouts = 0;
  bool a_petit = false;
  bool petit_sec = false;
  Carte c(PETIT);
  for(unsigned int i = 0 ; i < 4 ; i++)
    {
      Main m;
      nbr_atouts = 0;
      a_petit = false;
      for(unsigned int j = 0 ; j < 15 ; j++)
	{
	  c = nums[3 + i*15 + j];
	  if(c == PETIT) a_petit = true;
	  if(c.atout()) nbr_atouts++;
	  m.ajouter(c);
	}
      jeu_reel.push_back(m);
      if(a_petit && nbr_atouts == 1)
	{
	  petit_sec = true;
	}
    }
  if(!petit_sec)
    {
      for(unsigned int i = 0 ; i < 4 ; i++)
	{
	  Protocole::Message mess;
	  mess.type = Protocole::DISTRIBUTION;
	  jeu_reel[i].distribution(mess.m.distribution);
	  emit doit_emettre(i, mess);
	}
      set_phase(Partie::ENCHERES);
    }
  else distribuer();
}
