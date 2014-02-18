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
#define _LIB_LIBXHERDER_FILE_C 1
#include "file.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef XHERDER_PMARK
#pragma mark - Headers
#endif

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
#ifdef XHERDER_PMARK
#pragma mark - Definitions
#endif

#define XENHERDER_FILE_BUFF_SIZE  128LL


///////////////
//           //
//  Structs  //
//           //
///////////////
#ifdef XHERDER_PMARK
#pragma mark - Structs
#endif

struct xenherder_file_struct
{
   int              fd;
   char           * buff;
   char           * filename;
   size_t           bsize;       ///< Buffer size
   size_t           blen;        ///< Buffer length (amount of data stored)
   size_t           boffset;     ///< Buffer offset of EOL
   size_t           lnum;        ///< Line count
   struct stat      sb;          ///< stat() buffer of file
   xenherder_file * prev;        ///< previous file in file stack (used for processing includes)
   xenherder_file * cur;         ///< the current file being processed (used for processing includes)
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#ifdef XHERDER_PMARK
#pragma mark - Prototypes
#endif

xenherder_file * xenherder_file_alloc(const char * filename);
void xenherder_file_free(xenherder_file * xhfd);


/////////////////
//             //
//  Variables  //
//             //
/////////////////
#ifdef XHERDER_PMARK
#pragma mark - Variables
#endif

const char xenherder_pryr_gb[] =
{
   0x47, 0x6c, 0x6f, 0x72, 0x79, 0x20, 0x62, 0x65, 0x20, 0x74, 0x6f, 0x20,
   0x74, 0x68, 0x65, 0x20, 0x46, 0x61, 0x74, 0x68, 0x65, 0x72, 0x2c, 0x0a,
   0x61, 0x6e, 0x64, 0x20, 0x74, 0x6f, 0x20, 0x74, 0x68, 0x65, 0x20, 0x53,
   0x6f, 0x6e, 0x2c, 0x0a, 0x61, 0x6e, 0x64, 0x20, 0x74, 0x6f, 0x20, 0x74,
   0x68, 0x65, 0x20, 0x48, 0x6f, 0x6c, 0x79, 0x20, 0x53, 0x70, 0x69, 0x72,
   0x69, 0x74, 0x2e, 0x0a, 0x41, 0x73, 0x20, 0x69, 0x74, 0x20, 0x77, 0x61,
   0x73, 0x20, 0x69, 0x6e, 0x20, 0x74, 0x68, 0x65, 0x20, 0x62, 0x65, 0x67,
   0x69, 0x6e, 0x6e, 0x69, 0x6e, 0x67, 0x2c, 0x0a, 0x69, 0x73, 0x20, 0x6e,
   0x6f, 0x77, 0x2c, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x65, 0x76, 0x65, 0x72,
   0x20, 0x73, 0x68, 0x61, 0x6c, 0x6c, 0x20, 0x62, 0x65, 0x2c, 0x0a, 0x77,
   0x6f, 0x72, 0x6c, 0x64, 0x20, 0x77, 0x69, 0x74, 0x68, 0x6f, 0x75, 0x74,
   0x20, 0x65, 0x6e, 0x64, 0x2e, 0x20, 0x41, 0x6d, 0x65, 0x6e, 0x2e, 0x00
};


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#ifdef XHERDER_PMARK
#pragma mark - Functions
#endif

inline xenherder_file * xenherder_file_alloc(const char * filename)
{
   xenherder_file * xhfd;

   assert(filename != NULL);

   if ((xhfd = malloc(sizeof(xenherder_file))) == NULL)
      return(NULL);
   memset(xhfd, 0, sizeof(xenherder_file));

   if ((xhfd->fd = open(filename, O_RDONLY)) == -1)
   {
      xenherder_file_free(xhfd);
      return(NULL);
   };

   if (fstat(xhfd->fd, &xhfd->sb) == -1)
   {
      xenherder_file_free(xhfd);
      return(NULL);
   };

   if ((xhfd->buff = malloc(XENHERDER_FILE_BUFF_SIZE)) == NULL)
   {
      xenherder_file_free(xhfd);
      return(NULL);
   };
   xhfd->bsize  = XENHERDER_FILE_BUFF_SIZE;

   if ((xhfd->filename = strdup(filename)) == NULL)
   {
      xenherder_file_free(xhfd);
      return(NULL);
   };

   return(xhfd);
}


int xenherder_file_close(xenherder_file * xhfd)
{
   assert(xhfd != NULL);

   while(xhfd->cur != xhfd)
      if (xenherder_file_pop(xhfd) != 0)
         return(errno);

   xenherder_file_free(xhfd);

   return(0);
}


int xenherder_file_name(xenherder_file * xhfd, const char ** namep)
{
   assert(xhfd  != NULL);
   assert(namep != NULL);
   *namep = xhfd->cur->filename;
   return(0);
}


char const * xenherder_file_next_line(xenherder_file * xhfd, size_t * lenp,
   size_t * nump)
{
   xenherder_file  * cur;
   size_t            offset;
   size_t            pos;
   ssize_t           len;

   assert(xhfd  != NULL);

   cur = xhfd->cur;

   // shift buffer to the left (erasing current line)
   if (cur->boffset != 0)
   {
      offset = cur->blen - cur->boffset;
      for(pos = 0; pos < offset; pos++)
         cur->buff[pos] = cur->buff[pos + cur->boffset];
   };
   cur->blen    -= cur->boffset;
   cur->boffset  = 0;

   // attempt to fill buffer from file
   if ((len = read(cur->fd, &cur->buff[cur->blen], (cur->bsize - cur->blen))) == -1)
      return(NULL);
   cur->blen += len;

   // look for EOL
   for(cur->boffset = 0; cur->boffset < cur->blen; cur->boffset++)
   {
      switch(cur->buff[cur->boffset])
      {
         case '\n':
         cur->buff[cur->boffset] = '\0';
         cur->lnum++;
         if ((nump))
            *nump = cur->lnum;
         if ((lenp))
            *lenp = cur->boffset;
         if (cur->buff[cur->boffset-1] == '\r')
         {
            cur->buff[cur->boffset-1] = '\0';
            if ((lenp))
               *lenp -= 1;
         };
         cur->boffset++;
         return(cur->buff);

         default:
         break;
      };
   };

   return(NULL);
}


int xenherder_file_open(xenherder_file ** xhfdp, const char * filename)
{
   xenherder_file * xhfd;

   assert(xhfdp    != NULL);
   assert(filename != NULL);

   if ((xhfd = xenherder_file_alloc(filename)) == NULL)
      return(errno);

   xhfd->cur = xhfd;
   *xhfdp    = xhfd;

   return(0);
}


inline void xenherder_file_free(xenherder_file * xhfd)
{
   assert(xhfd != NULL);

   if (xhfd->fd != -1)
      close(xhfd->fd);

   if (xhfd->filename != NULL)
      free(xhfd->filename);
   xhfd->filename = NULL;

   if (xhfd->buff != NULL)
      free(xhfd->buff);
   xhfd->buff = NULL;

   free(xhfd);

   return;
}


int xenherder_file_pop(xenherder_file * xhfd)
{
   xenherder_file * cur;
   assert(xhfd != NULL);
   if (xhfd->cur == xhfd)
      return(0);
   cur       = xhfd->cur;
   xhfd->cur = xhfd->cur->prev;
   xenherder_file_free(cur);
   return(0);
}


int xenherder_file_push(xenherder_file * xhfd, const char * filename)
{
   xenherder_file * nxt;
   xenherder_file * cur;

   assert(xhfd     != NULL);
   assert(filename != NULL);

   if ((nxt = xenherder_file_alloc(filename)) == NULL)
      return(errno);

   cur = xhfd->cur;
   while(cur != NULL)
   {
      if (  (cur->sb.st_ino == nxt->sb.st_ino) &&
            (cur->sb.st_dev == nxt->sb.st_dev) )
      {
         xenherder_file_free(nxt);
         return(EMLINK);
      };
      cur = cur->cur;
   };

   nxt->prev = xhfd->cur;
   xhfd->cur = nxt;

   return(0);
}


/* end of source */
