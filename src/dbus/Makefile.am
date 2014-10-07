BUILT_SOURCES = dbusProcessApi.c dbusProcessApi.h dbusMesaApi.c dbusMesaApi.h

dbusProcessApi.c dbusProcessApi.h : dbus-process-api.xml
	gdbus-codegen --generate-c-code dbusProcessApi --c-namespace generated dbus-process-api.xml

dbusMesaApi.c dbusMesaApi.h : dbus-mesa-api.xml
	gdbus-codegen --generate-c-code dbusMesaApi --c-namespace generated dbus-mesa-api.xml

clean:
	rm -f *.c *.h *.o
