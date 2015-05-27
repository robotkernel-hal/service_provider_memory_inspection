ACLOCAL_AMFLAGS = -I m4 -I scripts/m4

libdir = $(prefix)/lib
lib_LTLIBRARIES = libinterface_memory_inspection.la
BUILT_SOURCES = ln_messages.h
CLEANFILES = ln_messages.h

libinterface_memory_inspection_la_SOURCES  = interface_memory_inspection.cpp
libinterface_memory_inspection_la_CXXFLAGS = -fno-strict-aliasing -Wall -I$(top_srcdir)/src \
										   -I$(top_builddir) @ROBOTKERNEL_CFLAGS@ 
libinterface_memory_inspection_la_LDFLAGS  = -Wall -release $(PACKAGE_VERSION)

VPATH = $(srcdir):$(srcdir)/share/message_definitions

LN_MESSAGES = \
			  robotkernel/memory_inspection/read \
			  robotkernel/memory_inspection/write \
			  robotkernel/memory_inspection/get_info

ln_messages.h: Makefile $(LN_MESSAGES)
	@echo creating ln_messages.h
	@LN_GENERATE@ -o $@ $(LN_MESSAGES)
	touch $@

install-exec-hook:
	cp -r $(srcdir)/share $(prefix)
