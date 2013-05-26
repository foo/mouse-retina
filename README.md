Project description
==

Reconstructing mouse retina nervous tissue from E2198 dataset.

Compilation
==

Program was developed on Ubuntu 12.04, installing following packages should be enough to compile the program:

<code>
$ apt-get install g++-4.6 make libboost-program-options1.46-dev \
                  libboost-filesystem1.46-dev libboost-mpi1.46-dev ffmpeg openmpi-bin<code>

Video of going through tissue
==

Run following command to download sample dataset from [knossostool.org](http://www.knossostool.org/get.html):

`$ make download-small-dataset`

Build and run program and render a video.

`$ make build-image-client`

`$ make run-image-client`

`$ make video`

Video should appear in output/video/ under name video.avi.

Edge detection
==

After downloading small dataset:

`$ make build-filters-client`

`$ make run-filters-client`

Original image of slice and slice image after different filters should appear in output/filters directory.

Running knossostool
==

To run knossos from the command line with a chosen data set (from the knossos directory)

`$ ./knossos --data-path=path-to-folder-with-data-set`

Remember not to enclose path with apostrophes! (knossos parses the path brutally after the equality sign) For example, this is a valid way:

`$ ./knossos --data-path=e1088_mag1_small`

Organization of source code
==

Program is structured into three modules: dataset, image and filters. Dependencies between modules are as follows: image stands alone, dataset depends on image, filters depends on image. Each module consists of several submodules, which are all linked into one bin/<module-name>-module.o object file. Each module can be built from project root directory with `make build-<module-name>` command.

Image module consists of:

* image class, which keeps pixel data in std::vector as well as image dimensions
* pgm export module, that exports image to Portable GrayMap format
* binary operations module, which contains operations on images, whose colors are only black and white (only 0 and 255 values allowed).

Dataset module consists of:

* dataset module that is the main submodule; it is responsible for managing in-memory cache of cubes
* coordinate class that is simple 3-element tuple; custom order is defined, which is lexicographical with z being the most significant coordinate
* dataset files module that iterates through dataset directory, parses names of the files and keeps pairs of < coordinate, pathname >
* cube class that loads .raw files into memory and allows to access voxels of loaded cube
* cross-section module that loads any slice of any place in dataset; cross-section can range across cubes
* config module that loads knossos configuration file; this module is unused in rest of the program

Filters module consists of:

* generic box filter implementation
* filters like gaussian, sobel, sharpening filter
* Minkowski operations: erosion and dilation
* threshold operation

For each module there is corresponding client module that tests functionality of the module and provides example usage.