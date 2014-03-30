#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

/* Sa mère ! ce truc marche !
*/


int main (int argc, char *argv[]) {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }

    if (argc < 2)
    {
        fprintf (stderr, "Too few arguments : %s fqdn \nBitch !\n", argv[0]);
        exit(errno);
    }

    struct hostent *hostinfo = NULL;
    SOCKADDR_IN sin = { 0 }; /* initialise la structure avec des 0 */
    const char *hostname = argv[1]; 

    hostinfo = gethostbyname(hostname); /* on récupère les informations de l'hôte auquel on veut se connecter */
    
    fprintf (stdout, "Résolution DNS dans ta face!\n");
    if (hostinfo == NULL) /* l'hôte n'existe pas */
    {
        fprintf (stderr, "Unknown host %s.\n", hostname);
        exit(EXIT_FAILURE);
    } else {
        fprintf (stdout, "Say my number, bitch : %d.%d.%d.%d\n", 
hostinfo->h_addr_list[0][0],
hostinfo->h_addr_list[0][1],
hostinfo->h_addr_list[0][2],
hostinfo->h_addr_list[0][3]
);
    }

    sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr; /* l'adresse se trouve dans le champ h_addr de la structure hostinfo */
    sin.sin_port = htons(80); /* on utilise htons pour le port */
    sin.sin_family = AF_INET;

    if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        perror("connect()");
        fprintf (stdout, "Ping!\n");
        exit(errno);
    }
    fprintf (stdout, "Ping!\n");


    closesocket(sock);
}
