/**
   @file client/ui/label_nom.hpp
   @brief Affichage simplifié d'un nom de joueur.
 */

#ifndef LABEL_NOM_DEFINI

/**
   @brief Empêche les inclusions récursives.
 */
#define LABEL_NOM_DEFINI

#include <QLabel>

/**
   @brief Classe d'affichage d'un nom.
 */
class LabelNom : public QLabel
{
  Q_OBJECT;
  
public :
  
  /**
     @brief Constructeur par défaut.
     @param parent Le Widget parent au sens de Qt.
  */
  LabelNom(QWidget * parent = 0);

  /**
     @brief Donne le nom de ce joueur.
     
     @param j Le numéro de joueur.
     @return Le nom correspondant :
     0 -> Agathe
     1 -> Emmanuel
     2 -> Isidore
     3 -> Olivier
     4 -> Ursula
     autre -> ???
   */
  static QString nom_de(unsigned int j);
				
public slots :

  /**
     @brief Affiche le joueur correspondant.
     @param j Le joueur à afficher.
     
     @see LabelNom::nom_de(unsigned int)
   */
  void set_num(unsigned int j);
};

#endif
