Speedsvw Calculations:
----------------------------------------------------------------------------
Wheel parameters:
•	R = wheel radius
•	V = wheel forward linear velocity
•	W = wheel angular velocity
Wheel forward linear velocity:
•	V = W * R

setSpeedips -> inches/second (in/s) for each wheel [linear velocity]
setSpeedsvw -> v = linear speed (in/s), w = angular speed (radian/s)
One revolution = 2 * pi radians
1 radian/s = 57.296 degrees/s

Max of 0.8RPS -> 0.8 * 2 * pi radians = 1.6 * pi radians/s = 5.027 rad/s

R = daxis (VR+VL) / (VL-VR)
V = ωR
ω = (VL-VR) / 2daxis
V = (VR+VL) / 2

R = V / W;               
d = 3.95;                 
vR = W * (R + (d / 2));
vL = W * (R - (d / 2));



Task 3 Calculations:
----------------------------------------------------------------------------
Given PARAM_X (inches) and PARAM_Y (seconds):
Inches per second (IPS) at which robot should travel at = PARAM_X/PARAM_Y 
Maximum IPS = Maximum RPS * CIRCUMFERENCE = 
= 0.8 * 8.2 = 6.55 inches/sec
Since 32 ticks = 1 revolutions 
                       = 2 * PI * R = 8.194”
Amount of ticks required for any PARAM_X = 32 * PARAM_X / 8.2



Task 4 Calculations:
----------------------------------------------------------------------------
Given PARAM_R1 (inches) and PARAM_Y (seconds):
d (Distance between wheels) = 3.95 inches
Angular velocity = 2𝝅 / PARAM_Y
Linear speed   	= v 
				= Angular speed * PARAM_R1 
				= (2𝝅 / PARAM_Y) * PARAM_R1
To obtain angular movement, two different velocities for each wheel are 
required: VL and VR, where:
VL 	= Angular Speed * (PARAM_1 + d/2) 
    = (2𝝅 / PARAM_Y) * (PARAM_1 + d/2)
VR 	= Angular Speed * (PARAM_1 - d/2) 
    = (2𝝅 / PARAM_Y) * (PARAM_1 -  d/2)

	
	
Task 5 Calculations:
----------------------------------------------------------------------------
Given PARAM_a (x in), PARAM_b (y in), PARAM_V (in/s):
Inches per seoncd (IPS or vMax) = PARAM_V
ellipse formula = (x/a)*(x/a) + (y/b)*(y/b) = 1
w = t = angle in radians
x = a*cos(w)
y = b*cos(w)
w = acos(x/a) + 2 * PI * n
w = acos(y/b) + 2 * PI * n

c^2 = 

w = k*v
k = 2 / (pow((sqrt(1 + 4 * sq(x))), 3))
