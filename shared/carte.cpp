#include "carte.hpp"

Carte::Carte(): m_defini(false)
{
}

Carte::Carte(const Carte & carte): m_numero(carte.m_numero),
				   m_defini(carte.m_defini)				   
{
}

Carte::Carte(unsigned int numero): m_numero(numero % 78), m_defini(numero < 78)
{
}

Carte const & Carte::operator=(const Carte & carte)
{
  m_defini = carte.m_defini;
  m_numero = carte.m_numero;
  return *this;
}

Carte const & Carte::operator=(unsigned int carte)
{
  m_defini = carte < 78;
  m_numero = carte % 78;
  return *this;
}

bool Carte::operator>(const Carte & carte) const
{
  if(m_defini && carte.m_defini)
    {
      //Si l'une des deux cartes est l'excuse, c'est facile
      if(carte == EXCUSE) return true;
      if(m_numero == EXCUSE) return false;
      /*Si elles sont de la même couleur (ou 2 cartes d'atout), il
      faut comparer les valeurs. */
      if(couleur() == carte.couleur())
	return valeur() > carte.valeur();
      //Si les cartes ne sont pas de la même couleur, 
      //soit la deuxième est de l'atout (elle gagne)
      if(carte.couleur() == ATOUT) return false;
      //soit la deuxième n'est pas de l'atout (this gagne)
      return true;
    }
  return false;
}

bool Carte::operator>(unsigned int numero) const
{
  return operator>(Carte(numero));
}

bool Carte::operator==(const Carte & carte) const
{
  return m_defini && carte.m_defini && carte.m_numero == m_numero;
}

bool Carte::operator==(unsigned int carte) const
{
  return m_defini && m_numero == carte;
}

bool Carte::operator!=(const Carte & carte) const
{
  return !operator==(carte);
}

bool Carte::operator!=(unsigned int carte) const
{
  return !operator==(carte);
}

unsigned int Carte::numero() const
{
  return m_numero;
}

bool Carte::defini() const
{
  return m_defini;
}

unsigned int Carte::couleur() const
{
  if(m_numero < DEBUT_ATOUT) return m_numero / 14;
  return ATOUT;
}

unsigned int Carte::valeur() const
{
  if(m_numero < DEBUT_ATOUT) return m_numero % 14;
  return m_numero - DEBUT_ATOUT;
}

unsigned int Carte::points() const
{
  if(couleur() != ATOUT)
    {
      if(valeur() < 10) return 1; //Un demi-point
      return (valeur() - 10 + 1) * 2 + 1;
      //Valet : valeur=10, points=3 demi-points
      //Ainsi de suite
    }
  else if(m_numero == EXCUSE 
	  || m_numero == PETIT 
	  || m_numero == VINGTETUN) return 9; //4.5 points
  else return 1; //Tous les autres atouts
}
