#ifndef __PARAMSVC_H__
#define __PARAMSVC_H__
/**
 *  @addtogroup PARAMETER_SERVICE
 *  @{
 *  @brief
 *    Implements the parameter service module
 *  @details
 *  Parameters is the standard way of presenting data between modules. Parameters
 *  is a generic data transport that is data type-agnostic. However the end user
 *  of a parameter will need to know how to interpret the data.
 *
 *  There are two main interfaces to he parameter engine:
 *  1. Parameter provider
 *  2. Parameter user
 *
 *  Navigation:
 *  A parameter is identified by the parameter ID. This ID is a 32bit value
 *  that is divided into sub groups/fields. The first field is the parameter
 *  "grouping". This is rough grouping number to be used to signal the closest
 *  relationship of the parameter. e.g. everything that has got to do with the
 *  GPS and its data will fall under the same grouping.
 *
 *  Uniqueness:
 *  Every parameter needs to be unique and my not change definition as it is a
 *  system-wide entity. The contents of packed parameters that is used to
 *  communicate with the server needs to stay constant. Internal parameters may
 *  vary its contents if all providers and users agree.
 *
 *  @file paramSvc.h
 *
 */

/* _____PROJECT INCLUDES_____________________________________________________ */
#include "typedef.h"
#include "paramId.h"
#include "parameter.h"

/* _____PUBLIC DECLERATIONS START____________________________________________ */
PUBLIC_DECLERATIONS_START

/* _____DEFINITIONS _________________________________________________________ */


/* _____ TYPE DEFINITIONS : GENERAL _________________________________________ */

//typedef u8  ParamSvc_DataLength;

/* _____ TYPE DEFINITIONS : PARAMETER PROVIDER ______________________________ */
/**
 * \fn ParamSvc_Updated
 * This function prototype is a template to implement a function be called if
 * an parameter or sub-parameter has been updated from the outside.
 *
 * @param[in] parameterId  parameter Id that was updated.
 */
typedef void (*ParamSvc_Updated)(ParamId_ParameterId parameterId);
/**
 * \struct ParamSvc_Provider
 * This structure defines the parameter provider storage. The provider needs to
 * make and <b>keep</b> and instance of this structure. The fields of the
 * structure is off limits. All access to parameters must be done via the provided
 * methods.
 *
 */
/*typedef struct ParamSvc_ProviderStruct
{
   ParamId_ProviderGroup            group;                 //!< group of parameters provided
   osMutexId                        mutex;                 //!< MUTEX to lock parameter access
   ParamSvc_Updated                 updateNotification;    //!< when a parameter was updated from the outside this method is called
   Parameter_Base*                  parameterList;         //!< This is a list of all parameters provided by this specific provider
   struct ParamSvc_ProviderStruct*  nextProvider;          //!< This is to manage the list of providers owned by the parameter service
}ParamSvc_Provider;*/

/* _____ TYPE DEFINITIONS : PARAMETER SUBSCRIBER ____________________________ */
/// Filter with convention: true = pass, false = stop
//typedef Boolean (*ParamSvc_EventFilter)(Event_Listener* eventListener);

typedef enum
{
   PARAM_SVC_SUBSCRIPTION_TYPE_ON_CHANGE,     //!< Notify only when the parameter data changed
   PARAM_SVC_SUBSCRIPTION_TYPE_LATCH_CHANGED, //!< Notify only when the parameter data changed (single)
   PARAM_SVC_SUBSCRIPTION_TYPE_ON_UPDATE,     //!< Notify every time the parameter was written to
   PARAM_SVC_SUBSCRIPTION_TYPE_LATCH_UPDATE   //!< Notify every time the parameter was written to (single)
}ParamSvc_SubscriptionType;

/*
typedef struct Parameter_SubscriptionStruct
{
   Event_Listener            eventListener;
   ParamSvc_SubscriptionType subscriptionType; //!< What notification to detect
   ParamSvc_EventFilter      eventFilter;      //!< Event filter
   Kernel_Semaphore          semaphore;
   osSemaphoreId             semaphoreId;
   ParamId_FieldOffset       fieldOffset;
   ParamId_FieldSize         fieldSize;
}ParamSvc_Subscription; */

/* _____GLOBAL VARIABLE DECLARATIONS_________________________________________ */
extern const ParamId_ParameterId PARAMID_PARAMETER_INVALID;

