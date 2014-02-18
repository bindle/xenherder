#
#   Xen Herder
#   Copyright (C) 2014 Bindle Binaries <syzdek@bindlebinaries.com>.
#
#   @BINDLE_BINARIES_BSD_LICENSE_START@
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are
#   met:
#
#      * Redistributions of source code must retain the above copyright
#        notice, this list of conditions and the following disclaimer.
#      * Redistributions in binary form must reproduce the above copyright
#        notice, this list of conditions and the following disclaimer in the
#        documentation and/or other materials provided with the distribution.
#      * Neither the name of Bindle Binaries nor the
#        names of its contributors may be used to endorse or promote products
#        derived from this software without specific prior written permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
#   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#   PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BINDLE BINARIES BE LIABLE FOR
#   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
#   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
#   SUCH DAMAGE.
#
#   @BINDLE_BINARIES_BSD_LICENSE_END@
#
#   @configure_input@
#
#   Makefile.am - automate compiling on a unix platform
#

# Sub directories
SUBDIRS					=
DIST_SUBDIRS				=


# non-standard directories
cgibindir				= $(pkglibexecdir)/cgi-bin
jsdir					= $(htmldir)/js
themesdir				= $(htmldir)/themes
defaultthemedir				= $(themesdir)/default


# Global flags
AM_LIBS					=
AM_LDFLAGS				= -L$(top_builddir)/lib
AM_CFLAGS				= -O2 $(CFLAGS_WARNINGS)
AM_CXXFLAGS				= -O2 @AM_CXXFLAGS@
AM_OBJCFLAGS				= -O2 @AM_OBJCFLAGS@
AM_CPPFLAGS				= -O2 -DHAVE_CONFIG_H=1 -I$(top_builddir)/include -I$(top_srcdir)/include
ACLOCAL_AMFLAGS				= -I m4 -I contrib/bindletools/m4 -W all -W error
AM_MAKEINFOFLAGS                        = --no-split
DEFS					=


# automake targets
check_PROGRAMS				=
doc_DATA				=
include_HEADERS				= include/xenherder.h
lib_LTLIBRARIES				= lib/libxenherder.la
man_MANS				=
info_TEXINFOS				=
noinst_DATA				=
noinst_LTLIBRARIES			= lib/libxlstub.la
noinst_HEADERS				= include/libxlstub/libxl.h \
					  include/libxlstub/libxl_utils.h
noinst_PROGRAMS				=
noinst_SCRIPTS				=
bin_PROGRAMS				=
bin_SCRIPTS				=
sbin_SCRIPTS				=
cgibin_PROGRAMS				=
js_DATA					=
defaulttheme_DATA			=


# lists
BUILT_SOURCES				=
TESTS					=
XFAIL_TESTS				=
EXTRA_MANS				=
EXTRA_DIST				= \
					  lib/libxenherder/libxenherder.sym \
					  lib/libxlstub/libxlstub.sym \
					  src/html/js/jquery.tablesorter.min.js \
					  src/html/js/jquery.min.js \
					  src/html/js/xenherder.js \
					  src/html/themes/default/asc.gif \
					  src/html/themes/default/bg.gif \
					  src/html/themes/default/desc.gif \
					  src/html/themes/default/xenherder.css \
					  src/html/themes/default/xenherder.html
CLEANFILES				= \
					  $(builddir)/a.out   $(srcdir)/a.out \
					  $(builddir)/*/a.out $(srcdir)/*/a.out \
					  autoscan.log $(srcdir)/autoscan.log \
					  config.h.in~ $(srcdir)/config.h.in~ \
					  configure.scan $(srcdir)/configure.scan \
					  src/html/js/xenherder.min.js \
					  src/html/js/xenherder.min.js.tmp \
					  src/html/themes/default/xenherder.min.css \
					  src/html/themes/default/xenherder.min.css.tmp \
					  $(man_MANS) \
					  $(bin_SCRIPTS) \
					  $(sbin_SCRIPTS) \
					  $(noinst_SCRIPTS) \
					  @PACKAGE_TARNAME@-*.tar.* \
					  @PACKAGE_TARNAME@-*.zip
DISTCHECK_CONFIGURE_FLAGS		= --enable-strictwarnings \
					  --enable-libxlstub \
					  --enable-devel-progs


# macros for lib/libxenherder.la
lib_libxenherder_la_DEPENDENCIES	= lib/libxenherder/libxenherder.sym \
					  lib/libxlstub.la \
					  $(include_HEADERS) \
					  $(pkginclude_HEADERS) \
					  Makefile
lib_libxenherder_la_CPPFLAGS		= $(AM_CPPFLAGS)
lib_libxenherder_la_LIBS		= $(XENLIGHT_LIBS)
lib_libxenherder_la_LDFLAGS		= -static \
					  -rpath'$(libdir)'\
					  -version-info $(LIB_VERSION_INFO) \
					  $(AM_LDFLAGS) \
					  -export-symbols $(srcdir)/lib/libxenherder/libxenherder.sym
lib_libxenherder_la_SOURCES		= $(include_HEADERS) \
					  $(pkginclude_HEADERS) \
					  $(noinst_HEADERS) \
					  lib/libxenherder/libxenherder.h \
					  lib/libxenherder/cgi.c \
					  lib/libxenherder/cgi.h \
					  lib/libxenherder/file.c \
					  lib/libxenherder/file.h \
					  lib/libxenherder/version.c \
					  lib/libxenherder/version.h


