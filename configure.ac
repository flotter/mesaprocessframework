AC_INIT(mesaprocessframework, 0.1)
AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE(foreign subdir-objects)

# The name of the MESA process (e.g. replace x with connectionmanager)
AC_SUBST(PROCESSNAME,x)

AC_CONFIG_SRCDIR(configure.ac)
AC_CONFIG_HEADERS(config.h)  
PKG_CHECK_MODULES(GLIB, glib-2.0)   
PKG_CHECK_MODULES(GIO, gio-unix-2.0)
AC_PROG_CC
AC_CONFIG_FILES(Makefile src/Makefile src/dbus/Makefile)
AC_OUTPUT
