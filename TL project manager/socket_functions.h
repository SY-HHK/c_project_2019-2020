/*
29/12/2019
Internet functions using sockets for TL PORJECT MANAGER by HHK
*/
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#if defined (WIN32)
    #include <winsock2.h>
    typedef int socklen_t;
#elif defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif
#define PORT 1234

//init the socket and the connection to the server
SOCKET server_init();

//close the socket
void close_socket(SOCKET sock);

//Send logins to the server
  struct connection_infos { GtkWidget *entry_username;
                            GtkWidget *entry_password;
                            SOCKET sock; };
  struct connection_infos infos;

void server_connect(GtkWidget *widget, struct connection_infos *infos);
//%%%%%%%%%%%%%%%%%%%%


