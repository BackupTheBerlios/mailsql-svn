#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xmlparser.h"

/**partie pour parser les tag <db></db>
 *fonction ce chargeant de parser cette partie specifique 
 *dosposant de plusieur malloc afin de remplir le struct
 *@TODO cleaner cette partie
 */

int
parse_db (xmlDocPtr doc, xmlNodePtr cur, struct config *conf_struct)
{
  xmlChar *key; //pour stocker la valueur entre tag

  cur = cur->xmlChildrenNode; //on plonge 1 noeud plus bas que <db>
  
  while (cur != NULL)
    {
      //si tag <connection></connection>
      if ((!xmlStrcmp (cur->name, (const xmlChar *) "connection")))
	{
	  /*key est malloc é donc fo la xmlFree, 
	   *on recupe la valeur du noeud <connection></connection>
	   */
	  key =xmlNodeListGetString (doc, cur->xmlChildrenNode, 1);

	  //on malloc pour eviter les pb
	  conf_struct->connection = malloc (sizeof (xmlChar) * strlen (key));

#ifdef DEBUG
	  printf ("keyword: %s sizeof:%d\n", key, strlen (key));
#endif
	  //on copie le resultat dans le menbre approprié
	  memcpy (conf_struct->connection, (char *) key,
		  strlen (key) * sizeof (xmlChar));
	  //xmlFree pour vider du malloc
	  xmlFree (key);
	}

      //si tag <user></user>
      if ((!xmlStrcmp (cur->name, (const xmlChar *) "user")))
	{
	  /*key est malloc é donc fo la xmlFree, 
	   *on recupe la valeur du noeud <connection></connection>
	   */
	  key =xmlNodeListGetString (doc, cur->xmlChildrenNode, 1);

#ifdef DEBUG
	  printf ("keyword: %s\n", key);
#endif

	  //on malloc pour eviter les pb
	  conf_struct->user = malloc (sizeof (char) * strlen (key));
	  //on copie le resultat dans le menbre approprié
	  memcpy (conf_struct->user, (char *) key,
		  sizeof (key) * strlen (key));
	  //xmlFree pour vider du malloc
	  xmlFree (key);
	}

      //si tag <password></password>
      if ((!xmlStrcmp (cur->name, (const xmlChar *) "password")))
	{

	  /*key est malloc é donc fo la xmlFree, 
	   *on recupe la valeur du noeud <connection></connection>
	   */
	  key = xmlNodeListGetString (doc, cur->xmlChildrenNode, 1);
	  
	  //on malloc pour eviter les pb
	  conf_struct->password = malloc (sizeof (key) * strlen (key));
	  //on copie le resultat dans le menbre approprié
	  memcpy (conf_struct->password, (char *) key,
		  sizeof (key) * strlen (key));

#ifdef DEBUG
	  printf ("keyword: %s\n", key);
#endif
	  
	  //xmlFree pour vider du malloc
	  xmlFree (key);
	}
      //on saute au noeud suivant
      cur = cur->next;
    }
  return 1;
}


/**fonction de parsing
 *cette fonction parser un fichier xml et sotcke le resultat dans une structure
 *de configuration
 */

struct config *
xmlparse (char *filename)
{
  struct config *conf_struct;
  conf_struct = malloc (sizeof (struct config));
  //un pointeur vers le doculents
  xmlDocPtr doc;
  //pointeur d une node
  xmlNodePtr cur;
  //on parse le doc
  doc = xmlParseFile (filename);
  //si doc vide bye
  if (doc == NULL)
    {
      fprintf (stderr, "Document not parsed successfully. \n");
      return NULL;
    }

  //on recupere l element  racine
  cur = xmlDocGetRootElement (doc);
  //si c'est vide alors c etait un doc vide
  if (cur == NULL)
    {
      fprintf (stderr, "empty document\n");
      //liberation de la memoire
      xmlFreeDoc (doc);
      return NULL;
    }

  //on verifie que c un document de conf
  if (xmlStrcmp (cur->name, (const xmlChar *) "mailsql"))
    {
      fprintf (stderr, "document of the wrong type, root node != story");
      xmlFreeDoc (doc);
      return NULL;
    }

  //on commence la ballade au pays des merveille

  //on descend d un cran pour recupe le premier noeud
  cur = cur->xmlChildrenNode;
  //on commence les recherche
  while (cur != NULL)
    {
      //printf ("%s\n", cur->name);
      if ((!xmlStrcmp (cur->name, (const xmlChar *) "db")))
	{
	  parse_db (doc, cur, conf_struct);
	}
      cur = cur->next;
    }

  //on libere lme doc de la memoire 
  xmlFreeDoc (doc);
  xmlCleanupParser ();
  return conf_struct;
}

/**libere la memoire de conf
 *on libere d abord les menbre de la structure 
 *puis la strucuture elle meme
 */

int
freeconf (struct config *conf)
{
  //on free() tout les menbre pour eviter les fuite
  free (conf->password);
  free (conf->user);
  free (conf->connection);
  free (conf);
}



#ifdef DEBUG
int
main (int argc, char **argv)
{
  struct config *newconf;
  newconf = (struct config *) malloc (sizeof (struct config));
  newconf = xmlparse ("conf.xml");
  //free (newconf);
  printf ("connection:%s\nuser:%s\npass:%s\n", newconf->connection,
	  newconf->user, newconf->password);
  //xmlFree(newconf->password);
  //xmlFree(newconf->user);
  //xmlFree(newconf->connection);
  freeconf (newconf);
  while (1)
    {
    }
  return 0;
}
#endif 
