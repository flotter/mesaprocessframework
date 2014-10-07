SUBDIRS = . src
EXTRA_DIST = autogen.sh

all-am:
	test ! -n "$(MESAPATH)" || test ! -d "$(MESAPATH)" || ln -s $(MESAPATH) mesa
	test -d mesa || git clone -b Develop https://MixFirmwareBuild:M1Xbu1ld3r@github.com/MiXTelematics/MESA mesa/

clean-am: 
	test ! -d mesa || rm -rf mesa
