#include <stdint.h>
#include <string.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/sys/printk.h>

// Custom 128-bit UUIDs for the RGB service and its write characteristic.
#define BT_UUID_RGB_SERVICE_VAL                                                \
  BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef0)
#define BT_UUID_RGB_CHAR_VAL                                                   \
  BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef1)

#define BT_UUID_RGB_SERVICE BT_UUID_DECLARE_128(BT_UUID_RGB_SERVICE_VAL)
#define BT_UUID_RGB_CHAR BT_UUID_DECLARE_128(BT_UUID_RGB_CHAR_VAL)

static uint8_t last_rgb[3];

static ssize_t rgb_write_cb(struct bt_conn *conn,
                            const struct bt_gatt_attr *attr, const void *buf,
                            uint16_t len, uint16_t offset, uint8_t flags) {
  if (offset != 0) {
    return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
  }

  if (len == 3) {
    memcpy(last_rgb, buf, 3);
    printk("RGB write: %02X %02X %02X\n", last_rgb[0], last_rgb[1],
           last_rgb[2]);
  } else {
    printk("RGB write length %u (expected 3)\n", len);
  }

  return len;
}

BT_GATT_SERVICE_DEFINE(
    rgb_svc, BT_GATT_PRIMARY_SERVICE(BT_UUID_RGB_SERVICE),
    BT_GATT_CHARACTERISTIC(BT_UUID_RGB_CHAR,
                           BT_GATT_CHRC_WRITE | BT_GATT_CHRC_WRITE_WITHOUT_RESP,
                           BT_GATT_PERM_WRITE, NULL, rgb_write_cb, NULL));

void get_rgb_hex(uint8_t hex[3]) { memcpy(hex, last_rgb, 3); }
