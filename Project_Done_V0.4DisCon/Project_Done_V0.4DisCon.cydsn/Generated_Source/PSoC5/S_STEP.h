/*******************************************************************************
* File Name: S_STEP.h  
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

#if !defined(CY_PINS_S_STEP_H) /* Pins S_STEP_H */
#define CY_PINS_S_STEP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "S_STEP_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 S_STEP__PORT == 15 && ((S_STEP__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    S_STEP_Write(uint8 value);
void    S_STEP_SetDriveMode(uint8 mode);
uint8   S_STEP_ReadDataReg(void);
uint8   S_STEP_Read(void);
void    S_STEP_SetInterruptMode(uint16 position, uint16 mode);
uint8   S_STEP_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the S_STEP_SetDriveMode() function.
     *  @{
     */
        #define S_STEP_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define S_STEP_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define S_STEP_DM_RES_UP          PIN_DM_RES_UP
        #define S_STEP_DM_RES_DWN         PIN_DM_RES_DWN
        #define S_STEP_DM_OD_LO           PIN_DM_OD_LO
        #define S_STEP_DM_OD_HI           PIN_DM_OD_HI
        #define S_STEP_DM_STRONG          PIN_DM_STRONG
        #define S_STEP_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define S_STEP_MASK               S_STEP__MASK
#define S_STEP_SHIFT              S_STEP__SHIFT
#define S_STEP_WIDTH              1u

/* Interrupt constants */
#if defined(S_STEP__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in S_STEP_SetInterruptMode() function.
     *  @{
     */
        #define S_STEP_INTR_NONE      (uint16)(0x0000u)
        #define S_STEP_INTR_RISING    (uint16)(0x0001u)
        #define S_STEP_INTR_FALLING   (uint16)(0x0002u)
        #define S_STEP_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define S_STEP_INTR_MASK      (0x01u) 
#endif /* (S_STEP__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define S_STEP_PS                     (* (reg8 *) S_STEP__PS)
/* Data Register */
#define S_STEP_DR                     (* (reg8 *) S_STEP__DR)
/* Port Number */
#define S_STEP_PRT_NUM                (* (reg8 *) S_STEP__PRT) 
/* Connect to Analog Globals */                                                  
#define S_STEP_AG                     (* (reg8 *) S_STEP__AG)                       
/* Analog MUX bux enable */
#define S_STEP_AMUX                   (* (reg8 *) S_STEP__AMUX) 
/* Bidirectional Enable */                                                        
#define S_STEP_BIE                    (* (reg8 *) S_STEP__BIE)
/* Bit-mask for Aliased Register Access */
#define S_STEP_BIT_MASK               (* (reg8 *) S_STEP__BIT_MASK)
/* Bypass Enable */
#define S_STEP_BYP                    (* (reg8 *) S_STEP__BYP)
/* Port wide control signals */                                                   
#define S_STEP_CTL                    (* (reg8 *) S_STEP__CTL)
/* Drive Modes */
#define S_STEP_DM0                    (* (reg8 *) S_STEP__DM0) 
#define S_STEP_DM1                    (* (reg8 *) S_STEP__DM1)
#define S_STEP_DM2                    (* (reg8 *) S_STEP__DM2) 
/* Input Buffer Disable Override */
#define S_STEP_INP_DIS                (* (reg8 *) S_STEP__INP_DIS)
/* LCD Common or Segment Drive */
#define S_STEP_LCD_COM_SEG            (* (reg8 *) S_STEP__LCD_COM_SEG)
/* Enable Segment LCD */
#define S_STEP_LCD_EN                 (* (reg8 *) S_STEP__LCD_EN)
/* Slew Rate Control */
#define S_STEP_SLW                    (* (reg8 *) S_STEP__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define S_STEP_PRTDSI__CAPS_SEL       (* (reg8 *) S_STEP__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define S_STEP_PRTDSI__DBL_SYNC_IN    (* (reg8 *) S_STEP__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define S_STEP_PRTDSI__OE_SEL0        (* (reg8 *) S_STEP__PRTDSI__OE_SEL0) 
#define S_STEP_PRTDSI__OE_SEL1        (* (reg8 *) S_STEP__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define S_STEP_PRTDSI__OUT_SEL0       (* (reg8 *) S_STEP__PRTDSI__OUT_SEL0) 
#define S_STEP_PRTDSI__OUT_SEL1       (* (reg8 *) S_STEP__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define S_STEP_PRTDSI__SYNC_OUT       (* (reg8 *) S_STEP__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(S_STEP__SIO_CFG)
    #define S_STEP_SIO_HYST_EN        (* (reg8 *) S_STEP__SIO_HYST_EN)
    #define S_STEP_SIO_REG_HIFREQ     (* (reg8 *) S_STEP__SIO_REG_HIFREQ)
    #define S_STEP_SIO_CFG            (* (reg8 *) S_STEP__SIO_CFG)
    #define S_STEP_SIO_DIFF           (* (reg8 *) S_STEP__SIO_DIFF)
#endif /* (S_STEP__SIO_CFG) */

/* Interrupt Registers */
#if defined(S_STEP__INTSTAT)
    #define S_STEP_INTSTAT            (* (reg8 *) S_STEP__INTSTAT)
    #define S_STEP_SNAP               (* (reg8 *) S_STEP__SNAP)
    
	#define S_STEP_0_INTTYPE_REG 		(* (reg8 *) S_STEP__0__INTTYPE)
#endif /* (S_STEP__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_S_STEP_H */


/* [] END OF FILE */
