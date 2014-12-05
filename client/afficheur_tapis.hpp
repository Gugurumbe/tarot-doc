/**
   @file client/afficheur_tapis.hpp
   @brief Gère l'affichage d'un Tapis au travers d'un QTableWidget.
 */

#ifndef AFFICHEUR_TAPIS_DEFINI

/**
   @brief Empêche les inclusions récursives.
 */
#define AFFICHEUR_TAPIS

#include "tapis.hpp"

#include <QTableWidget>

/**
   @brief Afficheur de tapis.
 */
class AfficheurTapis: public QTableWidget
{
  Q_OBJECT;
public:
  /**
     @brief Constructeur.

     @param parent Le QWidget parent.
   */
  AfficheurTapis(QWidget * parent = 0);
public slots:
  
  /**
     @brief Recalcule les éléments à afficher.
     
     @param tapis Le tapis à dessiner.
   */
  void recalculer(const Tapis & tapis);
};

#endif
