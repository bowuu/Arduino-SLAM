# Arduino Bot Lab 1
Lab Report
https://docs.google.com/document/d/1_QMHila0PpUmZuWhhGCuQY03XCz3tVxPCO8oa3vq-ZM/edit

# Task 1

Run the function setSpeeds(0,100). Use the encoders to plot the instantaneous speed4 of the right servo (in revolutions per second) vs time. Take measurements every 30 ms for approximately 2 seconds (about 67 measurements in total). Before taking any measurements wait 1 second to allow the motor to reach the desired speed. Aspects to think about:
• Is this value constant?
• If not, does the plot look random or does it have a pattern? Think of reasons that might
explain the behavior.

# Task 2

With a fully charged set of batteries, in a single graph use the encoders to plot the speed of both wheels (in revolutions per second) vs input to the implemented function setSpeeds. Measure the speeds of the wheels from -200 micros to 200 micros in increments of 10. Repeat the experiment with low batteries. Provide both plots in the report. Things to think about:
• How similar do both servos react to the same input? Does the difference look like random noise? If not, what could be causing the difference? Why is it a good idea to use software calibration?
• Before measuring the speed, you should allow some time for the servo to stabilize its speed. You may want to use the average speed over a time window instead of the instantaneous speed.

# Task 3

Implement the program ‘Forward.ino’. The program should make the robot stay still until the select button is pressed. After pressing select, the robot should move forward on a straight line for “X” inches. The robot should complete the movement in “Y” seconds. The robot should stop based on encoder readings (distance traversed), not on the time past. “X” and “Y” are parameters provided on “ForwardParams.h”. The program should work for any values “X” and “Y” for which it is possible to complete the movement on the given time. If the robot can’t complete the movement in the given amount of time, when pressing select, instead of moving forward, the robot should display an appropriate message on the LCD. During the task presentation, the TA will assign different values for “X” and “Y”.

# Task 4

Implement the program ‘SShape.ino’. The program should make the robot move in two semicircles of radius “R1” and “R2” respectively, as shown in Figure 2. The robot should stay still until the “select” button is pressed. When “select” is pressed, the robot should perform the first semicircle in a clockwise movement. After completing the first semicircle, the robot should wait for the “select” button to be pressed again, and then perform the second semicircle in a counterclockwise manner. The whole movement must be completed in “Y” seconds moving at the same constant speed for both halves. The robot should stop based on encoder readings (distance traversed), and not based on a given time.

“R1”, “R2” and “Y” will be provided on “SShapeParams.h”. The program must work for any values of “R1”, “R2” and “Y”. If the motion cannot be completed in the given time, after pressing “select” for the first time, the robot should display an appropriate message on the LCD. 

Figure 2. Path to be followed by the robot.

• Observe that, independently of the trajectory, the robot moves by fixing the speeds of the wheels for a given amount of time (as in the “S” shape shown in Figure 2). Taking this into consideration, can the robot move in any kind of trajectory? Consider an ellipse as an example.

# Task 5

Implement the program “Ellipse.ino”. The program should make the robot move in an
ellipse given by the formula



(as seen in Figure 3). The robot should stay still until the “select” button is pressed. When the button is pressed, the robot should move on an ellipse at constant linear speed “V”. The parameters “a”, “b”, and “V” will be provided on “EllipseParams.h”. The program should work for any assigned values. On this part, you do not need to worry on whether the robot can traverse the ellipse at the given speed, but you have to include in the report what limits the possible values of “V”. The robot should start on the leftmost point of the ellipse, corresponding to position (-a, 0) facing the positive y-axis direction. The robot should move in clockwise manner.


Figure 3. Path to be followed by the robot.

During the task presentation, the TA will assign different values to “a”, “b” and “v”. Hints and notes:
• The objective of this task is for you to understand the difficulties of doing a non-trivial curve. You should strive to draw the ellipse the best you can but don’t expect results to be perfect.
• Use the material seen in class to calculate curvature of an ellipse as a function of the position. Use the formula 𝜔 = 𝑘𝑣.
