#ifndef SCORE_DEFINI
#define SCORE_DEFINI

#include "carte.hpp"

#include "enchere.hpp"

#include <vector>

/**
   @brief À la fin de la partie, compte les points.
   
   @param contrat_final Le contrat final.
   @param joueur_appele Le joueur appelé.
   @param tours Les cartes engrangées par l'attaque à chaque tour de
   jeu. Certaines lignes sont vides.
   @param defense_petit_au_bout Vrai ssi la défense mène le petit au
   bout. 
   @param poignees Les tailles des poignées anoncées.

   @return Les points de chacun. La somme est nulle.
 */
std::vector<int> compter(const Enchere & contrat_final, 
			 unsigned int joueur_appele, 
			 std::vector<std::vector<Carte> >tours,
			 bool defense_petit_au_bout,
			 std::vector<unsigned int> poignees);

#endif
