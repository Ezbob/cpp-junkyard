PROJECT_ROOT=$(shell pwd)

BUILD_PREFIX=build
BUILD_SYSTEM="Unix Makefiles"
BUILD_FILE=Makefile
BUILD_EXEC=${MAKE}
BUILD_ARGS=-j

RELEASE_BUILD_DIR=release
DEBUG_BUILD_DIR=debug

all: _build_release

release: _build_release

debug: _build_debug

_build_release: ${BUILD_PREFIX}/${RELEASE_BUILD_DIR}/${BUILD_FILE}
	cd ${BUILD_PREFIX}/${RELEASE_BUILD_DIR} && ${BUILD_EXEC} ${BUILD_ARGS} 

${BUILD_PREFIX}/${RELEASE_BUILD_DIR}/${BUILD_FILE}:
	@mkdir -p $(@D) && cd $(@D) && cmake -DCMAKE_BUILD_DIR=$(@D) -DCMAKE_BUILD_TYPE=Release -G${BUILD_SYSTEM} ${PROJECT_ROOT}

_build_debug: ${BUILD_PREFIX}/${DEBUG_BUILD_DIR}/${BUILD_FILE}
	cd ${DEBUG_BUILD_DIR} && ${BUILD_EXEC} ${BUILD_ARGS} 

${BUILD_PREFIX}/${DEBUG_BUILD_DIR}/${BUILD_FILE}:
	@mkdir -p $(@D) && cd $(@D) && cmake -DCMAKE_BUILD_DIR=$(@D) -DCMAKE_BUILD_TYPE=Debug -G${BUILD_SYSTEM} ${PROJECT_ROOT}

clean:
	${RM} -r ${BUILD_PREFIX}