# PID Controller Tutorial

Prepared by David Hoysan, Advanced IoT 2016

## What is a PID Controller?
A PID (Proportional, Integral, Derivative) controller is a feedback system that attempts to control a system or process. The PID controller calculates the error between a desired setpoint and a measured process variable. The controller continuously attempts to minimuze this error over time by adjusting an output variable and recalculating the error. 

## PID Controller Schematic
![alt text](https://github.com/daraghbyrne/advancediot2016/blob/master/students/dhoysan/PID%20Tutorial/PID%20Schematic.png "PID Controller Schematic")

## PID Equation
![alt text](https://github.com/daraghbyrne/advancediot2016/blob/master/students/dhoysan/PID%20Tutorial/PID%20Equation.png "")

The PID controller equation is built around 3 constants, the proportional, integral, and derivative coefficient. Each of these constants can be adjusted to achieve a desired control response.
* u(t) - Output 
* e(t) - Error Value
* Kp - Proportional constant that accounts for the present error value. If the current error is large and positive, the output will be large and positive
* Ki - Integral constant that accounts for historical error values. If the output is not strong, the error will accumulate, and the controller will respond by increasing the output.
* Kd - Derivative constant that accounts for future error values. This term attempts to predict what the error will be in the future, and adjusts accordingly.

## PID Response Graph
![alt text](https://github.com/daraghbyrne/advancediot2016/blob/master/students/dhoysan/PID%20Tutorial/PID%20Graph.png "PID Response Graph")

The graph above shows how the response of PID controller can change based on the set coefficients. In this example, the system is subjected to a setpoint change. The controller with K = 0.5 reacts rather slowly and reaches the setpoint with no overshoot. The controller with K = 1.6 reacts extremely fast and severely overshoots the setpoint. The controller adjusts accordingly so that the output eventually settles down at the setpoint. Finally, the controller with K = 1.1 reaches the setpoint quickly with minimal overshoot. Each PID controller application is different than the next and the coefficients need to be adjusted appropriately to acieve the desired response.

## Example Applications
PID Controllers are useful for controlling any regulating system that is subjected to distrubances. The examples below represent just a few of the many applications where PID controllers can be useful.

### Automotives
PID controllers are useful in the automotive industry for maintaining a constant speed or separation distance during cruise control.

![alt text](https://github.com/daraghbyrne/advancediot2016/blob/master/students/dhoysan/PID%20Tutorial/PID%20Car.gif "PID Car")

### Robotics
PID controllers can help a robot achieve a desired movement or position.

![alt text](https://github.com/daraghbyrne/advancediot2016/blob/master/students/dhoysan/PID%20Tutorial/CMU%20Robot.gif "PID Robot")

### Temperature Control
A PID can be used to continually measure and adjust temperature.

![alt text](https://github.com/daraghbyrne/advancediot2016/blob/master/students/dhoysan/PID%20Tutorial/PID%20Temp%20Control.png "PID temperature control")
