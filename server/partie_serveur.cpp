#include "partie_serveur.hpp"

PartieServeur::PartieServeur(QObject * parent): Partie(parent),
						jeu_reel(5),
						prets(5, false)
{
  distribuer();
}

void PartieServeur::assimiler(Message const & message)
{
  Partie::assimiler(entrant);
  /* Le serveur met à jour les mains des joueurs et le tapis. */
  switch(
}

bool PartieServeur::tester(unsigned int joueur, Message const & message) const
{
  bool ok = false;
  switch(message.m.type)
    {
    case DECISION:
      // Ok si on en est aux enchères, que c'est son tour et qu'il monte
      ok = (phase() == ENCHERES && 
	    tour() == joueur &&
	    (message.m.decision.niveau == 0 
	     || message.m.decision.niveau > encheres[(tour + 4) % 5]));
      break;
    case APPELER:
      //Ok si on en est aux enchères, si c'est l'attaquant et que la carte
      //appelée n'est pas définie. Comme l'attaquant est initialisé à 5,
      //on ne peut pas appeler une carte tant qu'on n'a pas proposé le meilleur
      //contrat.
      //La carte appelée doit être un roi, ou une tête si le joueur a tous les rois
      ok = (phase() == ENCHERES &&
	    joueur == attaquant() &&
	    !(carte_appelee().defini()) && 
	    carte_appelee.tete());
      if(!carte_appelee().roi())
	{
	  int nombre_rois = 0;
	  for(unsigned int i = 0 ; i < jeu_reel[joueur].size(); i++)
	    {
	      if(jeu_reel[joueur][i].roi()) nombre_rois++;
	    }
	  ok = (nombre_rois == 4);
	}
      break;
    case ECART:
      //Ok si on en est à la phase de constitution de l'écart, 
      //si c'est l'attaquant qui cause,
      //si son enchère est inférieure strictement à une garde sans,
      //s'il dispose des 3 cartes dans son jeu et dans le chien,
      //si les 3 carts sont différentes.
      if(phase() == CONSTITUTION_ECART 
	 && joueur == attaquant() 
	 && encheres[joueur] < 3)
	{
	  ok = true;
	  for(unsigned int i = 0 ; ok && i < 3 ; i++)
	    {
	      ok = false;
	      //On cherche la i-ième carte de l'écart.
	      //Si on la trouve, on remet ok à true.
	      for(unsigned int j = 0 ; j < jeu_reel[joueur].size() ; j++)
		{
		  if(jeu_reel[joueur][j] == m.m.ecart.carte[i])
		    {
		      ok = true;
		      j = jeu_reel[joueur].size();
		    }
		}
	      if(!ok)
		{
		  //On cherche dans le chien
		  for(unsigned int j = 0 ; j < chien.size() ; j++)
		    {
		      if(chien[j] == m.m.ecart.carte[i])
			{
			  ok = true;
			  j = chien.size();
			}
		    }
		}
	    }
	  ok = ok && (m.m.ecart.carte[0] != m.m.ecart.carte[1])
	    && (m.m.ecart.carte[0] != m.m.ecart.carte[2])
	    && (m.m.ecart.carte[1] != m.m.ecart.carte[2])
	    && Carte(m.m.ecart.carte[0]).ecartable()
	    && Carte(m.m.ecart.carte[1]).ecartable()
	    && Carte(m.m.ecart.carte[2]).ecartable();
	}
      else ok = false;
      break;
    case CHELEM:
      // On en tient compte indépendamment du tour du joueur
      ok = prets[joueur];
      break;
    case MONTRER_POIGNEE:
      //Ok si on en est à la phase de jeu,
      //si c'est le tour du joueur,
      //si il a encore 15 cartes,
      //si la poignée est de 8, 10 ou 13 cartes
      //si le joueur possède ces cartes
      //si toutes les cartes sont différentes
      //si toutes les cartes sont des atouts
      ok = (phase() == JEU) &&
	tour() == joueur &&
	jeu_reel[joueur] == 15;
      break;
    }
  return ok;
}
