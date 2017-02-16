function figHandle = plotArm2(angles, linkLengths)    
    % Angles
%     baseAngle = single(angles(1)+45);
%     proxAngle = single(angles(2)+25);
%     distAngle = -1*single(angles(3)-110);

    baseAngle = single(angles(1));
    proxAngle = single(angles(2));
    distAngle = single(angles(3));

    %% Links
    baseLength = linkLengths(1);
    proxLength = linkLengths(2);
    distLength = linkLengths(3);
    
    basePointX = 0;
    basePointY = 400;
    
%     base link (the fixed vertical link)
    baseX = [basePointX,basePointX+baseLength*cosd(baseAngle)];% x coordinates of base link
    distY = [(basePointY+distLength*sind(distAngle)),basePointY];
    
    proxX = [baseX(2),baseX(2)+proxLength*cosd(proxAngle+baseAngle)];% x ooordinates of proximal link
    proxY = [distY(1)+proxLength*sind(proxAngle+baseAngle),distY(1)];% y coordinates of proximal link
    
    distX = [proxX(2),basePointX+baseLength*cosd(baseAngle)+proxLength*cosd(proxAngle+baseAngle)+distLength*cosd(proxAngle+baseAngle+distAngle)];% x coordinates of distal link
    baseY = [(basePointY+distLength*sind(distAngle)+proxLength*sind(proxAngle+baseAngle)+baseLength*sind(proxAngle+baseAngle+distAngle)),proxY(1)];%y coordinates of base link
    

    % proximal link (the middle link)        
    
    % distal link (the end link)
    
    %% Plot
    figHandle = figure(1);
    clf;
    %plot(baseX,baseY,'LineWidth',5,'Color','b');
    hold on;
    plot(baseX,baseY,'LineWidth',3,'Color','r');
    plot(proxX,proxY,'LineWidth',3,'Color','g');
    plot(distX,distY,'LineWidth',3,'Color','g');
    view(3)
    hold off;
    axis equal;
    axis([-700 700 0 900]);
    grid on;
    drawnow;
end