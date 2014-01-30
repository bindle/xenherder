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
#   configure.in - automate compiling on a unix platform
#

AC_PREREQ([2.65])

AC_COPYRIGHT([Copyright (c) 2014 Bindle Binaries <syzdek@bindlebinaries.com>.])
AC_REVISION(0.1)
AC_INIT([Xen Herder],[0.0],[syzdek@bindlebinaries.com],[xenherder])

AC_SUBST([RELEASE_MONTH],["January 2014"])

# Version Info:
#    Current    -- the current version number of this API
#    Revision   -- the revision of the implementation of the API version
#    Age        -- How many seqential past API versions is supported by
#                  this implementation
# Format => Current:Revision:Age
# Convenience macro:
#    AC_BINDLE_LIBTOOL_VERSION_INFO(current, revision, age)
AC_BINDLE_LIBTOOL_VERSION_INFO(0, 0, 0)

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([contrib/bindletools/build-aux/autogen.sh])
#AC_CONFIG_LIBOBJ_DIR(compat)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# determines host type
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

# configures for automake
AM_INIT_AUTOMAKE(gnu std-options subdir-objects)

# Compilers
AC_PROG_CC
#AC_PROG_OBJC
AC_PROG_CXX
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_USE_SYSTEM_EXTENSIONS # replaces AC_AIX AC_GNU_SOURCE AC_MINIX
AC_C_BIGENDIAN

# binary locations
AC_PROG_INSTALL
AC_PATH_PROG([SHELL],   sh bash,        [AC_MSG_ERROR([missing "sh"])], [$PATH])
AC_CHECK_TOOLS(AR,      ar gar,         [AC_MSG_ERROR([missing binutil "ar"])])
AC_CHECK_TOOLS(LD,      ld gld,         [AC_MSG_ERROR([missing binutil "ld"])])
AC_CHECK_TOOLS(NM,      nm gnm,         [AC_MSG_ERROR([missing binutil "nm"])])
AC_CHECK_TOOLS(RANLIB,  ranlib granlib, [AC_MSG_ERROR([missing binutil "ranlib"])])
AC_CHECK_TOOLS(STRIP,   strip gstrip,   [AC_MSG_ERROR([missing binutil "strip"])])

# shell programs
AC_PROG_AWK
AC_PROG_EGREP
AC_PROG_FGREP
AM_PROG_LEX
AC_PROG_LN_S

# GNU Libtool Support
LT_INIT(dlopen disable-fast-install win32-dll)

# initiates bindle tools macros
AC_BINDLE(contrib/bindletools)

# Function checks
AC_FUNC_CHOWN
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([gethostname],,   AC_MSG_ERROR([missing required libc function gethostname()]))
AC_CHECK_FUNCS([localtime_r],,   AC_MSG_ERROR([missing required libc function localtime_r()]))
AC_CHECK_FUNCS([memset],,        AC_MSG_ERROR([missing required libc function memset()]))
AC_CHECK_FUNCS([strdup],,        AC_MSG_ERROR([missing required libc function strdup()]))
AC_CHECK_FUNCS([uname],,         AC_MSG_ERROR([missing required libc function uname()]))

# Header checks
AC_CHECK_HEADERS([locale.h])

# Type checks
AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

# custom configure options
AC_BINDLE_ENABLE_WARNINGS
AC_XENHERDER_LIBXENLIGHT

# determine PACKAGE_VERSION via Git
AC_BINDLE_GIT_PACKAGE_VERSION([contrib/bindletools/build-aux/git-package-version.sh])

# Creates outputs
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

# Show local config
AC_MSG_NOTICE([])
AC_MSG_NOTICE([Xen Herder ${GIT_PACKAGE_VERSION} (${GIT_PACKAGE_BUILD})])
AC_MSG_NOTICE([])
AC_MSG_NOTICE([Features:])
AC_MSG_NOTICE([   libxenlight:         ${ENABLE_XENLIGHT}])
AC_MSG_NOTICE([   OpenSSL:             todo])
AC_MSG_NOTICE([   inet sockets:        todo])
AC_MSG_NOTICE([   inet6 sockets:       todo])
AC_MSG_NOTICE([   unix sockets:        todo])
AC_MSG_NOTICE([])
AC_MSG_NOTICE([Components:])
AC_MSG_NOTICE([   Xen Herder library:  yes])
AC_MSG_NOTICE([   xenlight stub:       ${ENABLE_LIBXLSTUB}])
AC_MSG_NOTICE([   daemon:              no])
AC_MSG_NOTICE([   CLI tools:           no])
AC_MSG_NOTICE([   CGI tools:           ${HAVE_XENLIGHT}])
AC_MSG_NOTICE([   docs:                no])
AC_MSG_NOTICE([])
AC_MSG_NOTICE([Compile Options:])
AC_MSG_NOTICE([   CC                   = ${CC}])
AC_MSG_NOTICE([   CFLAGS               = ${CFLAGS}])
AC_MSG_NOTICE([   LDFLAGS              = ${LDFLAGS}])
AC_MSG_NOTICE([   LIBS                 = ${LIBS}])
AC_MSG_NOTICE([   CPPFLAGS             = ${CPPFLAGS}])
AC_MSG_NOTICE([   CPP                  = ${CPP}])
AC_MSG_NOTICE([])
AC_MSG_NOTICE([run 'make all'])
AC_MSG_NOTICE([])

# end of configure.ac
