/********************************************************************************************************
 * @file    flash_prot.h
 *
 * @brief   This is the header file for BLE SDK
 *
 * @author  BLE GROUP
 * @date    06,2020
 *
 * @par     Copyright (c) 2020, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
 *
 *******************************************************************************************************/
#ifndef VENDOR_COMMON_FLASH_PROT_H_
#define VENDOR_COMMON_FLASH_PROT_H_


/**
 * @brief	Application Flash protection enable control. Default disable, use can enable it in app_conifg.h.
 * 			User must enable Flash protection on mass production application !!!
 */
#ifndef APP_FLASH_PROTECTION_ENABLE
#define APP_FLASH_PROTECTION_ENABLE					0   //enable or disable
#endif


/**
 * @brief	Application Flash protection log enable or not. Default disable, use can enable it in app_conifg.h.
 */
#ifndef APP_FLASH_PROT_LOG_EN
#define APP_FLASH_PROT_LOG_EN						0
#endif


/**
 * @brief    application lock block definition
 *   Each kind of IC have multiple flash supported.
 *   Different flash, especially form different vendor, do not use all same lock block size.
 *   If user want protect certain range of flash, they must consider different kind of flash supported lock block size.
 *   Here, we just put a few of block size to show how to use flash protection.
 *   If user want use more specific flash protection area, they should add by themselves.
 */
typedef enum{
	/* lock low 128K for firmware, do not consider system data and user data.
	 * 1. For 128K capacity flash
	 * 		can not lock 128K all, should leave some upper 64K for system data and user data.
	 *    	System data is stored above 64K(0x10000). User data must stored above 64K too. Then we can choose lock 64K.
	 *    	If user data stored below 64K, please do not use reference code, but design and implement by themselves.
	 * 2. For 512K capacity flash
	 * 		System data is stored above K. User data must stored above 512K too.
	 *      If using Telink OTA, low 512K area is used for both raw firmware and new firmware storage.
	 *      If user data stored below 512K, please do not use reference code, but design and implement by themselves. */

	FLASH_LOCK_FW_LOW_128K		=	0,		//000000h-01FFFFh
	/* lock low 256K for firmware, do not consider system data and user data.
	 * Flash size is at least 512K in this SDK, system data is stored above 256K. User data must stored above 256K too.
	 * If using Telink OTA, low 256K area is used for both raw firmware and new firmware storage.
	 * If user data stored below 256K, please do not use reference code, but design and implement by themselves. */
	FLASH_LOCK_FW_LOW_256K		=	1,		//000000h-03FFFFh

	/* lock low 512K for firmware, do not consider system data and user data.
	 * 1. For 512K capacity flash
	 * 		can not lock 512K all, should leave some upper 64K for system data and user data.
	 *    	System data is stored above 448K(0x70000). User data must stored above 448K too. Then we can choose lock 448K.
	 *    	If user data stored below 448K, please do not use reference code, but design and implement by themselves.
	 * 2. For 1M capacity flash
	 * 		System data is stored above 512K. User data must stored above 512K too.
	 *      If using Telink OTA, low 512K area is used for both raw firmware and new firmware storage.
	 *      If user data stored below 512K, please do not use reference code, but design and implement by themselves. */

	FLASH_LOCK_FW_LOW_512K		=	2,		//000000h-07FFFFh

	/* attention special case:
	 * for some 1M capacity flash, do not support lock low 256/448/512K command, choose locking low 768K area.
       System data is stored above 960K(0xF0000). User data must stored above 768K !!! */
}flash_app_lock_e;

/**
 * @brief	The structure of some initialization error about flash protect.
 */
typedef struct{
	u8	init_err;

}flash_prot_t;
extern flash_prot_t	blc_flashProt;
/**
 * @brief		this function serves to  locks a specific region or address range in the flash memory.
 * @param[in]	none
 * @return      none
 */
typedef void  (*flash_lock_t)(unsigned int);
/**
 * @brief		this function serves to unlocks a specific region or address range in the flash memory.
 * @param[in]	none
 * @return      none
 */
