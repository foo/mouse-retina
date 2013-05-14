download-small-dataset:
	cd images && wget http://www.knossostool.org/e1088_mag1_small.zip
	cd images && unzip e1088_mag1_small.zip

download-large-dataset:
	cd images && wget http://www.knossostool.org/e1088_mag1_large.zip
	cd images && unzip e1088_mag1_large.zip

clean-small-dataset:
	rm -rf images/e1088_mag1_small.zip images/e1088_mag1_small

clean-large-dataset:
	rm -rf images/e1088_mag1_large.zip images/e1088_mag1_large

build-load-cubes:
	cd src/load-cubes && make

build-cubes-client: build-load-cubes
	cd src/cubes-client && make

run-cubes-client:
	cd bin/ && ./cubes-client

build-filters:
	cd src/filters && make

build-filters-client: build-filters
	cd src/filters-client && make

run-filters-client: clean-filters-pgm
	cd bin/ && ./filters-client

build-image:
	cd src/image && make

build-image-client: build-load-cubes build-image
	cd src/image-client && make

run-image-client:
	cd bin && ./image-client

clean-bin:
	rm bin/*.o bin/cubes-client bin/image-client

clean-video-pgm:
	rm output/video/*.pgm

video:
	cd output/video && ffmpeg -i slice%d.pgm video.avi

clean-filters-pgm:
	rm output/filters/*.pgm
