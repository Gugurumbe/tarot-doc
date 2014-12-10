/**
   @file client/transaction.hpp
   @brief Traite un échange de cartes.

   Décrit l'incertitude qui flotte dans l'air entre le moment
   où un client décide de se séparer d'une carte et le moment où le
   serveur accepte cette action (ou la refuse).
 */
#ifndef TRANSACTION_DEFINIE

/**
   @brief Évite les inclusions récursives.
*/
#define TRANSACTION_DEFINIE

#include "carte.hpp"
#include "enchere.hpp"
#include "option.hpp"
#include <vector>

/**
   @brief Enregistre une transaction.
   
   La transaction est un outil pour que le client comprenne ce qu'il
   se passe en cas de refus de la part du serveur.
 */
class Transaction
{
public:
  /**
     @brief Classe permettant de stocker les informations pour une
     enchère.
     
     Cette classe copie l'Enchère donnée.
   */
  class Enchere
  {
  public:
    /**
       @brief Constructeur par défaut.
       
       Par défaut, l'enchère est invalide.
     */
    Enchere();
    /**
       @brief Constructeur de copie.
       @param e L'enchère de transaction à copier.
     */
    Enchere(const Transaction::Enchere & e);
    /**
       @brief Constructeur standard.
       
       @param e L'enchère à représenter.
     */
    Enchere(const ::Enchere & e);
    /**
       @brief Constructeur avec indice.

       @param e L'enchère à représenter.
       @param indice Un indice. Exemple : l'enchère minimale à faire.
     */
    Enchere(const ::Enchere & e, const ::Enchere & indice);
    /**
       @brief Affectation par copie.
       
       @param e L'enchère de transaction à copier.
     */
    Transaction::Enchere & operator=(const Transaction::Enchere & e);
    /**
       @brief Affectation standard (sans indice).

       @param e L'enchère (objet) à représenter.
     */
    Transaction::Enchere & operator=(const ::Enchere & e);
    /**
       @brief Retourne le contenu.
       
       @return Une véritable enchère... ou rien.
     */
    const Option< ::Enchere> & obtenir() const;
    /**
       @brief Retourne l'indice.
       
       @return L'indice s'il existe, ou rien.
     */
    const Option< ::Enchere> & indice() const;
    
  private:
    Option< ::Enchere> m_enchere;
    Option< ::Enchere> m_indice;
  };
  /**
     @brief Classe permettant de stocker les informations pour un
     appel de carte.
     
     Cette classe copie la Carte donnée.
   */
  class Appel
  {
  public:
    /**
       @brief Constructeur par défaut.
     */
    Appel();
    /**
       @brief Constructeur de copie.
       @param a L'appel de transaction à copier.
     */
    Appel(const Transaction::Appel & a);
    /**
       @brief Constructeur standard.
       
       @param c L'appel à représenter.
     */
    Appel(const Carte & c);
    /**
       @brief Constructeur avec indice.

       @param c L'appel à représenter.
       @param indice Un indice. Par exemple, les cartes appelables.
     */
    Appel(const Carte & c, const std::vector<Carte> & indice);
    /**
       @brief Affectation par copie.
       
       @param a L'appel de transaction à copier.
     */
    Transaction::Appel & operator=(const Transaction::Appel & a);
    /**
       @brief Affectation standard (sans indice).

       @param c La Carte à appeler.
     */
    Transaction::Appel & operator=(const Carte & c);
    /**
       @brief Retourne la carte appelée.
       
       @return Une véritable carte... ou rien.
     */
    const Option<Carte> & obtenir() const;
    /**
       @brief Retourne l'indice.
       
       @return Un tableau de Carte, ou rien.
     */
    const Option<std::vector<Carte> > & indice() const;
    
  private:
    Option<Carte> m_carte;
    Option<std::vector<Carte> > m_indice;
  };
  /**
     @brief Classe permettant de stocker les informations pour un
     écart de cartes.
     
     Cette classe copie les cartes données.
   */
  class Ecart
  {
  public:
    /**
       @brief Constructeur par défaut.
     */
    Ecart();
    /**
       @brief Constructeur de copie.
       @param e L'ecart de transaction à copier.
     */
    Ecart(const Transaction::Ecart & e);
    /**
       @brief Constructeur standard.
       
       @param cartes Les cartes de l'écart.
     */
    Ecart(const std::vector<Carte> & cartes);
    /**
       @brief Constructeur avec indice.

       @param cartes Les cartes de l'écart.
       @param indice Un indice. Par exemple, les cartes écartables.
       @param indice_2 Un autre indice. Par exemple, les atouts
       écartables.
     */
    Ecart(const std::vector<Carte> & cartes, 
	  const std::vector<Carte> & indice,
	  const std::vector<Carte> & indice_2);
    /**
       @brief Affectation par copie.
       
       @param e L'écart à copier.
     */
    Transaction::Ecart & operator=(const Transaction::Ecart & e);
    /**
       @brief Affectation standard (sans indice).

       @param cartes Les cartes à écarter.
     */
    Transaction::Ecart & operator=(const std::vector<Carte> & cartes);
    /**
       @brief Retourne l'écart.
       
       @return L'écart, ou rien.
     */
    const Option<std::vector<Carte> > & obtenir() const;
    /**
       @brief Retourne l'indice 1.
       
       @return Un tableau de Carte, ou rien.
     */
    Option<std::vector<Carte> > indice1() const;
    /**
       @brief Retourne l'indice 2.
       
       @return Un tableau de Carte, ou rien.
     */
    Option<std::vector<Carte> > indice2() const;
    
