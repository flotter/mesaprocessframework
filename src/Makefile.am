bin_PROGRAMS = mesa-process-@PROCESSNAME@
mesa_process_@PROCESSNAME@_SOURCES = dbus-process/dbusProcessApi.c dbus-process/dbusProcessApi.h mesa/dbusMesaParameterApi.c mesa/dbusMesaParameterApi.h main.c
AM_CFLAGS = $(GLIB_CFLAGS) $(GIO_CFLAGS)
LIBS += $(GLIB_LIBS) $(GIO_LIBS)

SUBDIRS = dbus-process mesa

clean-local:
	rm -rf *~ *.o 

