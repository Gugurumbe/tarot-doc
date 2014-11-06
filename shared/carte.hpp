/**
   @file shared/carte.hpp
   @brief Définit une classe de carte à jouer.
 */

#ifndef CARTE_DEFINIE

/**
   Empêche les inclusions récursives.
 */
#define CARTE_DEFINIE

/**
   Premier atout.
 */
#define DEBUT_ATOUT 56

/**
  Numéro de la couleur Pique.
*/
#define PIQUE 0

/**
  Numéro de la couleur Cœur.
*/
#define COEUR 1

/**
  Numéro de la couleur Carreau.
*/
#define CARREAU 2

/**
  Numéro de la couleur Trèfle.
*/
#define TREFLE 3

/**
  Numéro de la couleur Atout. L'excuse est un atout.
*/
#define ATOUT 4

/**
   Première carte de pique.
 */
#define DEBUT_PIQUE PIQUE * 14

/**
   Première carte de cœur.
 */
#define DEBUT_COEUR COEUR * 14

/**
   Première carte de carreau.
 */
#define DEBUT_CARREAU CARREAU * 14

/**
   Première carte de trèfle.
 */
#define DEBUT_TREFLE TREFLE * 14

/**
   Numéro du Petit.
 */
#define PETIT 56

/**
   Numéro du Vingt et Un.
*/
#define VINGTETUN 76

/**
   Numéro de l'Excuse.
*/
#define EXCUSE 77

/**
   Numéro de la Dette d'Excuse.
   La Dette d'Excuse est une carte artificielle qui est jouée en même
   temps que l'Excuse. Aucun joueur ne possède la Dette d'Excuse, mais
   elle apparaît dans les plis ramassés. Elle rapporte 0.5 points,
   n'est pas un bout mais est considérée comme un atout de valeur
   0. Elle est tout le temps gagnée par le joueur qui remporte le pli.

   L'Excuse est un bout, rapporte 4 points et est considérée comme un
   atout de valeur 0. Sauf circonstances exceptionnelles, elle est
   gagnée par celui qui l'a jouée.
 */
#define DETTE_EXCUSE 78

/**
   @brief Définition d'une Carte du jeu.

   Une classe permettant de définir les comportements d'une carte au
   tarot. Une Carte est définie par un numéro unique entre 0 et 78. 
   Les cartes du tarot sont au nombre de 78, mais pour des raisons de
   commodité on considère qu'il y en a 79. L'excuse est un bout qui
   vaut 4 points, et la dette d'excuse est une carte basse qui revient
   à celui qui fait le pli.
 */
class Carte
{
public:

  /**
     Représente la valeur des cartes de couleur non atout.
     @see Carte::valeur() const
  */
  enum{AS, DEUX, TROIS, QUATRE, CINQ, SIX,
       SEPT, HUIT, NEUF, DIX, VALET, CAVALIER, DAME, ROI};
  
  /**
     Sert à dire si une carte peut être écartée ou non, et les
     modalités éventuelles (montrer les atouts).
     @see Carte::ecartable() const
  */  
  enum ModaliteEcart
    {
      ECARTABLE,     /**<La carte est écartable.*/
      MONTRER_CARTE, /**<Il faut montrer la carte.*/
      NON_ECARTABLE  /**<On ne peut pas écarter cette carte.*/
    };
  
