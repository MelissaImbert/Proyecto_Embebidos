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

#ifndef _BUTTONS_H    /* Guard against multiple inclusion */
#define _BUTTONS_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
/* ************************************************************************** */
/* ************************************************************************** */
extern bool umbralset = true;
/* This section lists the other files that are included in this file.
 */
void userInterfaceButton(void *p_param);
void setUmbralButton(void *p_param);
/* TODO:  Include other files here if needed. */


#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