# macros for lib/libxlstub.la
lib_libxlstub_la_DEPENDENCIES		= lib/libxlstub/libxlstub.sym \
					  $(noinst_HEADERS) \
					  Makefile
lib_libxlstub_la_CPPFLAGS		= $(AM_CPPFLAGS) -I$(srcdir)/include/libxlstub
lib_libxlstub_la_LIBADD			=
lib_libxlstub_la_LDFLAGS		= -static \
					  -rpath'$(libdir)'\
					  -version-info $(LIB_VERSION_INFO) \
					  $(AM_LDFLAGS) \
					  -export-symbols $(srcdir)/lib/libxlstub/libxlstub.sym
lib_libxlstub_la_SOURCES		= $(include_HEADERS) \
					  $(pkginclude_HEADERS) \
					  $(noinst_HEADERS) \
					  lib/libxlstub/libxlstub.h \
					  lib/libxlstub/ctx.c \
					  lib/libxlstub/ctx.h \
					  lib/libxlstub/domain.c \
					  lib/libxlstub/domain.h \
					  lib/libxlstub/physinfo.c \
					  lib/libxlstub/physinfo.h


# macros for src/xenherder-linenum
src_xenherder_linenum_DEPENDENCIES	= lib/libxenherder.la
src_xenherder_linenum_LDADD		= $(XENLIGHT_LIBS) lib/libxenherder.la
src_xenherder_linenum_CPPFLAGS		= $(AM_CPPFLAGS) $(XENLIGHT_CPPFLAGS)
src_xenherder_linenum_SOURCES		= src/misc/xenherder-linenum.c
if XENHERDER_DEVELPROG
noinst_PROGRAMS				+= src/xenherder-linenum
endif


# macros for src/xenherder-mockup.cgi
src_xenherder_mockup_cgi_DEPENDENCIES	= lib/libxenherder.la
src_xenherder_mockup_cgi_LDADD		= $(XENLIGHT_LIBS) lib/libxenherder.la
src_xenherder_mockup_cgi_CPPFLAGS	= $(AM_CPPFLAGS) $(XENLIGHT_CPPFLAGS)
src_xenherder_mockup_cgi_SOURCES	= src/xenherder-mockup/xenherder-mockup.c
if ENABLE_XENHERDER_CGI
if HAVE_XENLIGHT
cgibin_PROGRAMS				+= src/xenherder-mockup.cgi
endif
endif


# macros for HTML
if ENABLE_XENHERDER_CGI
js_DATA					+= src/html/js/xenherder.min.js
defaulttheme_DATA			+= src/html/themes/default/asc.gif
defaulttheme_DATA			+= src/html/themes/default/bg.gif
defaulttheme_DATA			+= src/html/themes/default/desc.gif
defaulttheme_DATA			+= src/html/themes/default/xenherder.html
defaulttheme_DATA			+= src/html/themes/default/xenherder.min.css
endif


# Makefile includes
GIT_PACKAGE_VERSION_DIR			= include
SUBST_EXPRESSIONS			=
include $(srcdir)/@bindletools_srcdir@/build-aux/makefile-autotools.am
include $(srcdir)/@bindletools_srcdir@/build-aux/makefile-subst.am
include $(srcdir)/@bindletools_srcdir@/build-aux/makefile-version.am


# custom targets
.PHONY:

src/html/js/xenherder.min.js: Makefile src/html/js/xenherder.js
	mkdir -p src/html/js
	rm -f $(@)
	sed -e 's,//.*$$,,g' \
	   -e 's/^ *//g' \
	   -e 's/ *$$//g' \
	   -e 's,/\*.*\*/,,g' \
	   $(srcdir)/src/html/js/xenherder.js \
	   |grep -v '^$$' \
	   |sed -e ':a' -e 'N' -e '$$!ba' -e 's/\([{;]\)\n/\1/g' \
	   >> $(@).tmp
	cat \
	   $(srcdir)/src/html/js/jquery.min.js \
	   $(srcdir)/src/html/js/jquery.tablesorter.min.js \
	   $(@).tmp \
	   > $(@)


src/html/themes/default/xenherder.min.css: Makefile src/html/themes/default/xenherder.css
	mkdir -p src/html/themes/default
	rm -f $(@)
	sed -e 's,//.*$$,,g' \
	   -e 's/^[[:space:]]*//g' \
	   -e 's/[[:space:]]*$$//g' \
	   -e 's/:[[:space:]]*/:/g' \
	   -e 's/[[:space:]]\{2,\}/ /g' \
	   -e 's,/\*.*\*/,,g' \
	   $(srcdir)/src/html/themes/default/xenherder.css \
	   |grep -v '^$$' \
	   |sed -e ':a' -e 'N' -e '$$!ba' -e 's/\([{;]\)\n/\1/g' \
	   > $(@)


# local targets
install-exec-hook:

install-exec-local:

install-data-hook:
	test ! -f $(DESTDIR)/$(cgibindir)/xenherder-mockup.cgi \
	   || chmod u+s $(DESTDIR)/$(cgibindir)/xenherder-mockup.cgi

install-data-local:

uninstall-local:

clean-local:

distclean-local:
	rm -fR $(srcdir)/autom4te.cache


# end of automake file
