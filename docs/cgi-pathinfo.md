

Xen Herder Path Info Hierarchy
==============================


Path Info Tree Structure
------------------------

    +--prefix                      List of clusters
       +--xenherder
       +--herd                     redirect: /xenherder/
       |  \--herdname              redirect: /xenherder/herdname/summary/
       |     \--summary            Host list
       +--host                     redirect: /xenherder/
       |  \--herdname              redirect: /xenherder/herdname/summary/
       |     \--hostname           redirect: /xenherder/host/hostname/summary/
       |        +--summary         Basic host information/DomU list
       |        +--open vswitch
       |        +--dom0 dmesg
       |        \--xen dmesg
       +--domu                     redirect: /xenherder/
       |  \--herdname              redirect: /xenherder/herdname/summary/
       |     \--hostname           redirect: /xenherder/host/hostname/summary/
       |        \--domuname        redirect: /xenherder/domu/hostname/domuname/summary/
       |           +--summary
       |           +--console
       |           \--details
       \--layout
          +--js
          |  \--xenherder.min.js
          +--themes
             \--themename
                +--css
                |  \--xenherder.min.css
                \--images


Example URLs
------------

   Node Name       | Value
   --------------- | -------------------
   HTTP Host       | xen.foo.org
   URL Prefix      | /herder
   Cluster Name    | herd3
   Host Name       | xen37
   DomU Name       | bar


   Description     | URL
   --------------- | ---------------------------------------------------------
   Home page       | http://xen.foo.org/herder/
   Cluster Summary | http://xen.foo.org/herder/herd/herd3/summary/
   Host Summary    | http://xen.foo.org/herder/host/herd3/xen14/summary/
   Host Details    | http://xen.foo.org/herder/host/herd3/xen14/details/
   DomU Summary    | http://xen.foo.org/herder/domu/herd3/xen14/bar/summary/
   DomU Details    | http://xen.foo.org/herder/domu/herd3/xen14/bar/details/

