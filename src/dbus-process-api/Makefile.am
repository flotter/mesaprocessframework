BUILT_SOURCES = dbusProcessApi.c dbusProcessApi.h

dbusProcessApi.c dbusProcessApi.h : dbus-process-api.xml
	gdbus-codegen --generate-c-code dbusProcessApi --c-namespace generated dbus-process-api.xml

clean-local:
	rm -f *.c *.h *.o *~
