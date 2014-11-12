#include "partie_client.hpp"

PartieClient::PartieClient(QObject * parent):
  QObject(parent), Partie(), m_mon_tour(5)
{
  mon_equipe.reserve(4);
}

bool PartieClient::mon_tour() const
{
  return tour() == m_mon_tour;
}

unsigned int PartieClient::mon_numero() const
{
  return m_mon_tour;
}

bool PartieClient::est_ami(unsigned int joueur) const
{
  std::vector<unsigned int>::const_iterator i = mon_equipe.begin();
  for(i = mon_equipe.begin();
      i != mon_equipe.end() && *i != joueur ; i++);
  return i != mon_equipe.end();
}

void PartieClient::assimiler(const Protocole::Message & m)
{
  switch(m.type)
    {
    case Protocole::ERREUR_PROTOCOLE:
      break;
    case Protocole::REFUSE:
      emit action_refusee();
      break;
    case Protocole::NUMERO:
      m_mon_tour = m.m.numero.n;
      mon_equipe.push_back(m.m.numero.n);
      break;
    case Protocole::DISTRIBUTION:
      mes_cartes = Main(m.m.distribution);
      set_phase(ENCHERES);
      break;
    case Protocole::PRISE:
      break;
    case Protocole::CONTRAT:
      break;
    case Protocole::APPEL:
      emit doit_appeler();
      break;
    case Protocole::APPELER:
      break;
    case Protocole::CONTRAT_FINAL:
      /* A-t-on la carte appelée ? */
      if(m_mon_tour == (unsigned int)m.m.contrat_final.preneur)
	{
	  /* Ah, ben c'est moi qui prends. */
	  /* Que j'aie la carte appelée ou pas, je ne connais */
	  /* pas d'autre allié. */
	}
      else if(mes_cartes.possede(m.m.contrat_final.appel))
	    /* Je suis appelé ! */
	mon_equipe.push_back(m.m.contrat_final.preneur);
      if(m.m.contrat_final.niveau >= Enchere::GARDE_SANS)
	{
	  // On ne parle pas du chien, donc c'est à nous !
	  emit doit_demander_chelem();
	}
      break;
    case Protocole::CHIEN:
      /* Si la carte appelée est dans le chien et que je n'ai pas */
      /* pris, alors je suis avec tous les autres défenseurs */
      if(attaquant() != m_mon_tour)
	{
	  Carte appelee = *(enchere_de(attaquant()).carte_appelee());
	  if(appelee == m.m.chien.chien[0]
	     ||appelee == m.m.chien.chien[1]
	     ||appelee == m.m.chien.chien[2])
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
      chien_si_devoile.clear();
      for(unsigned int i = 0 ; i < 3 ; i++)
	chien_si_devoile.push_back(Carte(m.m.chien.chien[i]));
      break;
    case Protocole::ECART:
      //J'enlève ces cartes de mon jeu si c'est moi qui ai pris,
      //et je les remplace par celles du chien.
      for(unsigned int i = 0 ; i < chien_si_devoile.size() ; i++)
	{
	  mes_cartes.ajouter(chien_si_devoile[i]);
	}
      for(unsigned int i = 0 ; i < 3 ; i++)
	{
	  mes_cartes.enlever(Carte(m.m.ecart.ecart[i]));
	}
      break;
    case Protocole::ATOUT:
      break;
    case Protocole::CHELEM:
      break;
    case Protocole::JEU:
      break;
    case Protocole::MONTRER_POIGNEE:
      break;
    case Protocole::POIGNEE:
      break;
    case Protocole::REQUETE:
      break;
    case Protocole::CARTE:
      if(mon_tour())
	{
	  //C'est moi qui ai joué ça
	  mes_cartes.enlever(m.m.carte.carte);
	}
      else if(*(enchere_de(attaquant()).carte_appelee()) == m.m.carte.carte)
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
    case Protocole::PLI:
      break;
    case Protocole::RESULTAT:
      break;
    default:
      break;
    }
  Partie::assimiler(m);
  if(mon_tour())
    {
      switch(phase())
	{
	case Partie::CONSTITUTION_TABLE:
	  break; //Rien à faire
	case Partie::ENCHERES:
	  if(m.type != Protocole::APPEL)
	    {
	      emit doit_priser();
	    }
	  //Dans le cas où le message est un appel,
	  // le tour n'a pas de sens
	  break;
	case Partie::CONSTITUTION_ECART:
	  //Déjà géré dans le cas CHIEN
	  break;
	case Partie::ATTENTE_CHELEM:
	  emit doit_demander_chelem(); //Attention : peut-être
	  //que ça a déjà été fait
	  break;
	case Partie::PHASE_JEU:
	  emit doit_jouer();
	  break;
	case Partie::FIN:
	  break;
	default:
	  break;
	}
    }
}

void PartieClient::montrer_poignee(std::vector<Carte> const & p)
{
  Protocole::Message m;
  m.type = Protocole::MONTRER_POIGNEE;
  m.m.montrer_poignee.taille = p.size();
  for(unsigned int i = 0 ; i < p.size() ; i++)
    {
      m.m.montrer_poignee.atouts[i] = p[i].numero();
    }
  emit doit_emettre(m);
}

void PartieClient::jouer(const Carte & c)
{
  Protocole::Message m;
  m.type = Protocole::REQUETE;
  m.m.requete.carte = c.numero();
  emit doit_emettre(m);
}

void PartieClient::formuler_prise(Enchere::Prise p)
{
  Protocole::Message m;
  m.type = Protocole::PRISE;
  m.m.prise.niveau = (int)p;
  emit doit_emettre(m);
}

void PartieClient::appeler(const Carte & c)
{
  Protocole::Message m;
  m.type = Protocole::APPELER;
  m.m.appeler.carte = c.numero();
  emit doit_emettre(m);
}

void PartieClient::ecarter(std::vector<Carte> const & c)
{
  Protocole::Message m;
  m.type = Protocole::ECART;
  for(unsigned int i = 0 ; i < 3 && i < c.size() ; i++)
    m.m.ecart.ecart[i] = c[i].numero();
  emit doit_emettre(m);
}

void PartieClient::demander_chelem()
{
}

void PartieClient::demander_jeu()
{
}

Main PartieClient::mon_jeu() const
{
  Main m(mes_cartes);
  if(phase() == CONSTITUTION_ECART && attaquant() == m_mon_tour)
    {
      for(unsigned int i = 0 ; i < chien_si_devoile.size() ; i++)
	{
	  m.ajouter(chien_si_devoile[i]);
	}
    }
  return m;
}
