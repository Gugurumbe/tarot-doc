#include "tapis.hpp"

Tapis::Tapis():joueur_ouverture(-1)
{
}

void Tapis::ajouter(const Protocole::Msg_carte & carte)
{
  Carte c(carte.carte);
  m_tapis.push_back(c);
  if(c == EXCUSE) m_tapis.push_back(Carte(DETTE_EXCUSE));
}

void Tapis::set_ouverture(unsigned int joueur)
{
  joueur_ouverture = (int)joueur;
}

bool Tapis::complet() const
{
  unsigned int cartes_reelles = 0;
  for(std::vector<Carte>::const_iterator i = m_tapis.begin();
      i != m_tapis.end(); i++)
    {
      if(*i != DETTE_EXCUSE) cartes_reelles++;
    }
  return cartes_reelles >= 5;
}

std::vector<Carte> concat(const std::vector<Carte> & t1,
			  const std::vector<Carte> & t2)
{
  std::vector<Carte> t;
  t.reserve(t1.size() + t2.size());
  for(unsigned int i = 0 ; i < t1.size() ; i++)
    {
      t.push_back(t1[i]);
    }
  for(unsigned int i = 0 ; i < t2.size() ; i++)
    {
      t.push_back(t2[i]);
    }
  return t;
}

std::vector<Carte> Tapis::terminer(
				   unsigned int attaquant,
				   unsigned int appele,
				   bool dernier_pli,
				   unsigned int & suivant)
{
  unsigned int gagnant = joueur_ouverture;
  unsigned int joueur = joueur_ouverture;
  std::vector<Carte> gagnees;
  std::vector<unsigned int> possesseurs;
  gagnees.reserve(6);
  possesseurs.reserve(6);
  //On établit les possesseurs de chaque carte
  joueur = joueur_ouverture;
  for(unsigned int i = 0 ; i < m_tapis.size() ; i++)
    {
      possesseurs[i] = joueur;
      if(m_tapis[i] != EXCUSE) //La prochaine carte
	//est au joueur suivant
	{
	  joueur = (joueur + 1) % 5;
	}
    }
  if(!dernier_pli)
    {
      //On recherche l'excuse et on l'enlève du tapis...
      joueur = joueur_ouverture;
      for(unsigned int i = 0; i < m_tapis.size(); i++)
	{
	  if(m_tapis[i] == EXCUSE)
	    {
	      if(joueur == attaquant || joueur == appele)
		{
		  //Elle revient à l'attaque
		  gagnees.push_back(m_tapis[i]);
		}
	      //Elle n'est pas attribuée au gagnant
	      m_tapis.erase(m_tapis.begin() + i);
	      possesseurs.erase(possesseurs.begin() + i);
	      i = m_tapis.size();
	    }
	  if(i < m_tapis.size() && m_tapis[i] != DETTE_EXCUSE)
	    joueur = (joueur + 1) % 5;
	}
    }
  joueur = joueur_ouverture;
  //Toutes les cartes restantes reviennent au gagnant.
  Carte gagnante = m_tapis[0];
  for(unsigned int i = 1; i < m_tapis.size(); i++)
    {
      if(gagnante>m_tapis[i])
	{
	  //C'est toujours le même joueur qui est maître
	}
      else
	{
	  gagnante = m_tapis[i];
	  gagnant = possesseurs[i];
	  suivant = gagnant;
	}
    }
  if(gagnant == attaquant || gagnant == appele)
    return concat(gagnees, m_tapis);
  return gagnees;
}

bool Tapis::plus_gros_atout(Carte & c) const
{
  bool b = false;
  int max = 0;
  int i_max = 0;
  for(unsigned int i = 0 ; i < m_tapis.size() ; i++)
    {
      if(m_tapis[i] != EXCUSE && m_tapis[i].atout())
	{
	  b = true;
	  if(max == 0 || m_tapis[i].valeur() > m_tapis[i_max].valeur())
	    {
	      max = m_tapis[i].valeur();
	      i_max = i;
	    }
	}
    }
  if(b)
    {
      c = m_tapis[i_max];
    }
  return b;
}

bool Tapis::entame(Carte & c) const
{
  if(m_tapis.size() == 0) return false;
  if(m_tapis[0] == EXCUSE && m_tapis.size() == 2) return false;
  if(m_tapis[0] == EXCUSE) c = m_tapis[1];
  else c = m_tapis[0];
  return true;
}
