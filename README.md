# ReadGMSH
> Read GMSH and create nodes, fractures for LEM

## Compile & Run
0. Run `autoreconf -fi`, if `configure` script is missing.

1. Run `./configure`

2. make clean && make -jN (where N is the number of cores)

3. Run readgmsh `./readgmsh`