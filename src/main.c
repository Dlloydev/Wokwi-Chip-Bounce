/* Bounce Chip by Dlloydev */

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  pin_t pin_in;
  pin_t pin_out;
  uint32_t mode_attr;
  uint32_t duration_attr;
  uint16_t bounce;
} chip_state_t;

static void chip_timer_event(void *user_data);
static void chip_pin_change(void *user_data, pin_t pin, uint32_t value);

void chip_init(void) {
  chip_state_t *chip = malloc(sizeof(chip_state_t));
  chip->pin_in = pin_init("IN", INPUT);
  chip->pin_out = pin_init("OUT", OUTPUT);
  chip->mode_attr = attr_init("mode", 3);
  chip->duration_attr = attr_init("duration", 1000);

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
  timer_t timer_id = timer_init(&timer_config);
  timer_start(timer_id, 1, true);
}

static void chip_timer_event(void *user_data) {
  chip_state_t *chip = (chip_state_t*)user_data;
  pin_write(chip->pin_out, (chip->bounce & 1) ^ pin_read(chip->pin_in));
  chip->bounce >>= 1;
  static uint8_t count;
  count++;
  if (!count) timer_start((timer_t)0, attr_read(chip->duration_attr) / 16, true);
}

static void chip_pin_change(void *user_data, pin_t pin, uint32_t value) {
  printf("Pin change: %d %d\n", pin, value);
  chip_state_t *chip = (chip_state_t*)user_data;
  if(attr_read(chip->mode_attr) == 1 && value) chip->bounce = get_sim_nanos();
  else if(attr_read(chip->mode_attr) == 2 && !value) chip->bounce = get_sim_nanos();
  else if(attr_read(chip->mode_attr) == 3) chip->bounce = get_sim_nanos();
}
