-> ARM's  official RTOS kernel

-> Formerly named as Real Time Library (RL-ARM)

-> Flexible Schedular Both Preemptive and Non-preemptive

-> Unlimited No. of task but can only handle 250 active Task

-> Fast Context switching time specialy optimized for ARM processor by arm

-> Small footprint so we can use in small microcontrollers

-> the CMSIS RTOS is just an API defined by ARM and not an actual real time operating system.

Keil has offered a variant of their RTX RTOS which is compatible with the CMSIS RTOS API. So you can use a firmware written against the CMSIS RTOS API directly on the Keil RTX.