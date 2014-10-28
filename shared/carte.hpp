//Fichier "carte.hpp"

#ifndef CARTE_DEFINIE
#define CARTE_DEFINIE

#define DEBUT_PIQUE 0
#define DEBUT_COEUR 14
#define DEBUT_CARREAU 28
#define DEBUT_TREFLE 42
#define DEBUT_ATOUT 56
#define EXCUSE 56

#define PIQUE 0
#define COEUR 1
#define CARREAU 2
#define TREFLE 3
#define ATOUT 4

#define PETIT 57
#define VINGTETUN 77

class Carte
{
public:
  Carte();
  Carte(const Carte & carte);
  Carte(unsigned int numero);
  Carte const & operator=(const Carte & carte);
  Carte const & operator=(unsigned int carte);
  bool operator>(const Carte & carte) const;
  bool operator>(unsigned int carte) const;
  /* Il n'y a pas de relation d'ordre : carte1 > carte2 veut dire "Si
  je joue d'abord carte1 puis qu'on joue carte2, c'est carte1 qui
  l'emporte. */
  bool operator==(const Carte & carte) const;
  bool operator==(unsigned int carte) const;
  bool operator!=(const Carte & carte) const;
  bool operator!=(unsigned int carte) const;
  unsigned int numero() const;
  bool defini() const;
  unsigned int couleur() const;
  unsigned int valeur() const;
  unsigned int points() const;
  //Le double des points
private:
  unsigned int m_numero;
  bool m_defini;
};

#endif
