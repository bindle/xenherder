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
#ifndef _XHERDER_LIBXLSTUB_XL_H
#define _XHERDER_LIBXLSTUB_XL_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef XHERDER_PMARK
#pragma mark - Headers
#endif

#include <xenherder.h>


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
#ifdef XHERDER_PMARK
#pragma mark - Definitions
#endif

#undef LIBXL_VERSION
#define LIBXL_VERSION 0

//////////////////
//              //
//  Data Types  //
//              //
//////////////////
#ifdef XHERDER_PMARK
#pragma mark - Data Types
#endif

typedef struct libxl_ctx_struct               libxl_ctx;
typedef struct libxl_dominfo_struct           libxl_dominfo;
typedef struct libxl_physinfo_struct          libxl_physinfo;
typedef struct libxl_uuid_struct              libxl_uuid;
typedef struct libxl_version_info_struct      libxl_version_info;
typedef struct xentoollog_logger_struct       xentoollog_logger;

typedef uint32_t libxl_hwcap[8];
typedef uint32_t libxl_domid;
typedef int libxl_devid;


////////////////////
//                //
//  Enumerations  //
//                //
////////////////////
#ifdef XHERDER_PMARK
#pragma mark - Structs
#endif

typedef enum
{
    LIBXL_SHUTDOWN_REASON_POWEROFF = 0,
    LIBXL_SHUTDOWN_REASON_REBOOT = 1,
    LIBXL_SHUTDOWN_REASON_SUSPEND = 2,
    LIBXL_SHUTDOWN_REASON_CRASH = 3,
    LIBXL_SHUTDOWN_REASON_WATCHDOG = 4,
} libxl_shutdown_reason;


///////////////
//           //
//  Structs  //
//           //
///////////////
#ifdef XHERDER_PMARK
#pragma mark - Structs
#endif

struct libxl_uuid_struct
{
   uint8_t uuid[16];
};


struct libxl_version_info_struct
{
    int        xen_version_major;
    int        xen_version_minor;
    char     * xen_version_extra;
    char     * compiler;
    char     * compile_by;
    char     * compile_domain;
    char     * compile_date;
    char     * capabilities;
    char     * changeset;
    uint64_t   virt_start;
    int        pagesize;
    char     * commandline;
};


struct libxl_physinfo_struct
{
   uint32_t threads_per_core;
   uint32_t cores_per_socket;

   uint32_t max_cpu_id;
   uint32_t nr_cpus;
   uint32_t cpu_khz;

   uint64_t total_pages;
   uint64_t free_pages;
   uint64_t scrub_pages;
   uint64_t outstanding_pages;
   uint64_t sharing_freed_pages;
   uint64_t sharing_used_frames;

   uint32_t nr_nodes;
   libxl_hwcap hw_cap;

   int cap_hvm;
   int cap_hvm_directio;
};


struct libxl_dominfo_struct
{
    libxl_uuid       uuid;
    libxl_domid      domid;
    uint32_t         ssidref;
    int              running;
    int              blocked;
    int              paused;
    int              shutdown;
    int              dying;
    libxl_shutdown_reason shutdown_reason;
    uint64_t         outstanding_memkb;
    uint64_t         current_memkb;
    uint64_t         shared_memkb;
    uint64_t         paged_memkb;
    uint64_t         max_memkb;
    uint64_t         cpu_time;
    uint32_t         vcpu_max_id;
    uint32_t         vcpu_online;
    uint32_t         cpupool;
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#ifdef XHERDER_PMARK
#pragma mark - Prototypes
#endif

int libxl_ctx_alloc (libxl_ctx ** pctx, int version, unsigned flags,
   xentoollog_logger *lg);
int libxl_ctx_free(libxl_ctx * ctx);


const libxl_version_info * libxl_get_version_info(libxl_ctx * ctx);
int libxl_get_physinfo(libxl_ctx * ctx, libxl_physinfo * physinfo);
void libxl_physinfo_dispose(libxl_physinfo * physinfo);
libxl_dominfo * libxl_list_domain(libxl_ctx * ctx, int * nb_domain_out);
void libxl_dominfo_list_free(libxl_dominfo * list, int nb_domain);

#endif /* end of header */
