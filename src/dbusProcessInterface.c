/* _____THIS MODULES INCLUDE_________________________________________________ */
#include "dbusProcessApi.h"
#include "dbusProcessInterface.h"

/* _____STANDARD INCLUDES____________________________________________________ */

/* _____PROJECT INCLUDES_____________________________________________________ */

/* _____LOCAL DEFINITIONS____________________________________________________ */

/* _____MACROS_______________________________________________________________ */

#define DBUS_OBJECT_PATH "/com/mixtelematics/connectionmanager"
#define DBUS_INTERFACE "com.mixtelematics.connectionmanager"

/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____LOCAL VARIABLES______________________________________________________ */

/* _____LOCAL FUNCTION DECLARATIONS__________________________________________ */

/* _____LOCAL FUNCTIONS______________________________________________________ */

 gboolean onHandleGetStatus (  generatedComMixtelematicsConnectionmanager *object,
                               GDBusMethodInvocation *invocation)
{

   GVariant *state;
   GVariantBuilder statusReply;


   g_variant_builder_init (&statusReply, G_VARIANT_TYPE ("a{sv}"));

   g_variant_builder_add (&statusReply, "{sv}", "commissioning",  g_variant_new_boolean (FALSE));
   g_variant_builder_add (&statusReply, "{sv}", "type",  g_variant_new_string ("gsm"));
   g_variant_builder_add (&statusReply, "{sv}", "state",  g_variant_new_string ("online"));

   state = g_variant_builder_end (&statusReply);

   (void)g_variant_ref_sink(state);

   generated_com_mixtelematics_connectionmanager_complete_get_status (object,invocation,state);

   return TRUE;
}

 gboolean onHandleReportCommsError(  generatedComMixtelematicsConnectionmanager *object,
                                     GDBusMethodInvocation *invocation,
                                     const gchar *arg_reporter)
{
   g_print("[onHandleReportCommsError] Received from: %s\n",arg_reporter);

   generated_com_mixtelematics_connectionmanager_complete_report_comms_error (object,invocation);

   return TRUE;
}

/* _____GLOBAL FUNCTIONS_____________________________________________________ */

void dbusProcessInterface_exportInterface(GDBusConnection *connection)
{

   g_print("[dbusProcessInterface_exportInterface] Interface published\n");

   generatedComMixtelematicsConnectionmanager *interface;

   // Get a DBUS handle (generated function)

   interface=generated_com_mixtelematics_connectionmanager_skeleton_new();

   // Register the callback

   /*lint -save -e929 -e740 -e826
    *
    * GLIB redefines some of the base types (e.g. void * -> gpointer), and requires
    * some pointer to pointer conversions to type gpointer for passing in paramters
    * to callbacks.
    * */
   (void)g_signal_connect (interface, "handle-get-status", G_CALLBACK (onHandleGetStatus), NULL);

   (void)g_signal_connect (interface, "handle-report-comms-error", G_CALLBACK (onHandleReportCommsError), NULL);


   GError *error = NULL;

   // Publish the DBUS interface
   if (g_dbus_interface_skeleton_export (G_DBUS_INTERFACE_SKELETON (interface),
                                         connection,
                                         DBUS_OBJECT_PATH,
                                         &error) != TRUE)
   {
      /*
       * This is a critical message we always want to show on the MESA terminal so we use
       * DEBUG_PRINT instead of the maskable GLIB_PRINT
       */
      g_print("[dbusProcessInterface_exportInterface]: DBUS Open service interface failed.(%s : %s)\n",DBUS_INTERFACE,error->message);
      g_error_free(error);
   }

   /*lint -restore*/

}

void dbusProcessInterface_init()
{


}

void dbusProcessInterface_destroy()
{

}

/* =============================================================================
 *  Copyright (c) 2014 MiX Telematics (Pty) Ltd [www.mixtelematics.com]
 *  All rights reserved.
 * ============================================================================= */
