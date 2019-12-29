/*
29/12/2019
graphic functions for TL PROJECT MANAGER by HHK
*/
#include "socket_functions.h"
#include "graphics_functions.h"

GtkWidget *connection_window(void *argc, void *argv, SOCKET sock) {

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
        //return code;
      }

        /* Récupération du pointeur de la fenêtre principale */
      GtkWidget *connexion_window = GTK_WIDGET(gtk_builder_get_object (builder, "window_connexion"));
      GtkWidget *cancel_button = GTK_WIDGET(gtk_builder_get_object (builder, "button_cancel"));
      GtkWidget *connection_button = GTK_WIDGET(gtk_builder_get_object (builder, "button_connect"));
      GtkWidget *entry_username = GTK_WIDGET(gtk_builder_get_object(builder, "entry_username"));
      GtkWidget *entry_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_password"));

        infos.entry_username = entry_username;
        infos.entry_password = entry_password;
        infos.sock = sock;

      /* Affectation du signal "destroy" à la fonction gtk_main_quit(); pour la */
      /* fermeture de la fenêtre. */
      g_signal_connect (G_OBJECT (cancel_button), "clicked", (GCallback)gtk_main_quit, NULL);

      //envoie d'une demande de connexion
      g_signal_connect (G_OBJECT (connection_button), "clicked", (GCallback)server_connect, &infos);


      /* Affichage de la fenêtre principale. */
      return connexion_window;

}
