#include "score.hpp"

#include "debogueur.hpp"

#define dbg Debogueur::debug()

std::vector<int> compter(const Enchere & contrat_final,
			 unsigned int joueur_appele,
			 std::vector<std::vector<Carte> > tours,
			 bool defense_petit_au_bout,
			 std::vector<unsigned int> poignees)
{
  ENTER_FUNCTION
    ("compter(Enchere cf, uint appele, vector<vector<Carte>> tours");
  Debogueur::arg("cf", contrat_final);
  Debogueur::arg("appele", joueur_appele);
  Debogueur::arg("tours", tours);
  //Décompte des points de cartes :
  int demipoints_attaque = 0;
  int nombre_bouts = 0;
  unsigned int preneur = contrat_final.joueur();
  bool petit_au_bout = false;
  dbg<<"Comptage des cartes : "<<std::endl;
  for(unsigned int i = 0 ; i < tours.size() ; i++)
    {
      dbg<<"Tour "<<i<<"..."<<std::endl;
      for(unsigned int j = 0 ; j < tours[i].size() ; j++)
	{
	  dbg<<"La carte "<<tours[i][j]<<" rapporte "
	     <<tours[i][j].demipoints()<<" demi-points."
	     <<std::endl;
	  demipoints_attaque+=tours[i][j].demipoints();
	  if(tours[i][j].bout())
	    {
	      dbg<<"C'est un bout."<<std::endl;
	      nombre_bouts++;
	    }
	  if(i == -1 + tours.size() && tours[i][j] == PETIT)
	    {
	      dbg<<"Petit au bout !"<<std::endl;
	      petit_au_bout = true;
	    }
	}
    }
  unsigned int points = demipoints_attaque / 2;
  unsigned int doit_faire = 0;
  switch(nombre_bouts)
    {
    case 0 :
      dbg<<"Sans bout, il faut faire 56 points."
	 <<std::endl;
      doit_faire = 56;
      break;
    case 1 :
      dbg<<"Avec un bout, il faut faire 51 points."
	 <<std::endl;
      doit_faire = 51;
      break;
    case 2 :
      dbg<<"2 Bouts ? Il faut faire 41."
	 <<std::endl;
      doit_faire = 41;
      break;
    default :
      dbg<<"Avec "<<nombre_bouts<<", il faut faire 36 points."
	 <<std::endl;
      doit_faire = 36;
      break;
    }
  int total = 0;
  if(points >= doit_faire)
    {
      dbg<<"Le contrat est rempli, on part de +25."
	 <<std::endl;
      total = 25;
    }
  else
    {
      dbg<<"Le contrat est chuté, on part de -25."
	 <<std::endl;
      total = -25;
    }
  dbg<<"On ajoute le nombre de points de l'attaque."
     <<std::endl;
  total += points - doit_faire;
  if(petit_au_bout)
    {
      dbg<<"Petit au bout pour l'attaque : +10."
	 <<std::endl;
      total += 10;
    }
  if(defense_petit_au_bout)
    {
      dbg<<"Petit au bout pour la défense : -10."
	 <<std::endl;
      total -= 10;
    }
  switch(contrat_final.prise())
    {
    case Enchere::GARDE :
      total *= 2 ;
      dbg<<"Garde : multiplication par 2."
	 <<std::endl;
      break;
    case Enchere::GARDE_SANS :
      total *= 4 ;
      dbg<<"Garde sans : multiplication par 4 !"
	 <<std::endl;
      break;
    case Enchere::GARDE_CONTRE :
      total *= 6 ;
      dbg<<"Garde : multiplication par 6 !"
	 <<std::endl;
      break;
    case Enchere::PASSE : //absurde
    case Enchere::PRISE :
      dbg<<"Pas de multiplication."<<std::endl;
    default:
      break;
    }
  dbg<<"Traitement des poignées :"<<std::endl;
  for(unsigned int i = 0 ; i < poignees.size() ; i++)
    {
      switch(poignees[i])
	{
	case 8 :
	  dbg<<i<<" déclare une simple poignée."
	     <<std::endl;
	  if(i == preneur || i == joueur_appele)
	    {
	      dbg<<"Pour l'attaque : +20"<<std::endl;
	      total += 20;
	    }
	  else
	    {
	      dbg<<"Pour la défense : +20"<<std::endl;
	      total -= 20;
	    }
	  break;
	case 10 :
	  dbg<<i<<" déclare une double poignée."
	     <<std::endl;
	  if(i == preneur || i == joueur_appele)
	    {
	      dbg<<"Pour l'attaque : +30"<<std::endl;
	      total += 30;
	    }
	  else
	    {
	      dbg<<"Pour la défense : +30"<<std::endl;
	      total -= 30;
	    }
	  break;
	case 13 :
	  dbg<<i<<" déclare une triple poignée."
	     <<std::endl;
	  if(i == preneur || i == joueur_appele)
	    {
	      dbg<<"Pour l'attaque : +40"<<std::endl;
	      total += 40;
	    }
	  else
	    {
	      dbg<<"Pour la défense : +40"<<std::endl;
	      total -= 40;
	    }
	  break;
	default:
	  dbg<<"Pas de poignée déclarée par "<<i<<std::endl;
	}
    }
  dbg<<"Tout le monde part de "<<-total<<std::endl;
  std::vector<int> resultat;
  for(unsigned int i = 0 ; i < 5 ; i++)
    {
      resultat.push_back(-total);
    }
  dbg<<"Le joueur appelé marque "<<total<<std::endl;
  resultat[joueur_appele] = total;
  dbg<<"Pour l'instant, le preneur marque 0"<<std::endl;
  resultat[preneur] = 0;
  int somme = 0;
  for(unsigned int i = 0 ; i < resultat.size() ; i++)
    {
      somme += resultat[i];
    }
  dbg<<"Le preneur marque "<<-somme<<std::endl;
  resultat[preneur] = -somme;
  Debogueur::ret(resultat);
  return resultat;
}
