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
#define _LIB_LIBXHERDER_VERSION_C 1
#include "version.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef XHERDER_PMARK
#pragma mark - Headers
#endif

#include <assert.h>
#include <stdio.h>


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#ifdef XHERDER_PMARK
#pragma mark - Prototypes
#endif


/////////////////
//             //
//  Variables  //
//             //
/////////////////
#ifdef XHERDER_PMARK
#pragma mark - Variables
#endif

xenherder_info xenherder_information =
{
   XENHERDER_API_CURRENT,     // api_current;
   XENHERDER_API_REVISION,    // api_revision;
   XENHERDER_API_AGE,         // api_age;
   GIT_PACKAGE_MAJOR,         // version_major;
   GIT_PACKAGE_MINOR,         // version_minor;
   GIT_PACKAGE_PATCH,         // version_patch;
   GIT_PACKAGE_BUILD,         // version_build;
};


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#ifdef XHERDER_PMARK
#pragma mark - Functions
#endif

int xenherder_version(const xenherder_info ** infop)
{
   assert(infop != NULL);
   *infop = &xenherder_information;
   return(0);
}

/* end of source */
