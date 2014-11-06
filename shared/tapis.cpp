#include "tapis.hpp"

Tapis::Tapis():joueur_ouverture(-1)
{
}

void Tapis::ajouter(const Msg_carte & carte)
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

std::vector<Carte> Tapis::terminer(
				   unsigned int attaquant,
				   unsigned int appele,
				   bool dernier_pli)
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
	      m_tapis.remove(m_tapis.begin() + i);
	      possesseurs.remove(possesseurs.begin() + i);
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
	}
    }
  if(gagnant == attaquant || gagnant == appele)
    gagnees.push_back(m_tapis);
  return gagnees;
}
