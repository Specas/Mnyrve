#!/bin/bash

BASE_DIR=$(pwd)

PYTHON_DIR='/visualization/python'

EXPORT_DIR="$BASE_DIR$PYTHON_DIR"

export PYTHONPATH=$PYTHONPATH:$EXPORT_DIR

