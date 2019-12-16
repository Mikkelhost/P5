/*******************************************************************************
* File Name: PWM_step.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_PWM_step_H)
#define CY_PWM_PWM_step_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 PWM_step_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define PWM_step_Resolution                     (16u)
#define PWM_step_UsingFixedFunction             (0u)
#define PWM_step_DeadBandMode                   (0u)
#define PWM_step_KillModeMinTime                (0u)
#define PWM_step_KillMode                       (0u)
#define PWM_step_PWMMode                        (0u)
#define PWM_step_PWMModeIsCenterAligned         (0u)
#define PWM_step_DeadBandUsed                   (0u)
#define PWM_step_DeadBand2_4                    (0u)

#if !defined(PWM_step_PWMUDB_genblk8_stsreg__REMOVED)
    #define PWM_step_UseStatus                  (1u)
#else
    #define PWM_step_UseStatus                  (0u)
#endif /* !defined(PWM_step_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(PWM_step_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define PWM_step_UseControl                 (1u)
#else
    #define PWM_step_UseControl                 (0u)
#endif /* !defined(PWM_step_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define PWM_step_UseOneCompareMode              (1u)
#define PWM_step_MinimumKillTime                (1u)
#define PWM_step_EnableMode                     (0u)

#define PWM_step_CompareMode1SW                 (0u)
#define PWM_step_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define PWM_step__B_PWM__DISABLED 0
#define PWM_step__B_PWM__ASYNCHRONOUS 1
#define PWM_step__B_PWM__SINGLECYCLE 2
#define PWM_step__B_PWM__LATCHED 3
#define PWM_step__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define PWM_step__B_PWM__DBMDISABLED 0
#define PWM_step__B_PWM__DBM_2_4_CLOCKS 1
#define PWM_step__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define PWM_step__B_PWM__ONE_OUTPUT 0
#define PWM_step__B_PWM__TWO_OUTPUTS 1
#define PWM_step__B_PWM__DUAL_EDGE 2
#define PWM_step__B_PWM__CENTER_ALIGN 3
#define PWM_step__B_PWM__DITHER 5
#define PWM_step__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define PWM_step__B_PWM__LESS_THAN 1
#define PWM_step__B_PWM__LESS_THAN_OR_EQUAL 2
#define PWM_step__B_PWM__GREATER_THAN 3
#define PWM_step__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define PWM_step__B_PWM__EQUAL 0
#define PWM_step__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!PWM_step_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!PWM_step_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!PWM_step_PWMModeIsCenterAligned) */
        #if (PWM_step_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (PWM_step_UseStatus) */

        /* Backup for Deadband parameters */
        #if(PWM_step_DeadBandMode == PWM_step__B_PWM__DBM_256_CLOCKS || \
            PWM_step_DeadBandMode == PWM_step__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(PWM_step_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (PWM_step_KillModeMinTime) */

        /* Backup control register */
        #if(PWM_step_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (PWM_step_UseControl) */

    #endif /* (!PWM_step_UsingFixedFunction) */

}PWM_step_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    PWM_step_Start(void) ;
void    PWM_step_Stop(void) ;

#if (PWM_step_UseStatus || PWM_step_UsingFixedFunction)
    void  PWM_step_SetInterruptMode(uint8 interruptMode) ;
    uint8 PWM_step_ReadStatusRegister(void) ;
#endif /* (PWM_step_UseStatus || PWM_step_UsingFixedFunction) */

#define PWM_step_GetInterruptSource() PWM_step_ReadStatusRegister()

#if (PWM_step_UseControl)
    uint8 PWM_step_ReadControlRegister(void) ;
    void  PWM_step_WriteControlRegister(uint8 control)
          ;
#endif /* (PWM_step_UseControl) */

#if (PWM_step_UseOneCompareMode)
   #if (PWM_step_CompareMode1SW)
       void    PWM_step_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (PWM_step_CompareMode1SW) */
#else
    #if (PWM_step_CompareMode1SW)
        void    PWM_step_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (PWM_step_CompareMode1SW) */
    #if (PWM_step_CompareMode2SW)
        void    PWM_step_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (PWM_step_CompareMode2SW) */
#endif /* (PWM_step_UseOneCompareMode) */

