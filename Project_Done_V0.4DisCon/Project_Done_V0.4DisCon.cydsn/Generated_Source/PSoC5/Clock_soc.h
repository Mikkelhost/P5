/*******************************************************************************
* File Name: Clock_soc.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Clock_soc_H)
#define CY_CLOCK_Clock_soc_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void Clock_soc_Start(void) ;
void Clock_soc_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Clock_soc_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Clock_soc_StandbyPower(uint8 state) ;
void Clock_soc_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Clock_soc_GetDividerRegister(void) ;
void Clock_soc_SetModeRegister(uint8 modeBitMask) ;
void Clock_soc_ClearModeRegister(uint8 modeBitMask) ;
uint8 Clock_soc_GetModeRegister(void) ;
void Clock_soc_SetSourceRegister(uint8 clkSource) ;
uint8 Clock_soc_GetSourceRegister(void) ;
#if defined(Clock_soc__CFG3)
void Clock_soc_SetPhaseRegister(uint8 clkPhase) ;
uint8 Clock_soc_GetPhaseRegister(void) ;
#endif /* defined(Clock_soc__CFG3) */

#define Clock_soc_Enable()                       Clock_soc_Start()
#define Clock_soc_Disable()                      Clock_soc_Stop()
#define Clock_soc_SetDivider(clkDivider)         Clock_soc_SetDividerRegister(clkDivider, 1u)
#define Clock_soc_SetDividerValue(clkDivider)    Clock_soc_SetDividerRegister((clkDivider) - 1u, 1u)
#define Clock_soc_SetMode(clkMode)               Clock_soc_SetModeRegister(clkMode)
#define Clock_soc_SetSource(clkSource)           Clock_soc_SetSourceRegister(clkSource)
#if defined(Clock_soc__CFG3)
#define Clock_soc_SetPhase(clkPhase)             Clock_soc_SetPhaseRegister(clkPhase)
#define Clock_soc_SetPhaseValue(clkPhase)        Clock_soc_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Clock_soc__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Clock_soc_CLKEN              (* (reg8 *) Clock_soc__PM_ACT_CFG)
#define Clock_soc_CLKEN_PTR          ((reg8 *) Clock_soc__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Clock_soc_CLKSTBY            (* (reg8 *) Clock_soc__PM_STBY_CFG)
#define Clock_soc_CLKSTBY_PTR        ((reg8 *) Clock_soc__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Clock_soc_DIV_LSB            (* (reg8 *) Clock_soc__CFG0)
#define Clock_soc_DIV_LSB_PTR        ((reg8 *) Clock_soc__CFG0)
#define Clock_soc_DIV_PTR            ((reg16 *) Clock_soc__CFG0)

/* Clock MSB divider configuration register. */
#define Clock_soc_DIV_MSB            (* (reg8 *) Clock_soc__CFG1)
#define Clock_soc_DIV_MSB_PTR        ((reg8 *) Clock_soc__CFG1)

/* Mode and source configuration register */
#define Clock_soc_MOD_SRC            (* (reg8 *) Clock_soc__CFG2)
#define Clock_soc_MOD_SRC_PTR        ((reg8 *) Clock_soc__CFG2)

#if defined(Clock_soc__CFG3)
/* Analog clock phase configuration register */
#define Clock_soc_PHASE              (* (reg8 *) Clock_soc__CFG3)
#define Clock_soc_PHASE_PTR          ((reg8 *) Clock_soc__CFG3)
#endif /* defined(Clock_soc__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Clock_soc_CLKEN_MASK         Clock_soc__PM_ACT_MSK
#define Clock_soc_CLKSTBY_MASK       Clock_soc__PM_STBY_MSK

/* CFG2 field masks */
#define Clock_soc_SRC_SEL_MSK        Clock_soc__CFG2_SRC_SEL_MASK
#define Clock_soc_MODE_MASK          (~(Clock_soc_SRC_SEL_MSK))

#if defined(Clock_soc__CFG3)
/* CFG3 phase mask */
#define Clock_soc_PHASE_MASK         Clock_soc__CFG3_PHASE_DLY_MASK
#endif /* defined(Clock_soc__CFG3) */

#endif /* CY_CLOCK_Clock_soc_H */


/* [] END OF FILE */
