/*******************************************************************************
* File Name: PIN_SWITCH.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PIN_SWITCH_H) /* Pins PIN_SWITCH_H */
#define CY_PINS_PIN_SWITCH_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PIN_SWITCH_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PIN_SWITCH__PORT == 15 && ((PIN_SWITCH__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PIN_SWITCH_Write(uint8 value);
void    PIN_SWITCH_SetDriveMode(uint8 mode);
uint8   PIN_SWITCH_ReadDataReg(void);
uint8   PIN_SWITCH_Read(void);
void    PIN_SWITCH_SetInterruptMode(uint16 position, uint16 mode);
uint8   PIN_SWITCH_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PIN_SWITCH_SetDriveMode() function.
     *  @{
     */
        #define PIN_SWITCH_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PIN_SWITCH_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PIN_SWITCH_DM_RES_UP          PIN_DM_RES_UP
        #define PIN_SWITCH_DM_RES_DWN         PIN_DM_RES_DWN
        #define PIN_SWITCH_DM_OD_LO           PIN_DM_OD_LO
        #define PIN_SWITCH_DM_OD_HI           PIN_DM_OD_HI
        #define PIN_SWITCH_DM_STRONG          PIN_DM_STRONG
        #define PIN_SWITCH_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PIN_SWITCH_MASK               PIN_SWITCH__MASK
#define PIN_SWITCH_SHIFT              PIN_SWITCH__SHIFT
#define PIN_SWITCH_WIDTH              1u

/* Interrupt constants */
#if defined(PIN_SWITCH__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PIN_SWITCH_SetInterruptMode() function.
     *  @{
     */
        #define PIN_SWITCH_INTR_NONE      (uint16)(0x0000u)
        #define PIN_SWITCH_INTR_RISING    (uint16)(0x0001u)
        #define PIN_SWITCH_INTR_FALLING   (uint16)(0x0002u)
        #define PIN_SWITCH_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PIN_SWITCH_INTR_MASK      (0x01u) 
#endif /* (PIN_SWITCH__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PIN_SWITCH_PS                     (* (reg8 *) PIN_SWITCH__PS)
/* Data Register */
#define PIN_SWITCH_DR                     (* (reg8 *) PIN_SWITCH__DR)
/* Port Number */
#define PIN_SWITCH_PRT_NUM                (* (reg8 *) PIN_SWITCH__PRT) 
/* Connect to Analog Globals */                                                  
#define PIN_SWITCH_AG                     (* (reg8 *) PIN_SWITCH__AG)                       
/* Analog MUX bux enable */
#define PIN_SWITCH_AMUX                   (* (reg8 *) PIN_SWITCH__AMUX) 
/* Bidirectional Enable */                                                        
#define PIN_SWITCH_BIE                    (* (reg8 *) PIN_SWITCH__BIE)
/* Bit-mask for Aliased Register Access */
#define PIN_SWITCH_BIT_MASK               (* (reg8 *) PIN_SWITCH__BIT_MASK)
/* Bypass Enable */
#define PIN_SWITCH_BYP                    (* (reg8 *) PIN_SWITCH__BYP)
/* Port wide control signals */                                                   
#define PIN_SWITCH_CTL                    (* (reg8 *) PIN_SWITCH__CTL)
/* Drive Modes */
#define PIN_SWITCH_DM0                    (* (reg8 *) PIN_SWITCH__DM0) 
#define PIN_SWITCH_DM1                    (* (reg8 *) PIN_SWITCH__DM1)
#define PIN_SWITCH_DM2                    (* (reg8 *) PIN_SWITCH__DM2) 
/* Input Buffer Disable Override */
#define PIN_SWITCH_INP_DIS                (* (reg8 *) PIN_SWITCH__INP_DIS)
/* LCD Common or Segment Drive */
#define PIN_SWITCH_LCD_COM_SEG            (* (reg8 *) PIN_SWITCH__LCD_COM_SEG)
/* Enable Segment LCD */
#define PIN_SWITCH_LCD_EN                 (* (reg8 *) PIN_SWITCH__LCD_EN)
/* Slew Rate Control */
#define PIN_SWITCH_SLW                    (* (reg8 *) PIN_SWITCH__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PIN_SWITCH_PRTDSI__CAPS_SEL       (* (reg8 *) PIN_SWITCH__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PIN_SWITCH_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PIN_SWITCH__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PIN_SWITCH_PRTDSI__OE_SEL0        (* (reg8 *) PIN_SWITCH__PRTDSI__OE_SEL0) 
#define PIN_SWITCH_PRTDSI__OE_SEL1        (* (reg8 *) PIN_SWITCH__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PIN_SWITCH_PRTDSI__OUT_SEL0       (* (reg8 *) PIN_SWITCH__PRTDSI__OUT_SEL0) 
#define PIN_SWITCH_PRTDSI__OUT_SEL1       (* (reg8 *) PIN_SWITCH__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PIN_SWITCH_PRTDSI__SYNC_OUT       (* (reg8 *) PIN_SWITCH__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PIN_SWITCH__SIO_CFG)
    #define PIN_SWITCH_SIO_HYST_EN        (* (reg8 *) PIN_SWITCH__SIO_HYST_EN)
    #define PIN_SWITCH_SIO_REG_HIFREQ     (* (reg8 *) PIN_SWITCH__SIO_REG_HIFREQ)
    #define PIN_SWITCH_SIO_CFG            (* (reg8 *) PIN_SWITCH__SIO_CFG)
    #define PIN_SWITCH_SIO_DIFF           (* (reg8 *) PIN_SWITCH__SIO_DIFF)
#endif /* (PIN_SWITCH__SIO_CFG) */

/* Interrupt Registers */
#if defined(PIN_SWITCH__INTSTAT)
    #define PIN_SWITCH_INTSTAT            (* (reg8 *) PIN_SWITCH__INTSTAT)
    #define PIN_SWITCH_SNAP               (* (reg8 *) PIN_SWITCH__SNAP)
    
	#define PIN_SWITCH_0_INTTYPE_REG 		(* (reg8 *) PIN_SWITCH__0__INTTYPE)
#endif /* (PIN_SWITCH__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PIN_SWITCH_H */


/* [] END OF FILE */