#if (!PWM_step_UsingFixedFunction)
    uint16   PWM_step_ReadCounter(void) ;
    uint16 PWM_step_ReadCapture(void) ;

    #if (PWM_step_UseStatus)
            void PWM_step_ClearFIFO(void) ;
    #endif /* (PWM_step_UseStatus) */

    void    PWM_step_WriteCounter(uint16 counter)
            ;
#endif /* (!PWM_step_UsingFixedFunction) */

void    PWM_step_WritePeriod(uint16 period)
        ;
uint16 PWM_step_ReadPeriod(void) ;

#if (PWM_step_UseOneCompareMode)
    void    PWM_step_WriteCompare(uint16 compare)
            ;
    uint16 PWM_step_ReadCompare(void) ;
#else
    void    PWM_step_WriteCompare1(uint16 compare)
            ;
    uint16 PWM_step_ReadCompare1(void) ;
    void    PWM_step_WriteCompare2(uint16 compare)
            ;
    uint16 PWM_step_ReadCompare2(void) ;
#endif /* (PWM_step_UseOneCompareMode) */


#if (PWM_step_DeadBandUsed)
    void    PWM_step_WriteDeadTime(uint8 deadtime) ;
    uint8   PWM_step_ReadDeadTime(void) ;
#endif /* (PWM_step_DeadBandUsed) */

#if ( PWM_step_KillModeMinTime)
    void PWM_step_WriteKillTime(uint8 killtime) ;
    uint8 PWM_step_ReadKillTime(void) ;
#endif /* ( PWM_step_KillModeMinTime) */

void PWM_step_Init(void) ;
void PWM_step_Enable(void) ;
void PWM_step_Sleep(void) ;
void PWM_step_Wakeup(void) ;
void PWM_step_SaveConfig(void) ;
void PWM_step_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define PWM_step_INIT_PERIOD_VALUE          (100u)
#define PWM_step_INIT_COMPARE_VALUE1        (0u)
#define PWM_step_INIT_COMPARE_VALUE2        (63u)
#define PWM_step_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    PWM_step_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PWM_step_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PWM_step_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PWM_step_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define PWM_step_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  PWM_step_CTRL_CMPMODE2_SHIFT)
#define PWM_step_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  PWM_step_CTRL_CMPMODE1_SHIFT)
#define PWM_step_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (PWM_step_UsingFixedFunction)
   #define PWM_step_PERIOD_LSB              (*(reg16 *) PWM_step_PWMHW__PER0)
   #define PWM_step_PERIOD_LSB_PTR          ( (reg16 *) PWM_step_PWMHW__PER0)
   #define PWM_step_COMPARE1_LSB            (*(reg16 *) PWM_step_PWMHW__CNT_CMP0)
   #define PWM_step_COMPARE1_LSB_PTR        ( (reg16 *) PWM_step_PWMHW__CNT_CMP0)
   #define PWM_step_COMPARE2_LSB            (0x00u)
   #define PWM_step_COMPARE2_LSB_PTR        (0x00u)
   #define PWM_step_COUNTER_LSB             (*(reg16 *) PWM_step_PWMHW__CNT_CMP0)
   #define PWM_step_COUNTER_LSB_PTR         ( (reg16 *) PWM_step_PWMHW__CNT_CMP0)
   #define PWM_step_CAPTURE_LSB             (*(reg16 *) PWM_step_PWMHW__CAP0)
   #define PWM_step_CAPTURE_LSB_PTR         ( (reg16 *) PWM_step_PWMHW__CAP0)
   #define PWM_step_RT1                     (*(reg8 *)  PWM_step_PWMHW__RT1)
   #define PWM_step_RT1_PTR                 ( (reg8 *)  PWM_step_PWMHW__RT1)

