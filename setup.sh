#!/usr/bin/env bash

############################
# 

set -e

TARGET=i686-elf

BINUTILS_VERSION=2.45
GCC_VERSION=15.3.0

PREFIX="$HOME/opt/cross"
SRC_DIR="$HOME/src"

echo "=== ColossOS development environment setup ==="

# ------------------------------------------------------------
# 1. Make sure we're running inside MSYS2
# ------------------------------------------------------------

if [ -z "$MSYSTEM" ]; then
    echo "ERROR: This script must be run from an MSYS2 shell."
    exit 1
fi

echo "MSYS2 environment: $MSYSTEM"

# ------------------------------------------------------------
# 2. Install build dependencies
# ------------------------------------------------------------

echo
echo "=== Installing MSYS2 dependencies ==="

pacman -S --needed --noconfirm \
    base-devel \
    gcc \
    make \
    bison \
    flex \
    gmp-devel \
    mpfr-devel \
    mpc-devel \
    texinfo \
    wget \
    nasm

# QEMU is distributed through the MinGW64 repository
pacman -S --needed --noconfirm mingw-w64-x86_64-qemu

# ------------------------------------------------------------
# 3. Set up directories
# ------------------------------------------------------------

echo
echo "=== Preparing cross-compiler directories ==="

mkdir -p "$PREFIX"
mkdir -p "$SRC_DIR"

export PATH="/mingw64/bin:$PREFIX/bin:$PATH"

cd "$SRC_DIR"

# ------------------------------------------------------------
# 4. Download Binutils
# ------------------------------------------------------------

if [ ! -d "binutils-$BINUTILS_VERSION" ]; then

    echo
    echo "=== Downloading Binutils $BINUTILS_VERSION ==="

    if [ ! -f "binutils-$BINUTILS_VERSION.tar.xz" ]; then
        wget "https://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.xz"
    fi

    tar -xf "binutils-$BINUTILS_VERSION.tar.xz"
fi

# ------------------------------------------------------------
# 5. Build Binutils
# ------------------------------------------------------------

if ! command -v "$TARGET-ld" >/dev/null 2>&1; then

    echo
    echo "=== Building Binutils for $TARGET ==="

    rm -rf build-binutils
    mkdir build-binutils
    cd build-binutils

    "../binutils-$BINUTILS_VERSION/configure" \
        --target="$TARGET" \
        --prefix="$PREFIX" \
        --with-sysroot \
        --disable-nls \
        --disable-werror

    make -j"$(nproc)"
    make install

    cd "$SRC_DIR"

else
    echo
    echo "Binutils already installed. Skipping."
fi

# ------------------------------------------------------------
# 6. Download GCC
# ------------------------------------------------------------

if [ ! -d "gcc-$GCC_VERSION" ]; then

    echo
    echo "=== Downloading GCC $GCC_VERSION ==="

    if [ ! -f "gcc-$GCC_VERSION.tar.xz" ]; then
        wget "https://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.xz"
    fi

    tar -xf "gcc-$GCC_VERSION.tar.xz"
fi

# ------------------------------------------------------------
# 7. Build GCC
# ------------------------------------------------------------

if ! command -v "$TARGET-gcc" >/dev/null 2>&1; then

    echo
    echo "=== Building GCC for $TARGET ==="

    rm -rf build-gcc
    mkdir build-gcc
    cd build-gcc

    "../gcc-$GCC_VERSION/configure" \
        --target="$TARGET" \
        --prefix="$PREFIX" \
        --disable-nls \
        --enable-languages=c \
        --without-headers

    make -j"$(nproc)" all-gcc
    make -j"$(nproc)" all-target-libgcc

    make install-gcc
    make install-target-libgcc

    cd "$SRC_DIR"

else
    echo
    echo "GCC cross-compiler already installed. Skipping."
fi

# ------------------------------------------------------------
# 8. Permanently add tools to PATH
# ------------------------------------------------------------

PATH_LINE='export PATH="/mingw64/bin:$HOME/opt/cross/bin:$PATH"'

if ! grep -Fq "$PATH_LINE" "$HOME/.bashrc" 2>/dev/null; then
    echo
    echo "=== Adding toolchain to ~/.bashrc ==="
    echo "$PATH_LINE" >> "$HOME/.bashrc"
fi

export PATH="/mingw64/bin:$HOME/opt/cross/bin:$PATH"

# ------------------------------------------------------------
# 9. Verify installation
# ------------------------------------------------------------

echo
echo "=== Verifying installation ==="

echo
echo "Cross compiler:"
"$TARGET-gcc" --version | head -n 1

echo
echo "Cross linker:"
"$TARGET-ld" --version | head -n 1

echo
echo "NASM:"
nasm -v

echo
echo "QEMU:"
qemu-system-i386 --version | head -n 1

echo
echo "Target:"
"$TARGET-gcc" -dumpmachine

echo
echo "=== Setup complete ==="
echo
echo "You can now run:"
echo
echo "    cd /c/Github/ColossOS"
echo "    make run"