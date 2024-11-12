#!/usr/bin/bash
# https://stackoverflow.com/a/1482133
export SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
fuego --config "$SCRIPT_DIR/configfile"
