download-small-dataset:
	cd images && wget http://www.knossostool.org/e1088_mag1_small.zip
	cd images && unzip e1088_mag1_small.zip

clean-small-dataset:
	rm -rf images/e1088_mag1_small.zip images/e1088_mag1_small

build-load-cubes:
	cd src/load-cubes && make

build-cubes-client: build-load-cubes
	cd src/cubes-client && make

run-cubes-client:
	cd bin/ && ./cubes-client

build-image:
	cd src/image && make

build-image-client: build-image build-load-cubes
	cd src/image-client && make

run-image-client:
	cd bin && ./image-client

clean-bin:
	rm bin/*.o bin/cubes-client