#else
   #if (PWM_step_Resolution == 8u) /* 8bit - PWM */

       #if(PWM_step_PWMModeIsCenterAligned)
           #define PWM_step_PERIOD_LSB      (*(reg8 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define PWM_step_PERIOD_LSB_PTR  ((reg8 *)   PWM_step_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define PWM_step_PERIOD_LSB      (*(reg8 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define PWM_step_PERIOD_LSB_PTR  ((reg8 *)   PWM_step_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (PWM_step_PWMModeIsCenterAligned) */

       #define PWM_step_COMPARE1_LSB        (*(reg8 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define PWM_step_COMPARE1_LSB_PTR    ((reg8 *)   PWM_step_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define PWM_step_COMPARE2_LSB        (*(reg8 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define PWM_step_COMPARE2_LSB_PTR    ((reg8 *)   PWM_step_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define PWM_step_COUNTERCAP_LSB      (*(reg8 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define PWM_step_COUNTERCAP_LSB_PTR  ((reg8 *)   PWM_step_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define PWM_step_COUNTER_LSB         (*(reg8 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define PWM_step_COUNTER_LSB_PTR     ((reg8 *)   PWM_step_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define PWM_step_CAPTURE_LSB         (*(reg8 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define PWM_step_CAPTURE_LSB_PTR     ((reg8 *)   PWM_step_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(PWM_step_PWMModeIsCenterAligned)
               #define PWM_step_PERIOD_LSB      (*(reg16 *) PWM_step_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define PWM_step_PERIOD_LSB_PTR  ((reg16 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define PWM_step_PERIOD_LSB      (*(reg16 *) PWM_step_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define PWM_step_PERIOD_LSB_PTR  ((reg16 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (PWM_step_PWMModeIsCenterAligned) */

            #define PWM_step_COMPARE1_LSB       (*(reg16 *) PWM_step_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define PWM_step_COMPARE1_LSB_PTR   ((reg16 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define PWM_step_COMPARE2_LSB       (*(reg16 *) PWM_step_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define PWM_step_COMPARE2_LSB_PTR   ((reg16 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define PWM_step_COUNTERCAP_LSB     (*(reg16 *) PWM_step_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define PWM_step_COUNTERCAP_LSB_PTR ((reg16 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define PWM_step_COUNTER_LSB        (*(reg16 *) PWM_step_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define PWM_step_COUNTER_LSB_PTR    ((reg16 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define PWM_step_CAPTURE_LSB        (*(reg16 *) PWM_step_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define PWM_step_CAPTURE_LSB_PTR    ((reg16 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(PWM_step_PWMModeIsCenterAligned)
               #define PWM_step_PERIOD_LSB      (*(reg16 *) PWM_step_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define PWM_step_PERIOD_LSB_PTR  ((reg16 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define PWM_step_PERIOD_LSB      (*(reg16 *) PWM_step_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define PWM_step_PERIOD_LSB_PTR  ((reg16 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (PWM_step_PWMModeIsCenterAligned) */

            #define PWM_step_COMPARE1_LSB       (*(reg16 *) PWM_step_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define PWM_step_COMPARE1_LSB_PTR   ((reg16 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define PWM_step_COMPARE2_LSB       (*(reg16 *) PWM_step_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define PWM_step_COMPARE2_LSB_PTR   ((reg16 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define PWM_step_COUNTERCAP_LSB     (*(reg16 *) PWM_step_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define PWM_step_COUNTERCAP_LSB_PTR ((reg16 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define PWM_step_COUNTER_LSB        (*(reg16 *) PWM_step_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define PWM_step_COUNTER_LSB_PTR    ((reg16 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define PWM_step_CAPTURE_LSB        (*(reg16 *) PWM_step_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define PWM_step_CAPTURE_LSB_PTR    ((reg16 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define PWM_step_AUX_CONTROLDP1          (*(reg8 *)  PWM_step_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define PWM_step_AUX_CONTROLDP1_PTR      ((reg8 *)   PWM_step_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (PWM_step_Resolution == 8) */

   #define PWM_step_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define PWM_step_AUX_CONTROLDP0          (*(reg8 *)  PWM_step_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define PWM_step_AUX_CONTROLDP0_PTR      ((reg8 *)   PWM_step_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (PWM_step_UsingFixedFunction) */

#if(PWM_step_KillModeMinTime )
    #define PWM_step_KILLMODEMINTIME        (*(reg8 *)  PWM_step_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define PWM_step_KILLMODEMINTIME_PTR    ((reg8 *)   PWM_step_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (PWM_step_KillModeMinTime ) */

