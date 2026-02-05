#include "zephyr/kernel.h"
#include <zephyr/sys/printk.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/settings/settings.h>

static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
};

static const struct bt_data sd[] = {
    BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME,
            sizeof(CONFIG_BT_DEVICE_NAME) - 1),
};

void bt_ready(int err) {
  if (err) {
    printk("Bluetooth init failed (err %d)\n", err);
    return;
  }

  printk("Bluetooth initialized\n");

  if (IS_ENABLED(CONFIG_SETTINGS)) {
    settings_load();
  }

  err = bt_le_adv_start(BT_LE_ADV_CONN_FAST_1, ad, ARRAY_SIZE(ad), sd,
                        ARRAY_SIZE(sd));
  if (err) {
    printk("Advertising failed to start (err %d)\n", err);
    return;
  }

  printk("Advertising successfully started\n");
}
