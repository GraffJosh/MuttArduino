last = [0 0 0];
angles = zeros(3);
base = 0;
prox = -100;
dist = -40;
basegoal = 0;
proxgoal = -100;% -100 -100 -100];
basestep = zeros(4);
proxstep = zeros(4);


figure(1);
figHandle = gcf;
axis equal;
%axis([-1500 700]);% 0 900]);
grid on;    


leg_angles = zeros(200,3);


basegoal = -20;% 20 20 -20];     % set angle goals for each of the leg's upper joint
proxgoal = -100;% -50 -50 -100];
timegoal = 20;                   % set the time to get there.

for i = 1%:4 %for each leg
    % set the step distance for each limb
    basestep(i) = (basegoal(i)-base(i))/timegoal;
    proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
end
for i = 1:timegoal              %for each time step
    base = base(1)+basestep(1);% base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
    prox = prox(1)+proxstep(1);% prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
    dist = -40;% -40 -40 -40];
    angles = [base;prox;dist];
    leg_angles(i,1)=angles(1);
    leg_angles(i,2)=angles(2);
    points = plotArm3(angles,[500,300,350],fighandle);
end
