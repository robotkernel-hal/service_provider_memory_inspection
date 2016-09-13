
libdir = $(prefix)/lib
lib_LTLIBRARIES = libinterface_memory_inspection.la
BUILT_SOURCES = interface_memory_inspection_ln_messages.h
CLEANFILES = interface_memory_inspection_ln_messages.h

include_headersdir = $(includedir)/interface_memory_inspection
include_headers_HEADERS = interface_memory_inspection_ln_messages.h

libinterface_memory_inspection_la_SOURCES  = interface_memory_inspection.cpp
libinterface_memory_inspection_la_CXXFLAGS = -fno-strict-aliasing -Wall -I$(top_srcdir)/src -DBUILD_INTERFACE_MEMORY_INSPECTION \
										   -I$(top_builddir) @ROBOTKERNEL_CFLAGS@ @YAML_CPP_CFLAGS@
libinterface_memory_inspection_la_LDFLAGS  = -Wall -release $(PACKAGE_VERSION)

VPATH = $(srcdir):$(top_srcdir)/share/ln/message_definitions

LN_MESSAGES = \
			  robotkernel/memory_inspection/read \
			  robotkernel/memory_inspection/write \
			  robotkernel/memory_inspection/get_info

interface_memory_inspection_ln_messages.h: Makefile $(LN_MESSAGES)
	@echo creating $@
	@LN_GENERATE@ -o $@ $(LN_MESSAGES)
	touch $@

install-exec-hook:
	cp -r $(top_srcdir)/share $(prefix)
