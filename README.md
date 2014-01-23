
Xen Herder
==========


Contents
--------

   1. Disclaimer
   2. Software Requirements
   3. Tested Platforms
   4. Maintainers
   5. Community
   6. Source Code
   7. Package Maintence Notes


Disclaimer
----------

   This software is provided by the copyright holders and contributors "as
   is" and any express or implied warranties, including, but not limited to,
   the implied warranties of merchantability and fitness for a particular
   purpose are disclaimed. In no event shall Bindle Binaries be liable for
   any direct, indirect, incidental, special, exemplary, or consequential
   damages (including, but not limited to, procurement of substitute goods or
   services; loss of use, data, or profits; or business interruption) however
   caused and on any theory of liability, whether in contract, strict
   liability, or tort (including negligence or otherwise) arising in any way
   out of the use of this software, even if advised of the possibility of
   such damage.


Design
------

   Design Priorities:

   1. Security
   2. Minimal Resource Requirements
   3. UI Consistency
   3. Server Portability
   4. Client Portability

   Design Goals:

   1. Web Interface
      1. Ability to view running guests.
      2. Ability to view host information.
      3. Ability to start, stop, reboot guests.
      4. Ability to manage clusters/multiple hosts.


Software Requirements
---------------------

   * GNU GCC 4.2.1
   * GNU Libtool 2.4
   * GNU Autoconf 2.65
   * GNU Automake 1.11.1
   * Git 1.7.2.3
   * Bash Shell
   * Xen 4.3.1
   * Linux 3.10


Maintainers
-----------

   David M. Syzdek,
   Bindle Binaries,
   syzdek@bindlebinaries.com


Source Code
-----------

   The source code for this project is maintained using git
   (http://git-scm.com).  The following contains information to checkout the
   source code from the git repository.

   Browse Source:   https://github.com/bindle/xenherder  
   Git URLs:        git://github.com/bindle/xenherder.git  

   Preparing source from git:

       $ git clone git://github.com/bindle/xenherder.git
       $ cd xenherder
       $ ./autogen.sh

   Git Branches:

      Name    | Description  
      --------|-------------------------------------------------------------  
      master  | Current release of packages.  
      next    | changes staged for next release  
      pu      | proposed updates for next release  
      xx/yy+  | branch for testing new changes before merging to 'pu' branch  


Package Maintence Notes
-----------------------

   This is a collection of notes for developers to use when maintaining this
   package.

   New Release Checklist:

   * GNU GCC 4.2.1
   * Switch to 'master' branch in Git repository.
   * Update version in configure.ac.
   * Update date and version in ChangeLog.
   * Commit configure.ac and ChangeLog changes to repository.
   * Create tag in git repository:

      $ git tag -s v${MAJOR}.${MINOR}

   * Push repository to publishing server:

      $ git push --tags origin master:master next:next pu:pu

   Creating Source Distribution Archives:

       $ ./configure
       $ make update
       $ make distcheck
       $ make dist-bzip2

