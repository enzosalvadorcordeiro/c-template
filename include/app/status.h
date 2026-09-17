#ifndef APP_STATUS_H
#define APP_STATUS_H

/**
 * Process-wide status codes. Zero is success so the value can be returned
 * from main and from library functions without a parallel bool.
 */
typedef enum app_status
{
    APP_OK = 0,
    APP_ERR_USAGE = 64, /* EX_USAGE  -- bad arguments */
    APP_ERR_IO = 74,    /* EX_IOERR  -- read/write failed */
    APP_ERR_NOINPUT = 66
} app_status;

#endif /* APP_STATUS_H */