/* _____GLOBAL FUNCTION DECLARATIONS SYSTEM__________________________________ */

/**
 * This function is called from the system initialisation.
 * @return ERROR_RESULT_OK if success else an error code
 */
//ResultCode paramSvc_init(void);

/**
 * This function is called from the system startup.
 * @return ERROR_RESULT_OK if success else an error code
 */
//ResultCode paramSvc_start(void);

/**
 * Clear all parameters and reboot system (system cannot function after all parameters are cleared)
 */
//void paramSvc_clearAllParameters(void);

/**
 * Persists all non volatile parameter to flash. This is required for clean recovery.
 * @param[in] timeout   number of ms allowed for the save action to complete
 * @return true on success
 */
//Boolean paramSvc_persistToFlash(u32 timeoutInMs);

/**
 * Traverse the list of registered parameters. This function is purely intended for diagnostic purposes.
 * @param[in,out] provider    the current provider, to initiate a find-first, set the pointer to NULL before calling the function.
 * @param[in,out] parameter   the current provider, to initiate a find-first, set the pointer to NULL before calling the function.
 * @return                    true if a valid parameter was found
 */
//Boolean paramSvc_findNextParameter(ParamSvc_Provider** provider, Parameter_Base** parameter);


/* _____GLOBAL FUNCTION DECLARATIONS USER____________________________________ */
/**
 * <b>Simple parameter user</b>
 * A simple parameter user will make use of the following functions to gain
 * access to parameter data.
 */

/**
 * The simple parameter user can make use of the paramSvc_parameterGet method to
 * get the data safely from the parameter provider. This method makes a copy of
 * the data to the structure provided by the caller.
 *
 * @param parameterId      Unique reference to the parameter
 * @param readBuffer       Data will be copied to this structure
 * @param readBufferSize   Size of the buffer the data will be coped to
 * @return                 true indicates success
 */
Boolean paramSvc_parameterGet(ParamId_ParameterId parameterId, void* readBuffer, u16 readBufferSize);

/**
 * The simple parameter user can make use of the paramSvc_parameterSet method to
 * set/update the data safely to the parameter provider.
 *
 * @param parameterId      Unique reference to the parameter
 * @param writeBuffer      Buffer containing the new data
 * @param writeBufferSize  Size of the data, must match the parameter size 100%
 * @return                 true indicates success
 */
Boolean paramSvc_parameterSet(ParamId_ParameterId parameterId, const void* writeBuffer, u16 writeBufferSize);

/* _____GLOBAL FUNCTION DECLARATIONS ENHANCED USER___________________________ */
/**
 * <b>Enhanced parameter user</b>
 * The enhanced parameter user will make use of the following functions.These
 * functions provides a means to access sub elements of a structure returned
 * by the paramSvc_parameterGet method.
 */

/**
 * The flowing function can be used to speed up the parameter structure data
 * access. The function retrieves a pointer that must be used in subsequent calls
 * to extract parameter structure fields.
 *
 * @param[in] parameterId        unique reference to the parameter
 * @return ParamSvc_Parameter*   data access structure
 */
//const Parameter_Base* paramSvc_getParameterReference(ParamId_ParameterId parameterId);

/**
 * Use this function in conjunction with paramSvc_getParameterReference to access
 * sub structure data from the retrieved data block.
 *
 * @param[in] parameterId        unique reference to the parameter
 * @param[out] offset            offset of the requested parameter
 * @param[out] size              size of the requested parameter
 * @return                       true on success
 */
//Boolean paramSvc_parameterGetDetails(ParamId_ParameterId parameterId, u16* offset, u16* size);

/* _____GLOBAL FUNCTION DECLARATIONS SUBSCRIBER______________________________ */
/**
 * This function allows a parameter user to get notification on parameter data changes.
 *
 * @param[in] parameterId         What parameter to watch, Sub parts of parameters can be watched if access functions is specified
 * @param[in] type               OnChange: a delta in the watched data is detected, or OnUpdate: someone wrote to the watched data.
 * @param[in] messageQueueId     The notification will be written to this messageQueue
 * @param[in] messageQueueValue  This value will be passed into the message queue, This could be user defined, e.g. the actual parameter Id
 * @param[out] subscription      This object needs to be static, and is used to store the search information
 *
 * @return True on success
 */
Boolean paramSvc_subscribe(ParamId_ParameterId parameterId, ParamSvc_SubscriptionType type);

