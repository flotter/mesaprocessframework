/* _____THIS MODULES INCLUDE_________________________________________________ */

/* _____STANDARD INCLUDES____________________________________________________ */
#include <gio/gio.h>

/* _____PROJECT INCLUDES_____________________________________________________ */
#include "dbusProcessInterface.h"

#include "dbusSvc.h"

/* _____LOCAL DEFINITIONS____________________________________________________ */

/*
 * The DBUS server BUS name as published by MESA
 */

#define STRINGIZE_exp(S) #S
#define STRINGIZE(S) STRINGIZE_exp(S)
#define DBUS_NAME "com.mixtelematics." STRINGIZE(PROCESSNAME)
#define DBUS_REMOTE_IP_DEFAULT "55556"

#define NUMBER_OF_THREAD_INSTANCES  (1u)

/* _____MACROS_______________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____LOCAL VARIABLES______________________________________________________ */

static gchar *dbusRemoteIP;
static gchar *dbusRemotePort;

/* _____LOCAL FUNCTION DECLARATIONS__________________________________________ */

/* _____LOCAL FUNCTIONS______________________________________________________ */

/*
 * This the callback function for when DBUS access is established
 */
void onBusAcquired(GDBusConnection *connection, const gchar *name, gpointer userData)
{
   (void) userData;

   // Export Dbus interfaces here
   dbusProcessInterface_exportInterface(connection);

   // We re-use the connection (to dbus-daemon) to look for the MESA Parameter interface
   dbusMesaInterface_addDbusNameWatch(connection);

}

/*
 * This the callback function for when our DBUS name got published (com.mixtelematics)
 */
void onNameAcquired(GDBusConnection *connection, const gchar *name, gpointer userData)
{
   (void) connection;
   (void) userData;

   g_print("[dbusSvc_instanceThread] We are now owning DBUS name: %s\n", name);
}

void onNameLost(GDBusConnection *connection, const gchar *name, gpointer userData)
{
   (void) connection;
   (void) userData;

   g_print("[dbusSvc_instanceThread] We lost DBUS name: %s\n", name);
}

/* _____GLOBAL FUNCTIONS_____________________________________________________ */

gpointer dbusSvc_instanceThread(gpointer data)
{
   (void) data;
   /*
    * This is thread in which a GLIB "main" loop will run. The GLIB callback functionality is handled
    * and registered in this context.
    */

   GError *error=NULL;
   GMainLoop *loop;
   GDBusConnection *connection;
   guint id;

   // Add watches for needed DBUS interfaces here

   // Create a new GLIB context which will attach to this thread
   loop = g_main_loop_new(NULL, FALSE);

   if(dbusRemoteIP == NULL)
   {
      // We are using the local DBUS SYSTEM bus

      g_print("[dbusSvc_instanceThread] Local DBUS connection on SYSTEM bus\n");

      id = g_bus_own_name(G_BUS_TYPE_SYSTEM,
                          DBUS_NAME,
                          G_BUS_NAME_OWNER_FLAGS_ALLOW_REPLACEMENT | G_BUS_NAME_OWNER_FLAGS_REPLACE,
                          onBusAcquired,
                          onNameAcquired,
                          onNameLost,
                          loop,
                          NULL);
   }
   else
   {
      // We are using a remote connection to a target DBUS daemon
      gchar *remoteAddress;

      remoteAddress = g_strdup_printf("tcp:host=%s,port=%s",dbusRemoteIP,dbusRemotePort);

      g_print("[dbusSvc_instanceThread] Remote DBUS connection on: %s\n",remoteAddress);

      connection = g_dbus_connection_new_for_address_sync(remoteAddress,
                                                          G_DBUS_CONNECTION_FLAGS_MESSAGE_BUS_CONNECTION | G_DBUS_CONNECTION_FLAGS_AUTHENTICATION_CLIENT,
                                                          NULL,
                                                          NULL,
                                                          &error);

      g_free(remoteAddress);

      if (error != NULL)
      {
         /*
          * Critical error remote bus was not obtainable
          */
         g_print("[dbusSvc_instanceThread] Failed to get remote bus. DBUS services disabled\n");
         g_error_free(error);
      }
      else
      {

      onBusAcquired(connection,"Remote DBUS over TCP",NULL);

      id = g_bus_own_name_on_connection (connection,
                                    DBUS_NAME,
                                    G_BUS_NAME_OWNER_FLAGS_ALLOW_REPLACEMENT | G_BUS_NAME_OWNER_FLAGS_REPLACE,
                                    onNameAcquired,
                                    onNameLost,
                                    loop,
                                    NULL);
      }

   }

   // Fire off the GLIB main loop. This will not return until the process is terminated.
   g_main_loop_run(loop);

   // Remove additional client watches here.


   // Release the DBUS name
   g_bus_unown_name(id);

   // Remove the DBUs watcher as we lost the connection anyways.
   dbusMesaInterface_removeDbusNameWatch();

   // Free the main loop object
   g_main_loop_unref(loop);
}

void dbusSvc_init(gchar * dbusIP, gchar * dbusPort)
{

   dbusMesaInterface_init();
   dbusProcessInterface_init();

   dbusRemoteIP = dbusIP;

   dbusRemotePort = dbusPort;

   if(dbusRemotePort == NULL)
   {
      dbusRemotePort = g_strdup_printf(DBUS_REMOTE_IP_DEFAULT);
   }

}

void dbusSvc_destroy()
{
   dbusMesaInterface_destroy();
   dbusProcessInterface_destroy();
}


void dbusSvc_start()
{

   g_print("[dbusSvc_start] GDBUS (GLIB) thread started\n");

   g_thread_new("dbusSvc",dbusSvc_instanceThread,NULL);

}

/* =============================================================================
 *  Copyright (c) 2014 MiX Telematics (Pty) Ltd [www.mixtelematics.com]
 *  All rights reserved.
 * ============================================================================= */
