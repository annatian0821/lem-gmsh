# Lattice Element Method - Mesh Generator (lem-gmsh)
> Cambridge Berkeley - Geomechanics

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/cb-geo/master/license.md)
[![Developer docs](https://img.shields.io/badge/developer-docs-blue.svg)](http://cb-geo.github.io/lem)
[![User docs](https://img.shields.io/badge/user-docs-blue.svg)](https://lem-gmsh-doc.cb-geo.com/)
[![Build status](https://api.travis-ci.org/cb-geo/lem-gmsh.svg)](https://travis-ci.org/cb-geo/lem-gmsh/builds)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/10088/badge.svg)](https://scan.coverity.com/projects/cb-geo-lem-gmsh)
[![codecov.io](http://codecov.io/github/cb-geo/lem-gmsh/coverage.svg?branch=develop)](http://codecov.io/github/cb-geo/lem-gmsh?branch=develop)
[![](https://img.shields.io/github/issues-raw/cb-geo/lem-gmsh.svg)](https://github.com/cb-geo/lem-gmsh/issues)
[![Project management](https://img.shields.io/badge/projects-view-ff69b4.svg)](https://github.com/cb-geo/lem-gmsh/projects/)

## Install dependencies

* Docker image for CB-Geo lem-gmsh code [https://hub.docker.com/r/cbgeo/lem](https://hub.docker.com/r/cbgeo/lem)

* Instructions for running lem docker container: [https://github.com/cb-geo/docker-lem/blob/master/README.md](https://github.com/cb-geo/docker-lem/blob/master/README.md).

### Packages
> These packages can be found in the docker image.

* [Eigen](http://eigen.tuxfamily.org/)
* [Voro++](http://math.lbl.gov/voro++/download/)
* [Intel TBB](https://www.threadingbuildingblocks.org/)

## Compile and Run

0. Run `mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release /path/to/CMakeLists.txt`

1. Run `make clean && make -jN` (where N is the number of cores)

2. Run lem-gmsh `./lem-gmsh -d /path/to/inputfile/`
