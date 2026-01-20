ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libservice_provider_memory_inspection.la

BUILT_SOURCES = $(top_builddir)/src/service_definitions.h
CLEANFILES = $(top_builddir)/src/service_definitions.h

extraincludedir = $(includedir)/service_provider_memory_inspection
extrainclude_HEADERS = $(top_srcdir)/include/service_provider_memory_inspection/base.h

libservice_provider_memory_inspection_la_SOURCES  = provider.cpp
libservice_provider_memory_inspection_la_CXXFLAGS = -fno-strict-aliasing -Wall 	\
											 -I$(top_srcdir)/include -I$(builddir)/include 	\
                                             @ROBOTKERNEL_CFLAGS@ 
libservice_provider_memory_inspection_la_LDFLAGS  = -Wall -release $(PACKAGE_VERSION)

VPATH = $(srcdir):$(top_srcdir)/share/service_definitions

SERVICE_DEFINITIONS = service_provider_memory_inspection/read_memory \
					  service_provider_memory_inspection/write_memory \
					  service_provider_memory_inspection/get_memory_areas

$(top_builddir)/src/service_definitions.h: Makefile $(SERVICE_DEFINITIONS)
	@echo creating $@
	service_generate --indir $(top_srcdir)/share/service_definitions --out $@ $(SERVICE_DEFINITIONS)
	touch $@

