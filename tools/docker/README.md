# docker tools

This directory provides tools to build moteus using docker for environment and virtualisation management.

Moteus manages its own dependencies well via Bazel, but it can still only be run on x86_64 Ubuntu.

This container + script (./env) provides a way to run the build and test tools on other platforms (eg. my M1 Macbook).

| OS      | State                       |
| ------- | --------------------------- |
| Linux   | Untested - expected to work |
| OSx     | Working 👌                   |
| Windows | Untested - expected to work |

## Setup Notes

This approach has been developed using [docker desktop](https://www.docker.com/products/docker-desktop/)

For OSx specifically, enabling the option "Use Rosetta for x86/amd64 emulation on Apple Silicon" should vastly improve performance.


## Usage

### Quick Build and Copy

For a one-command build that automatically copies outputs to `build_output/`:

```bash
./tools/docker/build-and-copy
```

This will:
1. Build the Docker image
2. Build the moteus firmware 
3. Automatically copy all build outputs to `build_output/` folder
4. List the generated files

### Interactive Development

For interactive development and debugging:

```bash
./tools/docker/env
```

This opens an interactive shell where you can:

- Build firmware: `./tools/bazel build --config=target //:target`
- Copy outputs manually: `copy_build_outputs`
- Build and copy in one command: `./tools/bazel build --config=target //:target && copy_build_outputs`

### Build Outputs

The following files will be copied to `build_output/` after a successful build:

- `moteus.elf` - Main firmware ELF file
- `can_bootloader.elf` - CAN bootloader ELF file  
- `moteus.08000000.bin` - ISR vector binary
- `moteus.0800c000.bin` - Bootloader binary
- `moteus.08010000.bin` - Main firmware binary

These files can be used for flashing or further development.

## Flashing Firmware

### Option 1: Flash with Docker (Recommended for Docker users)

If you're using Docker and have an ST-Link programmer connected:

```bash
./tools/docker/env-flash
```

This opens a Docker container with USB device access. Inside the container, you can flash using:

```bash
# Flash with pre-built binaries from build_output/
python3 fw/flash.py build_output/moteus.elf build_output/can_bootloader.elf

# Or flash with freshly built firmware
./tools/bazel build --config=target //:target
python3 fw/flash.py
```

### Option 2: Flash Directly (Native Linux/WSL)

If you're running on native Linux or WSL with direct USB access:

```bash
# Build first if needed
./tools/bazel build --config=target //:target

# Flash the firmware
python3 fw/flash.py

# Or specify custom ELF files
python3 fw/flash.py path/to/moteus.elf path/to/bootloader.elf
```

### Option 3: Using Bazel Flash Target

You can also use the Bazel flash target:

```bash
./tools/bazel run --config=target //fw:flash
```

### Flashing Options

- Add `--erase` to perform a full chip erase before flashing
- The flash script expects an ST-Link programmer to be connected
- Default paths point to `bazel-out/stm32g4-opt/bin/fw/` but you can specify custom paths