#if(PWM_step_DeadBandMode == PWM_step__B_PWM__DBM_256_CLOCKS)
    #define PWM_step_DEADBAND_COUNT         (*(reg8 *)  PWM_step_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWM_step_DEADBAND_COUNT_PTR     ((reg8 *)   PWM_step_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWM_step_DEADBAND_LSB_PTR       ((reg8 *)   PWM_step_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define PWM_step_DEADBAND_LSB           (*(reg8 *)  PWM_step_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(PWM_step_DeadBandMode == PWM_step__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (PWM_step_UsingFixedFunction)
        #define PWM_step_DEADBAND_COUNT         (*(reg8 *)  PWM_step_PWMHW__CFG0)
        #define PWM_step_DEADBAND_COUNT_PTR     ((reg8 *)   PWM_step_PWMHW__CFG0)
        #define PWM_step_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWM_step_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define PWM_step_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define PWM_step_DEADBAND_COUNT         (*(reg8 *)  PWM_step_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PWM_step_DEADBAND_COUNT_PTR     ((reg8 *)   PWM_step_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PWM_step_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWM_step_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define PWM_step_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (PWM_step_UsingFixedFunction) */
#endif /* (PWM_step_DeadBandMode == PWM_step__B_PWM__DBM_256_CLOCKS) */



#if (PWM_step_UsingFixedFunction)
    #define PWM_step_STATUS                 (*(reg8 *) PWM_step_PWMHW__SR0)
    #define PWM_step_STATUS_PTR             ((reg8 *) PWM_step_PWMHW__SR0)
    #define PWM_step_STATUS_MASK            (*(reg8 *) PWM_step_PWMHW__SR0)
    #define PWM_step_STATUS_MASK_PTR        ((reg8 *) PWM_step_PWMHW__SR0)
    #define PWM_step_CONTROL                (*(reg8 *) PWM_step_PWMHW__CFG0)
    #define PWM_step_CONTROL_PTR            ((reg8 *) PWM_step_PWMHW__CFG0)
    #define PWM_step_CONTROL2               (*(reg8 *) PWM_step_PWMHW__CFG1)
    #define PWM_step_CONTROL3               (*(reg8 *) PWM_step_PWMHW__CFG2)
    #define PWM_step_GLOBAL_ENABLE          (*(reg8 *) PWM_step_PWMHW__PM_ACT_CFG)
    #define PWM_step_GLOBAL_ENABLE_PTR      ( (reg8 *) PWM_step_PWMHW__PM_ACT_CFG)
    #define PWM_step_GLOBAL_STBY_ENABLE     (*(reg8 *) PWM_step_PWMHW__PM_STBY_CFG)
    #define PWM_step_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) PWM_step_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define PWM_step_BLOCK_EN_MASK          (PWM_step_PWMHW__PM_ACT_MSK)
    #define PWM_step_BLOCK_STBY_EN_MASK     (PWM_step_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define PWM_step_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define PWM_step_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define PWM_step_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define PWM_step_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define PWM_step_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define PWM_step_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define PWM_step_CTRL_ENABLE            (uint8)((uint8)0x01u << PWM_step_CTRL_ENABLE_SHIFT)
    #define PWM_step_CTRL_RESET             (uint8)((uint8)0x01u << PWM_step_CTRL_RESET_SHIFT)
    #define PWM_step_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWM_step_CTRL_CMPMODE2_SHIFT)
    #define PWM_step_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWM_step_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define PWM_step_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define PWM_step_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << PWM_step_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define PWM_step_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define PWM_step_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define PWM_step_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define PWM_step_STATUS_TC_INT_EN_MASK_SHIFT            (PWM_step_STATUS_TC_SHIFT - 4u)
    #define PWM_step_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define PWM_step_STATUS_CMP1_INT_EN_MASK_SHIFT          (PWM_step_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define PWM_step_STATUS_TC              (uint8)((uint8)0x01u << PWM_step_STATUS_TC_SHIFT)
    #define PWM_step_STATUS_CMP1            (uint8)((uint8)0x01u << PWM_step_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define PWM_step_STATUS_TC_INT_EN_MASK              (uint8)((uint8)PWM_step_STATUS_TC >> 4u)
    #define PWM_step_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)PWM_step_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define PWM_step_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define PWM_step_RT1_MASK              (uint8)((uint8)0x03u << PWM_step_RT1_SHIFT)
    #define PWM_step_SYNC                  (uint8)((uint8)0x03u << PWM_step_RT1_SHIFT)
    #define PWM_step_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define PWM_step_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << PWM_step_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define PWM_step_SYNCDSI_EN            (uint8)((uint8)0x0Fu << PWM_step_SYNCDSI_SHIFT)


