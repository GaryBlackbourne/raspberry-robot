# Embedded OS tasks for motor control

# Main function

Get initialization done within the microcontroller, create init, and start freeRTOS.

- initialize hardware:
- GPIOs
- timers
- I2Cs
- USARTs
- create `init task` 
- call scheduler

Useful feature might be, to store all data in a struct which represents the robot, and all data could be transfered at once. An example structure is written in `state_struct_example.c`.

# init task

Initialize all hardware outside of the microcontroller, and create other tasks. Must be `high priority` to ensure init.

- init peripherals
- send welcoming message through debug usart
- initialize proximity sensors one-by-one (enable them and give proper I2C addresses)
- hold motors in `HALT` position
- initialize stepper motor driver module (configure through UART signal)
- init other tasks:
		- 
	
# motor control

In charge of controlling the timers ( TIM1, TIM2, TIM3 ) which control and measure the motors speed and direction.

- TIM1 -> motor speed controll, PWM mode
- TIM2 -> left motor speed measurement, encoder mode
- TIM3 -> right motor speed measurement, encoder mode
	
The task sets the speed of the timers, and reads timer data afterwards. 
Control messages to task are received into a mailbox, or equivalent structure. 
The cars internal model is a structure in wich, speed shall be stored. Mutuall exclusion is 
necessary to maintain this structures integrity, or other interfaces should be set up to avoid racing conditions.

After writing control, and reading speed values the task yields.

Between schedules the timer stays in the last modified state. If no control words found, then the task can:
- maintain current state; resulting less communication, but harder control flow
- halts the robot; resulting the constant need of communication, but simpler control flow. More immune to errors.

Control words:
- <side><speed>
- side: `L` / `R` / `B` characters, represent `Left`, `Right`, `Both` respectively. 
- speed: -100 to 100 integer value, representing the given speed in percentage.

# camera control

Uses `DIR`, `STEP` and `TMC_PDN_UART` signals to rotate the camera. Actual position, is stored, as an accessible data. If other information is required then it might be stored as well. 

# command interpreter

Handles the communication with the raspberry pi. Received commands are redistriburted between the separate module controlling tasks. Status info and other diagnostics are also handled and provided by this task.

# debug task (temporary?)

Handles debug uart, and controls the command interpreter, emulating to be the raspberry.