
libcaja_seahorse_la_CPPFLAGS = -I$(top_builddir) 	\
	-I$(top_srcdir) 			\
	$(CAJA_CFLAGS) 			\
	-DGNOMELOCALEDIR=\""$(datadir)/locale"\"

caja_extensiondir=$(CAJA_EXTENSION_DIR)

caja_extension_LTLIBRARIES=libcaja-seahorse.la

libcaja_seahorse_la_SOURCES =     \
        seahorse-caja.c           \
        seahorse-caja.h           \
        seahorse-caja-module.c

libcaja_seahorse_la_LDFLAGS = -module -avoid-version -no-undefined
libcaja_seahorse_la_LIBADD  = $(CAJA_LIBS)
