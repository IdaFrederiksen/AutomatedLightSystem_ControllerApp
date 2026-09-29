The Automated Light System controls and adapts aritificial light in a workspace to ensure good working conditions while minimizing power usage.

To accomplish that we build a 2 part embedded system, only the ControllerApp is a part of this repository:

ControllerApp (C++, runs on a Arduino Mega 2560) uses:
The ControllerApp runs and controls the sensors and lights to ensure the light in the workspace corresponds with settings provideded by the user through the GUI.
* 3 Light sensors
* 3 PIR sensors
* Led rings

GUIApp (Python, runs on a laptop).

To communicate they utilised a UART connection, where we designed a communication protocol for the messaging format.
