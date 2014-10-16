bin_PROGRAMS = mesa-process-@PROCESSNAME@

## Process specific DBUS API
mesa_process_@PROCESSNAME@_SOURCES  = dbus-process-api/dbusProcessApi.c dbus-process-api/dbusProcessApi.h 

## Mesa Parameter DBUS API
mesa_process_@PROCESSNAME@_SOURCES += mesa/dbusMesaParameterApi.c mesa/dbusMesaParameterApi.h

## Process framework files 
mesa_process_@PROCESSNAME@_SOURCES += main.c dbusMesaInterface.c dbusMesaInterface.h dbusProcessInterface.c dbusProcessInterface.h dbusSvc.c dbusSvc.h mesa/parameter/providers/paramProviderSystem.c mesa/parameter/providers/paramProviderSystem.h paramSvc.h paramSvc.c            

## Unique process function files



AM_CFLAGS = $(GLIB_CFLAGS) $(GIO_CFLAGS) -DPROCESSNAME=mesa-process-@PROCESSNAME@
AM_CFLAGS +=  -Imesa -Imesa/defines -Imesa/dbus-mesa-api -Idbus-process-api -Imesa/parameter/providers
LIBS += $(GLIB_LIBS) $(GIO_LIBS)

SUBDIRS = dbus-process-api mesa

clean-local:
	rm -rf *~ *.o 

