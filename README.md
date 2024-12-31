# BLEnky-core
platform-independant BLEnky core implementation

# Goal
BLEnky, in general, is supposed to serve as an easy entry into hacking and building connected devices.
It exposes functionality concerning GPIO-centric tasks like
- reading binary sensors
- writing binary outputs
    - relais
    - leds
- writing analog outputs
    - dimmable LEDs
    - servos
- executing more complicated or timing-critical tasks on-chip, offline via [gpioASM](https://github.com/dakhnod/gpioASM)

This repository contains most of BLEnkys business logic, consisting of of handling of some GATT protocols. Some other tasks are also present, like
- input debouncing
- speed calculation (for Cycling Speed/Cadence profile)
- gpioASM handling

Essentially, theses tasks do not differ from platform to platform.

As such, this core can be included unchanged on any platform. The only thing added is the "glue" to the real hardware, be it some microcontroller or a simulated environment. This "glue" consists of the following parts:
- writing physical output pins
- (a)synchronous reading of input pins
- handling of timer requests
- handling of transports
    - GATT based (endpoints structured in services and characteristics, two levels)
    - i2c based (for transport-pinned peripherals)
- handling of persistent binary data

On an nrf device, the BLEnky "glue" could look like this:
```
void pin_write(uint32_t index, pin_state_t *state){
    # call a nordic specific function
    nrf_gpio_pin_write(index, state->state);
}
blenky_init_t blenky_init = {
    .on_write = pin_write
};
blenky_init(&blenky_init);
```

In a simulation on a PC it could look like this:
```
void pin_write(uint32_t index, pin_state_t *state){
    # call a mock function
    printf("setting pin %d to state %d\n", index, state->state);
}
blenky_init_t blenky_init = {
    .on_write = pin_write
};
blenky_init(&blenky_init);
```