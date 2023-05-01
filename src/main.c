// Bounce Chip v1.0.6 by David Lloyd

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  pin_t pin_in;
  pin_t pin_out;
  uint32_t Mode_attr;
  uint32_t mode_attr;
  uint32_t mode;
  uint32_t Microseconds_attr;
  uint32_t microseconds_attr;
  uint32_t microseconds;
  uint16_t bounce;
  bool inputChanged;
  timer_t timer;
} chip_state_t;

static void chip_timer_event(void *user_data);
static void chip_pin_change(void *user_data, pin_t pin, uint32_t value);

void chip_init(void) {
  chip_state_t *chip = malloc(sizeof(chip_state_t));
  chip->pin_in = pin_init("IN", INPUT);
  chip->pin_out = pin_init("OUT", OUTPUT);

  chip->mode_attr = attr_init_float("mode", 3);
  chip->mode = attr_read(chip->mode_attr);
  if (chip->mode < 0) chip->mode = 0;
  else if (chip->mode > 3) chip->mode = 3;
  chip->Mode_attr = attr_init("Mode", chip->mode);

  chip->microseconds_attr = attr_init_float("microseconds", 3);
  chip->microseconds = attr_read(chip->microseconds_attr);
  if (chip->microseconds < 0) chip->microseconds = 0;
  else if (chip->microseconds > 5000) chip->microseconds = 5000;
  chip->Microseconds_attr = attr_init("Microseconds", chip->microseconds);

  const pin_watch_config_t both = {
    .edge = BOTH,
    .pin_change = chip_pin_change,
    .user_data = chip
  };
  pin_watch(chip->pin_in, &both);

  const timer_config_t timer_config = {
    .callback = chip_timer_event,
    .user_data = chip,
  };
  chip->timer = timer_init(&timer_config);
  timer_start(chip->timer, 10, true);
}

static void chip_timer_event(void *user_data) {
  chip_state_t *chip = (chip_state_t*)user_data;
  if(chip->inputChanged) {
  pin_write(chip->pin_out, pin_read(chip->pin_in));
  chip->inputChanged = false;
  } else pin_write(chip->pin_out, (chip->bounce & 1) ^ pin_read(chip->pin_in));
  chip->bounce >>= 1;
  static uint8_t count;
  count++;
  if (!count) timer_start(chip->timer, attr_read(chip->Microseconds_attr) / 16, true);
}

static void chip_pin_change(void *user_data, pin_t pin, uint32_t value) {
  chip_state_t *chip = (chip_state_t*)user_data;
  if(attr_read(chip->Mode_attr) == 1 && value) chip->bounce = get_sim_nanos();
  else if(attr_read(chip->Mode_attr) == 2 && !value) chip->bounce = get_sim_nanos();
  else if(attr_read(chip->Mode_attr) == 3) chip->bounce = get_sim_nanos();
  chip->inputChanged = true;
}
