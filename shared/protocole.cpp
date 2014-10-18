#include "protocole.hpp"

//Les premières fonctions sont là pour lire la partie spécifique des
//messages. Celle appelée sera déterminée en fonction du premier octet.

bool lire_erreur_protocole(QDataStream & in, 
			   struct Msg_erreur_protocole & erreur_protocole)
{
  //Rien à remplir dans un Msg_erreur_protocole
  return in.status() == QDataStream::Ok;
}

void ecrire_erreur_protocole(struct Msg_erreur_protocole 
			     const & erreur_protocole,
			     QDataStream & out)
{
}

bool lire_refuse(QDataStream & in, 
		 struct Msg_refuse & refuse)
{
  //Idem
  return in.status() == QDataStream::Ok;
}

void ecrire_refuse(struct Msg_refuse const &  refuse,
		   QDataStream & out)
{
}

bool lire_numero(QDataStream & in,
		 struct Msg_numero & numero)
{
  quint8 num;
  in>>num;
  numero.n = num;
  return in.status() == QDataStream::Ok;
}

void ecrire_numero(struct Msg_numero const & numero,
		   QDataStream & out)
{
  out<<(quint8)numero.n;
}

bool lire_distribution(QDataStream & in, 
		       struct Msg_distribution & distribution)
{
  quint8 num;
  for(int i = 0 ; i < 15 ; i++)
    {
      in>>num;
      distribution.cartes[i] = num;
    }
  return in.status() == QDataStream::Ok;
}

void ecrire_distribution(struct Msg_distribution const & distribution,
			 QDataStream & out)
{
  for(int i = 0 ; i < 15 ; i ++)
    {
      out<<(quint8)distribution.cartes[i];
    }
}

bool lire_decision(QDataStream & in,
		   struct Msg_decision & decision)
{
  quint8 niv;
  in>>niv;
  decision.niveau = niv;
  return in.status() == QDataStream::Ok;
}

void ecrire_decision(struct Msg_decision const & decision,
		     QDataStream & out)
{
  out<<(quint8)decision.niveau;
}

bool lire_contrat(QDataStream & in,
		  struct Msg_contrat & contrat)
{
  quint8 niv;
  in>>niv;
  contrat.niveau = niv;
  return in.status() == QDataStream::Ok;
}

void ecrire_contrat(struct Msg_contrat const & contrat,
		    QDataStream & out)
{
  out<<(quint8)contrat.niveau;
}

bool lire_appel(QDataStream & in,
		struct Msg_appel & appel)
{
  return in.status() == QDataStream::Ok;
}

void ecrire_appel(struct Msg_appel const & appel,
		  QDataStream & out)
{
}

bool lire_appeler(QDataStream & in,
		  struct Msg_appeler & appeler)
{
  quint8 carte;
  in>>carte;
  appeler.carte = carte;
  return in.status() == QDataStream::Ok;
}

void ecrire_appeler(struct Msg_appeler const & appeler,
		    QDataStream & out)
{
  out<<(quint8)appeler.carte;
}

bool lire_contrat_final(QDataStream & in,
			struct Msg_contrat_final & contrat_final)
{
  quint8 preneur, niv, appel;
  in>>preneur;
  in>>niv;
  in>>appel;
  contrat_final.preneur = preneur;
  contrat_final.niveau = niv;
  contrat_final.appel = appel;
  return in.status() == QDataStream::Ok;
}

void ecrire_contrat_final(struct Msg_contrat_final const & contrat_final,
			  QDataStream & out)
{
  out<<(quint8)contrat_final.preneur;
  out<<(quint8)contrat_final.niveau;
  out<<(quint8)contrat_final.appel;
}

bool lire_chien(QDataStream & in,
		struct Msg_chien & chien)
{
  quint8 carte;
  for(int i = 0 ; i < 3 ; i++)
    {
      in>>carte;
      chien.chien[i] = carte;
    }
  return in.status() == QDataStream::Ok;
}

void ecrire_chien(struct Msg_chien const & chien,
		  QDataStream & out)
{
  for(int i = 0 ; i < 3 ; i++)
    {
      out<<(quint8)chien.chien[i];
    }
}

bool lire_ecart(QDataStream & in,
		struct Msg_ecart & ecart)
{
  quint8 carte;
  for(int i = 0 ; i < 3 ; i++)
    {
      in>>carte;
      ecart.ecart[i] = carte;
    }
  return in.status() == QDataStream::Ok;
}

void ecrire_ecart(struct Msg_ecart const & ecart,
		  QDataStream & out)
{
  for(int i = 0 ; i < 3 ; i ++)
    {
      out<<(quint8)ecart.ecart[i];
    }
}

bool lire_jeu(QDataStream & in,
	      struct Msg_jeu & jeu)
{
  return in.status() == QDataStream::Ok;
}

void ecrire_jeu(struct Msg_jeu const & jeu,
		QDataStream & out)
{
}

bool lire_requete(QDataStream & in,
		  struct Msg_requete & requete)
{
  quint8 carte;
  in>>carte;
  requete.carte = carte;
  return in.status() == QDataStream::Ok;
}

