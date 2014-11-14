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

#define ENTER(classe,methode)					\
  Debogueur autogen_debugger(methode, classe, (void *)this);    \
  std::stringstream autogen_debugger_stream;		        

#define ADD_ARG(nom, valeur)						\
  autogen_debugger_stream.str(std::string());				\
  autogen_debugger_stream<<valeur;					\
  autogen_debugger.ajouter_argument(nom, autogen_debugger_stream.str());

#define EXIT(ret)						\
  autogen_debugger_stream.str(std::string());			\
  autogen_debugger_stream<<ret;					\
  autogen_debugger.retourner(autogen_debugger_stream.str())	

#define DEBUG \
  std::cout<<"\x1B[33m"<<std::setw(autogen_debugger.indentation())<<" "<<"DBG : \x1B[0m"

#define ERROR\
  std::cout<<"\x1B[31m!"<<std::setw(autogen_debugger.indentation() - 1)<<" "<<"ERR : \x1B[0m"

/**
   @brief Liste les appels / retours de fonction.
 */
class Debogueur
{
public:
  Debogueur(std::string const & nom_methode,
	    std::string const & nom_classe = "",
	    void * objet = 0);
  virtual ~Debogueur();
  void ajouter_argument(std::string const & nom, std::string const & valeur);
  void retourner(std::string const & chaine);
  unsigned int indentation() const;
private:
  static Debogueur * current;
  Debogueur * parent;
  std::string retour;
  std::string nom_methode;
  std::string nom_classe;
  void * objet;
};

#endif
