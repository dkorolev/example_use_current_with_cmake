# NOTE(dkorolev): 99% of the goal of this `Makefile` is to have `vim` jump to errors on `:mak`.
#
# NOTE(dkorolev): Yes, I am well aware it is ugly to have a `Makefile` for a `cmake`-built project.
#                 Am just too much of a `vi` user to not leverage `:mak`.

.PHONY: release debug release_dir debug_dir release_test debug_test test fmt clean

DEBUG_BUILD_DIR=$(shell echo "$${DEBUG_BUILD_DIR:-.current_debug}")
RELEASE_BUILD_DIR=$(shell echo "$${RELEASE_BUILD_DIR:-.current}")

OS=$(shell uname)
ifeq ($(OS),Darwin)
  CORES=$(shell sysctl -n hw.physicalcpu)
else
  CORES=$(shell nproc)
endif

CLANG_FORMAT=$(shell echo "$${CLANG_FORMAT:-clang-format}")

release: release_dir
	@MAKEFLAGS=--no-print-directory cmake --build "${RELEASE_BUILD_DIR}" -j ${CORES}

release_dir: ${RELEASE_BUILD_DIR}

${RELEASE_BUILD_DIR}: CMakeLists.txt src
	@cmake -DCMAKE_BUILD_TYPE=Release -B "${RELEASE_BUILD_DIR}" .

test: release
	@(cd "${RELEASE_BUILD_DIR}"; make test)

debug: debug_dir
	@MAKEFLAGS=--no-print-directory cmake --build "${DEBUG_BUILD_DIR}" -j ${CORES}

debug_dir: ${DEBUG_BUILD_DIR}

${DEBUG_BUILD_DIR}: CMakeLists.txt src
	@cmake -B "${DEBUG_BUILD_DIR}" .

debug_test: debug
	@(cd "${DEBUG_BUILD_DIR}"; make test)

test: release_test

fmt:
	${CLANG_FORMAT} -i src/*.cc src/*.h

clean:
	rm -rf "${DEBUG_BUILD_DIR}" "${RELEASE_BUILD_DIR}"
