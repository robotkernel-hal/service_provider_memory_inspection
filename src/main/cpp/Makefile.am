lib_LTLIBRARIES = libservice_provider_memory_inspection.la

extraincludedir = $(includedir)/service_provider/memory_inspection
extrainclude_HEADERS = include/service_provider/memory_inspection/base.h

libservice_provider_memory_inspection_la_SOURCES  = provider.cpp
libservice_provider_memory_inspection_la_CXXFLAGS = --std=c++11 -fno-strict-aliasing -Wall 		\
											 -I$(srcdir) -I$(builddir) -I$(srcdir)/include 	\
                                             -DBUILD_service_provider_MEMORY_INSPECTION 			\
                                             @ROBOTKERNEL_CFLAGS@ 
libservice_provider_memory_inspection_la_LDFLAGS  = -Wall -release $(PACKAGE_VERSION)

