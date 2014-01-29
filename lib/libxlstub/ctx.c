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
#define _LIB_LIBXLSTUB_CTX_C 1
#include "ctx.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef XHERDER_PMARK
#pragma mark - Headers
#endif

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


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
//  Functions  //
//             //
/////////////////
#ifdef XHERDER_PMARK
#pragma mark - Functions
#endif

int libxl_ctx_alloc (libxl_ctx ** pctx, int version, unsigned flags,
   xentoollog_logger * lg)
{
   assert(pctx != NULL);
   if ((*pctx = malloc(sizeof(libxl_ctx))) == NULL)
      return(1);
   memset(*pctx, 0, sizeof(libxl_ctx));

   (*pctx)->args_version = version;
   (*pctx)->args_flags   = flags;
   (*pctx)->args_logger  = lg;

   (*pctx)->version.xen_version_major = 4;
   (*pctx)->version.xen_version_minor = 3;
   (*pctx)->version.xen_version_extra = strdup(" libxlstub from xenherder");

   (*pctx)->physinfo.threads_per_core     = 4;
   (*pctx)->physinfo.cores_per_socket     = 6;
   (*pctx)->physinfo.max_cpu_id           = 48;
   (*pctx)->physinfo.nr_cpus              = 2;
   (*pctx)->physinfo.cpu_khz              = 3700000;
   (*pctx)->physinfo.total_pages          = 4000;
   (*pctx)->physinfo.free_pages           = 4000;
   (*pctx)->physinfo.scrub_pages          = 4000;
   (*pctx)->physinfo.outstanding_pages    = 0;
   (*pctx)->physinfo.sharing_freed_pages  = 0;
   (*pctx)->physinfo.sharing_used_frames  = 0;
   (*pctx)->physinfo.nr_nodes             = 12;
   (*pctx)->physinfo.cap_hvm              = 1;
   (*pctx)->physinfo.cap_hvm_directio     = 1;

   (*pctx)->dominfo[0].domid         = 0;
   (*pctx)->dominfo[0].blocked       = 1;
   (*pctx)->dominfo[0].max_memkb     = (1024*1024);
   (*pctx)->dominfo[0].current_memkb = (1024*1024);
   (*pctx)->dominfo[0].vcpu_online   = 1;
   (*pctx)->dominfo[0].vcpu_max_id   = 2;
   (*pctx)->dominfo[1].domid         = 1;
   (*pctx)->dominfo[1].blocked       = 1;
   (*pctx)->dominfo[1].max_memkb     = (1024*1024*8);
   (*pctx)->dominfo[1].current_memkb = (1024*1024*8);
   (*pctx)->dominfo[1].vcpu_online   = 4;
   (*pctx)->dominfo[1].vcpu_max_id   = 4;
   (*pctx)->dominfo[2].domid         = 3;
   (*pctx)->dominfo[2].blocked       = 1;
   (*pctx)->dominfo[2].max_memkb     = (1024*1024*6);
   (*pctx)->dominfo[2].current_memkb = (1024*1024*6);
   (*pctx)->dominfo[2].vcpu_online   = 8;
   (*pctx)->dominfo[2].vcpu_max_id   = 8;

   (*pctx)->domnames[0] = "Domain-0";
   (*pctx)->domnames[0] = "foo";
   (*pctx)->domnames[0] = "bar";

   return(0);
}


int libxl_ctx_free(libxl_ctx * ctx)
{
   assert(ctx != NULL);
   free(ctx);
   return(0);
}


const libxl_version_info * libxl_get_version_info(libxl_ctx *ctx)
{
   assert(ctx != NULL);
   return(&ctx->version);
}



/* end of source */
