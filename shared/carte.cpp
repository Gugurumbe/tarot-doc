#include "carte.hpp"

Carte::Carte(unsigned int numero): m_numero(numero % 79)
{
}

Carte::Carte(const Carte & carte): m_numero(carte.m_numero)
{
}

bool Carte::operator>(unsigned int numero) const
{
  return operator>(Carte(numero));
}

bool Carte::operator>(const Carte & carte) const
{
  //Si la carte est l'excuse, alors elle ne remporte pas le pli
  if(m_numero == EXCUSE || m_numero == DETTE_EXCUSE) return false;
  //Si on est de la même couleur, c'est la valeur qui décide
  if(couleur() == carte.couleur()) return valeur() > carte.valeur();
  //Sinon, on perd ssi l'autre carte est un atout
  return !(carte.atout());
}

bool Carte::operator==(unsigned int carte) const
{
  return m_numero == carte;
}

bool Carte::operator==(const Carte & carte) const
{
  return carte.m_numero == m_numero;
}

bool Carte::operator!=(unsigned int carte) const
{
  return !operator==(carte);
}

bool Carte::operator!=(const Carte & carte) const
{
  return !operator==(carte);
}

unsigned int Carte::numero() const
{
  return m_numero;
}

unsigned int Carte::couleur() const
{
  if(m_numero < DEBUT_ATOUT) return m_numero / 14;
  return ATOUT;
}

bool Carte::atout() const
{
  return m_numero >= DEBUT_ATOUT; //L'excuse est un atout
}

bool Carte::tete() const
{
  return !atout() && valeur() >= VALET;
}

bool Carte::roi() const
{
  return !atout() && valeur() == ROI;
}

bool Carte::bout() const
{
  return m_numero == PETIT
    || m_numero == EXCUSE
    || m_numero == VINGTETUN;
}

unsigned int Carte::valeur() const
{
  if(m_numero < DEBUT_ATOUT) return m_numero % 14;
  if(m_numero == EXCUSE || m_numero == DETTE_EXCUSE) return 0;
  return m_numero - DEBUT_ATOUT + 1;
  /* Ainsi, le petit a la valeur 1 (supérieure à l'excuse) */
}

unsigned int Carte::demipoints() const
{
  if(couleur() != ATOUT)
    {
      if(valeur() < VALET) return 1; //Un demi-point
      return (valeur() - VALET + 1) * 2 + 1;
      //Valet : valeur=10, points=3 demi-points
      //Ainsi de suite
    }
  else if(m_numero == PETIT 
	  || m_numero == VINGTETUN) return 9; //4.5 points
  else if(m_numero == EXCUSE) return 8; //4 points
  else return 1; //Les autres atouts et la dette d'excuse
}

Carte::ModaliteEcart Carte::ecartable() const
{
  if(bout() || roi()) return NON_ECARTABLE;
  if(atout()) return MONTRER_CARTE;
  return ECARTABLE;
}

Carte const & Carte::operator=(const Carte & carte)
{
  m_numero = carte.m_numero;
  return *this;
}

Carte const & Carte::operator=(unsigned int carte)
{
  m_numero = carte % 79;
  return *this;
}
