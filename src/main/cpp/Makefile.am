ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libservice_provider_memory_inspection.la

BUILT_SOURCES = $(top_builddir)/src/main/cpp/service_definitions.h
CLEANFILES = $(top_builddir)/src/main/cpp/service_definitions.h

extraincludedir = $(includedir)/service_provider/memory_inspection
extrainclude_HEADERS = include/service_provider/memory_inspection/base.h

libservice_provider_memory_inspection_la_SOURCES  = provider.cpp
libservice_provider_memory_inspection_la_CXXFLAGS = --std=c++11 -fno-strict-aliasing -Wall 		\
											 -I$(srcdir) -I$(builddir) -I$(srcdir)/include 	\
                                             -DBUILD_service_provider_MEMORY_INSPECTION 			\
                                             @ROBOTKERNEL_CFLAGS@ 
libservice_provider_memory_inspection_la_LDFLAGS  = -Wall -release $(PACKAGE_VERSION)

VPATH = $(srcdir):$(top_srcdir)/share/service_definitions

SERVICE_DEFINITIONS = service_provider/memory_inspection/read_memory \
					  service_provider/memory_inspection/write_memory \
					  service_provider/memory_inspection/get_memory_areas

$(top_builddir)/src/main/cpp/service_definitions.h: Makefile $(SERVICE_DEFINITIONS)
	install -d $(top_builddir)/src/main/cpp/include/robotkernel
	@echo creating $@
	service_generate --indir $(top_srcdir)/share/service_definitions --out $@ $(SERVICE_DEFINITIONS)
	touch $@

