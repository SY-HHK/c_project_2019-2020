#include <stdlib.h>
#include <gtk/gtk.h> //compiler: `pkg-config gtk+-3.0 --cflags` & linker: `pkg-config gtk+-3.0 --libs`
//#include <mysql/mysql.h> //linker : -lmysqlclient
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

#include <stdio.h>
#include <stdlib.h>
#define PORT 1234

int main(int argc,char **argv)
{
char username[50] = "";
char password[50] = "";
int server_connect(GtkWidget *widget, GtkWidget *entry_username, char *username,char *password);
GtkWidget *connexion_window = NULL;
GtkWidget *cancel_button = NULL;
GtkWidget *connection_button = NULL;
GtkWidget *entry_username = NULL;
      GtkBuilder *builder = NULL;
      GError *error = NULL;
      gchar *filename = NULL;
      /* Initialisation de la librairie Gtk. */
      gtk_init(&argc, &argv);

      /* Ouverture du fichier Glade de la fenêtre principale */
      builder = gtk_builder_new();

      /* Création du chemin complet pour accéder au fichier test.glade. */
      /* g_build_filename(); construit le chemin complet en fonction du système */
      /* d'exploitation. ( / pour Linux et \ pour Windows) */
      filename =  g_build_filename ("../interfaces_glade/projet_c_connexion.glade", NULL);

          /* Chargement du fichier test.glade. */
      gtk_builder_add_from_file (builder, filename, &error);
      g_free (filename);
      if (error)
      {
        gint code = error->code;
        g_printerr("%s\n", error->message);
        g_error_free (error);
        return code;
      }

        /* Récupération du pointeur de la fenêtre principale */
      connexion_window = GTK_WIDGET(gtk_builder_get_object (builder, "window_connexion"));
      cancel_button = GTK_WIDGET(gtk_builder_get_object (builder, "button_cancel"));
      connection_button = GTK_WIDGET(gtk_builder_get_object (builder, "button_connect"));
      entry_username = GTK_WIDGET(gtk_builder_get_object(builder, "entry_username"));

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
        }
        else {
            printf("Impossible de se connecter\n");
        }

        /* On ferme la socket précédemment ouverte */
        closesocket(sock);

        #if defined (WIN32)
            WSACleanup();
        #endif
    }
    //fin socket


      /* Affectation du signal "destroy" à la fonction gtk_main_quit(); pour la */
      /* fermeture de la fenêtre. */
      g_signal_connect (G_OBJECT (cancel_button), "clicked", (GCallback)gtk_main_quit, NULL);

      //envoie d'une demande de connexion
      g_signal_connect (G_OBJECT (connection_button), "clicked", (GCallback)server_connect, entry_username);



      /* Affichage de la fenêtre principale. */
      gtk_widget_show_all (connexion_window);

      gtk_main();

      return 0;
}


int server_connect(GtkWidget *widget, GtkWidget *entry_username, char *username, char *password) {

//send(sock,username,strlen(username),MSG_CONFIRM);
//send(sock,password,strlen(password),MSG_CONFIRM);
const gchar *entry_text;
entry_text = gtk_entry_get_text(GTK_ENTRY (entry_username));
printf("test %s \n",entry_text);



return 0;
}