#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>
#include "socketfactory.h"

/** \file socketfactory.c
 *  \brief Fonction de creation de socket
 *
 *   permet de mapper divers fonction des socket
 * afin d en simplifier l utilisation
*/

/** strucutre de manipulation de chaine
 *strucutre permantant de manipuler des chaine assez facilement grace
 *a la taille definie
 */

/**
  *fonction de creation de socket
  *permet de crée un socket pouvant etre asynchrone
  *@param port un int d port
  *@return Un socket bindé
  */
int
server_socket (int port)
{
  int sock;			//le socket
  int optval = -1;		//valeur d option
  struct sockaddr_in sockname;

  if ((sock = socket (PF_INET, SOCK_STREAM, 0)) < 0)
    {
      return -1;
    }

  setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (int));

#ifdef NO_BLOCK
  if (!(fcntl (sock, F_SETFL, O_NONBLOCK)))
    {
      return -1;
    }
#endif

  //on met a zero par securité
  memset ((char *) &sockname, 0, sizeof (struct sockaddr_in));

  //on remplis la structure
  sockname.sin_family = AF_INET;
  sockname.sin_port = htons (port);
  sockname.sin_addr.s_addr = htonl (INADDR_ANY);

  //on bind
  if (bind (sock, (struct sockaddr *) &sockname, sizeof (struct sockaddr_in))
      < 0)
    {
      return -1;
    }

  if (listen (sock, 100) < 0)
    {
      return -1;
    }

  //on revoie le socket
  return sock;
}

/**met en mode listen le socket
 *permet de faire ecouter un socket puis de recup un nouveau socket 
 *branche sur l appelant
 *@param main_sock necessite en entrée un socket
 *@return un nouveau socket dont la connexion est etablie
 */
int
sock_listen (int main_sock)
{
  int sock;

  if ((sock = accept (main_sock, NULL, 0)) < 0)
    {
      if (errno == EINTR)
	{
	  shutdown (main_sock, SHUT_RDWR);
	  close (main_sock);
	  return -1;
	}
      else
	{
	  return -1;
	}
    }
  return sock;
}

/** fonction d ecriture sur un socket **securise**
 *donc permet d ecrire sur un socket de facon simple et rapide pour des
 *char* dont la taille est determiner par strlen()
 *\param sock necessite un socket
 *\param text est le char* a transmettre
 *\return la longueur de text reussi a envoyer
 */
int
sock_write (int sock, char *text)
{
  int length = 0;		//longueur du texte
  int sended = 0;		//char* envoyer

  length = strlen (text);	//on recupere la longueur du texte

  sended = send (sock, text, length, 0);

  return sended;
}


/**rendre les socket non bloquant
 *on rend les socket passé en argument non bloquant 
 *grace a un appel a fcntl
 *\param sock socket a rendre non bloquant
 *\return 1 success 0 fail
 */
int
sock_setnoblock (int sock)
{
  if (!(fcntl (sock, F_SETFL, O_NONBLOCK)))
    {
      return 0;
    }
  else
    {
      return 1;
    }
}

/** Fonction de lecture simplifié
 *fonction de lecture simplifié permantant de se passer de certain arguments
 *@param sock le socket ou on lis
 *@param buf le buffer de reception des donnée
 *@return 0 succes -1 erreur
 */
int
sock_read (int sock, char *buf, int len)
{
  int count = 0;
  int pos = 0;			//indique la postion sur la lecture
  char c;
  buf = (char *) malloc (sizeof (char) * len);

  c = '\0';
  while ((c != '\n') || (count == len))
    {
      int l = read (sock, &c, sizeof (char));
      if (l != sizeof (char))
	{
	  buf[pos] = '\0';
	  return -1;
	}
      buf[pos] = c;
      pos++;
      count++;
    }
  buf[pos] = '\0';
  return 0;
}

ssize_t
ls_read (int sock, void *buffer, size_t len, int mode)
{
  int len_read = 0;
  void *p = buffer;
  while ((p - buffer) < len)
    {
      len_read = read (sock, p, len - (p - buffer));
      if (len_read < 0)
	{
	  if (errno != EINTR)
	    {
	      return (len_read);
	    }
	}
      else if (len_read == 0)
	{
	  return (p - buffer);
	}
      else
	{
	  if (mode == 0)
	    {
	      return (p - buffer);
	    }
	  else
	    {
	      p += len_read;
	    }
	}
    }
  return (p - buffer);
}
