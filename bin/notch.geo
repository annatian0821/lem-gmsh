/*********************************************************************
 *
 *  Notch
 *
 *********************************************************************/

// Mesh size - characteristic length
lc = 0.0125;

// 8 corner points of a cube
Point(1) = {0, 0, 0, lc};
Point(2) = {0.75, 0, 0, lc};
Point(3) = {0.75, 0.75, 0, lc};
Point(4) = {0, 0.75, 0, lc};
Point(5) = {0, 0, 0.13, lc};
Point(6) = {0.75, 0, 0.13, lc};
Point(7) = {0.75, 0.75, 0.13, lc};
Point(8) = {0, 0.75, 0.13, lc};

// 4 point define square crack # 1 near the boundary 
Point(9) = {0.0+lc, 0.375, 0.01, lc}; 
Point(10) = {0.13, 0.375, 0.01, lc};
Point(11) = {0.13, 0.375, 0.12, lc};
Point(12) = {0.0+lc, 0.375, 0.12, lc};

// 4 point define square crack # 2 near the boundary 
Point(13) = {0.62, 0.375, 0.01, lc};
Point(14) = {0.75-lc, 0.375, 0.01, lc};
Point(15) = {0.75-lc, 0.375, 0.12, lc};
Point(16) = {0.62, 0.375, 0.12, lc};

// The distribution of the mesh element sizes is then obtained by
// interpolation of these characteristic lengths throughout the
// geometry.

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

Line(13) = {9,10}; 
Line(14) = {10,11}; 
Line(15) = {11,12};
Line(16) = {12,9}; 

Line(17) = {13,14}; 
Line(18) = {14,15}; 
Line(19) = {15,16}; 
Line(20) = {16,13}; 

//Circle(13) = {10,9,11};
//Circle(14) = {11,9,12};
//Circle(15) = {12,9,13};
//Circle(16) = {13,9,10};

//Line(17) = {14,15};
//Line(18) = {15,16};
//Line(19) = {16,17};
//Line(20) = {17,14};

Line Loop(1) = {1,2,3,4};
Line Loop(2) = {1,6,-9,-5};
Line Loop(3) = {2,7,-10,-6};
Line Loop(4) = {3,8,-11,-7};
Line Loop(5) = {-4,8,12,-5};
Line Loop(6) = {9,10,11,12};

Line Loop(7) = {13,14,15,16}; 
Line Loop(8) = {17,18,19,20}; 

//Line Loop(7) = {13,14,15,16};
//Line Loop(8) = {17,18,19,20};

Plane Surface(1) = {1};
Plane Surface(2) = {2};
Plane Surface(3) = {3};
Plane Surface(4) = {4};
Plane Surface(5) = {5};
Plane Surface(6) = {6};

Plane Surface(7) = {7}; 
Plane Surface(8) = {8}; 

//Plane Surface(7) = {7};
//Plane Surface(8) = {8,7};

Surface Loop(1) = {1,2,3,4,5,6};
Volume(1) = {1};

Surface{7} In Volume{1};
Surface{8} In Volume{1};  

//Surface{7} In Volume{1};

//Surface{8} In Volume{1};

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
Fracture1 = 2001; 
Physical Surface("Fracture1") = {7}; 
Fracture2 = 2002; 
Physical Surface("Fracture2") = {8}; 

//Fracture = 2001;
//Physical Surface("Fracture") = {7} ;
//WeakPlane = 2002;
//Physical Surface("WeakPlane") = {8} ;

MyVolume = 10001;
Physical Volume("MyVolume") = {1} ;

// The third elementary entity is the surface. In order to define a
// simple rectangular surface from the four lines defined above, a
// line loop has first to be defined. A line loop is a list of
// connected lines, a sign being associated with each line (depending
// on the orientation of the line):

// Line Loop(5) = {4,1,-2,3} ;

// We can then define the surface as a list of line loops (only one
// here, since there are no holes--see `t4.geo'):

// Plane Surface(6) = {5} ;
// Line{1000} In Surface{6};
//surf = Extrude {0, 0, 0.04} { Line{102}; };
//vol = Extrude {0, 0, 0.12} { Surface{6}; };
//Surface{surf} In Volume{vol};

// At this level, Gmsh knows everything to display the rectangular
// surface 6 and to mesh it. An optional step is needed if we want to
// associate specific region numbers to the various elements in the
// mesh (e.g. to the line segments discretizing lines 1 to 4 or to the
// triangles discretizing surface 6). This is achieved by the
// definition of `physical entities'. Physical entities will group
// elements belonging to several elementary entities by giving them a
// common number (a region number).

// We can for example group the points 1 and 2 into the physical
// entity 1:

// Physical Point(1) = {1,2} ;

// Consequently, two punctual elements will be saved in the output
// mesh file, both with the region number 1. The mechanism is
// identical for line or surface elements:

// MyLine = 1;
// Physical Line(MyLine) = {102} ;
// Physical Line(MyLine) = {1000} ;
// MySurface = 2;
// Physical Surface(MySurface) = {6} ;

// All the line elements created during the meshing of lines 1, 2 and
// 4 will be saved in the output mesh file with the region number 99;
// and all the triangular elements resulting from the discretization
// of surface 6 will be given an automatic region number (100,
// associated with the label "My fancy surface label").

// Note that if no physical entities are defined, then all the
// elements in the mesh will be saved "as is", with their default
// orientation.

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
