# Lattice Element Method - GMSH (lem-gmsh)
> Cambridge Berkeley - Geomechanics

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/cb-geo/develop/license.md)
[![CircleCI](https://circleci.com/gh/cb-geo/lem-gmsh.svg?style=svg)](https://circleci.com/gh/cb-geo/lem-gmsh)
[![Build status](https://api.travis-ci.org/cb-geo/lem-gmsh.svg)](https://travis-ci.org/cb-geo/lem-gmsh/builds)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/10088/badge.svg)](https://scan.coverity.com/projects/cb-geo-lem-gmsh)
[![codecov.io](http://codecov.io/github/cb-geo/lem-gmsh/coverage.svg?branch=develop)](http://codecov.io/github/cb-geo/lem-gmsh?branch=develop)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/0912b6e6e3d144d6b695067e0b815420)](https://www.codacy.com/app/CB-Geo/lem-gmsh/)
[![](https://img.shields.io/github/issues-raw/cb-geo/lem-gmsh.svg)](https://github.com/cb-geo/lem-gmsh/issues)
[![Project management](https://img.shields.io/badge/projects-view-ff69b4.svg)](https://github.com/cb-geo/lem-gmsh/projects/)

## Install dependencies

* Docker image for CB-Geo lem-gmsh code [https://hub.docker.com/r/cbgeo/lem](https://hub.docker.com/r/cbgeo/lem)

* Instructions for running lem docker container: [https://github.com/cb-geo/docker-lem/blob/master/README.md](https://github.com/cb-geo/docker-lem/blob/master/README.md).

## Create a GMSH file

* Make sure `gmsh` is installed. 

* To generate a mesh file in 3D (for example to mesh the `bin/tension.geo`) run `gmsh -3 tension.geo`, this will create a `tension.msh` file, which can be found in the `bin/` directory as well.

## Compile and Run

0. Run `mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release /path/to/CMakeLists.txt`

1. Run `make clean && make -jN` (where N is the number of cores)

2. Run lem-gmsh `./lem-gmsh /path/to/meshfile.msh` this will generate a `nodes.txt` file in the `build` directory.
