
last = [0 0 0];
angles = zeros(3,4);
base = zeros(4);
prox = [-100 -100 -100 -100];
dist = [-40 -40 -40 -40];
basegoal = zeros(4);
proxgoal = [-100 -100 -100 -100];
basestep = zeros(4);
proxstep = zeros(4);


figure(1);
figHandle = gcf;
axis equal;
axis([-1500 700 0 900]);
grid on;

for n = 1:5
%     basegoal = -20;
%     proxgoal = prox;
%     timegoal = 20;
%     
%     step = (basegoal-base)/timegoal;
%     s = 20;
%     for i = 1:s
%         base = base+step;
%         prox = prox;
%         points = plotArm3([base,prox,-40],[500,300,350]);
%     end
%     currpos = [0 0];
%     currpos = go_to_position(-20, currpos(2),20);

%   internal definition of go to pos. didn't want to deal with sharing
%   data.
    basegoal = [-20 20 20 -20];
    proxgoal = [-100 -50 -50 -100];
    timegoal = 7;
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i,1)=angles(1);
        leg_angles(i,2)=angles(2);
        points = plotArm3(angles,[500,300,350],fighandle);
    end


    
    
    basegoal = [0 0 0 0];
    proxgoal = [-25 -75 -75 -25];
    timegoal = 7;
    
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        points = plotArm3(angles,[500,300,350],fighandle);
    end
    
    
    
    
    
    basegoal = [20 -20 -20 20];
    proxgoal = [-50 -100 -100 -50];
    timegoal = 7;
    
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        points = plotArm3(angles,[500,300,350],fighandle);
    end 
    
    
    
    basegoal = [-20 20 20 -20];
    proxgoal = [-75 -25 -25 -75];
    timegoal = 10;
    
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        points = plotArm3(angles,[500,300,350],fighandle);
    end

end

% function position = go_to_position(basegoal,proxgoal,timegoal)
%     basegoal = -20;
%     proxgoal = prox;
%     timegoal = 20;
%     
%     basestep = (basegoal-base)/timegoal;
%     proxstep = (proxgoal-prox)/timegoal;
%     for i = 1:timegoal
%         base = base+basestep;
%         prox = prox+proxstep;
%         points = plotArm3([base,prox,-40],[500,300,350]);
%     end
% end