typedef void  (*flash_unlock_t)(void);
/**
 * @brief		this function that retrieves the lock status of a specific region or address range in the flash memory.
 * @param[in]	none
 * @return      none
 */
typedef unsigned short  (*flash_get_lock_status_t)(void);
/**
 * @brief		this function as a callback function for flash protection operations.
 * @param[in]	none
 * @return      none
 */
typedef void  (*flash_prot_op_callback_t)(u8, u32, u32);
extern	flash_prot_op_callback_t 		flash_prot_op_cb;








/*
 * @brief flash operation event
 *    Here just list all type appeared in SDK sample, including APP initialization and OTA/SMP operating flash
 *    If you have more flash write or erase action for your application, should add more type and process them
 *
 */

/* application layer event, initialization, lock flash */
#define FLASH_OP_EVT_APP_INITIALIZATION					 			1



/*
 * @brief OTA operate Flash
 *
 * If using Telink OTA, 2 type of Flash operation must be processed as below:
 *     OTA operate Flash type 1: clear old firmware area(erase Flash), backup for storing new OTA data in future.
 *     OTA operate Flash type 2: write new firmware data(write Flash) for OTA ongoing
 *
 * If user design and implement OTA with proprietary mechanism, Please refer to Telink OTA.
 * 	   Sample code in BLE stack below, taking OTA writing new firmware for example:
 * 	 		   	  	if(flash_prot_op_cb){
 *						flash_prot_op_cb(FLASH_OP_EVT_STACK_OTA_WRITE_NEW_FW_BEGIN, address_start, address_end);
 *					}
 *
 * 	 		   	  	if(flash_prot_op_cb){
 *						flash_prot_op_cb(FLASH_OP_EVT_STACK_OTA_WRITE_NEW_FW_END, address_start, address_end);
 *					}
 */

/* stack layer event, OTA initialization, clear old firmware begin, may need unlock flash */
#define FLASH_OP_EVT_STACK_OTA_CLEAR_OLD_FW_BEGIN					10
/* stack layer event, OTA initialization, clear old firmware end , may need restore locking flash */
#define FLASH_OP_EVT_STACK_OTA_CLEAR_OLD_FW_END						11



/* stack layer event, OTA initialization, write new firmware begin, may need unlock flash */
#define FLASH_OP_EVT_STACK_OTA_WRITE_NEW_FW_BEGIN					12
/* stack layer event, OTA initialization, write new firmware begin, may need restore locking flash */
#define FLASH_OP_EVT_STACK_OTA_WRITE_NEW_FW_END						13





/**
 * @brief      this function is used to initialize flash protection.
 * @param[in]  none
 * @return     none
 */
void flash_protection_init(void);


/**
 * @brief      this function is used to register callback for stack, when OTA write or erase flash, send event to application layer
 * @param[in]  cb - flash protection operation callback function
 * @return     none
 */
void blc_appRegisterStackFlashOperationCallback(flash_prot_op_callback_t cb);

/**
 * @brief 		This function serves to set the protection of the flash.
 * @param[in]   flash_lock_cmd - flash lock block command for different flash type
 * 				e.g. for P25Q16SU, command is selected from "mid156085_lock_block_e"
 * @return 		none.
 */
void flash_lock(unsigned int flash_lock_cmd);

/**
 * @brief 		This function serves to release flash protection.
 * @param[in]   none.
 * @return 		none.
 */
void flash_unlock(void);

/**
 * @brief      this function is used to change application lock block definition to flash lock block definition according to flash type used
 * 			   attention: only processed a few lock block size for SDK demo, if you have more lock block size, please
 * 			              add more code by yourself
 * @param[in]  app_lock_block - application lock block definition
 * @return     flash_lock_block_size - The size of the lock block size of flash.
 */
u16 flash_change_app_lock_block_to_flash_lock_block(flash_app_lock_e app_lock_block);

#endif /* VENDOR_COMMON_FLASH_PROT_H_ */
