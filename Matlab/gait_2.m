clearvars
%last = [0 0 0];
angles = zeros(3,4);
base = zeros(4);
prox = [-100 -100 -100 -100];
dist = [-20 -20 -20 -20];
basegoal = [0 0 0 0]; %upper join, hip joint
proxgoal = [-100 -100 -100 -100]; %lower joint, knee joint
basestep = zeros(4);
proxstep = zeros(4);

last_timegoal = 0;
rear_base_offset =30;
figure(1);
figHandle = gcf;
axis equal;
axis([-1500 700 0 900]);
grid on;



filename = 'gait_2';
for n = 1:1                        % repeat the motion 
    
            %       STEP 1
            basegoal = [0 0 -40 -40];
            proxgoal = [-75 -75 -75 -75];
            timegoal = 1;                   % set the time to get there.
            for j = 1:4 %for each leg
                % set the step distance for each limb
                basestep(j) = (basegoal(j)-base(j))/timegoal;
                proxstep(j) = (proxgoal(j)-prox(j))/timegoal;
            end
            for j = 1:timegoal              %for each time step
                base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
                prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
                dist = [-40 -40 -40 -40];
                angles = [base;prox;dist];
                    leg_angles(j+last_timegoal,2)=-3*angles(1,1);                           % rf_leg_upper
                    leg_angles(j+last_timegoal,3)=cam_transform(angles(1,1),angles(2,1));   % rf_leg_lower
                    leg_angles(j+last_timegoal,8)=-3*(angles(1,2)-rear_base_offset);        % lf_leg_upper
                    leg_angles(j+last_timegoal,9)=cam_transform(angles(1,2),angles(2,2));   % lf_leg_lower
                    leg_angles(j+last_timegoal,6)=-3*(angles(1,3)-rear_base_offset);        % rb_leg_upper
                    leg_angles(j+last_timegoal,7)=cam_transform(angles(1,3),angles(2,3));   % rb_leg_lower
                    leg_angles(j+last_timegoal,4)=-3*angles(1,4);                           % lb_leg_upper
                    leg_angles(j+last_timegoal,5)=cam_transform(angles(1,4),angles(2,4));   % lb_leg_lower
                points = plotArm3(angles,[500,300,350],fighandle);
            end
            last_timegoal = timegoal+last_timegoal;
            
                        %       STEP 1
            basegoal = [0 0 -40 -40];
            proxgoal = [-75 -75 -75 -75];
            timegoal = 40;                   % set the time to get there.
            for j = 1:4 %for each leg
                % set the step distance for each limb
                basestep(j) = (basegoal(j)-base(j))/timegoal;
                proxstep(j) = (proxgoal(j)-prox(j))/timegoal;
            end
            for j = 1:timegoal              %for each time step
                base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
                prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
                dist = [-40 -40 -40 -40];
                angles = [base;prox;dist];
                    leg_angles(j+last_timegoal,2)=-3*angles(1,1);                           % rf_leg_upper
                    leg_angles(j+last_timegoal,3)=cam_transform(angles(1,1),angles(2,1));   % rf_leg_lower
                    leg_angles(j+last_timegoal,8)=-3*(angles(1,2)-rear_base_offset);        % lf_leg_upper
                    leg_angles(j+last_timegoal,9)=cam_transform(angles(1,2),angles(2,2));   % lf_leg_lower
                    leg_angles(j+last_timegoal,6)=-3*(angles(1,3)-rear_base_offset);        % rb_leg_upper
                    leg_angles(j+last_timegoal,7)=cam_transform(angles(1,3),angles(2,3));   % rb_leg_lower
                    leg_angles(j+last_timegoal,4)=-3*angles(1,4);                           % lb_leg_upper
                    leg_angles(j+last_timegoal,5)=cam_transform(angles(1,4),angles(2,4));   % lb_leg_lower
                points = plotArm3(angles,[500,300,350],fighandle);
            end
            last_timegoal = timegoal+last_timegoal;
            
                        %       STEP 1
            basegoal = [-40 -40 0 0];
            proxgoal = [-75 -75 -75 -75];
            timegoal = 1;                   % set the time to get there.
            for j = 1:4 %for each leg
                % set the step distance for each limb
                basestep(j) = (basegoal(j)-base(j))/timegoal;
                proxstep(j) = (proxgoal(j)-prox(j))/timegoal;
            end
            for j = 1:timegoal              %for each time step
                base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
                prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
                dist = [-40 -40 -40 -40];
                angles = [base;prox;dist];
                    leg_angles(j+last_timegoal,2)=-3*angles(1,1);                           % rf_leg_upper
                    leg_angles(j+last_timegoal,3)=cam_transform(angles(1,1),angles(2,1));   % rf_leg_lower
                    leg_angles(j+last_timegoal,8)=-3*(angles(1,2)-rear_base_offset);        % lf_leg_upper
                    leg_angles(j+last_timegoal,9)=cam_transform(angles(1,2),angles(2,2));   % lf_leg_lower
                    leg_angles(j+last_timegoal,6)=-3*(angles(1,3)-rear_base_offset);        % rb_leg_upper
                    leg_angles(j+last_timegoal,7)=cam_transform(angles(1,3),angles(2,3));   % rb_leg_lower
                    leg_angles(j+last_timegoal,4)=-3*angles(1,4);                           % lb_leg_upper
                    leg_angles(j+last_timegoal,5)=cam_transform(angles(1,4),angles(2,4));   % lb_leg_lower
                points = plotArm3(angles,[500,300,350],fighandle);
            end
            last_timegoal = timegoal+last_timegoal;
            
                        %       STEP 1
            basegoal = [-40 -40 0 0];
            proxgoal = [-75 -75 -75 -75];
            timegoal = 40;                   % set the time to get there.
            for j = 1:4 %for each leg
                % set the step distance for each limb
                basestep(j) = (basegoal(j)-base(j))/timegoal;
                proxstep(j) = (proxgoal(j)-prox(j))/timegoal;
            end
            for j = 1:timegoal              %for each time step
                base = [base(1)+basestep(1) base(2)+basestep(2) base(3)+basestep(3) base(4)+basestep(4)];
                prox = [prox(1)+proxstep(1) prox(2)+proxstep(2) prox(3)+proxstep(3) prox(4)+proxstep(4)];
                dist = [-40 -40 -40 -40];
                angles = [base;prox;dist];
                    leg_angles(j+last_timegoal,2)=-3*angles(1,1);                           % rf_leg_upper
                    leg_angles(j+last_timegoal,3)=cam_transform(angles(1,1),angles(2,1));   % rf_leg_lower
                    leg_angles(j+last_timegoal,8)=-3*(angles(1,2)-rear_base_offset);        % lf_leg_upper
                    leg_angles(j+last_timegoal,9)=cam_transform(angles(1,2),angles(2,2));   % lf_leg_lower
                    leg_angles(j+last_timegoal,6)=-3*(angles(1,3)-rear_base_offset);        % rb_leg_upper
                    leg_angles(j+last_timegoal,7)=cam_transform(angles(1,3),angles(2,3));   % rb_leg_lower
                    leg_angles(j+last_timegoal,4)=-3*angles(1,4);                           % lb_leg_upper
                    leg_angles(j+last_timegoal,5)=cam_transform(angles(1,4),angles(2,4));   % lb_leg_lower
                points = plotArm3(angles,[500,300,350],fighandle);
            end
            last_timegoal = timegoal+last_timegoal;
end


filepath = strcat('C:\Users\jpgraff\Downloads\MuttArduino\',filename,'.h')
fileID = fopen(filepath,'w');
fprintf(fileID,'#include <avr/pgmspace.h>\n');
fprintf(fileID,'#ifndef %s\n#define %s 1\n',strcat(filename,'_h'),strcat(filename,'_h'));
fprintf(fileID,'#define %s_size %d\n',filename,size(leg_angles,1)+2);
fprintf(fileID,'const int %s[%s][8] PROGMEM=\n',filename,strcat(filename,'_size'));
fprintf(fileID,'{');
for o = 2:last_timegoal
    fprintf(fileID,'{');
    for p = 2:8
        fprintf(fileID,'%s,',int2str(leg_angles(o-1,p)));
    end    
        fprintf(fileID,'%s',int2str(leg_angles(o-1,p+1)));
    fprintf(fileID,'},\n');
end

fprintf(fileID,'{4200,4200,4200,4200,4200,4200,4200,4200}};');
fprintf(fileID,'\n#endif');
fclose(fileID);