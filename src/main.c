#include "bluetooth/bluetooth.h"
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/settings/settings.h>

int main(void) {
  int err = bt_enable(bt_ready);

  if (err) {
    printk("Bluetooth enable failed (err %d)\n", err);
  }

  while (true) {
    k_sleep(K_SECONDS(1));
  }
}
