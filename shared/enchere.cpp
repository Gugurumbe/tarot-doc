#include "enchere.hpp"

Enchere::Enchere(): m_joueur(5), m_prise(PASSE), m_carte_appelee(0)
{
}

Enchere::Enchere(const Enchere & e):
  m_joueur(e.m_joueur), m_prise(e.m_prise),
  m_carte_appelee(e.m_carte_appelee?new Carte(*e.m_carte_appelee):0)
{
}

Enchere::Enchere(unsigned int joueur, const Msg_decision & m):
  m_joueur(joueur), m_prise(m.niveau), m_carte_appelee(0)
{
}

Enchere::Enchere(const Msg_contrat_final & m):
  m_joueur(m.joueur), m_prise(m.niveau),
  m_carte_appelee(new Carte(m.carte_appelee))
{
}

Enchere::~Enchere()
{
  if(m_carte_appelee)
    {
      delete m_carte_appelee;
      m_carte_appelee = 0;
    }
}

const Carte * Enchere::carte_appelee() const
{
  return m_carte_appelee;
}

void Enchere::appeler(const Carte & carte)
{
  if(m_carte_appelee)
    {
      delete m_carte_appelee;
      m_carte_appelee = 0;
    }
  m_carte_appelee = new Carte(carte);
}

Prise Enchere::prise() const
{
  return m_prise;
}

unsigned int Enchere::joueur() const
{
  return m_joueur;
}

const Enchere & Enchere::operator=(const Enchere & e)
{
  m_joueur = e.m_joueur;
  m_prise = e.m_prise;
  if(m_carte_appelee)
    {
      delete m_carte_appelee;
      m_carte_appelee = 0;
    }
  m_carte_appelee = new Carte(e.m_carte_appelee);
  return *this;
}

const Enchere & Enchere::operator=(const Msg_contrat_final & m)
{
  return operator=(Enchere(m));
}

bool Enchere::operator>(const Enchere & e) const
{
  return m_prise > e.m_prise;
}

bool Enchere::operator>(Prise p) const
{
  return m_prise > p;
}
