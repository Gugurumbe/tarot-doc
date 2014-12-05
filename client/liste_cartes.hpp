/**
   @file client/liste_cartes.hpp
   @brief Affiche une liste de cartes.
 */

#ifndef LISTE_CARTES_DEFINIE

/**
   @brief Empêche les inclusions récursives.
 */
#define LISTE_CARTES_DEFINIE

#include "carte.hpp"

#include <QTextBrowser>

/**
   @brief Affiche une liste de cartes, dans l'ordre.
 */
class ListeCartes : public QTextBrowser
{
  Q_OBJECT;
public:
  /**
     @brief Constructeur par défaut.
     @param parent Le QWidget parent.
   */
  ListeCartes(QWidget * parent = 0);
  
public slots:
  /**
     @brief Change les cartes dont on dispose.
     @param gagnees Les cartes gagnees.
     @param perdues Les cartes perdues.
   */
  void gagner(std::vector<Carte> gagnees, std::vector<Carte> perdues);

private:
  std::vector<Carte> cartes;
  QString header;
  QString footer;
};

#endif
