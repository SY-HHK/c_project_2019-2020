/*
29/12/2019
graphic functions for TL PROJECT MANAGER by Louis & Tom
*/

GtkWidget *connection_window(void *argc, void *argv, SOCKET sock);

GtkWidget *main_window(void *argc, void *argv, SOCKET sock);

GtkWidget *project_window(GtkWidget *widget, struct connection_infos *infos);

GtkWidget *new_step(GtkWidget *widget, struct connection_infos *infos);

GtkWidget *new_task(GtkWidget *button_new_task, struct task_structure *task);

void write_step(GtkWidget *confirm_button, struct step_structure *step);

void modify_step(GtkWidget *widget, struct connection_infos *infos);

