#include "partie_client.hpp"

PartieClient::PartieClient(QObject * parent = 0):
  QObject(parent), Partie(), m_mon_tour(5)
{
  mon_equipe.reserve(4);
}

bool PartieClient::mon_tour() const
{
  return tour() == m_mon_tour;
}

bool PartieClient::est_ami(unsigned int joueur) const
{
  for(std::vector<unsigned int>::iterator i = mon_equipe.begin();
      i != mon_equipe.end() && *i != joueur ; i++);
  return i != mon_equipe.end();
}

void PartieClient::assimiler(const Message & m)
{
  switch(m.type)
    {
    case ERREUR_PROTOCOLE:
      break;
    case REFUSE:
      emit action_refusee();
      break;
    case NUMERO:
      mon_tour = m.m.numero.n;
      mon_equipe.push_back(m.m.numero.n);
      break;
    case DISTRIBUTION:
      mes_cartes = Main(m.m.distribution);
      set_phase(ENCHERES);
      break;
    case DECISION:
      break;
    case CONTRAT:
      break;
    case APPEL:
      emit doit_appeler();
      break;
    case APPELER:
      break;
    case CONTRAT_FINAL:
      /* A-t-on la carte appelée ? */
      if(m_mon_tour == m.m.contrat_final.joueur)
	{
	  /* Ah, ben c'est moi qui prends. */
	  /* Que j'aie la carte appelée ou pas, je ne connais */
	  /* pas d'autre allié. */
	}
      else if(mes_cartes.possede(m.m.contrat_final.carte))
	    /* Je suis appelé ! */
	mon_equipe.push_back(m.m.contrat_final.joueur);
      if(m.m.contrat_final.niveau >= GARDE_SANS)
	{
	  // On ne parle pas du chien, donc c'est à nous !
	  emit doit_demander_chelem();
	}
      break;
    case CHIEN:
      /* Si la carte appelée est dans le chien et que je n'ai pas */
      /* pris, alors je suis avec tous les autres défenseurs */
      if(attaquant() != m_mon_tour)
	{
	  Carte appelee = *(contrat_final().carte_appelee());
	  if(appelee == m.m.chien.cartes[0]
	     ||appelee == m.m.chien.cartes[1]
	     ||appelee == m.m.chien.cartes[2])
	    {
	      mon_equipe.clear();
	      for(unsigned int i = 0 ; i < 5 ; i++)
		{
		  if(i != attaquant())
		    {
		      mon_equipe.push_back(i);
		    }
		}
	    }
	}
      else
	{
	  //Je dois écarter !
	  emit doit_ecarter();
	}
      break;
    case ECART:
      break;
    case ATOUT:
      break;
    case CHELEM:
      break;
    case JEU:
      break;
    case MONTRER_POIGNEE:
      break;
    case POIGNEE:
      break;
    case REQUETE:
      break;
    case CARTE:
      if(mon_tour())
	{
	  //C'est moi qui ai joué ça
	  mes_cartes.enlever(m.m.carte.carte);
	}
      else if(*(contrat_final().carte_appelee()) == m.m.carte.carte)
	{
	  /* Je suis un défenseur */
	  mon_equipe.clear();
	  for(unsigned int i = 0 ; i < 5 ; i++)
	    {
	      if(i != attaquant() && i != tour())
		{
		  mon_equipe.push_back(i);
		}
	    }
	}
      break;
    case PLI:
      break;
    case RESULTAT:
      break;
    default:
      break;
    }
  Partie::assimiler(m);
  if(mon_tour())
    {
      switch(phase())
	{
	case CONSTITUTION_TABLE:
	  break; //Rien à faire
	case ENCHERES:
	  if(m.type != APPEL)
	    {
	      emit doit_decider();
	    }
	  //Dans le cas où le message est un appel,
	  // le tour n'a pas de sens
	  break;
	case CONSTITUTION_ECART:
	  //Déjà géré dans le cas CHIEN
	  break;
	case ATTENTE_CHELEM:
	  emit doit_demander_chelem; //Attention : peut-être
	  //que ça a déjà été fait
	  break;
	case PHASE_JEU:
	  emit doit_jouer();
	  break;
	case FIN:
	  break;
	default:
	  break;
	}
    }
}
