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
#define _SRC_MISC_XENHERDER_LINENUM_C 1
#undef XHERDER_PMARK

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef XHERDER_PMARK
#pragma mark - Headers
#endif

#ifdef HAVE_CONFIG_H
#   include "config.h"
#endif

#include <xenherder.h>
#include <stdio.h>
#include <getopt.h>


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#ifdef XHERDER_PMARK
#pragma mark - Prototypes
#endif

int main(int argc, char * argv[]);


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#ifdef XHERDER_PMARK
#pragma mark - Functions
#endif

int main(int argc, char * argv[])
{
   int              c;
   int              opt_index;
   xenherder_file * xhfd;
   size_t           count;
   const char     * line;

   static char   short_opt[] = "hV";
   static struct option long_opt[] =
   {
      { "help",          no_argument, 0, 'h'},
      { "version",       no_argument, 0, 'V'},
      { NULL,            0,           0, 0  }
   };

   while((c = getopt_long(argc, argv, short_opt, long_opt, &opt_index)) != -1)
   {
      switch(c)
      {
         case -1:	/* no more arguments */
         case 0:	/* long options toggles */
         break;

         case 'h':
         fprintf(stderr, "Usage: %s <file>\n", argv[0]);
         return(0);

         case 'V':
         fprintf(stderr, "%s: no version information\n", argv[0]);
         return(0);

         case '?':
         fprintf(stderr, "Try `%s --help' for more information.\n", argv[0]);
         return(1);

         default:
         fprintf(stderr, "%s: unrecognized option `--%c'\n", argv[0], c);
         fprintf(stderr, "Try `%s --help' for more information.\n", argv[0]);
         return(1);
      };
   };
   if (argc != 2)
   {
      fprintf(stderr, "%s: missing required argument.\n", argv[0]);
      return(1);
   };

   if (xenherder_file_open(&xhfd, argv[1]) != 0)
   {
      perror("xenherder_file_open()");
      return(1);
   };

   while((line = xenherder_file_next_line(xhfd, NULL, &count)) != NULL)
   {
      printf("%3zu:%s\n", count, line);
   };

   xenherder_file_close(xhfd);

   return(0);
}


/* end of source */
