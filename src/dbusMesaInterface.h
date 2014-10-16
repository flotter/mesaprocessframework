#ifndef __DBUSMESAINTERFACE_H__
#define __DBUSMESAINTERFACE_H__
//note. Doxygen Module Structure is defined in "mesaDoxygenStruct.h" and needs to be kept up to date.
/**
 *  @file
 *  @addtogroup xxx_PARENT_MODULE_NAME_xxx
 *  @{
 *  @brief 
 *
 *  @details 
 *  xxx_detailed_description_of_this_header_file_xxx
 *  
 *
 */


/* _____PROJECT INCLUDES_____________________________________________________ */
#include "typedef.h"

/* _____PUBLIC DECLERATIONS START____________________________________________ */
PUBLIC_DECLERATIONS_START

/* _____DEFINITIONS _________________________________________________________ */

/* _____TYPE DEFINITIONS_____________________________________________________ */

/* _____GLOBAL VARIABLE EXPORTS______________________________________________ */

/* _____GLOBAL FUNCTION DECLARATIONS_________________________________________ */

void dbusMesaInterface_getParameter(ParamId_ParameterId id,void *buffer, u16 size);

void dbusMesaInterface_setParameter(ParamId_ParameterId parameterId, const void* buffer, u16 size);

void dbusMesaInterface_addDbusNameWatch(GDBusConnection *connection);

void dbusMesaInterface_removeDbusNameWatch();

void dbusMesaInterface_init();

void dbusMesaInterface_destroy();

/* _____MACROS_______________________________________________________________ */

/* _____PUBLIC DECLERATIONS END______________________________________________ */
PUBLIC_DECLERATIONS_END

/**
 *  @}
 */
#endif /* __DBUSMESAINTERFACE_H__ */

/* =============================================================================
 *  Copyright (c) 2012 MiX Telematics (Pty) Ltd [www.mixtelematics.com]
 *  All rights reserved.   
 * ============================================================================= */
