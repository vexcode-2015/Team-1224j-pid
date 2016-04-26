void iteratePID() {
   measured = nMotorEncoder[flywheel1];
   // Ignore strangely high error values
   if (abs(error) < 130) {
      error = target - measured;
   }

   integral += error;
   if (integral > integral_limit) {
      integral = integral_limit;
   } else if (integral < -integral_limit) {
      integral = -integral_limit;
   }

   derivative = error - error_prev;
   error_prev = error;

   motor[flywheel1] = motor[flywheel2] = motor[flywheel3] += KP*(error) + KI*(integral) + KD*(derivative);

   nMotorEncoder[flywheel1] = 0;
   wait1Msec(PIDdelay);
}

void tunePID() {
   clearTimer(T1);
   target = 24;
   motor[intakeFront] = motor[intakeUp] = 127;
   while (true) {
   	iteratePID();

      // Uncomment the debug stream writer below if you want to output values that would
      // be human readable
      // writeDebugStreamLine("Time: %d ms. Measured: %d ticks. Error: %d Motor power: %d", time1[T1], measured, error, motor[flywheel1]);

      // Uncomment the debug stream writer below if you want to output values that would
      // be good for making a spreadsheet or graph
      //writeDebugStreamLine("%d,%d,%d", time1[T1], measured, motor[flywheel1]);

      // Automatically ramp flywheel motors down after 18 seconds
      if (time1[T1] > 18000) {
         while (true) {
   			if (motor[flywheel1] > 0) {
   				motor[flywheel1] = motor[flywheel2] = motor[flywheel3] -= 1;
   				wait1Msec(100);
   			}
   		}
      }
   }
}
