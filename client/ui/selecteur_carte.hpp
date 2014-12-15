/**
   @file client/ui/selecteur_carte.hpp
   
   @brief Widget d'entrée, qui permet de sélectionner une Carte.
 */

#ifndef SELECTEUR_CARTE_DEFINI

/**
   @brief Empêche les inclusions récursives.
 */
#define SELECTEUR_CARTE_DEFINI

#include <QComboBox>

#include "carte.hpp"

/**
   @brief Classe permettant de sélectionner une Carte.
 */
class SelecteurCarte : public QComboBox
{
  Q_OBJECT;
public:
  /**
     @brief Constructeur par défaut.
     
     @param parent Le QWidget parent.
   */
  SelecteurCarte(QWidget * parent = 0);
  /**
     @brief Indique la carte sélectionnée.
     
     @return La carte sélectionnée.
     
     @see SelecteurCarte::carte_change(Carte)

     @warning Accès à la case 0 d'un tableau vide si jamais la
     ComboBox est vide !
   */
  const Carte & carte_selectionnee() const;
public slots:
  /**
     @brief Permet d'ajouter une Carte.

     @param c La carte à ajouter.
   */
  void ajouter_carte(const Carte & c);
  /**
     @brief Permet d'enlever une Carte.
     
     @param c La carte à enlever.
   */
  void enlever_carte(const Carte & c);
  /**
     @brief Change plusieurs cartes.
     
     @param gagnees Les cartes gagnees.
     @param perdues Les cartes perdues.

     @see SelecteurCarte::ajouter_carte(const Carte &)
     @see SelecteurCarte::enlever_carte(const Carte &)
     @see ClientJeu::jeu_change(std::vector<Carte>, std::vector<Carte>)
   */
  void modifier_cartes(std::vector<Carte> gagnees,
		       std::vector<Carte> perdues);
  /**
     @brief Permet de montrer des cartes d'un coup.

     @param cartes Les cartes à montrer.

     @see SelecteurCarte::ajouter_carte(const Carte &)
     @see SelecteurCarte::enlever_carte(const Carte &)
   */
  void set_cartes(const std::vector<Carte> & cartes);
  /**
     @brief Permet de montrer toutes les cartes possibles d'un coup.
     
     @note Les cartes restent dans cet ordre !
   */
  void afficher_toutes();
signals:
  /**
     @brief Émis lorsque la carte sélectionnée change.
     
     @param c La nouvelle carte sélectionnée.
     
     @see SelecteurCarte::carte_selectionnee() const
   */
  void carte_change(Carte c);
private slots:
  // Connecté à currentIndexChanged(int);
  void changement_selection(int);
  void mise_a_jour(); //Met à jour le contenu de la ComboBox
private:
  std::vector<Carte> affichees; //même ordre que la ComboBox
};

#endif
