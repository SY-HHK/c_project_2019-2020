/*
29/12/2019
graphic functions for TL PROJECT MANAGER by Louis & Tom
*/
#include "socket_functions.h"
#include "graphics_functions.h"

GtkWidget *connection_window(void *argc, void *argv, SOCKET sock) {

      GtkBuilder *builder = NULL;
      GError *error = NULL;
      gchar *filename = NULL;
      /* Initialisation de la librairie Gtk. */
      gtk_init(argc, argv);

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
      GtkWidget *connection_window = GTK_WIDGET(gtk_builder_get_object (builder, "window_connexion"));
      GtkWidget *cancel_button = GTK_WIDGET(gtk_builder_get_object (builder, "button_cancel"));
      GtkWidget *connection_button = GTK_WIDGET(gtk_builder_get_object (builder, "button_connect"));
      GtkWidget *entry_username = GTK_WIDGET(gtk_builder_get_object(builder, "entry_username"));
      GtkWidget *entry_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_password"));

        infos.entry_username = entry_username;
        infos.entry_password = entry_password;
        infos.sock = sock;
        infos.window = connection_window;
        infos.argc = &argc;
        infos.argv = &argv;

      /* Affectation du signal "destroy" à la fonction gtk_main_quit(); pour la */
      /* fermeture de la fenêtre. */
      g_signal_connect (G_OBJECT (cancel_button), "clicked", (GCallback)gtk_main_quit, NULL);
      g_signal_connect(G_OBJECT(connection_window),"destroy",(GCallback)gtk_main_quit, NULL);

      //envoie d'une demande de connexion
      g_signal_connect (G_OBJECT (connection_button), "clicked", (GCallback)server_connect, &infos);


      /* Affichage de la fenêtre principale. */
      return connection_window;

}



GtkWidget *main_window(void *argc, void *argv, SOCKET sock) {

      GtkBuilder *builder = NULL;
      GError *error = NULL;
      gchar *filename = NULL;
      /* Initialisation de la librairie Gtk. */
      gtk_init(argc, argv);

      /* Ouverture du fichier Glade de la fenêtre principale */
      builder = gtk_builder_new();

      /* Création du chemin complet pour accéder au fichier test.glade. */
      /* g_build_filename(); construit le chemin complet en fonction du système */
      /* d'exploitation. ( / pour Linux et \ pour Windows) */
      filename =  g_build_filename ("../interfaces_glade/projet_c_main_menu.glade", NULL);

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
      GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object (builder, "window_main_menu"));
      GtkWidget *entry_email_user_modify = GTK_WIDGET(gtk_builder_get_object(builder, "entry_email_user_modify"));
      GtkWidget *button_username_modify = GTK_WIDGET(gtk_builder_get_object(builder, "button_username_modify"));
      GtkWidget *button_project = GTK_WIDGET(gtk_builder_get_object(builder,"button_project"));

     infos.entry_email_user_modify = entry_email_user_modify;

     GtkWidget *entry_password_modify = GTK_WIDGET(gtk_builder_get_object(builder, "entry_password_modify"));
     GtkWidget *button_password_modify = GTK_WIDGET(gtk_builder_get_object(builder, "button_password_modify"));

     infos.entry_password_modify = entry_password_modify;

        g_signal_connect(G_OBJECT(main_window),"destroy",(GCallback)gtk_main_quit, NULL);

        g_signal_connect (G_OBJECT (button_username_modify), "clicked", (GCallback)change_email_user, &infos);

        g_signal_connect (G_OBJECT (button_password_modify), "clicked", (GCallback)change_password, &infos);

        g_signal_connect (G_OBJECT (button_project), "clicked", (GCallback)project_window, &infos);


      /* Affichage de la fenêtre principale. */
      return main_window;

}


