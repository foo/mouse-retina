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

build-traverser:
	cd src/traverser && make

build-traverser-client: build-traverser build-config
	cd src/traverser-client && make

run-traverser-client:
	cd bin/ && mpirun -n 2 ./traverser-client

build-config:
	cd src/config && make

build-config-client: build-config
	cd src/config-client && make

run-config-client:
	cd bin/ && ./config-client

build-dataset: build-config
	cd src/dataset && make

build-dataset-client: build-dataset build-config
	cd src/dataset-client && make

run-dataset-client:
	cd bin/ && ./dataset-client

build-edge-detection: build-filters
	cd src/edge-detection && make -B

build-edge-detection-client: build-edge-detection build-config
	cd src/edge-detection-client && make

run-edge-detection-client: clean-edge-detection
	cd bin/ && ./edge-detection-client

build-filters: build-dataset build-image
	cd src/filters && make

build-filters-client: build-filters build-config
	cd src/filters-client && make

run-filters-client: clean-filters-client-pgm
	cd bin/ && ./filters-client

build-image:
	cd src/image && make

build-image-client: build-dataset build-image build-config
	cd src/image-client && make

run-image-client: clean-image-client-pgm
	cd bin && ./image-client

build-clients: build-dataset-client build-image-client build-filters-client

clean-bin:
	rm -f bin/*.o bin/dataset-client bin/image-client bin/filters-client
	cd src/image && make clean
	cd src/dataset && make clean
	cd src/filters && make clean
	cd src/edge-detection && make clean

clean-image-client-pgm:
	rm -f output/image-client/*.pgm

video:
	cd output/image-client && ffmpeg -i slice%d.pgm video.avi

clean-edge-detection:
	rm -f output/edge-detection/*

clean-filters-pgm:
	rm -f output/filters/*.pgm

clean-filters-client-pgm:
	rm -f output/filters-client/*.pgm
