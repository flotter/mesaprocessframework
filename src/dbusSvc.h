#ifndef __DBUS_SVC_H__
#define __DBUS_SVC_H__

/**
 *  @file
 *  @addtogroup DBUS_GLIB_CONNECTIVITY_CODE
 *  @{
 *  @brief 
 *
 *  @details 
 *  Code used for chatting with Ofono and Connman to manage and establish network connectivity
 *  
 *
 */


/* _____PROJECT INCLUDES_____________________________________________________ */

/* _____PUBLIC DECLERATIONS START____________________________________________ */

/* _____DEFINITIONS _________________________________________________________ */

/* _____TYPE DEFINITIONS_____________________________________________________ */

/* _____GLOBAL VARIABLE EXPORTS______________________________________________ */

/* _____GLOBAL FUNCTION DECLARATIONS_________________________________________ */

/**
 * GLIB/DBUS thread
 *
 * @param[in]  argument      Thread parameter
 */
gpointer dbusSvc_instanceThread(gpointer data);

/**
 * GLIB/DBUS init
 *
 * @return ResultCode    Return code
 */
void dbusSvc_init(gchar *dbusIP,gchar *dbusPort);

/**
 * GLIB/DBUS start
 *
 * @return ResultCode   Return code
 */
void dbusSvc_start(void);

void dbusSvc_destroy(void);

/* _____MACROS_______________________________________________________________ */

/* _____PUBLIC DECLERATIONS END______________________________________________ */

/**
 *  @}
 */
#endif /* __DBUSSVC_H__ */

/* =============================================================================
 *  Copyright (c) 2012 MiX Telematics (Pty) Ltd [www.mixtelematics.com]
 *  All rights reserved.   
 * ============================================================================= */
