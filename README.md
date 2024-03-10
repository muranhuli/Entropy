# HypergraphMerge

## Introduction

This repository contains the source code for HypergraphMerge.

## Experimental Dataset

The experimental datasets are obtained from <http://www.cs.cornell.edu/~arb/data/>

## Environment Configuration

The environment configuration for this project is as follows:

1. Ubuntu version is `Ubuntu 22.04.3 LTS`.
2. g++ version is `gcc version 11.4.0 (Ubuntu 11.4.0-1ubuntu1~22.04)`.
3. C++ version is `C++11`.
4. Python version is `python 3.11.5`.

## Execution

### Git clone this project

```bash
git clone https://github.com/muranhuli/HypergraphMerge.git
```

### Install spdlog

This project uses `spdlog` as the logger, and you need to install it.

For detailed information of `spdlog`, see [here](https://github.com/gabime/spdlog).

Compiled version (recommended - much faster compile times)

```bash
cd HypergraphMerge
git clone https://github.com/gabime/spdlog.git
cd spdlog && mkdir build && cd build
cmake .. && make -j
```

### Run the Project

```bash
make
```