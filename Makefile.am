ACLOCAL_AMFLAGS = -I m4
SUBDIRS=src/main/cpp

pkgconfig_DATA = service_provider_memory_inspection.pc

install-exec-hook:
	mkdir -p $(prefix)/share/ln
	cp -rf $(top_srcdir)/share/ln/* $(prefix)/share/ln/
	cp -rf $(top_builddir)/share/ln/* $(prefix)/share/ln/
	mkdir -p $(prefix)/share/robotkernel_gui
	cp -rf $(top_srcdir)/share/robotkernel_gui/* $(prefix)/share/robotkernel_gui/
