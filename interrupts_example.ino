// This is scaffold code for working with interrupts. 
// You can use this code to count the pulses that a flow meter outputs.
// It is on you to modify this code to compute the flow rate.

// This can be any D or A pin on an Argon. 
// You may use up to 8 interrupts at a time.
int FLOW_PIN = D0;

// use a global variable so it can be accessed in the interupt handler.
uint32_t pulse_count = 0;

// a counter used to track the time since the interrupt function was last called.
unsigned long last_interrupt = millis();
unsigned long threshold = 50;               // In milliseconds. This needs to be tuned.

// define an function that is called when the interrupt fires.
void IncrementPulseCounter()
{
    // when pulling a pin high the interrupt will "bounce" (i.e., trigger several interrupts)
    // we need to throw away those bounce using the threshold.
    if ((millis() - last_interrupt) > threshold) {
        pulse_count++;              // increment the global counter
        last_interrupt = millis();  // update the last_interrupt
    }
}


// this runs once
void setup() {
    pinMode(FLOW_PIN, INPUT);       // sets interrupt pin as input
    
    // usage:
    //      attachedInterrupt(PIN, FUNCTION, MODE)
    //  
    //      PIN         pin that gets pulled to 3.3V (if MODE == RISING) or GND (if MODE == FALLING)
    //      FUNCTION    the function you'd like to use to count interrupts or compute a derivative value
    //      MODE        RISING, FALLING, or CHANGE
    attachInterrupt(FLOW_PIN, IncrementPulseCounter, RISING);
}

// this runs forever
void loop() {
    Particle.publish("Pulse Count", String(pulse_count));   // publish an update to the interrupt counter
    delay(2500);                                            // loop every 2.5 seconds 
}