#else
    #define PWM_step_STATUS                (*(reg8 *)   PWM_step_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PWM_step_STATUS_PTR            ((reg8 *)    PWM_step_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PWM_step_STATUS_MASK           (*(reg8 *)   PWM_step_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PWM_step_STATUS_MASK_PTR       ((reg8 *)    PWM_step_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PWM_step_STATUS_AUX_CTRL       (*(reg8 *)   PWM_step_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define PWM_step_CONTROL               (*(reg8 *)   PWM_step_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define PWM_step_CONTROL_PTR           ((reg8 *)    PWM_step_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define PWM_step_CTRL_ENABLE_SHIFT      (0x07u)
    #define PWM_step_CTRL_RESET_SHIFT       (0x06u)
    #define PWM_step_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define PWM_step_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define PWM_step_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define PWM_step_CTRL_ENABLE            (uint8)((uint8)0x01u << PWM_step_CTRL_ENABLE_SHIFT)
    #define PWM_step_CTRL_RESET             (uint8)((uint8)0x01u << PWM_step_CTRL_RESET_SHIFT)
    #define PWM_step_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWM_step_CTRL_CMPMODE2_SHIFT)
    #define PWM_step_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWM_step_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define PWM_step_STATUS_KILL_SHIFT          (0x05u)
    #define PWM_step_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define PWM_step_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define PWM_step_STATUS_TC_SHIFT            (0x02u)
    #define PWM_step_STATUS_CMP2_SHIFT          (0x01u)
    #define PWM_step_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define PWM_step_STATUS_KILL_INT_EN_MASK_SHIFT          (PWM_step_STATUS_KILL_SHIFT)
    #define PWM_step_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (PWM_step_STATUS_FIFONEMPTY_SHIFT)
    #define PWM_step_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (PWM_step_STATUS_FIFOFULL_SHIFT)
    #define PWM_step_STATUS_TC_INT_EN_MASK_SHIFT            (PWM_step_STATUS_TC_SHIFT)
    #define PWM_step_STATUS_CMP2_INT_EN_MASK_SHIFT          (PWM_step_STATUS_CMP2_SHIFT)
    #define PWM_step_STATUS_CMP1_INT_EN_MASK_SHIFT          (PWM_step_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define PWM_step_STATUS_KILL            (uint8)((uint8)0x00u << PWM_step_STATUS_KILL_SHIFT )
    #define PWM_step_STATUS_FIFOFULL        (uint8)((uint8)0x01u << PWM_step_STATUS_FIFOFULL_SHIFT)
    #define PWM_step_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << PWM_step_STATUS_FIFONEMPTY_SHIFT)
    #define PWM_step_STATUS_TC              (uint8)((uint8)0x01u << PWM_step_STATUS_TC_SHIFT)
    #define PWM_step_STATUS_CMP2            (uint8)((uint8)0x01u << PWM_step_STATUS_CMP2_SHIFT)
    #define PWM_step_STATUS_CMP1            (uint8)((uint8)0x01u << PWM_step_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define PWM_step_STATUS_KILL_INT_EN_MASK            (PWM_step_STATUS_KILL)
    #define PWM_step_STATUS_FIFOFULL_INT_EN_MASK        (PWM_step_STATUS_FIFOFULL)
    #define PWM_step_STATUS_FIFONEMPTY_INT_EN_MASK      (PWM_step_STATUS_FIFONEMPTY)
    #define PWM_step_STATUS_TC_INT_EN_MASK              (PWM_step_STATUS_TC)
    #define PWM_step_STATUS_CMP2_INT_EN_MASK            (PWM_step_STATUS_CMP2)
    #define PWM_step_STATUS_CMP1_INT_EN_MASK            (PWM_step_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define PWM_step_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define PWM_step_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define PWM_step_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define PWM_step_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define PWM_step_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* PWM_step_UsingFixedFunction */

#endif  /* CY_PWM_PWM_step_H */


/* [] END OF FILE */
