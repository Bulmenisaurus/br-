#!/usr/bin/env bash

# * make sure to chmod this script (chmod u+x build.sh) so you can run it like ./build.sh your args here

# https://sharats.me/posts/shell-script-best-practices/
# https://www.shellcheck.net/
set -o errexit
set -o nounset
# https://unix.stackexchange.com/a/304935
g++ -Wall -Wextra -pedantic main.cpp -o main && ./main "${@:1}"