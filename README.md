Project description
==

Reconstructing mouse retina nervous tissue from E2198 dataset.

Compilation
==

Program was developed on Ubuntu 12.04, installing following packages should be enough to compile the program:

`$ apt-get install g++-4.6 make libboost-program-options1.46-dev libboost-filesystem1.46-dev`

Usage
==

Run following command to download sample dataset from [knossostool.org](http://www.knossostool.org/get.html):

`$ make download-small-dataset`

Run following command to build load-cubes library:

`$ make build-load-cubes`

Run following command to build simple client of load-cubes library:

`$ make build-cubes-client`

Run following command to launch simple client of load-cubes library:

`$ make run-cubes-client`