  private:
    Option<std::vector<Carte> > m_ecart;
    std::vector<Option<std::vector<Carte> > > m_indices;
  };
  /**
     @brief Classe permettant de stocker les informations pour un
     jeu de carte.
     
     Cette classe copie la carte donnée.
   */
  class Jeu
  {
  public:
    /**
       @brief Constructeur par défaut.
     */
    Jeu();
    /**
       @brief Constructeur de copie.
       @param j Le jeu (transaction) à copier.
     */
    Jeu(const Transaction::Jeu & j);
    /**
       @brief Constructeur standard.
       
       @param c La carte à jouer.
     */
    Jeu(const Carte & c);
    /**
       @brief Affectation par copie.
       
       @param j Le jeu à copier.
     */
    Transaction::Jeu & operator=(const Transaction::Jeu & j);
    /**
       @brief Affectation standard.

       @param c La carte à jouer.
     */
    Transaction::Jeu & operator=(const Carte & c);
    /**
       @brief Retourne la carte jouée.
       
       @return La carte, ou rien.
     */
    const Option<Carte> & obtenir() const;
    
  private:
    Option<Carte> m_carte;
  };
  /**
     @brief Constructeur par défaut.
   */
  Transaction();
  /**
     @brief Constructeur de copie.
     
     @param t La transaction à copier.
   */
  Transaction(const Transaction & t);
  /**
     @brief Constructeur d'enchère.
     
     @param t L'enchère à représenter.
   */
  Transaction(const Transaction::Enchere & t);
  /**
     @brief Constructeur d'appel.
     
     @param t L'appel à représenter.
   */
  Transaction(const Transaction::Appel & t);
  /**
     @brief Constructeur d'écart.
     
     @param t L'écart à représenter.
   */
  Transaction(const Transaction::Ecart & t);
  /**
     @brief Constructeur de jeu d'une carte.
     
     @param t Le jeu de carte à représenter.
   */
  Transaction(const Transaction::Jeu & t);
  /**
     @brief Copie.

     @param t La transaction à copier.
     @return Une transaction valide.
   */
  Transaction & operator=(const Transaction & t);
  /**
     @brief Copie d'enchère.
     
     @param t L'enchère à représenter.
     @return Une transaction valide.
   */
  Transaction & operator=(const Transaction::Enchere & t);
  /**
     @brief Copie d'appel.
     
     @param t L'appel à représenter.
     @return Une transaction valide.
   */
  Transaction & operator=(const Transaction::Appel & t);
  /**
     @brief Copie d'écart.
     
     @param t L'écart à représenter.
     @return Une transaction valide.
   */
  Transaction & operator=(const Transaction::Ecart & t);
  /**
     @brief Copie de jeu d'une carte.
     
     @param t Le jeu de carte à représenter.
     @return Une transaction valide.
   */
  Transaction & operator=(const Transaction::Jeu & t);
  /**
     @brief Teste si la transaction est une enchère.
     
     @return Une enchère de transaction, ou rien.
   */
  const Option<Transaction::Enchere> & enchere() const;
  /**
     @brief Teste si la transaction est un appel.
     
     @return Un appel de transaction, ou rien.
   */
  const Option<Transaction::Appel> & appel() const;
  /**
     @brief Teste si la transaction est un écart.
     
     @return Un écart de transaction, ou rien.
   */
  const Option<Transaction::Ecart> & ecart() const;
  /**
     @brief Teste si la transaction est un jeu d'une carte.
     
     @return Un jeu de carte (transaction), ou rien.
   */
  const Option<Transaction::Jeu> & jeu() const;
private:
  
  Option<Transaction::Enchere> m_enchere;
  Option<Transaction::Appel> m_appel;
  Option<Transaction::Ecart> m_ecart;
  Option<Transaction::Jeu> m_jeu;
};
#endif
