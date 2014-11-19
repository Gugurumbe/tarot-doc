/**
   @file shared/ne_pas_debogueur.hpp
   @brief À inclure pour ne pas déboguer ce fichier.
*/

#include <iostream>

/**
   @brief Stub.
 */
#define ENTER(meth)

/**
   @brief Stub.
 */
#define ADD_ARG(nom, val)

/**
   @brief Stub.
*/
#define EXIT(val) return val

/**
   @brief Stub.
 */
#define DEBUG std::ostream(0)

/**
   @brief Flux d'erreur.
 */
#define ERROR std::cerr<<"!"<<
