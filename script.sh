#!/bin/bash
set -e

make
./bin/hypergraph_merge datasets NDCC
