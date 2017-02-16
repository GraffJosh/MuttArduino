function points = plotArm3(angles, linkLengths, fighandle)    

%     figure(fighandle);
    clf;
    axis equal;
    axis([-1500 700 0 900, 0, 900]);
    grid on;
    horizontal = 500;
    lengthwise = 1000;
    
for i = 1:4
    baseAngle = single(angles(1,i));
    proxAngle = single(angles(2,i));
    distAngle = single(angles(3,i));

    %% Links
    baseLength = linkLengths(1);
    proxLength = linkLengths(2);
    distLength = linkLengths(3);
    
    basePointX = -200;
    basePointY = 700;
    

    %base link (the fixed vertical link)
    baseX = [basePointX,basePointX+baseLength*cosd(baseAngle)];% x coordinates of base link
    baseY = [basePointY,basePointY+baseLength*sind(baseAngle)];%(basePointY+distLength*sind(distAngle)+proxLength*sind(proxAngle+baseAngle)+baseLength*sind(proxAngle+baseAngle+distAngle)),proxY(1)];%y coordinates of base link
    
    proxX = [baseX(2),baseX(2)+proxLength*cosd(proxAngle+baseAngle)];% x ooordinates of proximal link
    proxY = [baseY(2),baseY(2)+proxLength*sind(proxAngle+baseAngle)];%distY(1)+proxLength*sind(proxAngle+baseAngle),distY(1)];% y coordinates of proximal link
    
    distX = [proxX(2),basePointX+baseLength*cosd(baseAngle)+proxLength*cosd(proxAngle+baseAngle)+distLength*cosd(proxAngle+baseAngle+distAngle)];% x coordinates of distal link
    distY = [proxY(2),basePointY+baseLength*sind(baseAngle)+proxLength*sind(proxAngle+baseAngle)+distLength*sind(proxAngle+baseAngle+distAngle)];% (basePointY+distLength*sind(distAngle)),basePointY];
 
    % proximal link (the middle link)        
    
    % distal link (the end link)
    
    baseZ = [mod(i,2)*horizontal mod(i,2)*horizontal];
    proxZ = [mod(i,2)*horizontal mod(i,2)*horizontal];
    distZ = [mod(i,2)*horizontal mod(i,2)*horizontal];
    
    if i == 1 || i == 4
        baseX = baseX - lengthwise;
        proxX = proxX - lengthwise;
        distX = distX - lengthwise;
    end
    %% Plot
    %plot(baseX,baseY,'LineWidth',5,'Color','b');
    
    hold on;
    plot3(baseX,baseZ,baseY,'LineWidth',3,'Color','r');
    plot3(proxX,proxZ,proxY,'LineWidth',3,'Color','g');
    plot3(distX,distZ,distY,'LineWidth',3,'Color','g');
    base = [baseX baseY baseZ];
    prox = [proxX proxY proxZ];
    dist = [distX distY distZ];
    points = [base; prox; dist];
    hold off;
end
    view(18,4);
    drawnow;