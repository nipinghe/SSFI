Point(1) = {0, 0, 0, 1.0};
Point(2) = {5, 0, 0, 1.0};
Point(3) = {1, 3, 0, 1.0};
Point(4) = {4, 3, 0, 1.0};
Line(1) = {1, 2};
Line(2) = {2, 4};
Line(3) = {4, 3};
Line(4) = {3, 1};

Transfinite Line{1}=6;
Transfinite Line{2}=4;
Transfinite Line{3}=6;
Transfinite Line{4}=4;

Line Loop(1) = {1,2,3,4};

Plane Surface(1)={1};

Transfinite Surface {1};
Recombine Surface {1};