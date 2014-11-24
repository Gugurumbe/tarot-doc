#include "partie.hpp"
#include "debogueur.hpp"
#include <iostream>

#define NOM_CLASSE "Partie"

#include "ne_pas_deboguer.hpp"

class TapisPartie : public Tapis
{
public:
  TapisPartie(Partie * parent);

protected:
  virtual void changement_maitre(unsigned int, unsigned int);
  virtual void nouveau_maitre(unsigned int);
  virtual void cartes_gagnees(std::vector<Carte> const &,
			      std::vector<unsigned int> const &,
			      std::vector<unsigned int> const &);
private:
  Partie * const m_parent;
};

Partie::Partie(): m_encheres(5), m_chelem(false), 
		  m_tapis(new TapisPartie(this)), 
		  m_attaquant(5),
		  m_tour(0), plis_joues(0),
		  m_phase(CONSTITUTION_TABLE),
		  m_tailles_poignees(5, 0)
{
  ENTER("Partie()");
}

Partie::~Partie()
{
  ENTER("~Partie()");
  delete m_tapis;
}

const Enchere & Partie::contrat_final() const
{
  ENTER("contrat_final() const");
  /* assert(m_attaquant < 5); */
  EXIT(m_encheres[m_attaquant]);
}

const Enchere & Partie::enchere_de(unsigned int joueur) const
{
  ENTER("enchere_de(unsigned int joueur) const");
  ADD_ARG("joueur", joueur);
  EXIT(m_encheres[joueur]);
}

int Partie::chelem() const
{
  ENTER("chelem() const");
  EXIT(m_chelem);
}

unsigned int Partie::attaquant() const
{
  ENTER("attaquant() const");
  EXIT(m_attaquant);
}

void Partie::set_attaquant(unsigned int j)
{
  ENTER("set_attaquant(unsigned int j)");
  ADD_ARG("j", j);
  if(m_attaquant >= 5)
    {
      m_attaquant = j;
    }
}

unsigned int Partie::tour() const
{
  ENTER("tour() const");
  EXIT(m_tour);
}

unsigned int Partie::poignee(unsigned int joueur) const
{
  ENTER("poignee(unsigned int joueur const");
  ADD_ARG("joueur", joueur);
  EXIT(m_tailles_poignees[joueur]);
}

Partie::PhaseJeu Partie::phase() const
{
  ENTER("phase() const");
  EXIT(m_phase);
}

void Partie::set_phase(Partie::PhaseJeu p)
{
  ENTER("set_phase(PhaseJeu p)");
  ADD_ARG("p", p);
  m_phase = p;
}

void Partie::assimiler(const Protocole::Message & m)
{
  ENTER("assimiler(Message m)");
  ADD_ARG("m.type", m.type);
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
      m_tour = m_tour + 1; // pas modulo 5, car une fois que les 
      //enchères sont passées ce n'est plus le tour de personne.
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
      if(m_chelem) m_tour = attaquant();
      else m_tour = 0;
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
      if(m_tour == attaquant() && 
	 m_chelem &&
	 m.m.carte.carte == EXCUSE && 
	 plis_joues == 14)
	m_tapis->ajouter(m.m.carte, Carte::EXCUSE_GAGNANTE);
      else if(plis_joues == 14)
	m_tapis->ajouter(m.m.carte, Carte::EXCUSE_PRENABLE);
      else
	m_tapis->ajouter(m.m.carte, Carte::EXCUSE_IMPRENABLE);
      m_tour = (m_tour + 1) % 5 ;
      break;
    case Protocole::PLI:
      m_phase = PHASE_JEU;
      m_tour = m.m.pli.joueur;
      plis_joues++;
      break;
    case Protocole::RESULTAT:
      m_phase = FIN;
    default:
      break;
    }
  DEBUG<<"Phase : "<<m_phase<<", tour : "<<m_tour<<std::endl;;
}

const Tapis & Partie::tapis() const
{
  return *m_tapis;
}

void Partie::throw_changement_maitre(unsigned int ancien,
			       unsigned int nouveau)
{
  changement_maitre(ancien, nouveau);
}

void Partie::throw_nouveau_maitre(unsigned int maitre)
{
  nouveau_maitre(maitre);
}

void Partie::throw_cartes_gagnees
(std::vector<Carte> const & cartes,
 std::vector<unsigned int> const & poseurs,
 std::vector<unsigned int> const & gagnants)
{
  cartes_gagnees(cartes, poseurs, gagnants);
}

void Partie::changement_maitre(unsigned int, unsigned int)
{
}

void Partie::nouveau_maitre(unsigned int)
{
}

void Partie::cartes_gagnees(std::vector<Carte> const &,
			    std::vector<unsigned int> const &,
			    std::vector<unsigned int> const &)
{
}

TapisPartie::TapisPartie(Partie * parent) : m_parent(parent)
{
}

void TapisPartie::changement_maitre(unsigned int ancien,
					    unsigned int nouveau)
{
  m_parent->throw_changement_maitre(ancien, nouveau);
}

void TapisPartie::nouveau_maitre(unsigned int maitre)
{
  m_parent->throw_nouveau_maitre(maitre);
}

void TapisPartie::cartes_gagnees
(std::vector<Carte> const & cartes,
 std::vector<unsigned int> const & poseurs,
 std::vector<unsigned int> const & gagnants)
{
  m_parent->throw_cartes_gagnees(cartes, poseurs, gagnants);
}
