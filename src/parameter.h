#ifndef __PARAMETER_H__
#define __PARAMETER_H__
/**
 *  @file
 *  @addtogroup PARAMETER_DEF
 *  @{
 *  @brief 
 *  Defines and provides initialisation functions for parameter types
 *
 *  @details 
 *  Definition and helper module that defines all the different parameter types
 *  and provides initialisation functions for all of them
 *
 */


/* _____PROJECT INCLUDES_____________________________________________________ */
#include "typedef.h"
#include "paramId.h"
//#include "NvParam.h"
//#include "event.h"

/* _____DEFINITIONS _________________________________________________________ */
PUBLIC_DECLERATIONS_START

/* _____TYPE DEFINITIONS_____________________________________________________ */

typedef u16  Parameter_Size;

/**
 * \fn Parameter_FieldAccessFunc
 * This function prototype is a template to implement a function to deliver
 * sub-data/structure access to a parameter.
 *
 * @param[in] parameterId     parameter that need access
 * @param[out] subDataOffset  offset of the sub-data field in the memory block
 * @param[out] dataLength     size of the sub-data field
 * @return                    true on success
 */
typedef Boolean (*Parameter_FieldAccessFunc)(ParamId_FieldId fieldId, u16* fieldOffset, u16* fieldLength);


typedef enum Parameter_ParameterModifierEnum
{
   PARAM_MODIFIER_NULL,      //!< Data was NULLed
   PARAM_MODIFIER_DEFAULT,   //!< Parameter was loaded with the DEFAULT value
   PARAM_MODIFIER_NVRAM,     //!< Parameter was loaded from NVRAM
   PARAM_MODIFIER_FLASH,     //!< Parameter was loaded from FLASH
   PARAM_MODIFIER_PROVIDER,  //!< Parameter was set by the provider
   PARAM_MODIFIER_USER,      //!< Parameter was set by a USER
}Parameter_Modifier;

/**
 * Parameter Type
 */
typedef enum Parameter_TypeEnum
{
   PARAM_TYPE_SETTING,     //!< Setting parameter - stored directly to Flash
   PARAM_TYPE_VOLATILE,    //!< Volatile parameter - only stored in RAM
   PARAM_TYPE_NON_VOLATILE,//!< Non Volatile parameter - stored in NVRAM and backed up to flash
   PARAM_TYPE_ARBITRATED   //!< Arbitrated parameter - volatile parameter that has a callback function to determine whether the update is accepted
}Parameter_Type;

/**
 * Base parameter type - fields common to all parameter types
 */

/*
typedef struct Parameter_BaseStruct
{
   Parameter_Type               type;             //!< Parameter type: SETTING, VOLATILE or NON_VOLATILE
   ParamId_StructureId          dataStructureId;  //!< identifier of this parameter data structure
   Boolean                      readOnly;         //!< 3rd party access to this parameter
   struct Parameter_BaseStruct* nextParameter;    //!< next node in the parameter providers' list of parameters
   Parameter_Modifier           modifier;         //!< the last module that modified the data of this parameter
   Parameter_Size               dataSize;         //!< Size of parameter data
   Event_Dispatcher             eventDispatcher;  //!< Event dispatcher used to handle parameter subscriptions
}Parameter_Base; */

/**
 * Settings parameter
 */
/*
typedef struct Parameter_SettingParamStruct
{
   Parameter_Base base;    //!< Common parameter fields
}Parameter_SettingParam;
*/

/**
 * Volatile parameter type
 */
/*typedef struct Parameter_VolatileParamStruct
{
   Parameter_Base base;    //!< Common parameter fields
   void*          data;    //!< Pointer to ram location of data (allocated by parameter service)
}Parameter_VolatileParam;*/

/**
 * Non-volatile parameter type
 */
/*typedef struct Parameter_NonVolatileParamStruct
{
   Parameter_Base base;       //!< Common parameter fields
   NvParam_Address address;   //!< Address of parameter data in NVRAM storage
}Parameter_NonVolatileParam;*/

/**
 * Update source for arbitrated parameters
 */
/*typedef u8 Parameter_UpdateSource;

struct Parameter_ArbitratedParamStruct;*/

/**
 * Parameter arbitration callback function
 *
 * @param parameter  Parameter to update
 * @param source     Source attempting to update parameter
 * @return true if parameter update is allowed
 */
//typedef Boolean (*Parameter_Arbitrator)(struct Parameter_ArbitratedParamStruct* parameter, Parameter_UpdateSource source);

/**
 * Arbitrated parameter type
 */
/*
typedef struct Parameter_ArbitratedParamStruct
{
   Parameter_VolatileParam  param;        //!< Volatile parameter struct
   Parameter_Arbitrator     arbitrator;   //!< Arbitration callback function
}Parameter_ArbitratedParam;
*/


