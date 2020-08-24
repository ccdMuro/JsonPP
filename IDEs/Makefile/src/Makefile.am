## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	-I../../../include \
	-std=c++17 \
	$(LIBJSONPP_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g
	 
lib_LTLIBRARIES = libjsonpp.la

libjsonpp_la_SOURCES =     \
	../../../src/JsonPP.cpp   \
	../../../src/Value.cpp
	

libjsonpp_la_LDFLAGS = 

libjsonpp_la_LIBADD = $(LIBJSONPP_LIBS)


if PLATFORM_WIN32
libjsonpp_la_LDFLAGS += -no-undefined
endif

if NATIVE_WIN32
libjsonpp_la_LDFLAGS += -export-dynamic
endif

include_HEADERS = \
	../../../include/JsonPP.h \
	../../../include/Value.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libjsonpp-0.1.pc

EXTRA_DIST = \
	libjsonpp-0.1.pc.in

