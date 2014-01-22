
#include <stdio.h>
#include <libxl.h>
#include <libxl_utils.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>

int main(void);

int main(void)
{
   libxl_ctx     * ctx;
   libxl_physinfo  physinfo;
   libxl_dominfo * dominfo;
   const libxl_version_info * xeninfo;
   int             nb_domain;
   int             i;
   size_t          len;
   char          * domname;
   char            hostname[512];
   char            hostname_long[512];
   struct utsname utsbuf;
   int             count_vcpu;
   char            timestr[64];
   time_t          t;
   struct tm       ts;

   t  = time(NULL);
   localtime_r(&t, &ts);
   strftime(timestr, 64, "%Y/%m/%d %H:%M:%S", &ts);

   printf("Content-type: text/html\n\n");

   gethostname(hostname, 512);
   strncpy(hostname_long, hostname, 512);
   strncat(hostname_long, ".", 512);
   len = strlen(hostname_long);
   getdomainname(&hostname_long[len], 512-len);

   if (libxl_ctx_alloc(&ctx, LIBXL_VERSION, 0, NULL) != 0)
   {
      fprintf(stderr, "cannot init xl context\n");
      return(1);
   };

   if (!(xeninfo = libxl_get_version_info(ctx)))
   {
      fprintf(stderr, "libxl_get_version_info failed.\n");
      return;
   };

   if (libxl_get_physinfo(ctx, &physinfo) != 0)
   {
      fprintf(stderr, "libxl_physinfo failed.\n");
      return(1);
   };

   if ((dominfo = libxl_list_domain(ctx, &nb_domain)) == NULL)
   {
      fprintf(stderr, "libxl_list_domain failed.\n");
      libxl_ctx_free(ctx);
      return(1);
   };

   if (uname(&utsbuf) < 0)
   {
      fprintf(stderr, "uname failed.\n");
      return(1);
   };

   printf("<!DOCTYPE html>");
   printf("<html>");
   printf("  <head>");
   printf("    <title>Xen Herder (%s)</title>", hostname_long);
   printf("    <meta charset='UTF-8'>");
   printf("    <link href='/xenherder.css' type='text/css' rel='stylesheet'>");
   printf("    <style type='text/css'></style>");
   printf("  </head>");
   printf("  <body>");
   printf("    <div id='page'>");
   printf("      <div id='header'>");
   printf("        <h1>%s</h1>", hostname_long);
   printf("        <h2>Xen Herder</h2>");
   printf("      </div><!-- #header (end) -->");
   printf("      <div id='navbar'>");
   printf("        <ul>");
   printf("          <li><a href='/' title='Doashboard'>Dashboard</a></li>");
   printf("        </ul>");
   printf("        <p>");
   printf("          %s", timestr);
   printf("        </p>");
   printf("      </div><!-- #navbar (end) -->\n");
   printf("      <div id='menu'>\n");
   printf("        <h3>Dashboard</h3>\n");
   printf("        <ul>\n");
   printf("          <li><a href='#' title=''>Summary</a></li>\n");
   printf("          <li><a href='#' title=''>Host Details</a></li>\n");
   printf("          <li><a href='#' title=''>Xen Herder</a></li>\n");
   printf("        </ul>\n");
   printf("        <h3>Domains</h3>\n");
   printf("        <ul>\n");
   count_vcpu = 0;
   for(i = 0; i < nb_domain; i++)
   {
      domname = libxl_domid_to_name(ctx, dominfo[i].domid);
      count_vcpu += dominfo[i].vcpu_online;
      printf("          <li><a href='#' title=''>%s</a></li>\n", domname);
      free(domname);
   };
   printf("        </ul>\n");
   printf("      </div><!-- #menu (end) -->\n");
   printf("      <div id='content'>\n");
   printf("        <h3>Host</h3>\n");
   printf("        <div class='article'>\n");
   printf("          <table>\n");
   printf("            <thead>\n");
   printf("              <tr><th>Host</th><th>Xen</th><th>OS</th><th>Domains</th><th>vCPU</th><th>CPU Cores</th><th>Threads/Core</th><th>Free Memory</th><th>Total Memory</th></tr>\n");
   printf("            </thead>\n");
   printf("            <tbody>\n");
   printf("              <tr>");
   printf("<td><a href='/'>%s</a></td>", hostname);
   printf("<td>%i.%i%s</td>", xeninfo->xen_version_major, xeninfo->xen_version_minor, xeninfo->xen_version_extra);
   printf("<td>%s %s</td>", utsbuf.sysname, utsbuf.release);
   printf("<td>%i</td>", nb_domain);
   printf("<td>%i</td>", count_vcpu);
   printf("<td>%i</td>", physinfo.nr_cpus*physinfo.nr_nodes);
   printf("<td>%i</td>", physinfo.threads_per_core);
   printf("<td>()</td>");
   printf("<td></td>");
   printf("</tr>\n");
   printf("            </tbody>\n");
   printf("            <tfoot>\n");
   printf("              <tr><th colspan=9 class='cmdhint'>xl -v info -n</th></tr>\n");
   printf("            </tfoot>\n");
   printf("          </table>\n");
   printf("        </div><!-- #article (end) -->\n");
   printf("        <h3>Domains</h3>\n");
   printf("        <div class='article'>\n");
   printf("          <table>\n");
   printf("            <thead>\n");
   printf("              <tr><th>Name</th><th>ID</th><th>Status</th><th>Type</th><th>Memory Used</th><th>Max Memory</th><th>vCPU</th><th>CPU Time</th></tr>\n");
   printf("            </thead>\n");
   printf("            <tbody>\n");
   printf("              <tr>");
   for(i = 0; i < nb_domain; i++)
   {
      domname = libxl_domid_to_name(ctx, dominfo[i].domid);
      printf("<td><a href='#'>%s</a></td>", domname);
      printf("<td>%i</td>", dominfo[i].domid);
      printf("<td>Running</td>");
      printf("<td>unknown</td>");
      printf("<td>%i</td>", dominfo[i].current_memkb / 1024);
      printf("<td>%i</td>", (dominfo[i].outstanding_memkb+dominfo[i].current_memkb) / 1024);
      printf("<td>%i</td>", dominfo[i].vcpu_online);
      printf("<td>%.1f</td></tr>\n", ((float)dominfo[i].cpu_time / 1e9));
      free(domname);
   };
   printf("            </tbody>\n");
   printf("            <tfoot>\n");
   printf("              <tr><th colspan=8 class='cmdhint'>xl -v list -n</th></tr>\n");
   printf("            </tfoot>\n");
   printf("          </table>\n");
   printf("        </div><!-- #article (end) -->\n");
   printf("      </div><!-- #content (end) -->\n");
   printf("      <div id='footer'>\n");
   printf("        <p>Powered by Xen Herder Prototype</p>\n");
   printf("      </div><!-- #footer (end) -->\n");
   printf("    </div><!-- #page (end) -->\n");
   printf("  </body>\n");
   printf("</html>\n");


   libxl_dominfo_list_free(dominfo, nb_domain);
   libxl_physinfo_dispose(&physinfo);
   libxl_ctx_free(ctx);

   return(0);
}

