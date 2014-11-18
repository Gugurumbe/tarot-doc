#include "debogueur.hpp"
#include <iostream>
#include <iomanip>

#define C_NORMAL "\x1B[0m"
#define C_ROUGE "\x1B[31m"
#define C_VERT "\x1B[32m"
#define C_JAUNE "\x1B[33m"
#define C_BLEU "\x1B[34m"
#define C_MAGENTA "\x1B[35m"
#define C_CYAN "\x1B[36m"
#define C_BLANC "\x1B[37m"
#define C_NOMCLASSE C_MAGENTA
#define C_NOMMETHODE C_BLEU
#define C_OBJET C_VERT
#define C_NOMATTRIBUT C_JAUNE
#define C_VALEUR C_CYAN
#define C_RETOUR C_ROUGE

Debogueur * Debogueur::current = 0;

Debogueur::Debogueur(std::string const & n_methode,
		     std::string const & n_classe,
		     void * n_objet) :
  parent(current), nom_methode(n_methode),
  nom_classe(n_classe), objet(n_objet)
{
  std::cout<<std::setw(parent?parent->indentation() + 1:1)<<" ";
  std::cout<<"->";
  std::cout<<C_NOMCLASSE<<nom_classe<<C_NORMAL<<"::";
  std::cout<<C_NOMMETHODE<<nom_methode<<C_NORMAL;
  std::cout<<", with ";
  std::cout<<C_NOMATTRIBUT<<"object"<<C_NORMAL<<" = "<<C_OBJET<<objet<<std::endl;
  std::cout<<C_NORMAL;
  current = this;
}
Debogueur::~Debogueur()
{
  std::cout<<std::setw(parent?parent->indentation() + 1:1)<<" ";
  std::cout<<"<-";
  std::cout<<C_NOMCLASSE<<nom_classe<<C_NORMAL<<"::";
  std::cout<<C_NOMMETHODE<<nom_methode<<C_NORMAL;
  std::cout<<", with ";
  std::cout<<C_NOMATTRIBUT<<"object"<<C_NORMAL<<" = "<<C_OBJET<<objet;
  std::cout<<C_NORMAL;
  std::cout<<" : return ";
  std::cout<<C_RETOUR;
  std::cout<<retour<<std::endl;
  std::cout<<C_NORMAL;
  current = parent;
}

void Debogueur::ajouter_argument(std::string const & nom, std::string const & valeur)
{
  std::cout<<std::setw(parent?parent->indentation():1)<<" ";
  std::cout<<"  [given "<<C_NOMATTRIBUT<<nom<<C_NORMAL<<" = "<<C_VALEUR<<valeur<<C_NORMAL<<"]"<<std::endl;
}

void Debogueur::retourner(std::string const & c)
{
  retour=c;
}

unsigned int Debogueur::indentation() const
{
  if(parent)
    {
      return 1 + parent->indentation();
    }
  return 1;
}

std::ostream & Debogueur::debug()
{
  if(current)
    {
      return std::cout<<(std::setw(current->indentation()))
		      <<"."
		      <<C_JAUNE
		      <<"[DBG] : "
		      <<C_NORMAL;
    }
  return std::cout<<"."<<C_JAUNE<<"[DBG] : "<<C_NORMAL;
}

void Debogueur::arg(std::string const & nom, 
		    std::string const & valeur)
{
  if(current)
    current->ajouter_argument(nom, valeur);
}

void Debogueur::arg(std::string const & nom, long int valeur)
{
  std::stringstream out;
  out<<valeur;
  arg(nom, out.str());
}

void Debogueur::arg(std::string const & nom, void * valeur)
{
  std::stringstream out;
  out<<valeur;
  arg(nom, out.str());
}

void Debogueur::ret(std::string const & valeur)
{
  if(current)
    current->retourner(valeur);
}

void Debogueur::ret(long int valeur)
{
  std::stringstream out;
  out<<valeur;
  ret(out.str());
}

void Debogueur::ret(void * valeur)
{
  std::stringstream out;
  out<<valeur;
  ret(out.str());
}
