function phi = cam_transform(Theta1, Theta2)    
%phi = output;
Theta1f = Theta1;%input;
Theta2f = Theta2;%input;
alpha = 96.26;% deg
R = 0.65;% in
r = 1.00; 
lcable = 11.386;%in
l1 = 2.6206;% in
A = 3.423;% in
B = 2.6844;% in
C = 50.65;% deg
Theta1o = 0;% deg
D2 = 1.7526;% in
Beta = 132.50;% deg
D1 = 0.9114;% in
Theta2o = -100.00;% deg

k1 = sqrt(A^2 + B^2 + -2*A*B*cosd(C + (Theta1f - Theta1o)));
phi = Beta - (180 / (pi * r)) * (lcable - l1 - k1 - D2  - D1 - ((Theta2f - Theta2o + alpha) * pi * R) / 180);
phi = -1*phi;