void ecrire_requete(struct Msg_requete const & requete,
		    QDataStream & out)
{
  out<<(quint8)requete.carte;
}

bool lire_carte(QDataStream & in,
		struct Msg_carte & carte)
{
  quint8 carte_lue;
  in>>carte_lue;
  carte.carte = carte_lue;
  return in.status() == QDataStream::Ok;
}

void ecrire_carte(struct Msg_carte const & carte,
		  QDataStream & out)
{
  out<<(quint8)carte.carte;
}

bool lire_pli(QDataStream & in,
	      struct Msg_pli & pli)
{
  quint8 j;
  in>>j;
  pli.joueur = j;
  return in.status() == QDataStream::Ok;
}

void ecrire_pli(struct Msg_pli const & pli,
		QDataStream & out)
{
  out<<(quint8)pli.joueur;
}

bool lire_resultat(QDataStream & in,
		   struct Msg_resultat & resultat)
{
  quint16 points;
  for(int i = 0 ; i < 5 ; i ++)
    {
      in>>points;
      resultat.resultats[i] = points;
    }
  return in.status() == QDataStream::Ok;
}

void ecrire_resultat(struct Msg_resultat const & resultat,
		     QDataStream & out)
{
  for(int i = 0 ; i < 5 ; i ++)
    {
      out<<(quint16)resultat.resultats[i];
    }
}

//Fonctions générale :

bool lire(QDataStream & in, struct Message & m)
{
  quint8 type;
  in>>type;
  bool lu = false;
  m.compris = true;
  if(in.status() == QDataStream::Ok)
    {
      m.type = type;
      switch(type)
	{
	case ERREUR_PROTOCOLE:
	  //C'est moi qui ai fait une erreur de protocole la dernière fois,
	  //le serveur me le signale
	  lu = lire_erreur_protocole(in, m.m.erreur_protocole);
	  break;
	case REFUSE:
	  lu = lire_refuse(in, m.m.refuse);
	  break;
	case NUMERO:
	  lu = lire_numero(in, m.m.numero);
	  break;
	case DISTRIBUTION:
	  lu = lire_distribution(in, m.m.distribution);
	  break;
	case DECISION:
	  lu = lire_decision(in, m.m.decision);
	  break;
	case CONTRAT:
	  lu = lire_contrat(in, m.m.contrat);
	  break;
	case APPEL:
	  lu = lire_appel(in, m.m.appel);
	  break;
	case APPELER:
	  lu = lire_appeler(in, m.m.appeler);
	  break;
	case CONTRAT_FINAL:
	  lu = lire_contrat_final(in, m.m.contrat_final);
	  break;
	case CHIEN:
	  lu = lire_chien(in, m.m.chien);
	  break;
	case ECART:
	  lu = lire_ecart(in, m.m.ecart);
	  break;
	case JEU:
	  lu = lire_jeu(in, m.m.jeu);
	  break;
	case REQUETE:
	  lu = lire_requete(in, m.m.requete);
	  break;
	case CARTE:
	  lu = lire_carte(in, m.m.carte);
	  break;
	case PLI:
	  lu = lire_pli(in, m.m.pli);
	  break;
	case RESULTAT:
	  lu = lire_resultat(in, m.m.resultat);
	  break;
	default:
	  // Je n'ai pas compris le message du serveur. Je peux si je le 
	  // souhaite enoyer au serveur un message de type "erreur_protocole".
	  break;
	}
    }
  m.compris = lu;
  return lu;
}

void ecrire(struct Message const & m, QDataStream & out)
{
  out<<(quint8)m.type;
  switch(m.type)
    {
    case ERREUR_PROTOCOLE:
      ecrire_erreur_protocole(m.m.erreur_protocole, out);
      break;
    case REFUSE:
      ecrire_refuse(m.m.refuse, out);
      break;
    case NUMERO:
      ecrire_numero(m.m.numero, out);
      break;
    case DISTRIBUTION:
      ecrire_distribution(m.m.distribution, out);
      break;
    case DECISION:
      ecrire_decision(m.m.decision, out);
      break;
    case CONTRAT:
      ecrire_contrat(m.m.contrat, out);
      break;
    case APPEL:
      ecrire_appel(m.m.appel, out);
      break;
    case APPELER:
      ecrire_appeler(m.m.appeler, out);
      break;
    case CONTRAT_FINAL:
      ecrire_contrat_final(m.m.contrat_final, out);
      break;
    case CHIEN:
      ecrire_chien(m.m.chien, out);
      break;
    case ECART:
      ecrire_ecart(m.m.ecart, out);
      break;
    case JEU:
      ecrire_jeu(m.m.jeu, out);
      break;
    case REQUETE:
      ecrire_requete(m.m.requete, out);
      break;
    case CARTE:
      ecrire_carte(m.m.carte, out);
      break;
    case PLI:
      ecrire_pli(m.m.pli, out);
      break;
    case RESULTAT:
      ecrire_resultat(m.m.resultat, out);
      break;
    default:
      break;
    }
}