/* _____GLOBAL FUNCTION DECLARATIONS_________________________________________ */

/**
 * Initialise a setting parameter
 *
 * @param[in]   parameterId   Parameter ID
 * @param[in]   dataSize      Size of parameter data
 * @param[in]   readOnly      True if parameter must be accessed only by the owner
 * @param[out]  parameter     Pointer to parameter structure
 */
/*void parameter_initSettingParam(ParamId_ParameterId parameterId,
                                Parameter_Size dataSize,
                                Boolean readOnly,
                                Parameter_SettingParam* parameter);*/

/**
 * Initialise a volatile parameter
 *
 * @param[in]   parameterId   Parameter ID
 * @param[in]   dataSize      Size of parameter data
 * @param[in]   readOnly      True if parameter must be accessed only by the owner
 * @param[out]  parameter     Pointer to parameter structure
 */
/*void parameter_initVolatileParam(ParamId_ParameterId parameterId,
                                 Parameter_Size dataSize,
                                 Boolean readOnly,
                                 Parameter_VolatileParam* parameter);*/

/**
 * Initialise a non-volatile parameter
 *
 * @param[in]   parameterId   Parameter ID
 * @param[in]   dataSize      Size of parameter data
 * @param[in]   readOnly      True if parameter must be accessed only by the owner
 * @param[out]  parameter     Pointer to parameter structure
 */
/*void parameter_initNonVolatileParam(ParamId_ParameterId parameterId,
                                    Parameter_Size dataSize,
                                    Boolean readOnly,
                                    Parameter_NonVolatileParam* parameter);*/

/**
 * Initialise a arbitrated parameter
 *
 * @param[in]  parameterId   Parameter ID
 * @param[in]  dataSize      Size of parameter data
 * @param[in]  readOnly      True if parameter must be accessed only by the owner
 * @param[in]  arbitrator    Arbitration callback function
 * @param[out] parameter     Pointer to parameter structure
 */
/*void parameter_initArbitratedParam(ParamId_ParameterId parameterId,
                                   Parameter_Size dataSize,
                                   Boolean readOnly,
                                   Parameter_Arbitrator arbitrator,
                                   Parameter_ArbitratedParam* parameter);*/

/**
 * Compare two parameter IDs
 *
 * @param[in] paramA     Parameter ID to compare
 * @param[in] paramB     Parameter ID to compare
 *
 * @return  true if parameter IDs are equal
 */
//Boolean parameter_compareIds(ParamId_ParameterId paramA, ParamId_ParameterId paramB);

/* _____COMMS PARAMETER MAPPING______________________________________________ */
/**
 * Maps a server parameter ID to a local parameter ID
 *
 *  U16 == [U8Group][U8DataStructure]
 *         |       ||               |          ________
 *         |       ||               | ________/ 0x0000 \_________
 *         |       ||               |/                           \
 *  U32 == [U8Group][U8DataStructure][U16ParameterContextDependant]
 * 
 * @param svrParameterId   16bit server parameter ID
 * @return                 32bit internal parameter ID
 */
//ParamId_ParameterId parameter_serverToInternal(ParamId_ServerParameterId svrParameterId);

/**
 * Maps a internal parameter ID to a 16 server parameterID
 * 
 *  U32 == [U8Group][U8DataStructure][U16ParameterContextDependant]
 *         |       ||               |
 *         |       ||               |
 *         |       ||               |
 *  U16 == [U8Group][U8DataStructure]
 * 
 * @param ParameterId   32bit internal parameter ID
 * @return              16bit server parameter ID
 */
//ParamId_ServerParameterId parameter_internalToServer(ParamId_ParameterId parameterId);

/**
 * This function is intended to safely extract a context specific field from the
 * parameter data block returned by the paramSvc_parameterGet method. This is a
 * safe way of working with structures returned as parameters.
 *
 * @param parameterId         unique reference to the parameter
 * @param parameterData       pointer to the retrieved parameter structure
 * @param parameterDataSize   size of the parameter structure
 * @param readBuffer          destination to copy the data block to
 * @param readBufferSize      size of the destination buffer
 * @return                    true on success
 */
//Boolean parameter_parameterExtract(ParamId_ParameterId parameterId, const void* const parameterData, u16 parameterDataSize, void* readBuffer, u16 readBufferSize);

/* _____MACROS_______________________________________________________________ */

/**
 *  @}
 */
PUBLIC_DECLERATIONS_END
#endif /* __PARAMETER_H__ */

/* =============================================================================
 *  Copyright (c) 2012 MiX Telematics (Pty) Ltd [www.mixtelematics.com]
 *  All rights reserved.   
 * ============================================================================= */
