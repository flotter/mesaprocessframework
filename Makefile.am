SUBDIRS = . src
EXTRA_DIST = autogen.sh

all-am:
	test -d mesa || git clone -b Develop https://github.com/MiXTelematics/mix6000-angstrom mesa/

clean-am: 
	test ! -d mesa || rm -rf mesa
