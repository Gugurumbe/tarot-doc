#ifndef SCORE_DEFINI
#define SCORE_DEFINI

#include "carte.hpp"

#include "enchere.hpp"

#include <vector>

/**
   @brief À la fin de la partie, compte les points.
   
   @param contrat_final Le contrat final.
   @param joueur_appele Le joueur appelé.
   @param gagnees Les cartes engrangées par l'attaque à chaque tour de
   jeu. Certaines lignes sont vides. La première est possiblement le
   chien. 
   @param perdues Les cartes engrangées par la défense. Sert à dire si
   elle a mené le petit au bout.
   @param poignees Les tailles des poignées anoncées.

   @return Les points de chacun. La somme est nulle.
 */
std::vector<int> compter(const Enchere & contrat_final, 
			 unsigned int joueur_appele, 
			 const std::vector<std::vector<Carte> > 
			 & gagnees,
			 const std::vector<std::vector<Carte> >
			 & perdues,
			 const std::vector<unsigned int> & poignees);

#endif
