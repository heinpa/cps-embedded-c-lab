# CPS Embedded C Lab

This repo contains the code for the first four sessions of the CPS lab course (WS 2024/2025).

## Quick Start

### Install Toolchain

```bash
sudo apt install \
    python3 \
    git \
    tar \
    build-essential \
    cmake \ 
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib
```

### Download Code and Dependencies:

```bash
# Download code
git clone https://github.com/es-ude/cps-embedded-c-lab.git

# Navigate into downloaded folder
cd cps-embedded-c-lab

# Download dependencies
git submodule update --init --recursive
```

### Build/Compile Targets
```bash
# Create `build` folder
mkdir build

# Navigate into `build` folder
cd build

# Create required files for compiling and compile targets
cmake .. && make -j4
```