function setupLevel()

--PATH 0
i = newPath();
addPLine(i, 200, 200);
addPLine(i, 300, 0);


--WAYPOINT 0
i = newWayPoint();
setWPCycleInfo(i, 200, 1, 0);
setWPInitVel(i, 1, 1);
setWPDeathInfo(i, 1, 0);

--WAYPOINT 1
i = newWayPoint()
setWPCycleInfo(i, 100, 0, 1);
setWPInitVel(i, 0, -1.5);
setWPDeathInfo(i, 1, 0);

--WAYPOINT 2
i = newWayPoint()
setWPCycleInfo(i, 3000, 0, 1);
setWPInitVel(i, 0, 0);
setWPDeathInfo(i, 1, 0);
setWPSpeedPath(i, 400, 0, 0, 3, 1);

--WAYPOINT 3  terminal state
i = newWayPoint()
setWPCycleInfo(i, 3, 0, 1);
--setWPInitVel(i, 0, 0);
--setWPDeathInfo(i, 1, 0);
--setWPSpeedPath(i, 300, 0, 0, .85, 0);

--ENEMY 0
i = newEnemy();
setERadius(i, 6);
setESprite(i, 8);
addEWayPoint(i, 0);
addEWayPoint(i, 1);
setEHP(i, 8);

--ENEMY 1
i = newEnemy();
setERadius(i, 6);
setESprite(i, 9);
addEWayPoint(i, 2);
addEWayPoint(i, 3);
setEHP(i, 8);

addEToLevel(0, 20, 20, 50);
addEToLevel(0, 250, 250, 100);
addEToLevel(0, 250, 250, 150);
addEToLevel(0, 250, 250, 200);
addEToLevel(1, 100, 350, 100);
addEToLevel(1, 100, 330, 100);
addEToLevel(1, 100, 330, 100);
addEToLevel(1, 100, 330, 100);
addEToLevel(1, 100, 330, 100);
addEToLevel(1, 100, 330, 100);
end