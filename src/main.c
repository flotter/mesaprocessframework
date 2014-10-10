#include "src/mesa/dbusMesaParameterApi.h"

int main(int argc, char *argv[])
{

/* Commandline parameter parsing */

   gchar *opt_address=NULL;
   gboolean opt_debug=FALSE;
   GError *error=NULL;
   GOptionContext *opt_context;

   GOptionEntry opt_entries[] = {
      { "remote-dbus-ip", 'r', 0, G_OPTION_ARG_STRING, &opt_address, "TCP IP address <xxx.xxx.xxx.xxx>", NULL },
      { "debug", 'd', 0, G_OPTION_ARG_NONE, &opt_debug, "Enable verbose debug messages", NULL },
      { NULL }
   };

   opt_context = g_option_context_new ("MESA Process Framework Example");
   error = NULL;

   g_option_context_add_main_entries (opt_context, opt_entries, NULL);

   if (!g_option_context_parse (opt_context, &argc, &argv, &error))
   {
      g_printerr ("Error parsing options: %s\n", error->message);
      g_error_free (error);
   }
   else
   {

      if (opt_address == NULL)
      {
         /* If no address is specified we are running locally and using the SYSTEM BUS */

      }
      else
      {
         /* In this case we are making a remote DBUS connection over TCP */


      }

   printf("Hello ...\n");

   }

   return 0;
}

