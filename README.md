# WAPRED [![Build Status](https://api.travis-ci.org/wilseypa/warped.png)](https://travis-ci.org/wilseypa/warped)

A Parallel & Distributed Discrete Simulation Library

For a collection of Simulation Models that use this library, see 
[warped-models](https://github.com/wilseypa/warped-models).

# Building

WARPED is built with a C++11 compiler (see [here](http://lektiondestages.blogspot.de/2013/05/installing-and-switching-gccg-versions.html) for instructions about upgrading and switching GCC versions if you have an old version of GCC that does not support the required features.).  

#### Building from the Git repository

To build from the git repository, first clone a local copy.

	git clone https://github.com/wilseypa/pdes.git $HOME/warped

You can run the Autotools build without any options, although specifying a prefix (install location) is recommended.

	autoreconf -i && ./configure --prefix=$HOME/lib/warped && make && make install

#### Building from a tarball

To build from a source tarball, first download and extract [the latest release from GitHub](https://github.com/wilseypa/warped/releases). `cd` into the directory you extracted the tarball to, and run the following command:

	./configure --prefix=$HOME/lib/warped && make && make install

This will build and install the warped library to the path specified by the `--prefix` configuration option. If you omit the prefix, the library will be installed to `/usr`.

#### Troubleshooting

If you get a linker error telling you that the MPI library couldn't be found, you may need to specify the path to the MPI headers and libraries manually in the configuration step. You can specify the path to the library file with the `--with-mpich` configure option, and the header location with the `--with-mpiheader` option.

 	./configure --with-mpiheader=/usr/include/mpich --with-mpich=/usr/lib/mpich2

Replace the paths in the above example with the locations of the MPI libraries and headers on your machine. 

#### Silent Build Rules

By default, the output of `make` is very verbose. WARPED is configured to support silent build rules on Automake versions 1.10 and newer. To build with silent rules, pass the `--enable-silent-rules` flag to `configure`.

    ./configure --prefix=$HOME/lib/warped --enable-silent-rules


# Prerequisites
WARPED depends on an MPI implementation. It has only been tested with [mpich](http://www.mpich.org/), although other implementations may work.

If building from the git repository instead of a tarball, you  will also need the GNU Autotools tool-chain, including Automake, Autoconf, and Libtool.


# License
The WARPED code in this repository is licensed under the MIT license, unless otherwise specified. The full text of the MIT license can be found in the `LICENSE.txt` file. 

WARPED depends on some third party libraries which are redistributed in the `thirdparty/` folder. Each third party library used is licensed under a license that can be found at the top of each file for which the license applies.
