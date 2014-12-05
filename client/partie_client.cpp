#include "partie_client.hpp"

#define NOM_CLASSE "PartieClient"

#include "deboguer.hpp"

PartieClient::PartieClient(QObject * parent):
  QObject(parent), Partie(), m_mon_tour(5)
{
  ENTER("PartieClient(QObject * parent)");
  ADD_ARG("parent", parent);
  mon_equipe.reserve(4);
}

bool PartieClient::mon_tour() const
{
  ENTER("mon_tour() const");
  EXIT(tour() == m_mon_tour);
}

unsigned int PartieClient::mon_numero() const
{
  ENTER("mon_numero() const");
  EXIT(m_mon_tour);
}

bool PartieClient::est_ami(unsigned int joueur) const
{
  ENTER("est_ami(unsigned int joueur) const");
  ADD_ARG("joueur", joueur);
  std::vector<unsigned int>::const_iterator i = mon_equipe.begin();
  for(i = mon_equipe.begin();
      i != mon_equipe.end() && *i != joueur ; i++);
  EXIT(i != mon_equipe.end());
}

void PartieClient::assimiler(const Protocole::Message & m)
{
  ENTER("assimiler(Message m)");
  ADD_ARG("m", m);
  Partie::assimiler(m);
  switch(m.type)
    {
    case Protocole::ERREUR_PROTOCOLE:
      break;
    case Protocole::REFUSE:
      //On récupère les cartes en chemin
      for(unsigned int i = 0 ; i < en_chemin.size() ; i++)
	{
	  mes_cartes.ajouter(en_chemin[i]);
	}
      en_chemin.clear();
      emit action_refusee();
      if(phase() == Partie::CONSTITUTION_ECART) 
	{
	  emit ecart_refuse();
	  emit doit_ecarter();
	}
      else if(phase() == Partie::PHASE_JEU)
	{
	  emit requete_refusee();
	  emit doit_jouer();
	}
      else if(phase() == Partie::ENCHERES && en_chemin.empty())
	{
	  emit enchere_refusee();
	  if(m_mon_tour != 0)
	    emit doit_priser(meilleure_enchere());
	  else
	    emit doit_priser();
	}
      else if(phase() == Partie::ENCHERES)
	{
	  //C'est l'appel qui a été refusé
	  en_chemin.clear();
	  emit appel_refuse();
	  emit doit_appeler();
	}
      break;
    case Protocole::NUMERO:
      m_mon_tour = m.m.numero.n;
      mon_equipe.push_back(m.m.numero.n);
      emit numero_change(m_mon_tour);
      break;
    case Protocole::DISTRIBUTION:
      mes_cartes = Main(m.m.distribution);
      set_phase(ENCHERES);
      DEBUG<<"Le jeu change, c'est sûr."<<std::endl;
      emit jeu_change(std::vector<Carte>(mes_cartes.cartes()), 
		      std::vector<Carte>());
      if(m_mon_tour == 0) emit doit_priser();
      break;
    case Protocole::PRISE:
      break;
    case Protocole::CONTRAT:
      emit contrat_intermediaire((tour() + 4)%5, 
				 Enchere((tour() + 4)%5, m.m.contrat));
      if(mon_tour() && phase() == ENCHERES) 
	{
	  emit doit_priser(meilleure_enchere());
	}
      break;
    case Protocole::APPEL:
      emit doit_appeler();
      break;
    case Protocole::APPELER:
      //On dit que le roi est en chemin...
      en_chemin.push_back(Carte(m.m.appeler.carte));
      break;
    case Protocole::CONTRAT_FINAL:
      en_chemin.clear();
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
      chien_si_devoile.clear();
      for(unsigned int i = 0 ; i < 3 ; i++)
	chien_si_devoile.push_back(Carte(m.m.chien.chien[i]));
      emit chien_devoile(chien_si_devoile[0],
			 chien_si_devoile[1],
			 chien_si_devoile[2]);
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
      break;
    case Protocole::ECART:
      //Je dois écarter !
      for(unsigned int i = 0 ; i < 3 ; i++)
	{
	  mes_cartes.ajouter(chien_si_devoile[i]);
	}
      emit jeu_change(chien_si_devoile, std::vector<Carte>());
      emit doit_ecarter();
      break;
    case Protocole::ATOUT:
      if(true)
	{
	  std::vector<Carte> atouts;
	  for(int i = 0 ; i < m.m.atout.nombre && i < 3 ; i++)
	    {
	      atouts.push_back(Carte(m.m.atout.cartes[i]));
	    }
	  emit atout_au_chien(atouts);
	}
      break;
    case Protocole::CHELEM:
      break;
    case Protocole::JEU:
      if(mon_numero() == attaquant())
	{
	  //L'écart a été accepté.
	  //On remplace le chien par l'écart en chemin.
	  chien_si_devoile.clear();
	  for(unsigned int i = 0 ; i < en_chemin.size() ; i++)
	    {
	      chien_si_devoile.push_back(en_chemin[i]);
	    }
	  emit ecart_accepte();
	  emit jeu_change(std::vector<Carte>(), en_chemin);
	  en_chemin.clear();
	}
      if(mon_tour())
	{
	  emit doit_jouer();
	}
      break;
    case Protocole::MONTRER_POIGNEE:
      break;
    case Protocole::POIGNEE:
      break;
    case Protocole::REQUETE:
      // Je mets cette carte en chemin.
      if(true)
	{
	  Carte c(m.m.requete.carte);
	  if(mes_cartes.possede(c))
	    {
	      mes_cartes.enlever(c);
	      en_chemin.push_back(c);
	    }
	}
      break;
    case Protocole::CARTE:
      if(mon_tour())
	{
	  //C'est moi qui ai joué ça
	  emit requete_acceptee();
	  emit jeu_change(std::vector<Carte>(), en_chemin);
	  en_chemin.clear();
	}
      else if(*(enchere_de(attaquant()).carte_appelee()) 
	      == m.m.carte.carte)
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
      if(mon_tour()) emit doit_jouer();
      break;
    case Protocole::RESULTAT:
      break;
    default:
      break;
    }
}

