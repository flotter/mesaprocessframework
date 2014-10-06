bin_PROGRAMS = hello
hello_SOURCES = hello.c dbus_process_api.c dbus_process_api.h
AM_CFLAGS = $(GLIB_CFLAGS) $(GIO_CFLAGS)
LIBS += $(GLIB_LIBS) $(GIO_LIBS)

dbus_process_api.c dbus_process_api.h : dbus-interface.xml
	gdbus-codegen --generate-c-code dbus_process_api --c-namespace generated dbus-interface.xml
