#!/usr/bin/env python3

import subprocess
import os
import sys

TEST_SOURCE_DIR = "/workdir/project/tests/smart_door_lock"
TEST_OUTPUT_DIR = "/workdir/project/smart_door_lock/build/tests"
BUILD_OUTPUT_DIR = "/workdir/project/smart_door_lock/build"

CMAKE_ARGUMENT_1 = ""
CMAKE_ARGUMENT_2 = ""
RUN_COVERAGE_FLAG = False
HTML_COVERAGE_FLAG = False


def build_project():
    os.chdir(TEST_SOURCE_DIR)
    if os.path.exists(TEST_SOURCE_DIR) and os.path.isdir(TEST_SOURCE_DIR):
        try:
            if not (
                os.path.exists(BUILD_OUTPUT_DIR) and os.path.isdir(BUILD_OUTPUT_DIR)
            ):
                os.mkdir(BUILD_OUTPUT_DIR)
            if not (os.path.exists(TEST_OUTPUT_DIR) and os.path.isdir(TEST_OUTPUT_DIR)):
                os.mkdir(TEST_OUTPUT_DIR)
            os.chdir(TEST_OUTPUT_DIR)
            subprocess.check_call(
                ["cmake", CMAKE_ARGUMENT_1, CMAKE_ARGUMENT_2, TEST_SOURCE_DIR]
            )
            subprocess.check_call(["cmake", "--build", "."])
        except subprocess.CalledProcessError:
            sys.exit(1)


def run_tests():
    try:
        subprocess.check_call(["ctest", "--test-dir", TEST_OUTPUT_DIR])
        print(
            "Tests generated at /workdir/project/smart_door_lock/build/tests/Testing/Temporary/LastTest.log"
        )
    except subprocess.CalledProcessError:
        print("Unit tests failed")
        sys.exit(1)


def get_cmake_arguments():
    options = sys.argv

    global CMAKE_ARGUMENT_1
    global CMAKE_ARGUMENT_2
    global RUN_COVERAGE_FLAG
    global HTML_COVERAGE_FLAG

    if "COVERAGE" in options:
        CMAKE_ARGUMENT_1 = "-DCOVERAGE=ON"
        RUN_COVERAGE_FLAG = True
    elif "HTML_COVERAGE" in options:
        CMAKE_ARGUMENT_1 = "-DHTML_COVERAGE=ON"
        RUN_COVERAGE_FLAG = True
        HTML_COVERAGE_FLAG = True

    if "VALGRIND" in options:
        CMAKE_ARGUMENT_2 = "-DVALGRIND=ON"


def run_coverage():
    print("Coverage results: ")
    os.chdir(TEST_OUTPUT_DIR)
    subprocess.call(["make", "coverage"])
    if HTML_COVERAGE_FLAG:
        print("Coverage html are inside /workspace/tests/build/coverage folder")


if __name__ == "__main__":
    if len(sys.argv) > 1 and len(sys.argv) < 4:
        get_cmake_arguments()

    build_project()
    run_tests()
    if RUN_COVERAGE_FLAG:
        run_coverage()