void PartieClient::montrer_poignee(std::vector<Carte> const & p)
{
  ENTER("montrer_poignee(std::vector<Carte> p)");
  ADD_ARG("p", p);
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
  ENTER("jouer(const Carte & c)");
  ADD_ARG("c", c);
  Protocole::Message m;
  m.type = Protocole::REQUETE;
  m.m.requete.carte = c.numero();
  emit doit_emettre(m);
}

void PartieClient::formuler_prise(Enchere::Prise p)
{
  ENTER("formuler_prise(Prise p)");
  ADD_ARG("p", p);
  Protocole::Message m;
  m.type = Protocole::PRISE;
  m.m.prise.niveau = (int)p;
  emit doit_emettre(m);
}

void PartieClient::appeler(const Carte & c)
{
  ENTER("appeler(const Carte & c)");
  ADD_ARG("c", c);
  Protocole::Message m;
  m.type = Protocole::APPELER;
  m.m.appeler.carte = c.numero();
  emit doit_emettre(m);
}

void PartieClient::ecarter(std::vector<Carte> const & c)
{
  ENTER("ecarter(vector<Carte> c)");
  ADD_ARG("c", c);
  Protocole::Message m;
  m.type = Protocole::ECART;
  for(unsigned int i = 0 ; i < 3 && i < c.size() ; i++)
    {
      m.m.ecart.ecart[i] = c[i].numero();
      //On indique que la carte est en chemin
      if(mes_cartes.possede(c[i]))
	{
	  mes_cartes.enlever(c[i]);
	  en_chemin.push_back(c[i]);
	}
    }
  emit doit_emettre(m);
}

void PartieClient::demander_chelem()
{
  ENTER("demander_chelem()");
}

void PartieClient::demander_jeu()
{
  ENTER("demander_jeu()");
}

const Main & PartieClient::mon_jeu() const
{
  ENTER("mon_jeu() const");
  EXIT(mes_cartes);
}

void PartieClient::changement_maitre(unsigned int,
				     unsigned int nouveau)
{
  ENTER("changement_maitre(unsigned int, unsigned int nouveau)");
  ADD_ARG("nouveau", nouveau);
  emit maitre(nouveau);
}

void PartieClient::nouveau_maitre(unsigned int maitre)
{
  ENTER("nouveau_maitre(unsigned int maitre)");
  ADD_ARG("maitre", maitre);
  emit PartieClient::maitre(maitre);
}

void PartieClient::cartes_gagnees
(std::vector<Carte> const & cartes,
 std::vector<unsigned int> const & poseurs,
 std::vector<unsigned int> const & gagnants)
{
  ENTER("cartes_gagnees(vector<Carte> cartes, vector<uint> poseurs, vector<uint> gagnants)");
  ADD_ARG("cartes", cartes);
  ADD_ARG("poseurs", poseurs);
  ADD_ARG("gagnants", gagnants);
  for(unsigned int i = 0 ; i < cartes.size() ; i++)
    {
      emit carte_gagnee(cartes[i], poseurs[i], gagnants[i]);
    }
}
