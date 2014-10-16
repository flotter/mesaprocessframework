#include <glib.h>

// Services to manage

#include "dbusSvc.h"
#include "paramProviderSystem.h"

int main(int argc, char *argv[])
{

/* Commandline parameter parsing */

   gchar *opt_address=NULL;
   gchar *opt_port=NULL;
   gboolean opt_debug=FALSE;
   GError *error=NULL;
   GOptionContext *opt_context;

   GOptionEntry opt_entries[] = {
      { "remote-dbus-ip", 'i', 0, G_OPTION_ARG_STRING, &opt_address, "TCP IP address <xxx.xxx.xxx.xxx>", NULL },
      { "remote-dbus-port", 'p', 0, G_OPTION_ARG_STRING, &opt_port, "TCP port (default is 55556)", NULL },
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

      g_print("Ctrl-C to exit ...\n");

      /* Init Services */

      dbusSvc_init(opt_address,opt_port);

      /* Start Services */

      dbusSvc_start();


      Distance odometer = (Distance)0u;
      EngSpd rpm = (EngSpd)0u;
      Speed speed = (Speed)0u;

      while(1) {

         sleep(2);

         paramSvc_parameterGet(PARAM_STRUCT_SYS_STDPARAM_ODO,&odometer,sizeof(odometer));
         paramSvc_parameterGet(PARAM_STRUCT_SYS_STDPARAM_SPEED,&speed,sizeof(speed));
         paramSvc_parameterGet(PARAM_STRUCT_SYS_STDPARAM_RPM,&rpm,sizeof(rpm));

         g_print("PARAM GETs:\n");
         g_print("--------------------\n");
         g_print("Odo: %d\n",odometer);
         g_print("Speed: %d\n",speed);
         g_print("RPM: %d\n",rpm);
         g_print("--------------------\n");

         speed = 1000;
         g_print("PARAM SET:\n");
         g_print("--------------------\n");
         paramSvc_parameterSet(PARAM_STRUCT_SYS_STDPARAM_SPEED,&speed,sizeof(speed));
         g_print("Speed: %d\n",speed);
         g_print("--------------------\n");

         g_print("PARAM GETs:\n");
         g_print("--------------------\n");
         g_print("Odo: %d\n",odometer);
         g_print("Speed: %d\n",speed);
         g_print("RPM: %d\n",rpm);
         g_print("--------------------------------------------------------------\n");

      } ;

      dbusSvc_destroy();

   }

   return 0;
}

