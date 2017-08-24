#include "device.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int32_t open_device(const char* device)
{
    int32_t fd = open(device, O_RDWR);
    
    if(fd < 0)
    {
        printf("An error occurred in the open.\n");
        return RET_ERR;
    }
    
    return fd;
}

int32_t read_device(int32_t fd, nunchuk_t* values)
{
    if(read(fd, values, sizeof(nunchuk_t)) < 0)
    {
        printf("An error occurred in the read.\n");
        return RET_ERR;
    }
    
    return RET_OK;
}

int32_t close_device(int32_t fd)
{
    if(close(fd) < 0)
    {
        printf("An error occurred in the close.\n");
        return RET_ERR;
    }
    
    return RET_OK;
}

