function position = go_to_pos(basegoal,proxgoal,timegoal)
    
    basestep = (basegoal-base)/timegoal;
    proxstep = (proxgoal-prox)/timegoal;
    for i = 1:timegoal
        base = base+basestep;
        prox = prox+proxstep;
        points = plotArm3([base,prox,-40],[500,300,350]);
    end
end