/**
 * Setup subscription event filter
 *
 * @param[in] eventFilter   Pointer to event filter function
 * @param[in] subscription  Pointer to subscription definition
 *
 */
//void paramSvc_subscriptionEventFilter(const ParamSvc_EventFilter eventFilter, ParamSvc_Subscription* subscription);

/**
 * Unsubscribe from a parameter
 *
 * @param[in] parameterId  Parameter ID to unsubscribe from
 * @param[in] subscription Pointer to subscription definition
 */
void paramSvc_unsubscribe(ParamId_ParameterId parameterId);

/**
 * Clear the latch on change detection for the specified subscription
 *
 * @param[in] subscription Pointer to subscription definition
 */
//void paramSvc_subscriptionClear(const ParamSvc_Subscription* subscription);
/* _____GLOBAL FUNCTION DECLARATIONS PROVIDER________________________________ */
/**
 * <b>Parameter provider: registration</b>
 *
 * A parameter provider needs to register himself with the parameter service.
 * The following methods assist the provider in achieving this.
 */

/**
 * This is a helper function to initialise the parameter provider structure.
 * By making use of this method, the complexity of the structure is hidden
 * and we enforce future compatibility.
 *
 * @param[in] mutex        OS mutex that will be used to protect all parameters provided by this provider.
 * @param[in] group        parameters is split into parameter provider groups.
 * @param[in] updateNotificationFunction   when a parameter is updated by someone else, this call-back function will be executed.
 * @param[out] provider    instance of the parameter provider structure, must be static global.
 */
//void paramSvc_providerInitialise(osMutexId mutex, ParamId_ProviderGroup group, ParamSvc_Updated updateNotificationFunction, ParamSvc_Provider* const provider);

/**
 * This function gets called to actually add the parameter provider to the parameter
 * services' list of parameter providers.
 *
 * @param[in,out] provider reference to the fully initialised parameter provider structure.
 */
//void paramSvc_providerRegister(ParamSvc_Provider* provider);

/**
 * <b>Parameter provider: parameters</b>
 *
 * A parameter provider needs to register parameter that it will provide.
 * The following methods assist the provider in achieving this.
 */

/**
 * The function will actually add the parameter to the providers list of parameters.
 *
 * @param[in,out] provider    reference to the provider where this parameter must be added to.
 * @param[in,out] parameter   reference to fully populated the parameter structure.
 * @param[in]     defaultData if not null, this data will be loaded as the default data for the parameter.
 */
//void paramSvc_parameterAdd(ParamSvc_Provider* const provider, void* const parameter, const void* defaultData);

/**
 * The following function is used to update the contents of a parameter by copying
 * the data across into the parameter data structure. This method is simple, but would
 * require a temporary instance of the parameter data. This function lends itself to small
 * parameters.
 *
 * Mutexing is done by the parameter service.
 *
 * @param[in] provider         parameter provider structure
 * @param[in] parameter        parameter structure
 * @param[in] newDataPointer   pointer to the new data that will be copied into the parameter data field
 * @return
 */
//Boolean paramSvc_parameterUpdate(ParamSvc_Provider* const provider, void* const parameter, const void* const newDataPointer);

/**
 * the UpdateField method is useful to safely update members of a parameter struct.
 * @param[in] provider     Parameter provider for this field
 * @param[in] parameter    Parameter structure for this field
 * @param[in] parameterId  Parameter ID to identify sub data field to update
 * @param[in] newFieldData New data to be copied into this field
 *
 * @return true on success
 */
//Boolean paramSvc_parameterUpdateField(ParamSvc_Provider* const provider, void* const parameter, ParamId_ParameterId parameterId, const void* const newFieldData);
/**
 * <b>Parameter provider: complex parameters</b>
 *
 * If the parameter provides sub-data/structure access the following set of methods
 * can be used to update the sub elements individually. The process is protected
 * by a lock and unlock method .
 */


/* _____MACROS_______________________________________________________________ */

/* _____PUBLIC DECLERATIONS END______________________________________________ */
PUBLIC_DECLERATIONS_END
/**
 *  @}
 */
#endif /* __PARAMSVC_H__ */

/* =============================================================================
 *  Copyright (c) 2012 MiX Telematics (Pty) Ltd [www.mixtelematics.com]
 *  All rights reserved.
 * ============================================================================= */
