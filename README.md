# Smart Door Lock Emulation with NFC and BLE

Welcome to the **Smart Door Lock Emulation** project, where we bring access control to your doorstep using **NRF52840** microcontroller. This project harnesses the capabilities of NFC (Near Field Communication) and BLE (Bluetooth Low Energy) to deliver a secure and user-friendly door lock system.

## Features

- **NFC Integration:** Seamlessly transfer access credentials from a mobile device to the NRF52840 for swift and contactless entry.
- **BLE Connectivity:** With BLE support, you can perform Device Firmware Updates (DFU) over the air, ensuring your lock stays up-to-date with the latest security patches and features.

## Tools and Scripts

Navigate to the `scripts/` directory to find an assortment of utility scripts:

- `build.py`: Compile the source code into executable binaries.
- `clean.py`: Clean up the build environment by removing the `/workdir/project/build` directory.
- `flash.py`: Flash the compiled code onto the NRF52840 microcontroller.
- `generate_doxygen.py`: Generate comprehensive Doxygen documentation for the project.
- `monitor.py`: Observe and capture logs from the NRF52840 for debugging.
- `run_cpp_checker.py`: Conduct static code analysis with cppcheck to maintain high code standards.
- NOTE: When rerunning unit tests with different arguments, consider cleaning the smart_door_lock/build/tests folder and then rerun them again.
- `run_unit_tests.py`: Execute unit tests to verify each code segment functions as intended.
- `run_unit_tests.py COVERAGE/HTML_COVERAGE`: Execute unit tests with coverage informations(either on terminal or HTML files).
- `run_unit_tests.py VALGRIND`: Execute unit tests with valgrind.
- `run_unit_tests.py COVERAGE/HTML_COVERAGE VALGRIND`: Execute unit tests with coverage informations and valgrind.

## Continuous Integration and Delivery

Our project incorporates a fully automated CI/CD pipeline utilizing GitHub Actions to streamline development:

- **Build Job:** Automatically compiles the source code and assembles the executables.
- **Test Job:** Runs a suite of unit tests to ensure consistent quality and reliable performance.
- **Static Analysis Job:** Employs Cppcheck for a thorough static code analysis, highlighting potential improvements at the earliest stages.

## Getting Started with Docker

**Build the Docker image:**

```sh
docker build -t nrfconnect_smart_door_lock --build-arg sdk_nrf_revision=v2.4-branch .
```

Run the container from the built Docker image:

```sh
docker run -it --privileged --device="device_name_when_connected" -v ${PWD}:/workdir/project --entrypoint bash "docker_image"
```

## Notes

For NFC functionality, I've successfully used the NFC Tools app on a mobile device to interact with the NRF52840 (currently supported messages: "test123" to activate the LED, "turnbleon123" to enable BLE, and "turnbleoff123" to disable BLE). For BLE connections and firmware updates, nRF Connect has proven to be great tool for connecting to and updating the NRF52840.