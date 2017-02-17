
last = [0 0 0];
angles = zeros(3,4);
base = zeros(4);
prox = [-100 -100 -100 -100];
dist = [-20 -20 -20 -20];
basegoal = [0 0 0 0];
proxgoal = [-100 -100 -100 -100];
basestep = zeros(4);
proxstep = zeros(4);


figure(1);
figHandle = gcf;
axis equal;
axis([-1500 700 0 900]);
grid on;

for n = 1:2                         % repeat the motion 5 times
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
    leg_angles = zeros(320,8);
%       STEP 1
               % FR BL BR FL
    basegoal = [-20 0 0 0];     % set angle goals for each of the leg's upper joint
    proxgoal = [-100 -90 -90 -90];
    last_timegoal = 0;
    timegoal = 20;                   % set the time to get there.
    for i = 1:4 %for each leg
        % set the step distance for each limb
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal              %for each time step
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end
    last_timegoal = timegoal+last_timegoal;

    basegoal = [-20 0 0 0];
    proxgoal = [-75 -90 -90 -90];
    timegoal = 20;
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end
    last_timegoal = timegoal+last_timegoal;
        
    basegoal = [-10 0 0 0];
    proxgoal = [-85 -100 -100 -100];
    timegoal = 20;
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end 
    last_timegoal = timegoal+last_timegoal;
        
    basegoal = [0 0 0 0];
    proxgoal = [-100 -100 -100 -100];
    timegoal = 20;
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end
    last_timegoal = timegoal+last_timegoal;
    
    
%     STEP 2
               % FR BL BR FL
    basegoal = [0 -20 0 0];     % set angle goals for each of the leg's upper joint
    proxgoal = [-90 -100 -90 -90];
    timegoal = 20;                   % set the time to get there.
    for i = 1:4 %for each leg
        % set the step distance for each limb
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal              %for each time step
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end
    last_timegoal = timegoal+last_timegoal;

    basegoal = [0 -20 0 0];
    proxgoal = [-90 -75 -90 -90];
    timegoal = 20;
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end
    last_timegoal = timegoal+last_timegoal;
        
    basegoal = [0 -10 0 0];
    proxgoal = [-99 -85 -100 -100];
    timegoal = 20;
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end 
    last_timegoal = timegoal+last_timegoal;
        
    basegoal = [0 0 0 0];
    proxgoal = [-100 -100 -100 -100];
    timegoal = 20;
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end
    last_timegoal = timegoal+last_timegoal;
    
    %     STEP 3
               % FR BL BR FL
    basegoal = [0 0 0 -20];     % set angle goals for each of the leg's upper joint
    proxgoal = [-90 -90 -90 -100];
    timegoal = 20;                   % set the time to get there.
    for i = 1:4 %for each leg
        % set the step distance for each limb
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal              %for each time step
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end
    last_timegoal = timegoal+last_timegoal;

    basegoal = [0 0 0 -20];
    proxgoal = [-90 -90 -90 -75];
    timegoal = 20;
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end
    last_timegoal = timegoal+last_timegoal;
        
    basegoal = [0 0 0 -10];
    proxgoal = [-100 -100 -100 -85];
    timegoal = 20;
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end 
    last_timegoal = timegoal+last_timegoal;
        
    basegoal = [0 0 0 0];
    proxgoal = [-100 -100 -100 -100];
    timegoal = 20;
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end
    last_timegoal = timegoal+last_timegoal;
    
    
        %     STEP 4
               % FR BL BR FL
    basegoal = [0 0 -20 0 ];     % set angle goals for each of the leg's upper joint
    proxgoal = [-90 -90 -100 -90 ];
    timegoal = 20;                   % set the time to get there.
    for i = 1:4 %for each leg
        % set the step distance for each limb
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal              %for each time step
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end
    last_timegoal = timegoal+last_timegoal;

    basegoal = [0 0 -20 0];
    proxgoal = [-90 -90 -75 -90];
    timegoal = 20;
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end
    last_timegoal = timegoal+last_timegoal;
        
    basegoal = [0 0 -10 0];
    proxgoal = [-100 -100 -85 -100];
    timegoal = 20;
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end 
    last_timegoal = timegoal+last_timegoal;
        
    basegoal = [0 0 0 0];
    proxgoal = [-100 -100 -100 -100];
    timegoal = 20;
    for i = 1:4
        basestep(i) = (basegoal(i)-base(i))/timegoal;
        proxstep(i) = (proxgoal(i)-prox(i))/timegoal;
    end
    for i = 1:timegoal
        base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
        prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
        dist = [-40 -40 -40 -40];
        angles = [base;prox;dist];
        leg_angles(i+last_timegoal,1)=angles(1,1);
        leg_angles(i+last_timegoal,2)=angles(2,1);
        leg_angles(i+last_timegoal,3)=angles(1,2);
        leg_angles(i+last_timegoal,4)=angles(2,2);
        leg_angles(i+last_timegoal,5)=angles(1,3);
        leg_angles(i+last_timegoal,6)=angles(2,3);
        leg_angles(i+last_timegoal,7)=angles(1,4);
        leg_angles(i+last_timegoal,8)=angles(2,4);
        points = plotArm3(angles,[500,300,350],fighandle);
    end
    last_timegoal = timegoal+last_timegoal;
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