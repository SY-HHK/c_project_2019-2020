/*
29/12/2019
Internet functions using sockets for TL PORJECT MANAGER by HHK
*/
#include "socket_functions.h"
#include "graphics_functions.h"


SOCKET server_init() {

//création d'un socket
    #if defined (WIN32)
        WSADATA WSAData;
        int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
    #else
        int erreur = 0;
    #endif

    SOCKET sock;
    SOCKADDR_IN sin;

    if(!erreur)
    {
        /* Création de la socket */
        sock = socket(AF_INET, SOCK_STREAM, 0);

        /* Configuration de la connexion */
        sin.sin_addr.s_addr = inet_addr("51.75.133.145");
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);

        /* Si le client arrive à se connecter */
        if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR) {
        return sock;
        }
        else {
            printf("Impossible de se connecter\n");
            return 0;
        }

    }
    //fin socket

}


void server_connect(GtkWidget *widget, struct connection_infos *infos) {

const gchar *username;
const gchar *password;
char answer[10];
char logins[100] = "login:";
username = gtk_entry_get_text(GTK_ENTRY (infos->entry_username));
password = gtk_entry_get_text(GTK_ENTRY (infos->entry_password));
strcat(logins,username);
strcat(logins,"&&&");
strcat(logins,password);
send(infos->sock,logins,strlen(logins),NULL);
recv(infos->sock,answer,1,NULL);
if (answer[0] == '1') {
    gtk_window_close (infos->window);
    printf("Good logins !");
    gtk_widget_show_all (main_window(infos->argc, infos->argv, infos->sock));
}
else {
    gtk_main_quit();
    printf("Wrong logins !");
}

}


void close_socket(SOCKET sock) {

/* On ferme la socket précédemment ouverte */
        closesocket(sock);
        #if defined (WIN32)
            WSACleanup();
        #endif

}
