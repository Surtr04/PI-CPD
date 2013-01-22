// gmsh2.geo
// definition and variable
MINUS_THREE_DIM = 2147483648;
MINUS_TWO_DIM   = 1073741824;
MINUS_ONE_DIM   =  536870912;
H=1.;
L=H;
lc = H/40;
// geometrical part
Point(1) = {0.0, 0.0, 0.0, lc};
Point(2) = {L  , 0.0, 0.0, lc} ;
Point(3) = {L  , H  , 0.0, lc} ;
Point(4) = {0.0, H  , 0.0, lc} ;

Line(1) = {1,2} ;
Line(2) = {3,2} ;
Line(3) = {3,4} ;
Line(4) = {4,1} ;

Line Loop(5) = {4,1,-2,3} ;
Plane Surface(6) = {5} ;

//   the physical part
//code 1 dirichlet,, code 2 Neumann
Physical Line(1) = {2,4} ;
Physical Line(2) = {1,3} ;
//Physical Line(1) = {1,2,3,4} ;
//Physical Line(2) = {3} ;
//Physical Line(11) = {2,4} ;
Physical Surface(10) = {6} ;

//Physical Line(18+MINUS_ONE_DIM) = {4} ;
//Physical Surface(10) = {6} ;
//Physical Surface(12+MINUS_ONE_DIM) = {6} ;

Coherence;
Coherence;
