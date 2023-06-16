# CAT5140 Library

This library provides a class to control the CAT5140 digital potentiometer.

## Usage

The potentiometer position may be set using `writeWiper(position)`. The position is specified as a value between 0 and 255, where 0 is the lowest resistance between RL and RW, and 255 is the highest resistance between RL and RW.
