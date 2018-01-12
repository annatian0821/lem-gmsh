// The simplest construction in Gmsh's scripting language is the
// `affectation'. The following command defines a new variable `lc':

lc = 1.0;

// This variable can then be used in the definition of Gmsh's simplest
// `elementary entity', a `Point'. A Point is defined by a list of
// four numbers: three coordinates (X, Y and Z), and a characteristic
// length (lc) that sets the target element size at the point:

// 8 corner points of a cube
Point(1) = {0, 0, 0, lc};
Point(2) = {50.0, 0, 0, lc};
Point(3) = {50.0, 50.0, 0, lc};
Point(4) = {0, 50.0, 0, lc};
Point(5) = {0, 0, 50.0, lc};
Point(6) = {50.0, 0, 50.0, lc};
Point(7) = {50.0, 50.0, 50.0, lc};
Point(8) = {0, 50.0, 50.0, lc};

Line(1) = {1,2} ;
Line(2) = {2,3} ;
Line(3) = {3,4} ;
Line(4) = {4,1} ;
Line(5) = {1,5} ;
Line(6) = {2,6} ;
Line(7) = {3,7} ;
Line(8) = {4,8} ;
Line(9) = {5,6} ;
Line(10) = {6,7} ;
Line(11) = {7,8} ;
Line(12) = {8,5} ;

Line Loop(1) = {1,2,3,4};
Line Loop(2) = {1,6,-9,-5};
Line Loop(3) = {2,7,-10,-6};
Line Loop(4) = {3,8,-11,-7};
Line Loop(5) = {-4,8,12,-5};
Line Loop(6) = {9,10,11,12};

Plane Surface(1) = {1};
Plane Surface(2) = {2};
Plane Surface(3) = {3};
Plane Surface(4) = {4};
Plane Surface(5) = {5};
Plane Surface(6) = {6};

Surface Loop(1) = {1,2,3,4,5,6};
Volume(1) = {1};


BottomBottomLine = 101;
Physical Line("BottomBottomLine") = 1;
RightBottomLine = 102;
Physical Line("RightBottomLine") = 2;
TopBottomLine = 103;
Physical Line("TopBottomLine") = 3;
LeftBottomLine = 104;
Physical Line("LeftBottomLine") = 4;
SideBottomLeftLine = 105;
Physical Line("SideBottomLeftLine") = 5;
SideBottomRightLine = 106;
Physical Line("SideBottomRightLine") = 6;
SideTopRightLine = 107;
Physical Line("SideTopRightLine") = 7;
SideTopLeftLine = 108;
Physical Line("SideTopLeftLine") = 8;
BottomTopLine = 109;
Physical Line("BottomTopLine") = 9;
RightTopLine = 110;
Physical Line("RightTopLine") = 10;
TopTopLine = 111;
Physical Line("TopTopLine") = 11;
LeftTopLine = 112;
Physical Line("LeftTopLine") = 12;

BottomSurface = 1001;
Physical Surface("BottomSurface") = {1} ;
SideBottomSurface = 1002;
Physical Surface("SideBottomSurface") = {2} ;
SideRightSurface = 1003;
Physical Surface("SideRightSurface") = {3} ;
SideTopSurface = 1004;
Physical Surface("SideTopSurface") = {4} ;
SideLeftSurface = 1005;
Physical Surface("SideLeftSurface") = {5} ;
TopSurface = 1006;
Physical Surface("TopSurface") = {6} ;

MyVolume = 10001;
Physical Volume("MyVolume") = {1} ;

// 2D mesh algorithm (1=MeshAdapt, 2=Automatic, 5=Delaunay, 6=Frontal,
// 7=bamg, 8=delquad)
Mesh.Algorithm = 5;

// Apply recombination algorithm to all surfaces, ignoring per-surface
// spec Default value: '0'
Mesh.RecombineAll = 0;

// Mesh recombination algorithm (0=standard, 1=blossom)
Mesh.RecombinationAlgorithm = 0;

// Remeshing algorithm (0=no split, 1=automatic, 2=automatic)
Mesh.RemeshAlgorithm = 1;

// Remeshing using discrete parametrization (0=harmonic_circle,
// 1=conformal_spectral, 2=rbf, 3=harmonic_plane, 4=convex_circle,
// 5=convex_plane, 6=harmonic square, 7=conformal_fe
Mesh.RemeshParametrization = 1;

// Number of smoothing steps applied to the final mesh
Mesh.Smoothing = 50;

// Don't extend the elements sizes from the boundary inside the domain (0)
// Mesh.CharacteristicLengthExtendFromBoundary = 0;
