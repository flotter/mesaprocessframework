BUILT_SOURCES = dbusMesaParameterApi.c dbusMesaParameterApi.h

dbusMesaParameterApi.c dbusMesaParameterApi.h : dbus/dbus-mesa-parameter-api.xml
	gdbus-codegen --generate-c-code dbusMesaParameterApi --c-namespace generated dbus/dbus-mesa-parameter-api.xml

clean-local:
	rm -rf *.c *.h *.o dbus *~
