#include "bluetooth/bluetooth.h"
#include "bluetooth/gatt_service.h"
#include "display/display.h"
#include "rgb/rgb.h"

#include <stdint.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>

int main(void) {
  int err = bt_enable(bt_ready);

  if (err) {
    printk("Bluetooth enable failed (err %d)\n", err);
  }

  if (!init_rgb()) {
    printk("LED strip not ready\n");
  }

  display_init();
  display_set_value(1);

  uint8_t hex[3];
  uint8_t saved_hex[3] = {0, 0, 0};

  while (true) {

    get_rgb_hex(hex);

    for (uint8_t i = 0; i < 3; i++) {
      if (hex[i] != saved_hex[i]) {
        saved_hex[0] = hex[0];
        saved_hex[1] = hex[1];
        saved_hex[2] = hex[2];
        update_rgb(saved_hex);
        break;
      }
    }

    k_sleep(K_MSEC(50));
  }
}
