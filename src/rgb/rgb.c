#include <stdbool.h>
#include <stdint.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/kernel.h>

static const struct device *strip;

bool init_rgb() {

  const struct gpio_dt_spec pwr =
      GPIO_DT_SPEC_GET(DT_NODELABEL(neopixel_pwr), enable_gpios);

  if (device_is_ready(pwr.port)) {
    gpio_pin_configure_dt(&pwr, GPIO_OUTPUT_ACTIVE);
  }

  strip = DEVICE_DT_GET(DT_ALIAS(led_strip));

  if (!device_is_ready(strip) || !device_is_ready(pwr.port)) {
    return false;
  } else {
    return true;
  }
}

void update_rgb(const uint8_t rgb[3]) {
  struct led_rgb pixel = {.r = rgb[0], .g = rgb[1], .b = rgb[2]};
  led_strip_update_rgb(strip, &pixel, 1);
}
