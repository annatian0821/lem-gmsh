/*********************************************************************
 *
 *  Gmsh tutorial 1
 *
 *  Variables, elementary entities (points, lines, surfaces), physical
 *  entities (points, lines, surfaces)
 *
 *********************************************************************/

// The simplest construction in Gmsh's scripting language is the
// `affectation'. The following command defines a new variable `lc':

lc = 0.05;

// This variable can then be used in the definition of Gmsh's simplest
// `elementary entity', a `Point'. A Point is defined by a list of
// four numbers: three coordinates (X, Y and Z), and a characteristic
// length (lc) that sets the target element size at the point:

// 8 corner points of a cube
Point(1) = {0, 0, 0, lc};
Point(2) = {1.0, 0, 0, lc};
Point(3) = {1.0, 1.0, 0, lc};
Point(4) = {0, 1.0, 0, lc};
Point(5) = {0, 0, 1.0, lc};
Point(6) = {1.0, 0, 1.0, lc};
Point(7) = {1.0, 1.0, 1.0, lc};
Point(8) = {0, 1.0, 1.0, lc};

// 5 point define a circular crack at the centre
//Point(9) = {0.5,0.5,0.5, lc};
//Point(10) = {0.75,0.5,0.5, lc};
//Point(11) = {0.5,0.75,0.5, lc};
//Point(12) = {0.25,0.5,0.5, lc};
//Point(13) = {0.5,0.25,0.5, lc};

// oblique fracture 1 connecting existing points 7, 6, 1, 4
// edit oblique fracture 1 using new 4 points 
Point(22) = {0.8, 0.8, 0.8, lc};
Point(23) = {0.8, 0.2, 0.8, lc};
Point(24) = {0.2, 0.8, 0.2, lc};
Point(25) = {0.2, 0.2, 0.2, lc};

// points for oblique fracture 2
Point(14) = {0.75,0.2,0.5,lc};
Point(15) = {0.75,0.8,0.5,lc};
Point(16) = {0.5,0.2,0.25,lc}; 
Point(17) = {0.5,0.8,0.25,lc}; 

// points for oblique fracture 3
Point(18) = {0.4,0.2,0.8,lc};
Point(19) = {0.4,0.8,0.8,lc};
Point(20) = {0.2,0.8,0.6,lc};
Point(21) = {0.2,0.2,0.6,lc};

// points for fracture 4
//Point(26) = {0.8,0.8,0.2,lc};
//Point(27) = {0.8,0.2,0.2,lc};
//Point(28) = {0.3,0.8,0.7,lc};
//Point(29) = {0.3,0.2,0.7,lc};

// points for fracture 5
//Point(30) = {0.9,0.8,0.6,lc};
//Point(31) = {0.9,0.2,0.6,lc};
//Point(32) = {0.6,0.8,0.9,lc};
//Point(33) = {0.6,0.2,0.9,lc};

// points for fracture 6
Point(34) = {0.2,0.8,0.45,lc};
Point(35) = {0.2,0.2,0.45,lc};
Point(36) = {0.3,0.8,0.55,lc};
Point(37) = {0.3,0.2,0.55,lc};

// The distribution of the mesh element sizes is then obtained by
// interpolation of these characteristic lengths throughout the
// geometry. Another method to specify characteristic lengths is to
// use a background mesh (see `t7.geo' and `bgmesh.pos').

// We can then define some additional points as well as our first
// curve.  Curves are Gmsh's second type of elementery entities, and,
// amongst curves, straight lines are the simplest. A straight line is
// defined by a list of point numbers. In the commands below, for
// example, the line 1 starts at point 1 and ends at point 2:

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

//Circle(13) = {10,9,11};
//Circle(14) = {11,9,12};
//Circle(15) = {12,9,13};
//Circle(16) = {13,9,10};

// lines for oblique fracture 1
//Line(17) = {7,4}; 
//Line(18) = {6,1};
Line(27) = {22,23};
Line(28) = {23,25};
Line(29) = {25,24};
Line(30) = {24,22};

// lines for oblique fracture 2
Line(19) = {15,14}; 
Line(20) = {14,16};
Line(21) = {15,17};
Line(22) = {17,16}; 

// lines for oblique fracture 3
Line(23) = {19,18};
Line(24) = {18,21};
Line(25) = {21,20};
Line(26) = {20,19};

// lines for fracture 4
//Line(31) = {29,28};
//Line(32) = {28,26};
//Line(33) = {26,27};
//Line(34) = {27,29};

// lines for fracture 5
//Line(35) = {33,32};
//Line(36) = {32,30};
//Line(37) = {30,31};
//Line(38) = {31,33};

// lines for fracture 6
Line(39) = {36,37};
Line(40) = {37,35};
Line(41) = {35,34};
Line(42) = {34,36};

Line Loop(1) = {1,2,3,4};
Line Loop(2) = {1,6,-9,-5};
Line Loop(3) = {2,7,-10,-6};
Line Loop(4) = {3,8,-11,-7};
Line Loop(5) = {-4,8,12,-5};
Line Loop(6) = {9,10,11,12};

//Line Loop(7) = {13,14,15,16};

// line loop for oblique fracture 1 
//Line Loop(8) = {17,4,-18,10};
Line Loop(8) = {27,28,29,30};

// line loop for oblique fracture 2
Line Loop(9) = {19,20,-22,-21};

// line loop for oblique fracture 3
Line Loop(10) = {23,24,25,26};

// line loop for fracture 4
//Line Loop(11) = {31,32,33,34};

// line loop for fracture 5
//Line Loop(12) = {35,36,37,38};

// line loop for fracture 6
Line Loop(13) = {39,40,41,42};

Plane Surface(1) = {1};
Plane Surface(2) = {2};
Plane Surface(3) = {3};
Plane Surface(4) = {4};
Plane Surface(5) = {5};
Plane Surface(6) = {6};
//Plane Surface(7) = {7};

// plane surface for oblique fracture 1 
Plane Surface(8) = {8};

// plane surface for oblique fracture 2
Plane Surface(9) = {9}; 

// plane surface for oblique fracture 3
Plane Surface(10) = {10};

// plane surface for fracture 4
// Plane Surface(11) = {11};

// plane surface for fracture 5
//Plane Surface(12) = {12};

// plane surface for fracture 6
Plane Surface(13) = {13};

Surface Loop(1) = {1,2,3,4,5,6};
Volume(1) = {1};

//Surface{7} In Volume{1};

// for oblique fracture 1
Surface{8} In Volume{1};

// for oblique fracture 2
Surface{9} In Volume{1};

// for oblique fracture 3
Surface{10} In Volume{1};

// for fracture 4
//Surface{11} In Volume{1};

// fracture 5
//Surface{12} In Volume{1};

// fracture 6
Surface{13} In Volume{1};

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

//Fracture = 2001;
//Physical Surface(Fracture) = {7};

Fracture2 = 2002;
Physical Surface("Fracture2") = {8};
 
Fracture3 = 2003;
Physical Surface("Fracture3") = {9};

Fracture4 = 2004;
Physical Surface("Fracture4") = {10};

// do not cosider this frac - intesect with other surfaces 
//Fracture = 2005;
//Physical Surface(Fracture) = {11};

// do not consider this frac - intersects with other surfaces 
//Fracture = 2006; 
//Physical Surface(Fracture) = {12}; 

Fracture7 = 2007;
Physical Surface("Fracture7") = {13};

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
