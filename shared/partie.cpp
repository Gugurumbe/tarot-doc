#include "partie.hpp"

Partie::Partie(): m_encheres(5), m_chelem(-1), m_attaquant(5),
		  m_tour(0), m_phase(CONSTITUTION_TABLE),
		  m_tailles_poignees(5, 0)
{
}

const Enchere & Partie::contrat_final() const
{
  /* assert(m_attaquant < 5); */
  return m_encheres[m_attaquant];
}

int Partie::chelem() const
{
  return m_chelem;
}

const Tapis & Partie::tapis() const
{
  return m_tapis;
}

unsigned int Partie::attaquant() const
{
  return m_attaquant;
}

unsigned int Partie::tour() const
{
  return m_tour;
}

unsigned int Partie::poignee(unsigned int joueur) const
{
  return m_tailles_poignees[joueur];
}

void Partie::set_phase(PhaseJeu p)
{
  m_phase = p;
}

void Partie::assimiler(const Message & m)
{
  switch(m.type)
    {
    case ERREUR_PROTOCOLE:
      break;
    case REFUSE:
      break;
    case NUMERO:
      break;
    case DISTRIBUTION:
      break;
    case DECISION:
      break;
    case CONTRAT:
      // Le joueur dont c'est le tour a formulé le contrat suivant
      m_phase = ENCHERES;
      encheres[m_tour] = Enchere(m_tour, m.m.contrat.niveau);
      m_tour = (m_tour + 1) % 5;
      break;
    case APPEL:
      break;
    case APPELER:
      break;
    case CONTRAT_FINAL:
      m_attaquant = m.m.contrat_final.joueur;
      m_encheres[m_attaquant] = m.m.contrat_final;
      m_phase = CONSTITUTION_ECART;
      break;
    case CHIEN:
      break;
    case ECART:
      break;
    case ATOUT:
      //Il faut en informer le client !
      break;
    case CHELEM:
      break;
    case JEU:
      m_chelem = (m.m.jeu.chelem >= 5 ? -1 : m.m.jeu.chelem);
      if(m_chelem >= 0) m_tour = m_chelem;
      //Le joueur ayant demandé un chelem joue.
      m_phase = PHASE_JEU;
      break;
    case POIGNEE:
      m_tailles_poignees[m_tour] = m.m.poignee.taille;
      break;
    case REQUETE:
      break;
    case CARTE:
      m_tapis.ajouter(m.m.carte);
      m_tour = (m_tour + ) % 5 ;
      break;
    case PLI:
      m_tour = m.m.pli.joueur;
      break;
    case RESULTAT:
      m_phase = FIN;
    default:
      break;
    }
}
