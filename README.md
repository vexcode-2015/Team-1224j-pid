## Team-1224j-pid

This is the PID code 1224J used.

Pretty simple. I believe in the version we used at states, I set KI to 0 (no Integral). To compensate, I made the PID output add to the motor power value (instead of the motor power value being set directly to the PID output). This got rid of an oscillation issue we had, but just tuning KI more may have possibly fixed the oscillation too.
