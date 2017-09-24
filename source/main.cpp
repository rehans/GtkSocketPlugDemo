#include <cairo.h>
#include <gtk/gtkx.h>
#include <gtk/gtksocket.h>
#include <gtk/gtkplug.h>

using namespace std;

cairo_surface_t * image = nullptr;

gboolean timeout(gpointer data)
{
  GtkWidget *widget = GTK_WIDGET(data);
  gtk_widget_queue_draw(widget);
  return true;
}

gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data)
{
  cairo_save(cr);
  cairo_set_source_surface(cr, image, 0, 0);
  for (int i = 0; i < 100; i++)
  {
      cairo_paint(cr);
  }

  cairo_restore(cr);
  return true;
}

//-------------------------------------------------------------------------
int main(int argc, char** argv)
{
  gtk_init (&argc, &argv);

  image = cairo_image_surface_create_from_png("../GtkSocketPlugDemo/resource/1200px-GTK+_logo.svg.png");

  auto window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window, 1200, 1200);
  g_signal_connect (window, "destroy", gtk_main_quit, NULL);

  GtkWidget* socket = gtk_socket_new();
  gtk_widget_set_size_request (socket, 1200, 1200);
  gtk_container_add(GTK_CONTAINER(window), socket);

  ::Window socket_id = gtk_socket_get_id(GTK_SOCKET(socket));
  GtkWidget* plug = gtk_plug_new(socket_id);
  gtk_widget_set_size_request (plug, 1200, 1200);

  GtkWidget* drawing_area = gtk_drawing_area_new ();
  gtk_container_add(GTK_CONTAINER(plug), drawing_area);
  gtk_widget_set_size_request (drawing_area, 1200, 1200);
  g_signal_connect (G_OBJECT (drawing_area), "draw", G_CALLBACK (draw_callback), NULL);

  g_timeout_add(16, timeout, drawing_area);
  gtk_widget_show_all(plug);
  gtk_widget_show_all (window);
  gtk_main ();
  return 0;
}
