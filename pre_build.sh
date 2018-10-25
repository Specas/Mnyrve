#!/usr/bin/env bash

BASE_DIR=$(pwd)
PYTHON_VISUALIZATION_DIR='/visualization/python'
PYTHON_EXPORT_DIR="$BASE_DIR$PYTHON_VISUALIZATION_DIR"

# Adding to files
echo $BASE_DIR > tools/data/mnyrve_path.txt
echo $PYTHON_EXPORT_DIR > tools/data/python_paths.txt
