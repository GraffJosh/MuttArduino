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
%base_goal1 = -40;
%base_goal2 = -20;
rear_base_offset =100;
figure(1);
figHandle = gcf;
axis equal;
axis([-1500 700 0 900]);
grid on;

last_timegoal = 0;
for n = 1:1                        % repeat the motion 
    base_goal_set = [-40 0];%set the position of the upper limb in order of execution for one leg
    prox_goal_set = [-75 -100];
    
    for i = 1:4 %for each leg
        for k= 1:size(base_goal_set,2) %iterate for each frame 
            %       STEP 1
                       % FR BL BR FL 
            basegoal = zeros(4);
            basegoal(i) = base_goal_set(k);     % set angle goals for each of the leg's upper joint
            proxgoal = [-100 -100 -100 -100];
            proxgoal(i) = prox_goal_set(k);
            timegoal = 20;                   % set the time to get there.
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
                    leg_angles(j+last_timegoal,2)=-3*angles(1,1);
                    leg_angles(j+last_timegoal,3)=cam_transform(angles(1,1),angles(2,1))-180;
                    leg_angles(j+last_timegoal,8)=-3*angles(1,2)+rear_base_offset;
                    leg_angles(j+last_timegoal,9)=cam_transform(angles(1,2),angles(2,2))-180;
                    leg_angles(j+last_timegoal,6)=-3*angles(1,3)+rear_base_offset;
                    leg_angles(j+last_timegoal,7)=cam_transform(angles(1,3),angles(2,3))-180;
                    leg_angles(j+last_timegoal,4)=-3*angles(1,4);
                    leg_angles(j+last_timegoal,5)=cam_transform(angles(1,4),angles(2,4))-180;
                points = plotArm3(angles,[500,300,350],fighandle);
            end
%             angles(1,1)
%             angles(2,1)
%             cam_transform(angles(1,1),angles(2,1))
            last_timegoal = timegoal+last_timegoal;
            
                        %       STEP 1
                       % FR BL BR FL
            basegoal = zeros(4);
            basegoal(i) = base_goal_set(k);     % set angle goals for each of the leg's upper joint
            proxgoal = [-100 -100 -100 -100];
            proxgoal(i) = prox_goal_set(k);
            timegoal = 20;                   % set the time to get there.
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
                    leg_angles(j+last_timegoal,2)=-3*angles(1,1);
                    leg_angles(j+last_timegoal,3)=cam_transform(angles(1,1),angles(2,1))-180;
                    leg_angles(j+last_timegoal,8)=-3*angles(1,2)+rear_base_offset;
                    leg_angles(j+last_timegoal,9)=cam_transform(angles(1,2),angles(2,2))-180;
                    leg_angles(j+last_timegoal,6)=-3*angles(1,3)+rear_base_offset;
                    leg_angles(j+last_timegoal,7)=cam_transform(angles(1,3),angles(2,3))-180;
                    leg_angles(j+last_timegoal,4)=-3*angles(1,4);
                    leg_angles(j+last_timegoal,5)=cam_transform(angles(1,4),angles(2,4))-180;
                points = plotArm3(angles,[500,300,350],fighandle);
            end
            last_timegoal = timegoal+last_timegoal;
        end
    end
end

% leg_angles =int2str(leg_angles);
% int2str(leg_angles(i,2))
filename = 'gait_1';
filepath = strcat('C:\Users\amartinez\Documents\MuttArduino\',filename,'.h')
fileID = fopen(filepath,'w');
fprintf(fileID,'#include <avr/pgmspace.h>\n');
fprintf(fileID,'#ifndef %s\n#define %s 1\n',strcat(filename,'_h'),strcat(filename,'_h'));
fprintf(fileID,'const int %s[%d][8] PROGMEM=\n',filename,size(leg_angles,1)+2);
fprintf(fileID,'{');
% data{1,1} = '{';
for o = 2:last_timegoal
    
%  data{i,1} = ['{' int2str(leg_angles(i-1,2)) ',' int2str(leg_angles(i-1,3)) ',' int2str(leg_angles(i-1,4)) ',' int2str(leg_angles(i-1,5)) ',' int2str(leg_angles(i-1,6)) ',' int2str(leg_angles(i-1,7)) ',' int2str(leg_angles(i-1,8)) ',' int2str(leg_angles(i-1,9)) '},'];
%     if(i ~= 2)
%         fprintf(fileID,'},\n');
%     end
    fprintf(fileID,'{');
    for p = 2:8
        fprintf(fileID,'%s,',int2str(leg_angles(o-1,p)));
        
    end
    
        fprintf(fileID,'%s',int2str(leg_angles(o-1,p+1)));
    fprintf(fileID,'},\n');
%  data{i,1} = ['{' int2str(leg_angles(i-1,2)) ',' int2str(leg_angles(i-1,3)) ',' int2str(leg_angles(i-1,4)) ',' int2str(leg_angles(i-1,5)) ',' int2str(leg_angles(i-1,6)) ',' int2str(leg_angles(i-1,7)) ',' int2str(leg_angles(i-1,8)) ',' int2str(leg_angles(i-1,9)) '},'];
%     string_output(i,:) = data;
end



% data{i+1,1} = '}'
% fprintf(fileID,'{%d,%d,%d,%d,%d,%d,}','x','exp(x)');
fprintf(fileID,'{4200,4200,4200,4200,4200,4200,4200,4200}};');
fprintf(fileID,'\n#endif');
fclose(fileID);

% string_output(:,2) = leg_angles(:,2);
% string_output(:,3) = ',';
% string_output(:,4) = leg_angles(:,3);
% string_output(:,5) = ',';
% string_output(:,6) = leg_angles(:,4);
% string_output(:,7) = ',';
% string_output(:,8) = leg_angles(:,5);
% string_output(:,9) = ',';
% string_output(:,10) = leg_angles(:,6);
% string_output(:,11) = ',';
% string_output(:,12) = leg_angles(:,7);
% string_output(:,13) = ',';
% string_output(:,14) = leg_angles(:,8);
% string_output(:,15) = ',';
% string_output(:,16) = leg_angles(:,9);
% string_output(:,17) = '}';
% string_output(:,18) = ',';







% function position = go_to_position(basegoal,proxgoal,timegoal)
%     basegoal = -40;
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
