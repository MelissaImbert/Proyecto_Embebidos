/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _DATA_SAVE_H    /* Guard against multiple inclusion */
#define _DATA_SAVE_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
#include "framework/GPS.h"
#include "freeRTOS/include/FreeRTOS.h"
#include "freeRTOS/include/task.h"
#include "freeRTOS/include/semphr.h"
#include "framework/SIM808.h"
#include <stdint.h>
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
/* TODO:  Include other files here if needed. */
void data_GPS(void);
void datalog(void);
#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
