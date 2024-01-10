#!/usr/bin/env python3

import os
import subprocess

dir_path = "/workdir/project/output"
file_path = os.path.join(dir_path, "report.log")

os.makedirs(dir_path, exist_ok=True)

if not os.path.isfile(file_path):
    open(file_path, "a").close()

if os.path.isfile("/workdir/project/smart_door_lock/build/compile_commands.json"):
    subprocess.run(
        [
            "cppcheck",
            "--enable=all",
            "--inline-suppr",
            "/workdir/project/smart_door_lock/",
            "--output-file=/workdir/project/output/report.log",
            "-i/workdir/project/smart_door_lock/build/zephyr/misc/generated/configs.c",
            "-i/workdir/project/smart_door_lock/build/mcuboot/zephyr/misc/generated/configs.c",
            "-i/workdir/project/smart_door_lock/build/CMakeFiles/3.28.1/CompilerIdCXX/CMakeCXXCompilerId.cpp",
            "-i/workdir/project/smart_door_lock/build/CMakeFiles/3.28.1/CompilerIdC/CMakeCCompilerId.c",
            "-i/workdir/project/smart_door_lock/build/mcuboot/CMakeFiles/3.28.1/CompilerIdC/CMakeCCompilerId.c",
            "-i/workdir/project/smart_door_lock/build/mcuboot/CMakeFiles/3.28.1/CompilerIdCXX/CMakeCXXCompilerId.cpp"
        ]
    )
else:
    os.chdir("/workdir/project")
    subprocess.run(["./scripts/build.py"])
    subprocess.run(
        [
            "cppcheck",
            "--enable=all",
            "--inline-suppr",
            "smart_door_lock/",
            "--output-file=/workdir/project/output/report.log",
            "-i/workdir/project/smart_door_lock/build/zephyr/misc/generated/configs.c",
            "-i/workdir/project/smart_door_lock/build/mcuboot/zephyr/misc/generated/configs.c",
            "-i/workdir/project/smart_door_lock/build/CMakeFiles/3.28.1/CompilerIdCXX/CMakeCXXCompilerId.cpp",
            "-i/workdir/project/smart_door_lock/build/CMakeFiles/3.28.1/CompilerIdC/CMakeCCompilerId.c",
            "-i/workdir/project/smart_door_lock/build/mcuboot/CMakeFiles/3.28.1/CompilerIdC/CMakeCCompilerId.c",
            "-i/workdir/project/smart_door_lock/build/mcuboot/CMakeFiles/3.28.1/CompilerIdCXX/CMakeCXXCompilerId.cpp"
        ]
    )

# Clean non-printable characters
with open(file_path, "r", encoding="utf-8") as file:
    content = file.read()

clean_content = "".join(ch for ch in content if ch.isprintable() or ch.isspace())
with open(file_path, "w", encoding="utf-8") as file:
    file.write(clean_content)

# Remove specific patterns
for number in range(0, 101):
    clean_content = clean_content.replace("[{}m".format(number), "")

with open(file_path, "w", encoding="utf-8") as file:
    file.write(clean_content)

# Check for errors
with open(file_path, "r", encoding="utf-8") as file:
    if "error" in file.read().lower():
        print("Errors found in output/report.log")
        exit(1)
    else:
        print("No errors found in output/report.log")
