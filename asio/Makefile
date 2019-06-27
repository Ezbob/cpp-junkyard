BUILD_DIR=build
BUILD_TOOL?=ninja
BUILD_TOOL_CMAKE?=Ninja

all: _build

_build: ${BUILD_DIR}
	@cd ${BUILD_DIR} && ${BUILD_TOOL}

${BUILD_DIR}:
	@mkdir $@
	@cd $@ && cmake -G "${BUILD_TOOL_CMAKE}" ..

clean:
	${RM} -r ${BUILD_DIR}

help:
	@echo "Available targets:"
	@echo "  - all: Builds the binary in the '${BUILD_DIR}' directory"
	@echo "  - clean: Removes the '${BUILD_DIR}' directory and all its content"
