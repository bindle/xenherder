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


# AC_XENHERDER_WITH_XENLIGHT(action-if-true, action-if-false)
# ______________________________________________________________________________
AC_DEFUN([AC_XENHERDER_WITH_XENLIGHT],[dnl

   # prerequists
   AC_REQUIRE([AC_PROG_CC])

   # set initial values
   HAVE_XENLIGHT="yes"
   XENLIGHT_CFLAGS=""
   XENLIGHT_CPPFLAGS=""
   XENLIGHT_LDFLAGS=""
   XENLIGHT_LIBS=""

   # display options
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

   # checks for sqlite3-includedir
   if test "x${WITH_XENLIGHT_INCLUDEDIR}" != "x" && \
      test "x${WITH_XENLIGHT_INCLUDEDIR}" != "xno" && \
      test "x${WITH_XENLIGHT_INCLUDEDIR}" != "xyes";then
      XENLIGHT_CPPFLAGS="-I${WITH_XENLIGHT_INCLUDEDIR}"
   fi

   # checks for sqlite3-libdir
   if test "x${WITH_SQLITE_LIBDIR}" != "x" && \
      test "x${WITH_SQLITE_LIBDIR}" != "xno" && \
      test "x${WITH_SQLITE_LIBDIR}" != "xyes";then
      XENLIGHT_LDFLAGS="-L${WITH_SQLITE_LIBDIR}"
   fi

   # saves old parameters
   OLD_CFLAGS=${CFLAGS}
   OLD_CPPFLAGS=${CPPFLAGS}
   OLD_LDFLAGS=${LDFLAGS}
   OLD_LIBS=${LIBS}

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

   # Apply substitution
   AC_SUBST([HAVE_XENLIGHT],     [${HAVE_XENLIGHT}])
   AC_SUBST([XENLIGHT_CFLAGS],   [${SQLITE3_CFLAGS}])
   AC_SUBST([XENLIGHT_CPPFLAGS], [${SQLITE3_CPPFLAGS}])
   AC_SUBST([XENLIGHT_LDFLAGS],  [${SQLITE3_LDFLAGS}])
   AC_SUBST([XENLIGHT_LIBS],     [${LIBS}])

   # replace old parameters
   CFLAGS=${OLD_CFLAGS}
   CPPFLAGS=${OLD_CPPFLAGS}
   LDFLAGS=${OLD_LDFLAGS}
   LIBS=${OLD_LIBS}

   # runs specified response
   if test "x${HAVE_XENLIGHT}" == "xno" && test "x${2}" != "x";then
      :
      $2
   elif test "x${HAVE_XENLIGHT}" != "xno" && test "x${1}" != "x";then
      :
      $1
   fi
])dnl


# end of m4 file
