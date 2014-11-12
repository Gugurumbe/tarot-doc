#include "partie_serveur.hpp"

#include <iostream>

#define EMETTRE_A_TOUS(m) 		\
  for(unsigned int i = 0 ; i < 4 ; i++) \
    emit doit_emettre(i, m, false);	\
  emit doit_emettre(4, m, true);

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
    case Protocole::ERREUR_PROTOCOLE:
      std::cout<<"Un client n'a pas compris mon message."<<std::endl;
      break;
    case Protocole::REFUSE:
      break;
    case Protocole::NUMERO:
    case Protocole::DISTRIBUTION:
      //Dans le cas de Distribution, les jeux sont déjà à jour.
      break;
    case Protocole::PRISE:
      Protocole::Message contrat;
      contrat.type = Protocole::CONTRAT;
      contrat.m.contrat.niveau = message.m.prise.niveau;
      e_max = Enchere((tour() + 4) % 5, contrat.m.contrat);
      EMETTRE_A_TOUS(contrat);
      break;
    case Protocole::CONTRAT:
      if(tour() == 0)
	{
	  //Les enchères sont terminées.
	  //Détermination de l'enchère maximale.
	  std::cout<<"Enchères terminées."<<std::endl;
	  int i_attaquant = 0;
	  for(int i = 0 ; i < 5 ; i++)
	    {
	      if(enchere_de(i) > enchere_de(i_attaquant))
		{
		  i_attaquant = i;
		}
	    }
	  if(enchere_de(i_attaquant).prise())
	    {
	      //Quelqu'un a pris.
	      set_attaquant(i_attaquant);
	      std::cout<<"Attaquant : "<<i_attaquant<<std::endl;
	      //Envoi du message "appel"
	      Protocole::Message appel;
	      appel.type = Protocole::APPEL;
	      emit doit_emettre(i_attaquant, appel, true);
	    }
	  else
	    {
	      //Personne n'a pris.
	      set_phase(Partie::FIN);
	      Protocole::Message fin;
	      fin.type = Protocole::RESULTAT;
	      for(unsigned int i = 0 ; i < 5 ; i++)
		{
		  fin.m.resultat.resultats[i] = 0;
		}
	      EMETTRE_A_TOUS(fin);
	    }
	}
    case Protocole::APPEL:
      break;
    case Protocole::APPELER:
      Protocole::Message mess_contrat_final;
      mess_contrat_final.type = Protocole::CONTRAT_FINAL;
      mess_contrat_final.m.contrat_final.preneur = attaquant();
      mess_contrat_final.m.contrat_final.niveau = (int)contrat_final().prise();
      mess_contrat_final.m.contrat_final.appel = message.m.appeler.carte;
      EMETTRE_A_TOUS(mess_contrat_final);
      if(contrat_final().prise() >= Enchere::GARDE_SANS)
	{
	  if(contrat_final().prise() == Enchere::GARDE_SANS)
	    {
	      cartes_gagnees.push_back(chien);
	    }
	  Protocole::Message jeu;
	  jeu.type = Protocole::JEU;
	  jeu.m.jeu.chelem = (chelem() >= 0 ? chelem() : 5);
	  EMETTRE_A_TOUS(jeu);
	}
      else
	{
	  // Il faut montrer le chien
	  Protocole::Message mess_chien;
	  mess_chien.type = Protocole::CHIEN;
	  for(unsigned int i = 0 ; i < 3 ; i++)
	    {
	      mess_chien.m.chien.chien[i] = chien[i].numero();
	    }
	  EMETTRE_A_TOUS(mess_chien);
	}
      break;
    case Protocole::ECART:
      if(true) //On n'aime pas les déclarations dans les "case"
	{
	  std::vector<Carte> ecart;
	  for(unsigned int i = 0 ; i < 3 ; i++)
	    {
	      ecart.push_back(message.m.ecart.ecart[i]);
	    }
	  // On donne les 3 cartes du chien au preneur et on lui enlève
	  // les 3 cartes de l'écart
	  for(unsigned int i = 0 ; i < chien.size() ; i++)
	    {
	      jeu_reel[attaquant()].ajouter(chien[i]);
	    }
	  for(unsigned int i = 0 ; i < 3 ; i++)
	    {
	      jeu_reel[attaquant()].enlever(Carte(message.m.ecart.ecart[i]));
	    }
	  //Gestion des atouts :
	  std::vector<Carte::ModaliteEcart> resultat =
	    jeu_reel[attaquant()].peut_ecarter(ecart);
	  std::vector<Carte> montrees;
	  for(unsigned int i = 0 ; i < resultat.size() ; i++)
	    {
	      if(resultat[i] == Carte::MONTRER_CARTE)
		{
		  montrees.push_back(ecart[i]);
		}
	    }
	  Protocole::Message atout;
	  atout.type = Protocole::ATOUT;
	  atout.m.atout.nombre = montrees.size();
	  for(unsigned int i = 0 ; i < montrees.size() ; i++)
	    {
	      atout.m.atout.cartes[i] = montrees[i].numero();
	    }
	  EMETTRE_A_TOUS(atout);
	  //Envoi du message Jeu
	  Protocole::Message mess_jeu;
	  mess_jeu.type = Protocole::JEU;
	  mess_jeu.m.jeu.chelem = (chelem() < 0 ? 5 : chelem());
	  EMETTRE_A_TOUS(mess_jeu);
	}
      break;
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
	  if(!(e.prise()) || e > e_max)
	    {
	      std::cout<<"L'enchère "<<e.prise()<<" est validée."<<std::endl;
	    }
	  else ok = 2;
	}
      else
	{
	  ok = 1;
	    std::cout<<"Erreur de protocole sur Protocole::PRISE. ";
	  if(phase() != ENCHERES)
	    std::cout<<"On n'en est pas aux enchères."<<std::endl;
	  else std::cout<<"Ce n'est pas le tour du joueur "<<joueur
			<<" mais plutôt celui de "<<tour()<<std::endl;
	}
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
      std::cout<<"Test d'un écart : ";
      if(phase() == CONSTITUTION_ECART &&
	 joueur == attaquant() &&
	 Enchere::GARDE_SANS > enchere_de(joueur).prise())
	{
	  std::cout<<"c'est bien à son tour."<<std::endl;
	  std::cout<<"Cartes demandées : ";
	  std::vector<Carte> ecart;
	  for(unsigned int i = 0 ; i < 3 ; i ++)
	    {
	      ecart.push_back(message.m.ecart.ecart[i]);
	      std::cout<<ecart[i].numero()<<", ";
	    }
	  std::vector<Carte::ModaliteEcart> resultat;
	  resultat = jeu_reel[joueur].peut_ecarter(ecart);
	  for(unsigned int i = 0 ; i < resultat.size() ; i++)
	    {
	      switch(resultat[i])
		{
		case Carte::NON_ECARTABLE :
		  std::cout<<"La carte "<<i<<" ne peut pas être écartée."
			   <<std::endl;
		  ok = 2 ;
		  i = 3;
		default:
		  break;
		}
	    }
	}
      else ok = 1;
      std::cout<<"Fin du test, ok = "<<ok<<std::endl;
      break;
    case Protocole::CHELEM:
      ok = 1; //Pas encore implémenté.
      break;
    case Protocole::MONTRER_POIGNEE:
      ok = 1;
      break;
    default :
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
  //On prévoit le cas "petit sec"
  int nbr_atouts = 0;
  bool a_petit = false;
  bool petit_sec = false;
  Carte c(PETIT);
  for(unsigned int i = 0 ; i < 5 ; i++)
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
      for(unsigned int i = 0 ; i < 5 ; i++)
	{
	  Protocole::Message mess;
	  mess.type = Protocole::DISTRIBUTION;
	  jeu_reel[i].distribution(mess.m.distribution);
	  emit doit_emettre(i, mess, true);
	}
      set_phase(Partie::ENCHERES);
    }
  else distribuer();
}
