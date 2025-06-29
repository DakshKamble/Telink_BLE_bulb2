/********************************************************************************************************
 * @file     app_att.h
 *
 * @brief    This is the header file for BLE SDK
 *
 * @author	 BLE GROUP
 * @date         12,2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *******************************************************************************************************/

#ifndef APP_ATT_H_
#define APP_ATT_H_






/* ATT Handle define ---------------------------------------------------------*/
typedef enum
{
	ATT_H_START = 0,


	//// Gap ////
	/**********************************************************************************************/
	GenericAccess_PS_H, 					//UUID: 2800, 	VALUE: uuid 1800
	GenericAccess_DeviceName_CD_H,			//UUID: 2803, 	VALUE:  			Prop: Read | Notify
	GenericAccess_DeviceName_DP_H,			//UUID: 2A00,   VALUE: device name
	GenericAccess_Appearance_CD_H,			//UUID: 2803, 	VALUE:  			Prop: Read
	GenericAccess_Appearance_DP_H,			//UUID: 2A01,	VALUE: appearance
	CONN_PARAM_CD_H,						//UUID: 2803, 	VALUE:  			Prop: Read
	CONN_PARAM_DP_H,						//UUID: 2A04,   VALUE: connParameter


	//// gatt ////
	/**********************************************************************************************/
	GenericAttribute_PS_H,					//UUID: 2800, 	VALUE: uuid 1801
	GenericAttribute_ServiceChanged_CD_H,	//UUID: 2803, 	VALUE:  			Prop: Indicate
	GenericAttribute_ServiceChanged_DP_H,   //UUID:	2A05,	VALUE: service change
	GenericAttribute_ServiceChanged_CCB_H,	//UUID: 2902,	VALUE: serviceChangeCCC


	//// device information ////
	/**********************************************************************************************/
	DeviceInformation_PS_H,					//UUID: 2800, 	VALUE: uuid 180A
	DeviceInformation_pnpID_CD_H,			//UUID: 2803, 	VALUE:  			Prop: Read
	DeviceInformation_pnpID_DP_H,			//UUID: 2A50,	VALUE: PnPtrs


	//// battery service ////
	/**********************************************************************************************/
	BATT_PS_H, 								//UUID: 2800, 	VALUE: uuid 180f
	BATT_LEVEL_INPUT_CD_H,					//UUID: 2803, 	VALUE:  			Prop: Read | Notify
	BATT_LEVEL_INPUT_DP_H,					//UUID: 2A19 	VALUE: batVal
	BATT_LEVEL_INPUT_CCB_H,					//UUID: 2902, 	VALUE: batValCCC

	#if (BLE_OTA_SERVER_ENABLE)
	//// Ota ////
	/**********************************************************************************************/
	OTA_PS_H, 								//UUID: 2800, 	VALUE: telink ota service uuid
	OTA_CMD_OUT_CD_H,						//UUID: 2803, 	VALUE:  			Prop: read | write_without_rsp
	OTA_CMD_OUT_DP_H,						//UUID: telink ota uuid,  VALUE: otaData
	OTA_CMD_OUT_DESC_H,						//UUID: 2901, 	VALUE: otaName
	#endif

	#if (TELIK_SPP_SERVICE_ENABLE)
	//// SPP ////
	/**********************************************************************************************/
	SPP_PS_H,								//UUID: 2800, 	VALUE: telink spp service uuid

	//server to client
	SPP_SERVER_TO_CLIENT_CD_H,				//UUID: 2803, 	VALUE:  			Prop: read | Notify
	SPP_SERVER_TO_CLIENT_DP_H,				//UUID: telink spp s2c uuid,  VALUE: SppDataServer2ClientData
	SPP_SERVER_TO_CLIENT_CCB_H,				//UUID: 2902, 	VALUE: SppDataServer2ClientDataCCC
	SPP_SERVER_TO_CLIENT_DESC_H,			//UUID: 2901, 	VALUE: TelinkSPPS2CDescriptor

	//client to server
	SPP_CLIENT_TO_SERVER_CD_H,				//UUID: 2803, 	VALUE:  			Prop: read | write_without_rsp
	SPP_CLIENT_TO_SERVER_DP_H,				//UUID: telink spp c2s uuid,  VALUE: SppDataClient2ServerData
	SPP_CLIENT_TO_SERVER_DESC_H,			//UUID: 2901, 	VALUE: TelinkSPPC2SDescriptor
	
	//pair
	SPP_PAIR_CD_H,							//UUID: 2803, 	VALUE:  			Prop: write_without_rsp | Notify
	SPP_PAIR_DP_H,							//UUID: telink spp pair uuid,  VALUE: SppDataPairData
	SPP_PAIR_CCB_H,							//UUID: 2902, 	VALUE: SppDataPairDataCCC
	SPP_PAIR_DESC_H,						//UUID: 2901, 	VALUE: TelinkSPPPairDescriptor
#endif

	ATT_END_H,

}ATT_HANDLE;




/**
 * @brief   GATT initialization.
 *          !!!Note: this function is used to register ATT table to BLE Stack.
 * @param   none.
 * @return  none.
 */
void my_gatt_init (void);



#endif /* APP_ATT_H_ */
