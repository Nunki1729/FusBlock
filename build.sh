#!/bin/bash

set -e

echo "Building FusBlock..."

# =========================
# CONFIG
# =========================
ROOT_DIR="$(pwd)"
BUILD_LINUX="build"
BUILD_WIN="build-win"

DIST_LINUX="dist/linux"
DIST_WIN="dist/windows"

EXEC_NAME="FusBlock"

# =========================
# CLEAN OLD BINARIES
# =========================
echo "Cleaning previous builds..."

rm -f "$DIST_LINUX/$EXEC_NAME"
rm -f "$DIST_WIN/$EXEC_NAME.exe"

# =========================
# BUILD LINUX
# =========================
echo "Building Linux version..."

cmake -B "$BUILD_LINUX"
cmake --build "$BUILD_LINUX"

mkdir -p "$DIST_LINUX"
cp "$BUILD_LINUX/$EXEC_NAME" "$DIST_LINUX/"

echo "✔ Linux build ready"

# =========================
# BUILD WINDOWS (MinGW)
# =========================
echo "Building Windows version..."

cmake -B "$BUILD_WIN" \
    -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/mingw-w64-x86_64.cmake\
    -DSFML_DIR=/home/nunki/Escritorio/SFML-win/lib/cmake/SFML

cmake --build "$BUILD_WIN"

mkdir -p "$DIST_WIN"

cp "$BUILD_WIN/$EXEC_NAME.exe" "$DIST_WIN/"

# =========================
# OPTIONAL: DLLs (manual step reminder)
# =========================
echo "Remember: you may need to copy SFML DLLs into dist/windows/"

echo "✔ Windows build ready"

# =========================
# DONE
# =========================
echo "All builds completed successfully!"
echo "   - Linux:   $DIST_LINUX"
echo "   - Windows: $DIST_WIN"