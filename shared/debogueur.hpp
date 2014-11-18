/**
   @file Classe permettant de savoir où on en est.
*/

#ifndef DEBOGUEUR_DEFINI

/**
   @brief Empêche les inclusions multiples.
 */
#define DEBOGUEUR_DEFINI

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

/**
   @brief Crée un débogueur de type classe.

   Lorsque cette macro est utilisée au début d'une méthode
   de classe, elle crée un débogueur nommé "auto_debogueur"
   qui vivra pendant l'exécution de la méthode.
 */
#define ENTER_CLASS(nom_methode, nom_classe) \
  Debogueur auto_debogueur(nom_methode, nom_classe, this)

/**
   @brief Crée un débogueur de type fonction.

   @see ENTER_CLASS
 */
#define ENTER_FUNCTION(nom_fonction) \
  Debogueur auto_debogueur(nom_fonction, "", NULL)

/**
   @brief Liste les appels / retours de fonction.

   La classe Debogueur se base sur le fait suivant :
   Dans une fonction, la durée de vie des objets est 
   égale à la durée d'exécution de la fonction. Pour
   envoyer un message au début de l'exécution et un
   autre à la fin de l'exécution, il faut créer un
   objet au début de l'exécution. Cet objet a un 
   constructeur et un destructeur qui envoie ce genre
   de messages.

   Les débogueurs créés dans chaque appel suivent une
   hiérarchie : chaque débogueur a un parent, dont il
   respecte l'indentation.
 */
class Debogueur
{
public:
  /**
     @brief Crée un nouveau débogueur.
     
     @param nom_methode Le nom de la méthode pendant
     laquelle ce débogueur est actif.
     @param nom_classe Le nom de la classe rattachée
     à cette méthode.
     @param objet L'adresse de l'objet représentant
     de la classe.
   */
  Debogueur(std::string const & nom_methode,
	    std::string const & nom_classe = "",
	    void * objet = 0);

  /**
     @brief Appelé à la fin de l'exécution de la méthode.
   */
  virtual ~Debogueur();

  /**
     @brief Crée un flux respectant l'indentation.

     Dans le corps de vos fonctions, remplacez
     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
     std::cout<<"Message de débogage."<<std::endl;
     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     par
     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
     Debogueur::debug()<<"Message de débogage."<<std::endl()
     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     @return un flux de débogage.
   */
  static std::ostream & debug();

  /**
     @brief Spécifie un argument de la fonction.

     Si l'argument n'est pas facilement représentable,
     vous pouvez spécifier une propriété sur cet argument.

     Exemple :
     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
     Debogueur::arg("message.type", message.type);
     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     
     @note Ce n'est pas obligatoire, mais il est conseillé
     d'utiliser cette méthode juste après avoir construit
     un débogueur.

     @param nom Un nom d'élément ou une propriété.
     @param valeur Un élément ou le résultat d'une propriété.
   */
  static void arg(std::string const & nom, std::string const & valeur);
  
  /**
     @brief Redéfinition de Debogueur::arg(std::string const &, std::string const &)
   */
  static void arg(std::string const & nom, long int valeur);

  /**
     @brief Redéfinition de Debogueur::arg(std::string const &, std::string const &)
   */
  static void arg(std::string const & nom, void * valeur);

  /**
     @brief Spécifie une valeur de retour de la fonction.
     
     @see Debogueur::arg(std::string const &, std::stringstream const &)
   */
  static void ret(std::string const & valeur);

  /**
     @brief Redéfinition de Debogueur::ret(std::string const &)
   */
  static void ret(long int valeur);

  /**
     @brief Redéfinition de Debogueur::ret(std::string const &)
   */
  static void ret(void * valeur);

private:
  void ajouter_argument(std::string const & nom, std::string const & valeur);
  void retourner(std::string const & chaine);
  unsigned int indentation() const;
  static Debogueur * current;
  Debogueur * parent;
  std::string retour;
  std::string nom_methode;
  std::string nom_classe;
  void * objet;
};

#endif
