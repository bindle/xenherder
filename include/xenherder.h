/*
 *  Xen Herder
 *  Copyright (C) 2014 Bindle Binaries <syzdek@bindlebinaries.com>.
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_START@
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Bindle Binaries nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BINDLE BINARIES BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_END@
 */
/**
 *  @file
 */
#ifndef _XHERDER_H
#define _XHERDER_H 1
#undef XHERDER_PMARK

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef XHERDER_PMARK
#pragma mark - Headers
#endif

#include <inttypes.h>
#include <sys/types.h>


//////////////
//          //
//  Macros  //
//          //
//////////////
#ifdef XENHERDER_PMARK
#pragma mark - Macros
#endif

///////////////////
//               //
//  Definitions  //
//               //
///////////////////
#ifdef XHERDER_PMARK
#pragma mark - Definitions
#endif

#define XENHERDER_API_CURRENT     0LL
#define XENHERDER_API_REVISION    0LL
#define XENHERDER_API_AGE         0LL


// Exports function type
#undef XENHERDER_C_DECLS
#if defined(__cplusplus) || defined(c_plusplus)
#   define _XENHERDER_I             extern "C" inline
#   define XENHERDER_C_DECLS        "C"             ///< exports as C functions
#   define XENHERDER_BEGIN_C_DECLS  extern "C" {    ///< exports as C functions
#   define XENHERDER_END_C_DECLS    }               ///< exports as C functions
#else
#   define _XENHERDER_I             inline
#   define XENHERDER_C_DECLS        /* empty */     ///< exports as C functions
#   define XENHERDER_BEGIN_C_DECLS  /* empty */     ///< exports as C functions
#   define XENHERDER_END_C_DECLS    /* empty */     ///< exports as C functions
#endif
#ifdef WIN32
#   ifdef _LIB_LIBXENHERDER_H
#      define _XENHERDER_F   extern XENHERDER_C_DECLS __declspec(dllexport)   ///< used for library calls
#      define _XENHERDER_V   extern XENHERDER_C_DECLS __declspec(dllexport)   ///< used for library calls
#   else
#      define _XENHERDER_F   extern XENHERDER_C_DECLS __declspec(dllimport)   ///< used for library calls
#      define _XENHERDER_V   extern XENHERDER_C_DECLS __declspec(dllimport)   ///< used for library calls
#   endif
#else
#   ifdef _LIB_LIBXENHERDER_H
#      define _XENHERDER_F   /* empty */                                     ///< used for library calls
#      define _XENHERDER_V   extern XENHERDER_C_DECLS                        ///< used for library calls
#   else
#      define _XENHERDER_F   extern XENHERDER_C_DECLS                        ///< used for library calls
#      define _XENHERDER_V   extern XENHERDER_C_DECLS                        ///< used for library calls
#   endif
#endif


//////////////////
//              //
//  Data Types  //
//              //
//////////////////
#ifdef XHERDER_PMARK
#pragma mark - Data Types
#endif

typedef struct xenherder_info_struct  xenherder_info;
typedef struct xenherder_file_struct  xenherder_file;


///////////////
//           //
//  Structs  //
//           //
///////////////
#ifdef XHERDER_PMARK
#pragma mark - Structs
#endif

struct xenherder_info_struct
{
   const uint64_t    api_current;
   const uint64_t    api_revision;
   const uint64_t    api_age;
   const uint64_t    version_major;
   const uint64_t    version_minor;
   const uint64_t    version_patch;
   const char      * version_build;
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#ifdef XHERDER_PMARK
#pragma mark - Prototypes
#endif

/**
 *  @defgroup Version/API information
 *  @brief Array objects and functions.
 *  @{
 */
_XENHERDER_F int xenherder_version(const xenherder_info ** infop);
/** @} */


/**
 *  @defgroup File Parsing
 *  @brief Functions for parsing text files.
 *  @{
 */
_XENHERDER_F int xenherder_file_close(xenherder_file * xhfd);
_XENHERDER_F int xenherder_file_errno(xenherder_file * xhfd);
_XENHERDER_F int xenherder_file_name(xenherder_file * xhfd, char const ** namep);
_XENHERDER_F int xenherder_file_next_line(xenherder_file * xhfd,
   char * const * linep, size_t * lenp, size_t * nump);
_XENHERDER_F int xenherder_file_open(xenherder_file ** xhfdp,
   const char * filename);
_XENHERDER_F int xenherder_file_pop(xenherder_file * xhfd);
_XENHERDER_F int xenherder_file_push(xenherder_file * xhfd,
   const char * filename);
_XENHERDER_V const char xenherder_pryr_gb[];
/** @} */


#endif /* end of header */
