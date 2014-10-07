bin_PROGRAMS = mesa-process-@PROCESSNAME@
mesa_process_@PROCESSNAME@_SOURCES = dbus/dbusProcessApi.c dbus/dbusProcessApi.h dbus/dbusMesaApi.c dbus/dbusMesaApi.h main.c
AM_CFLAGS = $(GLIB_CFLAGS) $(GIO_CFLAGS)
LIBS += $(GLIB_LIBS) $(GIO_LIBS)

SUBDIRS = dbus

