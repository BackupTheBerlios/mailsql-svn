#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include "socketfactory.h"

//#define VIVANT 1
//#define MORT 0
/*
typedef struct{
  int sock_id;
  int state; 
  struct_sock *next;
  struct_sock *back;
} struct_sock
*/

/**la fonction principale
 *la fonction mere
 */

int
main (int argc, char **argv)
{
  //struct_sock test;
  char buf[255];
  fd_set readsocks;
  int readysock = 0;


  memset (buf, 0, 255);
  int main_sock;		//declaration du socket pricipal qui ecoute
  if (!(main_sock = server_socket (2222)))
    {
      perror ("impossible de cree le socket");
      exit (-1);
      return -1;
    }

  //while(1){
  //  FD_ZERO(&readsocks);
  //}
  int socky = sock_listen (main_sock);
  sock_write (socky, "plop\n");
  return 0;
}
