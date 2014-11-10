#include "partie.hpp"
#include <iostream>

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

const Enchere & Partie::enchere_de(unsigned int joueur) const
{
  return m_encheres[joueur];
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

void Partie::set_attaquant(unsigned int j)
{
  if(m_attaquant >= 5)
    {
      m_attaquant = j;
    }
}

unsigned int Partie::tour() const
{
  return m_tour;
}

unsigned int Partie::poignee(unsigned int joueur) const
{
  return m_tailles_poignees[joueur];
}

Partie::PhaseJeu Partie::phase() const
{
  return m_phase;
}

void Partie::set_phase(Partie::PhaseJeu p)
{
  m_phase = p;
}

void Partie::assimiler(const Protocole::Message & m)
{
  switch(m.type)
    {
    case Protocole::ERREUR_PROTOCOLE:
      break;
    case Protocole::REFUSE:
      break;
    case Protocole::NUMERO:
      m_phase = CONSTITUTION_TABLE;
      break;
    case Protocole::DISTRIBUTION:
      m_phase = ENCHERES;
      break;
    case Protocole::PRISE:
      m_phase = ENCHERES;
      break;
    case Protocole::CONTRAT:
      // Le joueur dont c'est le tour a formulé le contrat suivant
      m_phase = ENCHERES;
      m_encheres[m_tour] = Enchere(m_tour, m.m.contrat);
      m_tour = (m_tour + 1) % 5;
      break;
    case Protocole::APPEL:
      m_phase = ENCHERES;
      break;
    case Protocole::APPELER:
      m_phase = ENCHERES;
      break;
    case Protocole::CONTRAT_FINAL:
      m_phase = CONSTITUTION_ECART;
      m_attaquant = m.m.contrat_final.preneur;
      m_encheres[m_attaquant] = m.m.contrat_final;
      break;
    case Protocole::CHIEN:
      m_phase = CONSTITUTION_ECART;
      break;
    case Protocole::ECART:
      m_phase = CONSTITUTION_ECART;
      break;
    case Protocole::ATOUT:
      m_phase = CONSTITUTION_ECART;
      //Il faut en informer le client !
      break;
    case Protocole::CHELEM:
      //?? à supprimer
      break;
    case Protocole::JEU:
      m_phase = PHASE_JEU;
      m_chelem = (m.m.jeu.chelem >= 5 ? -1 : m.m.jeu.chelem);
      if(m_chelem >= 0) m_tour = m_chelem;
      //Le joueur ayant demandé un chelem joue.
      break;
    case Protocole::POIGNEE:
      m_phase = PHASE_JEU;
      m_tailles_poignees[m_tour] = m.m.poignee.taille;
      break;
    case Protocole::REQUETE:
      m_phase = PHASE_JEU;
      break;
    case Protocole::CARTE:
      m_phase = PHASE_JEU;
      m_tapis.ajouter(m.m.carte);
      m_tour = (m_tour + 1) % 5 ;
      break;
    case Protocole::PLI:
      m_phase = PHASE_JEU;
      m_tour = m.m.pli.joueur;
      break;
    case Protocole::RESULTAT:
      m_phase = FIN;
    default:
      break;
    }
  std::cout<<"Phase : "<<m_phase<<", tour : "<<m_tour<<std::endl;;
}
