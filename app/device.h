#ifndef DEVICE_C
#define DEVICE_C

#include <stdint.h>

#define NUNCHUK_DEVICE  "/dev/nunchuk"

#define RET_OK          0
#define RET_ERR         -1

typedef struct nunchuk_t {
    uint8_t x_axis;
    uint8_t y_axis;
    uint8_t c_pressed;
    uint8_t z_pressed;
} nunchuk_t;

int32_t open_device(const char* device);
int32_t read_device(int32_t fd, nunchuk_t* values);
int32_t close_device(int32_t fd);

#endif
