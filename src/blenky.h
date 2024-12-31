#include <stdint.h>

typedef uint32_t blenky_pin_index_t;

typedef enum {
    PIN_STATE_LOW,
    PIN_STATE_HIGH,
    PIN_STATE_FLOATING
} blenky_pin_state_t;

typedef enum {
    PERSISTENCE_TYPE_PIN_CONFIG,
    PERSISTENCE_TYPE_CONNECTION_CONFIG
} blenky_persistence_type_t;

typedef enum {
    ENERGY_LEVEL_LOWEST_POWER,
    ENERGY_LEVEL_LOW_POWER,
    ENERGY_LEVEL_BALANCED,
    ENERGY_LEVEL_LOW_LATENCY,
    ENERGY_LEVEL_LOWEST_LATENCY
} blenky_energy_level_t;

typedef enum {
    TIMER_MODE_SINGLE,
    TIMER_MODE_REPEATED
} blenky_timer_mode_t;

typedef enum {
    TIMER_INDEX_GPIOASM,
    ...,
    TIMER_INDEX_END // only marks the end of the timer list
} blenky_timer_index_t;

typedef struct {
    void (*on_digital_pin_write)(blenky_pin_index_t pin_index, blenky_pin_state_t state);
    blenky_pin_state_t (*on_digital_pin_read)(blenky_pin_index_t pin_index);
} blenky_gpio_callbacks;

typedef struct {
    void (*transport_init)(blenky_energy_level_t energy_level);

    void (*transport_send)(...);
} blenky_transport_generic_callbacks_t;

typedef struct {
    void (*on_i2c_write)(uint8_t address, uint8_t *data, uint32_t length);
    void (*on_i2c_read)(uint8_t address, uint8_t *data, uint32_t length);
} blenky_transport_i2c_callbacs_t;

typedef struct {
    blenky_transport_generic_callbacks_t generic;
    blenky_transport_i2c_callbacs_t i2c;
} blenky_transport_callbacks;

typedef struct {
    void (*on_persistence_data_write)(blenky_persistence_type_t persistence_type, uint8_t *data, uint32_t length);
    void (*on_persistence_data_read)(blenky_persistence_type_t persistence_type, uint8_t *data, uint32_t length);
} blenky_persistence_callbacks_t;

typedef struct {
    void (*on_timer_set)(blenky_timer_index_t timer_index, blenky_timer_mode_t timer_mode, uint32_t timeout);
    void (*on_timer_cancel)(blenky_timer_index_t timer_index);
} blenky_timer_callbacks;

typedef struct {
    blenky_gpio_callbacks gpio;
    blenky_transport_callbacks transport;
    blenky_timer_callbacks timer;
} blenky_callbacks_t;

typedef struct {
    blenky_callbacks_t callbacks;
} blenky_init_t;

typedef struct {
    blenky_callbacks_t callbacks;
} blenky_instance_t;

void blenky_init(blenky_instance_t *blenky_instance, blenky_init_t *blenky_init_s);

void blenky_transport_generic_receive(blenky_instance_t *instance, ...);

void blenky_gpio_handle_input_change(blenky_pin_index_t pin_index, blenky_pin_state_t pin_state);

void blenky_timer_handle_timeout(blenky_timer_index_t timer_index);
