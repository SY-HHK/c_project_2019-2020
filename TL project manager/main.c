//compiler: `pkg-config gtk+-3.0 --cflags` & linker: `pkg-config gtk+-3.0 --libs`
//linker : -lmysqlclient
#include "socket_functions.h"
#include "graphics_functions.h"

int main(int argc,char **argv)
{
    SOCKET sock = server_init();
        if (sock == 0) return 0;

    gtk_widget_show_all (connection_window(&argc, &argv, sock));
    gtk_main();

    close_socket(sock);

      return 0;

}