  /** 
      Constructeur principal.
      Le constructeur attend un numéro de carte valide.
      @param numero : le numéro entre 0 et 78.
  */
  Carte(unsigned int numero);
  /**
     Constructeur de copie.
     @param carte : la carte à copier.
  */
  Carte(const Carte & carte);
  /**
     Comparaison des cartes.
     Les cartes sont toutes comparables. La relation carte1 > carte2
     veut dire : "Si je joue carte1 puis qu'on joue carte2, c'est a
     priori moi qui remporte le pli". Il ne s'agit pas d'une relation
     d'ordre, car elle n'est pas antisymétrique. Par exemple, un deux
     de pique l'emporte sur un trois de coeur et vice versa.
     @param carte : le numéro de la carte à comparer.
     @return vrai dans le cas de l'exemple précédent.
   */
  bool operator>(unsigned int carte) const;
  /**
     Comparaison des cartes (2).
     @param carte : l'objet carte à comparer à "this".
     @see Carte::operator>(unsigned int) const
  */
  bool operator>(const Carte & carte) const;
  /**
     Test d'égalité entre les cartes.
     Puisque les cartes sont copiables, on veut tester l'égalité.
     @param carte : le numéro de la carte à comparer à "this".
     @return vrai ssi la carte a ce numéro.
   */
  bool operator==(unsigned int carte) const;
  /**
     Test d'égalité entre les cartes (2).
     @param carte : l'objet Carte à comparer à "this".
     @see Carte::operator==(unsigned int) const
  */
  bool operator==(const Carte & carte) const;
  /**
     Test de différence entre 2 cartes.
     @param carte : le numéro de la carte à comparer à "this".
     @return vrai ssi les cartes sont différentes.
     @see Carte::operator==(unsigned int) const
  */
  bool operator!=(unsigned int carte) const;
  /**
     Test de différence entre 2 cartes (2).
     @param carte : l'objet carte à comparer à "this".
     @see Carte::operator==(const Carte &) const
     @see Carte::operator!=(unsigned int) const
  */
  bool operator!=(const Carte & carte) const;
  /**
     Retourne le numéro de la carte.
     Le numéro de la carte est un entier entre 0 et 78.
     @return le numéro de la carte.
     @see Carte::Carte(unsigned int)
   */
  unsigned int numero() const;
  /**
     Retourne la couleur de la carte.
     La couleur de la carte est un nombre entre 0 et 4. La dernière
     couleur est la couleur atout. L'excuse est considérée comme un
     atout. Avant de faire des tests, il peut être utile de vérifier
     si la carte est l'excuse : 
     
     ~~~~~~~~~~~~~~~~~~~{.cpp}
     if(carte == EXCUSE || carte == DETTE_EXCUSE)
     {
     traiterCommeExcuse(carte);
     }
     else if(carte1.couleur() == carte2.couleur())
     {
     traiter(carte);
     }
     ~~~~~~~~~~~~~~~~~~~
     
     @return la couleur de la carte.
     @see Carte::operator==(unsigned int) const
   */
  unsigned int couleur() const;
  /**
     Indique si la carte est de l'atout.
     Peut être utile pour écarter des cartes ou pour déclarer des
     poignées. L'excuse est considérée comme un atout.
     @return vrai ssi la carte est l'excuse ou un atout.
     @see Carte::couleur() const
     @see Carte::bout() const
     @see Carte::roi() const
     @see Carte::tete() const
   */
  bool atout() const;
  /**
     Indique si la carte est une tête.
     Les têtes sont les valets, cavaliers, dames et rois.
     Peut être utile pour appeler une carte.
     @return vrai ssi la carte est une tête.
     @see Carte::atout() const
     @see Carte::roi() const
     @see Carte::couleur() const
     @see Carte::bout() const
   */
  bool tete() const;
  /**
     Indique si la carte est un roi.
     @return vrai ssi la carte est un roi.
     @see Carte::atout() const
     @see Carte::tete() const
     @see Carte::couleur() const
     @see Carte::bout() const     
   */
  bool roi() const;
  /**
     Indique si la carte est un bout.
     @return vrai ssi la carte est un bout.
     @see Carte::atout() const
     @see Carte::tete() const
     @see Carte::couleur() const
     @see Carte::roi() const     
   */
  bool bout() const;
  /**
     Retourne la valeur d'une carte.
     La valeur d'une carte est son ordre dans le classement par ordre
     croissant des cartes d'une même couleur. Par exemple, la valeur
     d'une Dame est 12. La valeur des Excuses est 0, celle du Petit
     est 1, celle du Vingt et un est 21. Utilisé pour déterminer la
     carte la plus forte d'un pli. N'a rien à voir avec le nombre de
     points que rapporte cette carte.
     @return la valeur de la carte.
     @see Carte::couleur() const
     @see Carte::demipoints() const
   */
  unsigned int valeur() const;
  /**
     Retourne le nombre de demi-points que cette carte rapporte.
     Le nombre de demi-points d'une carte basse et de la dette
     d'excuse est 1. Le nombre de demi-points de l'excuse est 8 (4
     points). Le nombre de demi-points d'un autre bout est 9 (4.5
     points). Le nombre de demi-points d'une tête est déterminé par sa
     valeur : Valet 3, Cavalier 5, Dame 7, Roi 9.
     @return le nombre de demi-points de cette carte.
     @see Carte::bout() const
     @see Carte::tete() const
     @see Carte::valeur() const
   */
  unsigned int demipoints() const;
  /**
     Indique si la carte est écartable.
     Lors de la constitution d'un écart, le joueur peut ou ne peut pas
     mettre certaines cartes dans le chien. Les bouts et les rois sont
     interdits, et les atouts sont tolérés dans une certaine mesure :
     si le joueur ne peut pas écarter autre chose, et en montrant ce
     ou ces atouts aux autres joueurs.
     @return de quelle manière on peut écarter cette carte.
     @see Carte::bout() const
     @see Carte::roi() const
     @see Carte::atout() const
   */
  ModaliteEcart ecartable() const;
  /**
     Affecte la carte (1).
     Modifie le numéro de la carte pour qu'il corresponde à celui
     d'une autre carte.
     @param carte : la carte à copier.
     @return la copie créée.
     @see Carte::Carte(const Carte &)
     @see Carte::numero() const
   */
  Carte const & operator=(const Carte & carte);
  /**
     Affecte la carte (2).
     Change le numéro de la carte. S'il n'est pas inférieur à 79, le
     résultat modulo 79 est utilisé.
     @param carte : le numéro à utiliser. 
     @return la copie créée.
     @see Carte::operator=(const Carte &)
     @see Carte::Carte(unsigned int)
     @see Carte::numero() const
  */
  Carte const & operator=(unsigned int carte);
private:
  /**
     Le numéro interne de la carte.
   */
  unsigned int m_numero;
};

#endif
