/**
   @file shared/deboguer.hpp
   @brief À inclure pour déboguer ce fichier.

   @note Vous devez définir NOM_CLASSE avec la valeur (sous forme de chaîne) du nom de la classe.
*/

#include "debogueur.hpp"

/**
   @brief Smart alias for ENTER_CLASS.

   @note Vous devez avoir défini NOM_CLASSE.
 */
#define ENTER(meth) ENTER_CLASS(meth, NOM_CLASSE)

/**
   @brief Alias pour Debogueur::arg.
 */
#define ADD_ARG(nom, val) Debogueur::arg(nom, val)

/**
   @brief Alias pour Debogueur::ret.

   @warning L'argument est évalué 2 fois !!!
*/
#define EXIT(val)				\
  Debogueur::ret(val);				\
  return val

/**
   @brief Flux de débogage.
 */
#define DEBUG Debogueur::debug()

/**
   @brief Flux d'erreur.
 */
#define ERROR Debogueur::error()
