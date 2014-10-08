SUBDIRS = . src
EXTRA_DIST = autogen.sh 

all-am:
	## If MESAPATH is supplied, create a symlinked directory to it
	test ! -n "$(MESAPATH)" || test ! -d "$(MESAPATH)" || test -d mesa || ln -r -s $(MESAPATH) mesa
	
	## If the MESAPATH environment variable was not passed to configure, we grab mesa from Github
	test -d mesa || git clone -b Develop https://MixFirmwareBuild:M1Xbu1ld3r@github.com/MiXTelematics/MESA mesa/
	
	## Map all the relavant MESA folders into our process
	test ! -d mesa || test -d "src/mesa/dbus" || ln -s -r $(MESAPATH)/targets/linux/services/dbus/gdbusCodeGen src/mesa/dbus

distclean-local: 
	test ! -d mesa || rm -rf mesa *~
	test ! -d "src/mesa/dbus" || rm -rf src/mesa/dbus
