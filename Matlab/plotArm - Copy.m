function figHandle = plotArm(angles, linkLengths)    
    %% Angles
    baseAngle = single(angles(1)+45);
    proxAngle = single(angles(2)+25);
    distAngle = -1*single(angles(3)-110);
    %% Links
    baseLength = linkLengths(1);
    proxLength = linkLengths(2);
    distLength = linkLengths(3);
    
    basePointX = 0;
    basePointY = 50;
    
%     base link (the fixed vertical link)
    baseX = [basePointX-distLength*cosd(distAngle+proxAngle+baseAngle) - proxLength*cosd(proxAngle+baseAngle) + baseLength*cosd(baseAngle),baseLength*cosd(baseAngle)];% x coordinates of base link
    baseY = [basePointY,baseLength*sind(baseAngle)];% y coordinates of base link
    
    % proximal link (the middle link)        
    proxX = [baseX(2),baseX(2)+proxLength*cosd(proxAngle+baseAngle)];% x ooordinates of proximal link
    proxY = [baseY(2),baseY(2)+proxLength*sind(proxAngle+baseAngle)];% y coordinates of proximal link
    
    % distal link (the end link)
    distX = [proxX(2),basePointX];% x coordinates of distal link
    distY = [proxY(2),distLength*sind(distAngle+proxAngle+baseAngle) + proxLength*sind(proxAngle+baseAngle) + baseLength*sind(baseAngle)];% y ooordinates of distal link
    
    %% Plot
    figHandle = figure(1);
    clf;
    %plot(baseX,baseY,'LineWidth',5,'Color','b');
    hold on;
    plot(baseX,baseY,'LineWidth',3,'Color','g');
    plot(proxX,proxY,'LineWidth',3,'Color','g');
    plot(distX,distY,'LineWidth',3,'Color','r');
    hold off;
    axis equal;
    axis([-700 700 0 900]);
    grid on;
    drawnow;
end