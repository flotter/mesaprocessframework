/* _____THIS MODULES INCLUDE_________________________________________________ */
#include "paramId.h"
#include "dbusMesaParameterApi.h"
#include "dbusMesaInterface.h"
#include <string.h>

/* _____STANDARD INCLUDES____________________________________________________ */

/* _____PROJECT INCLUDES_____________________________________________________ */
#include "typedef.h"

/* _____LOCAL DEFINITIONS____________________________________________________ */

#define DBUS_OBJECT_PATH "/com/mixtelematics/mesa/parameters"
#define DBUS_INTERFACE "com.mixtelematics.mesa.parameters"
#define DBUS_NAME "com.mixtelematics"

// The parameter interface handle structure.

typedef struct parameterInterface_Struct
{
   generatedComMixtelematicsMesaParameters *mesaParameterProxy;
   GMutex mutex;
} parameterInterface;

static parameterInterface parameters;

/* _____MACROS_______________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____LOCAL VARIABLES______________________________________________________ */

static guint busWatchHandle;



/* _____LOCAL FUNCTION DECLARATIONS__________________________________________ */

/* _____LOCAL FUNCTIONS______________________________________________________ */

void parameterUpdated(generatedComMixtelematicsMesaParameters *object, GVariant *arg_id)
{
   ParamId_ParameterId id;
   u16 paramStructSize;
   guint group,structure,offset,size;

   g_variant_get(arg_id,"(uuuu)",group,structure,offset,size);

   id.group =     (ParamId_ProviderGroup) group;
   id.structure = (ParamId_StructureId) structure;
   id.offset =    (ParamId_FieldOffset) offset;
   id.size=       (ParamId_FieldSize) size;

   g_print("[busNameAppeared] Received an update notification for parameter: Group=%d, Structure=%d, Offset=%d, Size=%d\n",id.group,id.structure,id.offset,id.size);
}


PRIVATE void busNameAppeared(GDBusConnection *connection, const gchar *name, const gchar *nameOwner, gpointer userData)
{
   (void) connection;
   (void) userData;

   g_print("[busNameAppeared] Mesa Interface bus name appeared: Name %s, owner: %s\n",name, nameOwner);

   GError *error=NULL;

   g_mutex_lock(&parameters.mutex);

   parameters.mesaParameterProxy = generated_com_mixtelematics_mesa_parameters_proxy_new_sync (  connection,
                                                                                                 G_DBUS_PROXY_FLAGS_NONE,
                                                                                                 DBUS_NAME,
                                                                                                 DBUS_OBJECT_PATH,
                                                                                                 NULL,
                                                                                                 &error);


   if(error != NULL)
   {
      g_print("[busNameAppeared] Mesa Interface connection failed.\n");
      g_error_free(error);
   }
   else
   {

      (void)g_signal_connect(G_OBJECT(parameters.mesaParameterProxy),"parameter-updated",G_CALLBACK(parameterUpdated),(gpointer)&parameters);
   }

   g_mutex_unlock(&parameters.mutex);

}

PRIVATE void busNameDisappeared(GDBusConnection *connection,
                                 const gchar *name,
                                 gpointer userData)
{
   (void) connection;
   (void) userData;

   g_print ("[busNameDisappeared] Mesa Interface bus name just disappeared: %s\n", name);

   g_mutex_lock(&parameters.mutex);

   parameters.mesaParameterProxy=NULL;

   g_mutex_unlock(&parameters.mutex);

}

/* _____GLOBAL FUNCTIONS_____________________________________________________ */

void dbusMesaInterface_getParameter(ParamId_ParameterId id,void *buffer, u16 size)
{

   g_mutex_lock(&parameters.mutex);

   if(parameters.mesaParameterProxy != NULL)
   {

      GError *error=NULL;

      GVariant *paramId;
      GVariant *paramData;

      paramId = g_variant_new("(uuuu)",(guint)id.group,(guint)id.structure,(guint)id.offset,(guint)id.size);

      generated_com_mixtelematics_mesa_parameters_call_get_parameter_sync (parameters.mesaParameterProxy,
                                                                           paramId,
                                                                           size,
                                                                           &paramData,
                                                                           NULL,
                                                                           &error);

      if(error != NULL)
     {
        g_print("[dbusMesaInterface_getParameter] Mesa Interface call failed.\n");
        g_error_free(error);
     }
     else
     {
        GVariant *rawByteStream;

        g_variant_get(paramData,"(@ay)",&rawByteStream);

        const u8 * writeBuffer = g_variant_get_fixed_array(rawByteStream,(gsize *)&size,sizeof(u8));

        memcpy(buffer,(void *)writeBuffer,size);

        g_free((void *)writeBuffer);

     }
   }

   g_mutex_unlock(&parameters.mutex);

}

void dbusMesaInterface_setParameter(ParamId_ParameterId parameterId, const void* buffer, u16 size)
{

   g_mutex_lock(&parameters.mutex);

   if(parameters.mesaParameterProxy != NULL)
   {
      GError *error=NULL;
      u16 paramStructSize;
      GVariant *paramId;
      GVariant *paramData;

      paramId = g_variant_new("(uuuu)",(guint)parameterId.group,(guint)parameterId.structure,(guint)parameterId.offset,(guint)parameterId.size);

      paramStructSize = size;

      GVariant *rawByteStream = g_variant_new_fixed_array(G_VARIANT_TYPE_BYTE,buffer,paramStructSize,sizeof(u8));

      GVariant *packedByteStream = g_variant_new("(@ay)",rawByteStream);

      generated_com_mixtelematics_mesa_parameters_call_set_parameter_sync (parameters.mesaParameterProxy,
                                                                           paramId,
                                                                           size,
                                                                           packedByteStream,
                                                                           NULL,
                                                                           &error);

      if(error != NULL)
     {
        g_print("[dbusMesaInterface_getParameter] Mesa Interface call failed.\n");
        g_error_free(error);
     }

   }

   g_mutex_unlock(&parameters.mutex);
}



void dbusMesaInterface_addDbusNameWatch(GDBusConnection *connection)
{

   busWatchHandle = g_bus_watch_name_on_connection(connection,
                                                   DBUS_NAME,
                                                   G_BUS_NAME_WATCHER_FLAGS_NONE,
                                                   &busNameAppeared,
                                                   &busNameDisappeared,
                                                   NULL,
                                                   NULL);

}

void dbusMesaInterface_removeDbusNameWatch()
{
   g_bus_unwatch_name(busWatchHandle);
}

void dbusMesaInterface_init()
{
   parameters.mesaParameterProxy=NULL;
   g_mutex_init(&parameters.mutex);
}

void dbusMesaInterface_destroy()
{
   g_mutex_clear(&parameters.mutex);
}


/* =============================================================================
 *  Copyright (c) 2014 MiX Telematics (Pty) Ltd [www.mixtelematics.com]
 *  All rights reserved.
 * ============================================================================= */
