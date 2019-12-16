/*******************************************************************************
* File Name: PWMout.h  
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

#if !defined(CY_PINS_PWMout_H) /* Pins PWMout_H */
#define CY_PINS_PWMout_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PWMout_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PWMout__PORT == 15 && ((PWMout__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PWMout_Write(uint8 value);
void    PWMout_SetDriveMode(uint8 mode);
uint8   PWMout_ReadDataReg(void);
uint8   PWMout_Read(void);
void    PWMout_SetInterruptMode(uint16 position, uint16 mode);
uint8   PWMout_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PWMout_SetDriveMode() function.
     *  @{
     */
        #define PWMout_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PWMout_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PWMout_DM_RES_UP          PIN_DM_RES_UP
        #define PWMout_DM_RES_DWN         PIN_DM_RES_DWN
        #define PWMout_DM_OD_LO           PIN_DM_OD_LO
        #define PWMout_DM_OD_HI           PIN_DM_OD_HI
        #define PWMout_DM_STRONG          PIN_DM_STRONG
        #define PWMout_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PWMout_MASK               PWMout__MASK
#define PWMout_SHIFT              PWMout__SHIFT
#define PWMout_WIDTH              1u

/* Interrupt constants */
#if defined(PWMout__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PWMout_SetInterruptMode() function.
     *  @{
     */
        #define PWMout_INTR_NONE      (uint16)(0x0000u)
        #define PWMout_INTR_RISING    (uint16)(0x0001u)
        #define PWMout_INTR_FALLING   (uint16)(0x0002u)
        #define PWMout_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PWMout_INTR_MASK      (0x01u) 
#endif /* (PWMout__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWMout_PS                     (* (reg8 *) PWMout__PS)
/* Data Register */
#define PWMout_DR                     (* (reg8 *) PWMout__DR)
/* Port Number */
#define PWMout_PRT_NUM                (* (reg8 *) PWMout__PRT) 
/* Connect to Analog Globals */                                                  
#define PWMout_AG                     (* (reg8 *) PWMout__AG)                       
/* Analog MUX bux enable */
#define PWMout_AMUX                   (* (reg8 *) PWMout__AMUX) 
/* Bidirectional Enable */                                                        
#define PWMout_BIE                    (* (reg8 *) PWMout__BIE)
/* Bit-mask for Aliased Register Access */
#define PWMout_BIT_MASK               (* (reg8 *) PWMout__BIT_MASK)
/* Bypass Enable */
#define PWMout_BYP                    (* (reg8 *) PWMout__BYP)
/* Port wide control signals */                                                   
#define PWMout_CTL                    (* (reg8 *) PWMout__CTL)
/* Drive Modes */
#define PWMout_DM0                    (* (reg8 *) PWMout__DM0) 
#define PWMout_DM1                    (* (reg8 *) PWMout__DM1)
#define PWMout_DM2                    (* (reg8 *) PWMout__DM2) 
/* Input Buffer Disable Override */
#define PWMout_INP_DIS                (* (reg8 *) PWMout__INP_DIS)
/* LCD Common or Segment Drive */
#define PWMout_LCD_COM_SEG            (* (reg8 *) PWMout__LCD_COM_SEG)
/* Enable Segment LCD */
#define PWMout_LCD_EN                 (* (reg8 *) PWMout__LCD_EN)
/* Slew Rate Control */
#define PWMout_SLW                    (* (reg8 *) PWMout__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PWMout_PRTDSI__CAPS_SEL       (* (reg8 *) PWMout__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PWMout_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PWMout__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PWMout_PRTDSI__OE_SEL0        (* (reg8 *) PWMout__PRTDSI__OE_SEL0) 
#define PWMout_PRTDSI__OE_SEL1        (* (reg8 *) PWMout__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PWMout_PRTDSI__OUT_SEL0       (* (reg8 *) PWMout__PRTDSI__OUT_SEL0) 
#define PWMout_PRTDSI__OUT_SEL1       (* (reg8 *) PWMout__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PWMout_PRTDSI__SYNC_OUT       (* (reg8 *) PWMout__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PWMout__SIO_CFG)
    #define PWMout_SIO_HYST_EN        (* (reg8 *) PWMout__SIO_HYST_EN)
    #define PWMout_SIO_REG_HIFREQ     (* (reg8 *) PWMout__SIO_REG_HIFREQ)
    #define PWMout_SIO_CFG            (* (reg8 *) PWMout__SIO_CFG)
    #define PWMout_SIO_DIFF           (* (reg8 *) PWMout__SIO_DIFF)
#endif /* (PWMout__SIO_CFG) */

/* Interrupt Registers */
#if defined(PWMout__INTSTAT)
    #define PWMout_INTSTAT            (* (reg8 *) PWMout__INTSTAT)
    #define PWMout_SNAP               (* (reg8 *) PWMout__SNAP)
    
	#define PWMout_0_INTTYPE_REG 		(* (reg8 *) PWMout__0__INTTYPE)
#endif /* (PWMout__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PWMout_H */


/* [] END OF FILE */