GtkWidget *project_window(GtkWidget *widget, struct connection_infos *infos) {

      GtkBuilder *builder = NULL;
      GError *error = NULL;
      gchar *filename = NULL;
      /* Initialisation de la librairie Gtk. */
      gtk_init(infos->argc, infos->argv);

      /* Ouverture du fichier Glade de la fenêtre principale */
      builder = gtk_builder_new();

      /* Création du chemin complet pour accéder au fichier test.glade. */
      /* g_build_filename(); construit le chemin complet en fonction du système */
      /* d'exploitation. ( / pour Linux et \ pour Windows) */
      filename =  g_build_filename ("../interfaces_glade/projet_c_project_interface.glade", NULL);

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
      GtkWidget *project_window = GTK_WIDGET(gtk_builder_get_object (builder, "window_main"));
      GtkWidget *button_add_step = GTK_WIDGET(gtk_builder_get_object(builder, "button_add_step"));
      GtkWidget *fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
      GtkWidget *arrow;

      infos->project_window = project_window;

      g_signal_connect(G_OBJECT(project_window),"destroy",(GCallback)gtk_window_close, project_window);

      g_signal_connect(G_OBJECT(button_add_step),"clicked",(GCallback)new_step, &infos);

      strcpy(infos->project_file_name,"project_conf/test.txt");

      FILE *pf = fopen(infos->project_file_name,"r+");
        if (pf == 0) {
            printf("impossible de lire le fichier");
            return 0;
        };

    gint x = 400;
    gint y = 75;
    int step_index = 0;
    char new_step_finder[65] = "";
    while (feof(pf) == 0) {
        strcpy(new_step_finder,"");
        while ( strstr(new_step_finder,"new_step:") == NULL ) {
            fgets(new_step_finder,60,pf);
            if (feof(pf) != 0) break;
        }
        if (feof(pf) != 0) break;
        step_index++;
        //créer les étapes avec le nom et la date de fin

        if (step_index % 3 == 0) {
        y += 300;
        x = 100;
            //trait entre les deux
            arrow = gtk_button_new();
            gtk_widget_set_size_request(arrow,5,90);
            gtk_fixed_put(fixed,arrow,780,y-180);
            gtk_widget_show(arrow);
            //trait entre les deux
            arrow = gtk_button_new();
            gtk_widget_set_size_request(arrow,610,5);
            gtk_fixed_put(fixed,arrow,185,y-90);
            gtk_widget_show(arrow);
            //trait entre les deux
            arrow = gtk_button_new();
            gtk_widget_set_size_request(arrow,5,90);
            gtk_fixed_put(fixed,arrow,170,y-90);
            gtk_widget_show(arrow);
        }
        else {
            //trait entre les deux
            arrow = gtk_button_new();
            gtk_widget_set_size_request(arrow,140,5);
            gtk_fixed_put(fixed,arrow,x-145,y+50);
            gtk_widget_show(arrow);
        }
        //renomme le btn
        gtk_button_set_label(button_add_step, new_step_finder+9);

        //g_signal_connect(G_OBJECT(button_add_step),"clicked",(GCallback)modify_step, &infos);
        //nouveau btn
        button_add_step = gtk_button_new_with_label("New step");
        gtk_widget_set_size_request(button_add_step,150,120);
        gtk_fixed_put(fixed,button_add_step,x,y);
        gtk_widget_show(button_add_step);
        g_signal_connect(G_OBJECT(button_add_step),"clicked",(GCallback)new_step, &infos);

        x += 300;

    }
        fclose(pf);

      /* Affichage de la fenêtre principale. */
        gtk_widget_show_all(project_window);

}


