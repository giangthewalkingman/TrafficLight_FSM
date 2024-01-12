# Lab 5
This lab exercise is the solution for "Lab 5. Traffic Light Controller  (Spring 2023)" of EE319K https://users.ece.utexas.edu/~valvano/Volume1/ . <br>
The program is implemented on STM32F103C8T6 kit instead of TM4C123GH6PM, the logic remains though. <br>
Instead of mounting leds and switch to a breadboard, I soldered them into a electrical board so that the signals can be observed clearly. <br>
This program works. <br>
## Logic:
 Runs on STM32F103C8T6 <br>
 Use a table implementation of a Moore finite state machine to operate <br>
 a traffic light. <br>
 Truong Giang Nguyen <br>
 Jan 10th, 2024 <br>

 walk button sensor connected to PB5 (1=button pressed) <br>
 north facing car detector connected to PB4 (1=car present) <br>
 east facing car detector connected to PB3 (1=car present) <br>

 east facing red light connected to PA9 (was PA8 but PA8 cannot output correctly) <br>
 east facing yellow light connected to PA7 <br>
 east facing green light connected to PA6 <br>
 north facing red light connected to PA5 <br>
 north facing yellow light connected to PA4 <br>
 north facing green light connected to PA3 <br>
 walk blue light connected to PA2 <br>
 walk green light connected to PA1 <br>
 walk red light connected to PA0 <br>

 ## Some images
 ![Image description]([https://github.com/giangthewalkingman/TrafficLight_FSM/image/fsm_tfc.png](https://github.com/giangthewalkingman/TrafficLight_FSM/blob/master/image/fsm_tfc.png)) <br>
 ![Image description]([https://github.com/giangthewalkingman/TrafficLight_FSM/image/wiring.jpg](https://github.com/giangthewalkingman/TrafficLight_FSM/blob/master/image/wiring.jpg))
