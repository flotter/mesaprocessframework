/* _____THIS MODULES INCLUDE_________________________________________________ */
#include "paramSvc.h"
#include "dbusMesaParameterApi.h"
#include "dbusMesaInterface.h"

/* _____STANDARD INCLUDES____________________________________________________ */

/* _____PROJECT INCLUDES_____________________________________________________ */
#include "typedef.h"

/* _____LOCAL DEFINITIONS____________________________________________________ */

/* _____MACROS_______________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____LOCAL VARIABLES______________________________________________________ */

/* _____LOCAL FUNCTION DECLARATIONS__________________________________________ */

/* _____LOCAL FUNCTIONS______________________________________________________ */

/* _____GLOBAL FUNCTIONS_____________________________________________________ */

Boolean paramSvc_parameterGet(ParamId_ParameterId parameterId, void* readBuffer, u16 readBufferSize)
{
   dbusMesaInterface_getParameter(parameterId,readBuffer, readBufferSize);
}

/**
 * The simple parameter user can make use of the paramSvc_parameterSet method to
 * set/update the data safely to the parameter provider.
 *
 * @param parameterId      Unique reference to the parameter
 * @param writeBuffer      Buffer containing the new data
 * @param writeBufferSize  Size of the data, must match the parameter size 100%
 * @return                 true indicates success
 */
Boolean paramSvc_parameterSet(ParamId_ParameterId parameterId, const void* writeBuffer, u16 writeBufferSize)
{
   dbusMesaInterface_setParameter(parameterId, writeBuffer, writeBufferSize);
}

Boolean paramSvc_subscribe(ParamId_ParameterId parameterId, ParamSvc_SubscriptionType type)
{


}

void paramSvc_unsubscribe(ParamId_ParameterId parameterId)
{

}

/* =============================================================================
 *  Copyright (c) 2014 MiX Telematics (Pty) Ltd [www.mixtelematics.com]
 *  All rights reserved.
 * ============================================================================= */