GtkWidget *new_step(GtkWidget *widget, struct connection_infos *infos) {

GtkBuilder *builder = NULL;
      GError *error = NULL;
      gchar *filename = NULL;
      /* Initialisation de la librairie Gtk. */
      gtk_init(infos->argc, infos->argv);

      /* Ouverture du fichier Glade de la fenêtre principale */
      builder = gtk_builder_new();

      strcpy(infos->project_file_name,"project_conf/test.txt");

      FILE *pf = fopen(infos->project_file_name,"r+");
        if (pf == 0) {
            printf("impossible de lire le fichier");
            return 0;
        };

        char step_finder[65] = "";
        while ( strstr(step_finder,gtk_button_get_label(widget)) == NULL ) {
            fgets(step_finder,60,pf);
            if (feof(pf) != 0) break;

        }
        if (strstr(step_finder,gtk_button_get_label(widget))) {

        /* Création du chemin complet pour accéder au fichier test.glade. */
      /* g_build_filename(); construit le chemin complet en fonction du système */
      /* d'exploitation. ( / pour Linux et \ pour Windows) */
      filename =  g_build_filename ("../interfaces_glade/projet_c_modify_step.glade", NULL);

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

    GtkWidget *modify_step_window = GTK_WIDGET(gtk_builder_get_object(builder, "modify_step_window"));
    GtkWidget *cancel_button = GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));
    GtkWidget *confirm_button = GTK_WIDGET(gtk_builder_get_object(builder, "confirm_button"));
    GtkWidget *step_name_entry = GTK_WIDGET(gtk_builder_get_object(builder, "step_name_entry"));
    GtkWidget *step_end_entry = GTK_WIDGET(gtk_builder_get_object(builder, "step_end_entry"));
    GtkContainer *new_task_box = GTK_CONTAINER(gtk_builder_get_object(builder, "new_task_box"));
    GtkWidget *new_task_child_checkbox;
    GtkWidget *new_task_child_label;
    GtkContainer *new_task_child_box;

    gtk_entry_set_text(step_name_entry,step_finder+9);
    fseek(pf,1,SEEK_CUR);
    fgets(step_finder,60,pf);
    gtk_entry_set_text(step_end_entry,step_finder+8);

    /*while (strstr("",step_finder+6) == NULL) {

    GtkWidget *new_task_child_checkbox = gtk_check_button_new();
    GtkWidget *new_task_child_label = gtk_label_new(step_finder+6);
    GtkContainer *new_task_child_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,2);

    fseek(pf,1,SEEK_CUR);
    fgets(step_finder,60,pf);
    if (strstr(step_finder+5,"1")) gtk_toggle_button_set_active(new_task_child_checkbox,TRUE);
    fseek(pf,1,SEEK_CUR);

    gtk_container_add(new_task_child_box,new_task_child_checkbox);
    gtk_container_add(new_task_child_box,new_task_child_label);

    gtk_container_add(new_task_box,new_task_child_box);
    gtk_widget_show_all(new_task_child_box);

    } */

    fclose(pf);

    gtk_widget_show_all(modify_step_window);

    }
    else {

      /* Création du chemin complet pour accéder au fichier test.glade. */
      /* g_build_filename(); construit le chemin complet en fonction du système */
      /* d'exploitation. ( / pour Linux et \ pour Windows) */
      filename =  g_build_filename ("../interfaces_glade/projet_c_add_step.glade", NULL);

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

    GtkWidget *add_step_window = GTK_WIDGET(gtk_builder_get_object(builder, "add_step_window"));
    GtkWidget *cancel_button = GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));
    GtkWidget *confirm_button = GTK_WIDGET(gtk_builder_get_object(builder, "confirm_button"));
    GtkWidget *step_name_entry = GTK_WIDGET(gtk_builder_get_object(builder, "step_name_entry"));
    GtkWidget *step_end_entry = GTK_WIDGET(gtk_builder_get_object(builder, "step_end_entry"));
    GtkWidget *new_task_button = GTK_WIDGET(gtk_builder_get_object(builder, "new_task_button"));
    GtkWidget *new_task_entry = GTK_WIDGET(gtk_builder_get_object(builder, "new_task_entry"));
    GtkContainer *new_task_box = GTK_CONTAINER(gtk_builder_get_object(builder, "new_task_box"));

    task.new_task_entry = new_task_entry;
    task.new_task_box = new_task_box;
    task.task_number = 0;

    step.add_step_window = add_step_window;
    step.step_name = step_name_entry;
    step.step_end = step_end_entry;

    g_signal_connect(G_OBJECT(cancel_button),"clicked",(GCallback)gtk_window_close, add_step_window);
    g_signal_connect(G_OBJECT(confirm_button),"clicked",(GCallback)write_step, &step);//fonction qui écrira dans le fichier
    g_signal_connect(G_OBJECT(new_task_button),"clicked",(GCallback)new_task, &task);//fonction qui ajoutera la tache dans add_step_window

    gtk_widget_show_all(add_step_window);

    }
}


GtkWidget *new_task(GtkWidget *button_new_task, struct task_structure *task) {

    GtkWidget *new_task_child_checkbox = gtk_check_button_new();
    GtkWidget *new_task_child_label = gtk_label_new(gtk_entry_get_text(GTK_ENTRY (task->new_task_entry)));
    GtkContainer *new_task_child_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,2);

    gtk_container_add(new_task_child_box,new_task_child_checkbox);
    gtk_container_add(new_task_child_box,new_task_child_label);

    gtk_container_add(task->new_task_box,new_task_child_box);
    gtk_widget_show_all(new_task_child_box);

    strcpy(step.task_description[task->task_number],gtk_label_get_text(GTK_LABEL (new_task_child_label)));
    step.task_checkbox[task->task_number] = new_task_child_checkbox;
    task->task_number ++;

}

void write_step(GtkWidget *confirm_button, struct step_structure *step) {

FILE *pf = fopen("project_conf/test.txt","r+");
if (pf != 0) {
    fseek(pf,0,SEEK_END);
    fprintf(pf,"new_step:%s\n",gtk_entry_get_text(GTK_ENTRY (step->step_name)));
    fprintf(pf,"step_end:%s\n",gtk_entry_get_text(GTK_ENTRY (step->step_end)));
    for(int i = 0; i < 10; i++) {
        fprintf(pf,"task%d:%s\n",i,step->task_description[i]);
        if (gtk_toggle_button_get_active(step->task_checkbox[i]))
        fputs("done:1\n",pf);
        else fputs("done:0\n",pf);
    }
    fclose(pf);
    gtk_window_close(step->add_step_window);
    gtk_window_close(infos.project_window);
}

else {
    printf("Impossible d'ouvrir le fichier de configuration \n");
}

}
