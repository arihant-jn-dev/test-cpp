#!/usr/bin/env bash
# Build and run every test_*.cpp and demos/*.cpp under this folder.
#
# Usage:
#   ./run_all.sh                  # everything
#   ./run_all.sh design_patterns  # only paths containing "design_patterns"
#
# Binaries, logs and any files the programs write go to build/.

cd "$(dirname "$0")" || exit 1

BUILD_DIR=build
TIMEOUT_SECS=10
mkdir -p "$BUILD_DIR"

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

passed=0
failed=0

sources=$(find . \( -path ./build -o -path ./archive \) -prune -o \
               \( -name 'test_*.cpp' -o -path './demos/*.cpp' \) -print | sort)

for src in $sources; do
    src=${src#./}
    if [[ -n "$1" && "$src" != *"$1"* ]]; then
        continue
    fi

    name=$(echo "${src%.cpp}" | tr '/' '_')

    if ! g++ -std=c++17 "$src" -o "$BUILD_DIR/$name" 2>"$BUILD_DIR/$name.compile.log"; then
        printf "${RED}COMPILE FAIL${NC}  %s  (see %s)\n" "$src" "$BUILD_DIR/$name.compile.log"
        failed=$((failed + 1))
        continue
    fi

    # Run from build/ so files the programs create don't land next to the sources.
    if (cd "$BUILD_DIR" && perl -e "alarm $TIMEOUT_SECS; exec @ARGV" "./$name" >"$name.out" 2>&1); then
        printf "${GREEN}PASS${NC}          %s\n" "$src"
        passed=$((passed + 1))
    else
        printf "${RED}RUN FAIL${NC}      %s  (see %s)\n" "$src" "$BUILD_DIR/$name.out"
        failed=$((failed + 1))
    fi
done

echo
echo "Passed: $passed   Failed: $failed"
[[ $failed -eq 0 ]]
