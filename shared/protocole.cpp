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

bool lire_prise(QDataStream & in,
		   struct Msg_prise & prise)
{
  quint8 niv;
  in>>niv;
  prise.niveau = niv;
  return in.status() == QDataStream::Ok;
}

void ecrire_prise(struct Msg_prise const & prise,
		     QDataStream & out)
{
  out<<(quint8)prise.niveau;
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

bool lire_atout(QDataStream & in, 
		struct Msg_atout & atout)
{
  quint8 carte;
  int i = 0;
  while(i < 3 && in.status() == QDataStream::Ok && !(in.atEnd()))
    {
      in>>carte;
      atout.cartes[i] = carte;
      i++;
    }
  atout.nombre = i;
  return in.status() == QDataStream::Ok;
}

void ecrire_atout(struct Msg_atout const & atout,
		  QDataStream & out)
{
  for(int i = 0 ; i < atout.nombre ; i++)
    {
      out<<(quint8)atout.cartes[i];
    }
}

bool lire_chelem(QDataStream & in, struct Msg_chelem & chelem)
{
  quint8 b;
  in>>b;
  chelem.demande = (b != 0);
  return in.status() == QDataStream::Ok;
}

void ecrire_chelem(struct Msg_chelem const & chelem,
		   QDataStream & out)
{
  out<<(quint8)(chelem.demande?1:0);
}

bool lire_jeu(QDataStream & in,
	      struct Msg_jeu & jeu)
{
  quint8 demandeur;
  in>>demandeur;
  jeu.chelem = demandeur;
  return in.status() == QDataStream::Ok;
}

void ecrire_jeu(struct Msg_jeu const & jeu,
		QDataStream & out)
{
  out<<(quint8)jeu.chelem;
}

bool lire_montrer_poignee(QDataStream & in,
			  struct Msg_montrer_poignee & montrer_poignee)
{
  quint8 atout;
  // On regarde si c'est plus qu'une simple poignée...
  for(int i = 0 ; i < 8 ; i++)
    {
      in>>atout;
      montrer_poignee.atouts[i] = atout;
    }
  if(in.atEnd() && in.status() == QDataStream::Ok)
    {
      montrer_poignee.taille = 8 ;
      return true;
    }
  // On regarde si c'est plus qu'une double poignée...
  for(int i = 8 ; i < 10 ; i++)
    {
      in>>atout;
      montrer_poignee.atouts[i] = atout;
    }
  if(in.atEnd() && in.status() == QDataStream::Ok)
    {
      montrer_poignee.taille = 10;
      return true;
    }
  //C'est peut-être une triple poignée...
  for(int i = 10 ; i < 13 ; i++)
    {
      in>>atout;
      montrer_poignee.atouts[i] = atout;
    }
  montrer_poignee.taille = 13;
  return (in.status() == QDataStream::Ok);
}

void ecrire_montrer_poignee(struct Msg_montrer_poignee const & montrer_poignee,
			    QDataStream & out)
{
  for(int i = 0 ; i < montrer_poignee.taille && i < 13 ; i++)
    {
      out<<(quint8)(montrer_poignee.atouts[i]);
    }
}

bool lire_poignee(QDataStream & in, struct Msg_poignee & poignee)
{
  quint8 atout;
  // On regarde si c'est plus qu'une simple poignée...
  for(int i = 0 ; i < 8 ; i++)
    {
      in>>atout;
      poignee.atouts[i] = atout;
    }
  if(in.atEnd() && in.status() == QDataStream::Ok)
    {
      poignee.taille = 8 ;
      return true;
    }
  // On regarde si c'est plus qu'une double poignée...
  for(int i = 8 ; i < 10 ; i++)
    {
      in>>atout;
      poignee.atouts[i] = atout;
    }
  if(in.atEnd() && in.status() == QDataStream::Ok)
    {
      poignee.taille = 10;
      return true;
    }
  //C'est peut-être une triple poignée...
  for(int i = 10 ; i < 13 ; i++)
    {
      in>>atout;
      poignee.atouts[i] = atout;
    }
  poignee.taille = 13;
  return (in.status() == QDataStream::Ok);
}

void ecrire_poignee(struct Msg_poignee const & poignee,
			    QDataStream & out)
{
  for(int i = 0 ; i < poignee.taille && i < 13 ; i++)
    {
      out<<(quint8)(poignee.atouts[i]);
    }
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
	case PRISE:
	  lu = lire_prise(in, m.m.prise);
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
	case ATOUT:
	  lu = lire_atout(in, m.m.atout);
	  break;
	case CHELEM:
	  lu = lire_chelem(in, m.m.chelem);
	  break;
	case JEU:
	  lu = lire_jeu(in, m.m.jeu);
	  break;
	case MONTRER_POIGNEE:
	  lu = lire_montrer_poignee(in, m.m.montrer_poignee);
	  break;
	case POIGNEE:
	  lu = lire_poignee(in, m.m.poignee);
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
    case PRISE:
      ecrire_prise(m.m.prise, out);
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
    case ATOUT:
      ecrire_atout(m.m.atout, out);
      break;
    case CHELEM:
      ecrire_chelem(m.m.chelem, out);
      break;
    case JEU:
      ecrire_jeu(m.m.jeu, out);
      break;
    case MONTRER_POIGNEE:
      ecrire_montrer_poignee(m.m.montrer_poignee, out);
      break;
    case POIGNEE:
      ecrire_poignee(m.m.poignee, out);
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
