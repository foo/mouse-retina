Project description
==

Reconstructing mouse retina nervous tissue from E2198 dataset.

Compilation
==

Program was developed on Ubuntu 12.04, installing following packages should be enough to compile the program:

`$ apt-get install g++-4.6 make libboost-program-options1.46-dev libboost-filesystem1.46-dev ffmpeg`

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
