ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	data \
	tool \
	caja-ext \
	po

EXTRA_DIST = \
	AUTHORS \
	COPYING \
	ChangeLog \
	INSTALL \
	MAINTAINERS \
	NEWS \
	README.md \
	THANKS \
	intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

DISTCLEANFILES = \
	intltool-extract \
	intltool-merge \
	intltool-update

DISTCHECK_CONFIGURE_FLAGS = \
	--with-caja-ext-dir=/tmp

dist-hook:
	@if test -d "$(srcdir)/.git"; \
	then \
		echo Creating ChangeLog && \
		( cd "$(top_srcdir)" && \
		  echo '# Generated automatically. Do not edit.'; echo; \
		  $(top_srcdir)/missing --run git log --stat --date=short ) > ChangeLog.tmp \
		&& mv -f ChangeLog.tmp $(top_distdir)/ChangeLog \
		|| ( rm -f ChangeLog.tmp ; \
		     echo Failed to generate ChangeLog >&2 ); \
	else \
		echo A git clone is required to generate a ChangeLog >&2; \
	fi

upload-release: $(DIST_ARCHIVES)
	scp $(DIST_ARCHIVES) master.gnome.org:
	ssh master.gnome.org ftpadmin install $(DIST_ARCHIVES)
