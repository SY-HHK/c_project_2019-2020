/*
29/12/2019
Internet functions using sockets for TL PORJECT MANAGER by Louis & Tom
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
  struct connection_infos { char project_file_name[50];
                            GtkWidget *entry_username;
                            GtkWidget *entry_password;
                            GtkWidget *window;
                            GtkWidget *entry_email_user_modify;
                            GtkWidget *entry_password_modify;
                            GtkWidget *project_window;
                            SOCKET sock;
                            void *argc;
                            void *argv; };
  struct connection_infos infos;

  struct task_structure {   GtkWidget *new_task_entry;
                            GtkContainer *new_task_box;
                            int task_number;            };
  struct task_structure task;

  struct step_structure {   char project_file_name[50];
                            GtkWidget *step_name;
                            GtkWidget *step_end;
                            char task_description[10][50];
                            GtkWidget *task_checkbox[10];
                            GtkWidget *add_step_window;  };
  struct step_structure step;

void server_connect(GtkWidget *widget, struct connection_infos *infos);
//%%%%%%%%%%%%%%%%%%%%

void change_email_user(GtkWidget *widget,struct connection_infos *infos);

void change_password(GtkWidget *widget,struct connection_infos *infos);


