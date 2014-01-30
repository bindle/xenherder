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
#   acinclude.m4 - custom m4 macros used by configure.ac
#


# AC_XENHERDER_LIBXENLIGHT()
# ______________________________________________________________________________
AC_DEFUN([AC_XENHERDER_CGI],[dnl

   # prerequists
   AC_REQUIRE([AC_PROG_CC])

   # display options
   enableval=""
   AC_ARG_ENABLE(
      cgi-portal,
      [AS_HELP_STRING([--enable-cgi-portal], [enable CGI web portal (default: auto)])],
      [ ENABLE_XENHERDER_CGI=$enableval ],
      [ ENABLE_XENHERDER_CGI=$enableval ]
   )

   # checks for libxlstub
   if test "x${ENABLE_XENHERDER_CGI}" != "xno";then
      ENABLE_XENHERDER_CGI="yes"
   fi

   # Automake conditionals
   AM_CONDITIONAL([ENABLE_XENHERDER_CGI], [test x$ENABLE_XENHERDER_CGI = xyes])
])dnl


# AC_XENHERDER_LIBXENLIGHT()
# ______________________________________________________________________________
AC_DEFUN([AC_XENHERDER_LIBXENLIGHT],[dnl

   # prerequists
   AC_REQUIRE([AC_PROG_CC])

   # set initial values
   HAVE_XENLIGHT="no"
   XENLIGHT_CFLAGS=""
   XENLIGHT_CPPFLAGS=""
   XENLIGHT_LDFLAGS=""
   XENLIGHT_LIBS="xenlight"

   # saves old parameters
   OLD_CFLAGS=${CFLAGS}
   OLD_CPPFLAGS=${CPPFLAGS}
   OLD_LDFLAGS=${LDFLAGS}
   OLD_LIBS=${LIBS}

   # display options
   enableval=""
   AC_ARG_ENABLE(
      libxlstub,
      [AS_HELP_STRING([--enable-libxlstub], [Use libxenlight development stubs (default: no)])],
      [ ENABLE_LIBXLSTUB=$enableval ],
      [ ENABLE_LIBXLSTUB=$enableval ]
   )
   enableval=""
   AC_ARG_ENABLE(
      libxenlight,
      [AS_HELP_STRING([--enable-libxenlight], [Use libxenlight (default: auto)])],
      [ ENABLE_XENLIGHT=$enableval ],
      [ ENABLE_XENLIGHT=$enableval ]
   )
   withval=""
   AC_ARG_WITH(
      libxenlight-includedir,
      [AS_HELP_STRING([--with-libxenlight-includedir=DIR], [Search for libxenlight headers in DIR.])],
      [ WITH_XENLIGHT_INCLUDEDIR=$withval ],
      [ WITH_XENLIGHT_INCLUDEDIR=$withval ]
   )
   withval=""
   AC_ARG_WITH(
      libxenlight-libdir,
      [AS_HELP_STRING([--with-libxenlight-libdir=DIR], [Search for SQLite3 library in DIR.])],
      [ WITH_XENLIGHT_LIBDIR=$withval ],
      [ WITH_XENLIGHT_LIBDIR=$withval ]
   )

   # check for conflicting options
   if test "x${ENABLE_LIBXLSTUB}" == "xyes" && \
      test "x${ENABLE_XENLIGHT}" == "xyes";then
      AC_MSG_ERROR([Cannot enable both 'libxlstub' and 'libxenlight'])
   fi

   # checks for libxlstub
   if test "x${ENABLE_LIBXLSTUB}" == "xyes";then
      HAVE_XENLIGHT="yes"
      ENABLE_XENLIGHT="no"
      XENLIGHT_CPPFLAGS="-I${srcdir}/include/libxlstub"
      XENLIGHT_LIBS="lib/libxlstub.la"
   fi

   # checks for libxenlight
   if test "x${ENABLE_XENLIGHT}" != "xno";then
      HAVE_XENLIGHT="yes"

      # checks for sqlite3-includedir
      if test "x${WITH_XENLIGHT_INCLUDEDIR}" != "x" && \
         test "x${WITH_XENLIGHT_INCLUDEDIR}" != "xno" && \
         test "x${WITH_XENLIGHT_INCLUDEDIR}" != "xyes";then
         XENLIGHT_CPPFLAGS="-I${WITH_XENLIGHT_INCLUDEDIR}"
      fi

      # checks for sqlite3-libdir
      if test "x${WITH_XENLIGHT_LIBDIR}" != "x" && \
         test "x${WITH_XENLIGHT_LIBDIR}" != "xno" && \
         test "x${WITH_XENLIGHT_LIBDIR}" != "xyes";then
         XENLIGHT_LDFLAGS="-L${WITH_XENLIGHT_LIBDIR}"
      fi

      # apply sqlite parameters
      CFLAGS="${CFLAGS} ${XENLIGHT_CFLAGS}"
      CPPFLAGS="${CPPFLAGS} ${XENLIGHT_CPPFLAGS}"
      LDFLAGS="${LDFLAGS} ${XENLIGHT_LDFLAGS}"
      LIBS="${LIBS} ${XENLIGHT_LIBS}"

      # check for SQLite3
      AC_CHECK_HEADERS([libxl.h],                              [], [HAVE_XENLIGHT="no"])
      AC_CHECK_HEADERS([libxl_utils.h],                        [], [HAVE_XENLIGHT="no"])
      AC_SEARCH_LIBS([libxl_ctx_alloc],            [xenlight], [], [HAVE_XENLIGHT="no"])
      AC_SEARCH_LIBS([libxl_ctx_free],             [xenlight], [], [HAVE_XENLIGHT="no"])
      AC_SEARCH_LIBS([libxl_domid_to_name],        [xenlight], [], [HAVE_XENLIGHT="no"])
      AC_SEARCH_LIBS([libxl_dominfo_list_free],    [xenlight], [], [HAVE_XENLIGHT="no"])
      AC_SEARCH_LIBS([libxl_get_physinfo],         [xenlight], [], [HAVE_XENLIGHT="no"])
      AC_SEARCH_LIBS([libxl_get_version_info],     [xenlight], [], [HAVE_XENLIGHT="no"])
      AC_SEARCH_LIBS([libxl_list_domain],          [xenlight], [], [HAVE_XENLIGHT="no"])
      AC_SEARCH_LIBS([libxl_physinfo_dispose],     [xenlight], [], [HAVE_XENLIGHT="no"])

      # checks results
      if test "x${ENABLE_XENLIGHT}" == "xyes" && \
         test "x${HAVE_XENLIGHT}" == "xno";then
         AC_MSG_ERROR([Unable to find libxenlight prerequists])
      fi
      ENABLE_XENLIGHT=${HAVE_XENLIGHT}
   fi

   # Apply substitution
   AC_SUBST([ENABLE_XENLIGHT],   [${ENABLE_XENLIGHT}])
   AC_SUBST([HAVE_XENLIGHT],     [${HAVE_XENLIGHT}])
   AC_SUBST([XENLIGHT_CFLAGS],   [${XENLIGHT_CFLAGS}])
   AC_SUBST([XENLIGHT_CPPFLAGS], [${XENLIGHT_CPPFLAGS}])
   AC_SUBST([XENLIGHT_LDFLAGS],  [${XENLIGHT_LDFLAGS}])
   AC_SUBST([XENLIGHT_LIBS],     [${XENLIGHT_LIBS}])

   # Automake conditionals
   AM_CONDITIONAL([HAVE_XENLIGHT],    [test x$HAVE_XENLIGHT = xyes])
   AM_CONDITIONAL([ENABLE_LIBXLSTUB], [test x$ENABLE_LIBXLSTUB = xyes])

   # replace old parameters
   CFLAGS=${OLD_CFLAGS}
   CPPFLAGS=${OLD_CPPFLAGS}
   LDFLAGS=${OLD_LDFLAGS}
   LIBS=${OLD_LIBS}

])dnl


# end of m4 file
