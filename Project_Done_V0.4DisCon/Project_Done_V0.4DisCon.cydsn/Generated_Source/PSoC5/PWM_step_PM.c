/*******************************************************************************
* File Name: PWM_step_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_step.h"

static PWM_step_backupStruct PWM_step_backup;


/*******************************************************************************
* Function Name: PWM_step_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_step_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_step_SaveConfig(void) 
{

    #if(!PWM_step_UsingFixedFunction)
        #if(!PWM_step_PWMModeIsCenterAligned)
            PWM_step_backup.PWMPeriod = PWM_step_ReadPeriod();
        #endif /* (!PWM_step_PWMModeIsCenterAligned) */
        PWM_step_backup.PWMUdb = PWM_step_ReadCounter();
        #if (PWM_step_UseStatus)
            PWM_step_backup.InterruptMaskValue = PWM_step_STATUS_MASK;
        #endif /* (PWM_step_UseStatus) */

        #if(PWM_step_DeadBandMode == PWM_step__B_PWM__DBM_256_CLOCKS || \
            PWM_step_DeadBandMode == PWM_step__B_PWM__DBM_2_4_CLOCKS)
            PWM_step_backup.PWMdeadBandValue = PWM_step_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_step_KillModeMinTime)
             PWM_step_backup.PWMKillCounterPeriod = PWM_step_ReadKillTime();
        #endif /* (PWM_step_KillModeMinTime) */

        #if(PWM_step_UseControl)
            PWM_step_backup.PWMControlRegister = PWM_step_ReadControlRegister();
        #endif /* (PWM_step_UseControl) */
    #endif  /* (!PWM_step_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_step_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_step_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_step_RestoreConfig(void) 
{
        #if(!PWM_step_UsingFixedFunction)
            #if(!PWM_step_PWMModeIsCenterAligned)
                PWM_step_WritePeriod(PWM_step_backup.PWMPeriod);
            #endif /* (!PWM_step_PWMModeIsCenterAligned) */

            PWM_step_WriteCounter(PWM_step_backup.PWMUdb);

            #if (PWM_step_UseStatus)
                PWM_step_STATUS_MASK = PWM_step_backup.InterruptMaskValue;
            #endif /* (PWM_step_UseStatus) */

            #if(PWM_step_DeadBandMode == PWM_step__B_PWM__DBM_256_CLOCKS || \
                PWM_step_DeadBandMode == PWM_step__B_PWM__DBM_2_4_CLOCKS)
                PWM_step_WriteDeadTime(PWM_step_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_step_KillModeMinTime)
                PWM_step_WriteKillTime(PWM_step_backup.PWMKillCounterPeriod);
            #endif /* (PWM_step_KillModeMinTime) */

            #if(PWM_step_UseControl)
                PWM_step_WriteControlRegister(PWM_step_backup.PWMControlRegister);
            #endif /* (PWM_step_UseControl) */
        #endif  /* (!PWM_step_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_step_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_step_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_step_Sleep(void) 
{
    #if(PWM_step_UseControl)
        if(PWM_step_CTRL_ENABLE == (PWM_step_CONTROL & PWM_step_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_step_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_step_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_step_UseControl) */

    /* Stop component */
    PWM_step_Stop();

    /* Save registers configuration */
    PWM_step_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_step_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_step_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_step_Wakeup(void) 
{
     /* Restore registers values */
    PWM_step_RestoreConfig();

    if(PWM_step_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_step_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
