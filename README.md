About
=====

PSoC Tools is a collection of projects that enable the programmer to
quickly incorporate a range of useful functionality into their next
[Cypress][cypress] [PSoC][psoc] embedded application.

The first project to be added to PSoC Tools is the Code Vault.
 
[cypress]: http://www.cypress.com/
[psoc]: http://www.cypress.com/psoc/

Installation
============

PSoC Tools is distributed as a self-contained Cypress Creator workspace. To
install it, either:

1. Clone the repository to your local machine using git, or
2. Download the repository as a zip file and unpack it.

With this accomplished, generate the documentation for the code vault project
using [Doxygen][doxygen]. To do this, simply run the project Doxyfile, which
is located in the Doxygen directory. Note that Graphviz must be installed in
addition to Doxygen itself.

With the documentation generated, verify that both hardware and software are
setup properly. This is best done by running the test unit of each of the
libraries contained in the code vault.

[doxygen]: http://www.stack.nl/~dimitri/doxygen/

Compatibility
=============

PSoC Tools has been written using the following software:

* Cypress Creator 2.2 SP1
* Doxygen 1.8.3
* git 1.8.0
* Graphviz 2.28

The code has been tested on a Cypress CY8CKIT-001 development kit fitted with
a PSoC5 CY8C5568AXI-060 module.

License
=======

PSoC Tools is released under the [GNU General Public License][license].

[license]: http://www.gnu.org/licenses/gpl.html

Authors
=======

Code by Rodney Elliott, <rodney.elliott@gmail.com>

The doubly linked list and circular linked list libraries are based upon code
by Richard Heathfield. This code was contained on the CD that accompanied the
book [C Unleashed][book], and was released under the GPL.

[book]: http://www.amazon.com/C-Unleashed-Richard-Heathfield/dp/0672318962
