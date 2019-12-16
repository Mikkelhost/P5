/* This project is made by EIT group 513 at Aalborg university */

#include <project.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*define for the number of samples to be transferred to memory on each switch press*/
#define NO_OF_SAMPLES 128

int k = 16; //K = 261 for N = 1024 & f = 200 kHz, K = 131 for N = 1024 & f = 100 kHz
            //K = 16, for N = 128 & f = 100 kHz
  /* Lovely pi */
float pi = 3.1416;
float half_pi = 1.571;


/* Values for the motors*/
   float prev_1_AOA_Az = 0;
   float prev_2_AOA_Az = 0;
   float prev_1_DC_speed = 0;
   float prev_2_DC_speed = 0;


  float Step_integral = 0;
  float Step_derivative  = 0;
  float prev_AoA_El = 0;

/* Arrays for saving samples*/
uint16 adc_sampleArray_1[NO_OF_SAMPLES] = {0};
uint16 adc_sampleArray_2[NO_OF_SAMPLES] = {0};

/*Array for pre calculation */
float Cos_sampleArray[NO_OF_SAMPLES] = {0};
float Sin_sampleArray[NO_OF_SAMPLES] = {0};

/* These variables are used to indicate if Pin_Switch is pressed or DMADone_flag is pressed */
volatile uint8 switch_flag;
volatile uint8 DMADone_1_flag;
volatile uint8 DMADone_2_flag;

 /* Statemachine */
int state = 0; //0 = Initalize, 1, search, 2 = PinPointAoA

/* Threshhold for detecting a signal in seach */
float AmpThreshold = 7000; //Skal nok lave en test for at finde en god værdi

/* Variable declarations for DMA . 
* These variables are defined as global variables to avoid "may be used before being set" warning 
* issued by the PSoC 5 compilers  MDK/RVDS.In this case these variables are automatically initialized to zero */

/* DMA_Chan is used to store the DMA channel handle */ 
uint8 DMA_1_Chan;
uint8 DMA_2_Chan;

/* DMA_TD array is used to store all of the TDs associated with the channel
 * Since there is only one TD in this example, DMA_TD array contains only one element */
uint8 DMA_1_TD[1];
uint8 DMA_2_TD[1];

/* DMA_DISABLE_TD definition not available for PSoC 5LP inside CyDmac.h in PSoC Creator 2.1 SP1.
 * So, manually define the DMA_DISABLE_TD */
#if (CY_PSOC5LP)
	#if !defined(DMA_DISABLE_TD)
	    #define DMA_DISABLE_TD          0xFEu
	#endif
#endif  /* (CY_PSOC5LP) */



                                    /* FUNCTIONS */
float PhaseDifference(uint16 a[], uint16 b[])
{
  //Value to be returned by the function
  float c;


  float theta_a = 0, theta_b = 0;


// Frequency spectrum variables
  float Are = {0};
  float Aim = {0};
  float Bre = {0};
  float Bim = {0};

 //float test_az[NO_OF_SAMPLES] = {0}, test_bz[NO_OF_SAMPLES] = {0};


 // Calculate DFT of x using brute force

    for(int n=0; n<NO_OF_SAMPLES; n++)
    {  
        Are = Are + a[n]*Cos_sampleArray[n];
        Aim = Aim + a[n]*Sin_sampleArray[n]; 
        Bre = Bre + b[n]*Cos_sampleArray[n];
        Bim = Bim + b[n]*Sin_sampleArray[n];
    }

    theta_a = atanf(Aim/Are);
    theta_b = atanf(Bim/Bre);
    
    //Compensating for tangens errors 
    if((Aim < 0) && (Are < 0 ))  
    {
        theta_a = theta_a - pi;
    } else if (Are < 0 )
    {
        theta_a = theta_a + pi;   
    }
    
    if((Bim < 0) && (Bre < 0 ))
    {
        theta_b = theta_b - pi;
    } else if (Bre < 0 )
    {
        theta_b = theta_b + pi;   
    }
    
 
    c = theta_a - theta_b ; //Calculate the phase difference
    
    if ( c < -(pi))  //Phase wrapping, fixes overflow of the phase
    {
        c = c + (2*pi);
    } else if (c > (pi))
    {
        c = c - (2*pi);
    }
    c = -c;
    
    
    return c;   
}


float PhaseDifferenceEL(uint16 a[], uint16 b[]) //A seperate function the for elevation do to a 180 degree phaseshift in the signals
{
  //Value to be returned by the function
  float c;


  float theta_a = 0, theta_b = 0;


// Frequency spectrum variables
  float Are = {0};
  float Aim = {0};
  float Bre = {0};
  float Bim = {0};

 // Calculate DFT of x using brute force
    for(int n=0; n<NO_OF_SAMPLES; n++)
    {  
        Are = Are + a[n]*Cos_sampleArray[n];
        Aim = Aim + a[n]*Sin_sampleArray[n]; 
        Bre = Bre + b[n]*Cos_sampleArray[n];
        Bim = Bim + b[n]*Sin_sampleArray[n];
    }

    theta_a = atanf(Aim/Are);
    theta_b = atanf(Bim/Bre)-pi;
    
    //Compensating for tangens errors 
    if((Aim < 0) && (Are < 0 ))  
    {
        theta_a = theta_a - pi;
    } else if (Are < 0 )
    {
        theta_a = theta_a + pi;   
    }
    
    if((Bim < 0) && (Bre < 0 ))
    {
        theta_b = theta_b - pi;
    } else if (Bre < 0 )
    {
        theta_b = theta_b + pi;   
    }
    
 
    c = theta_a - theta_b - 1.571; //Calculate the phase difference
    
    if ( c < -(pi))  //Phase wrapping, fixes overflow of the phase
    {
        c = c + (2*pi);
    } else if (c > (pi))
    {
        c = c - (2*pi);
    }
    c = -c;
    
    
    return c;   
}

float AmplitudeDFT(uint16 a[]) //Only listens on one of the antennas which is faster.
{
 //Value to be returned
  float amp;
    
    
    // Frequency spectrum variables
  float Are = {0};
  float Aim = {0};


 // Calculate DFT of x using brute force

    for(int n=0; n<NO_OF_SAMPLES; n++)
    {  
        Are = Are + a[n]*Cos_sampleArray[n];
        Aim = Aim + a[n]*Sin_sampleArray[n]; 
    }
    
    amp = sqrt(Are*Are + Aim*Aim);
    
    return amp;
}


void DMA_getSample(void) 
{
    /* Enable the DMA channel */
	CyDmaChEnable(DMA_1_Chan, 1);
    CyDmaChEnable(DMA_2_Chan, 1);
}


void MotorSetup(void) 
{
//DC Motor
    PWM_Start();
    H_ENA_Write(1); //INA = 1 & INA = 1: Brake to VDD
    H_ENB_Write(1); //INA = 1 & INA = 0: Clockwise (CW)
    H_INA_Write(1); //INA = 0 & INA = 1: Counterclockwise (CCW)
    H_INB_Write(0); //INA = 0 & INA = 0: Brake to GND
   
// STEPPER
    S_EN_Write(1);
    S_DIR_Write(1);
    PWM_step_Start();
}

void DCMotorControl(int DC_dir, int DC_Speed)
{
 if (DC_Speed > 0) {
     H_INA_Write(DC_dir); //DC_dir = 1: Clockwise
     H_INB_Write(!DC_dir);
} else { //Brake to GND
     H_INA_Write(0);
     H_INB_Write(0);
}

PWM_WriteCompare(DC_Speed); // 0 - 1000. 
}


void StepperMotorControl(int Step_dir, int Step_Speed)
{
    //Step_dir: 0 = DOWN (Clockwise), 1 = UP (CounterClockwise)    
    
    if(Step_Speed > 60000)
    {
      PWM_step_WriteCompare(0); //Stops the steppermotor if the speed is lower than a certain threshold.
    } else 
    {
      PWM_step_WriteCompare((int)(Step_Speed/2));
    }
    
    S_DIR_Write(Step_dir);
    PWM_step_WritePeriod(Step_Speed);  
}


void Setup(void) 
{
    /* Start ADC */
	ADC_SAR_1_Start();
    ADC_SAR_2_Start();
    
    /* Disable the ADC ISR as it is not required */
    ADC_SAR_1_IRQ_Disable();
    ADC_SAR_2_IRQ_Disable();

	/* Start ADC conversion */
	//ADC_SAR_1_StartConvert();
    //ADC_SAR_2_StartConvert();
    
    /*Start UART */
    UART_1_Start();
    
    // MUX Start
    AMux_1_Start();   // Use AMUX_1_Fastselec(xxx); to change mux. 
    
    // motor setup
    MotorSetup();
    
    /* Pre calculate different values */ 
    for (int n = 0; n < NO_OF_SAMPLES; n++)
    {
        int N = NO_OF_SAMPLES;
        Cos_sampleArray[n] = cosf(n*2*pi*k/N);
        Sin_sampleArray[n] = sinf(n*2*pi*k/N);      
    }
}


void search(void)
{
  int DC_motor_speed = 400;
  int DC_dir = 1; //1 = Clockwise, 0 = CounterClockwise
  int TakingSampleAz = 1; //Uses as a delay
  float Amp = 0;
  int STEP_dir = 1;
  int STEP_speed = 65535; //Stops the stepper motor.  
      
  DCMotorControl(DC_dir, DC_motor_speed);
 StepperMotorControl(STEP_dir, STEP_speed); 

  // Azimuth
  AMux_1_FastSelect(0);  //1 = PIN_ADC_IN_AZ
  DMA_getSample();
  while(TakingSampleAz == 1){ //Waiting until a sample is ready from the DMA
      if(DMADone_1_flag && DMADone_2_flag )
      {	      
        TakingSampleAz = 0;
    	DMADone_1_flag = 0; 
        DMADone_2_flag = 0;	
      }
  }

  Amp = AmplitudeDFT(adc_sampleArray_1);
  if (Amp > AmpThreshold){ 
 //Resets values until the next time a signal has been found
    prev_1_AOA_Az = 0;
    prev_2_AOA_Az = 0;
    prev_1_DC_speed = 0;
    prev_2_DC_speed = 0;
    state = 2;
  }     
}


void PinPointAoA(void)
{
  int TakingSampleAz = 1, TakingSampleEl = 1; //Uses as a delay
  float theta_Az = 0, theta_El = 0;
  float AoA_Az = 0, AoA_El = 0;
  float Amp = 0;
  int NO_OF_MEAN = 1;
    
    /* DC MOTOR */
  int DC_motor_speed = 400;
  int DC_dir = 1; //1 = Clockwise, 0 = CounterClockwise
  float AOA_Az_ref = 0;
    
    
    /* Stepper */
  int STEP_dir = 1; //1 = up, 0 = down; 
  int STEP_speed = 200; 
  float STEP_Kp =500, STEP_Ki = 0, STEP_Kd = 0;
  float AoA_EL_REF = 0;
  

    
    for (int n_mean = 0; n_mean < NO_OF_MEAN; n_mean++)
    {
    // Azimuth
    AMux_1_FastSelect(0);  //0 = PIN_ADC_IN_AZ
    DMA_getSample();
    while(TakingSampleAz == 1){ //Waits until a sample is ready from the DMA
        if(DMADone_1_flag && DMADone_2_flag )
        {	      
            TakingSampleAz = 0;
            DMADone_1_flag = 0; 
            DMADone_2_flag = 0;	
        }
    }
    theta_Az = PhaseDifference(adc_sampleArray_1,adc_sampleArray_2);

    // Elevation
    AMux_1_FastSelect(1);  //1 = PIN_ADC_IN_EL
    DMA_getSample();
    while(TakingSampleEl == 1){ //Waits until a sample is ready from the DMA
        if(DMADone_1_flag && DMADone_2_flag )
        {	      
            TakingSampleEl = 0;
            DMADone_1_flag = 0; 
            DMADone_2_flag = 0;	
        }
    }
    theta_El = PhaseDifferenceEL(adc_sampleArray_1,adc_sampleArray_2);
    
    //Regner theta'er om til AoA'er
    AoA_Az = sinf(theta_Az/pi)*(180/pi)+AoA_Az+26;//+26 is an offset which has been found from different measurements
    AoA_El = sinf(theta_El/pi)*(180/pi)+AoA_El+7.5; //+7.5 is an offset which has been found from different measurements
    
    }
    AoA_Az = AoA_Az/NO_OF_MEAN;
    AoA_El = AoA_El/NO_OF_MEAN;
    
    
    /* DC MOTOR */
    
    if(AoA_Az < 0) //Changes the direction that the motor is running according to the AoA
    {
       DC_dir = 0; // 1 = Clockwise 
       
    } else {
       DC_dir = 1; // 0 = CounterClockwise   
    }
        
    if((prev_1_AOA_Az > 0 && AoA_Az < 0) || (prev_1_AOA_Az < 0 && AoA_Az > 0))
    {
        prev_2_DC_speed = 0;
        prev_1_DC_speed = 0;
    }
   
    DC_motor_speed = (int)(8.204*(AoA_Az-AOA_Az_ref)-4.793*prev_1_AOA_Az-3.397*prev_2_AOA_Az+prev_2_DC_speed); //The controller itself.
    
    prev_2_AOA_Az = prev_1_AOA_Az;
    prev_1_AOA_Az = (AoA_Az-AOA_Az_ref);

    prev_2_DC_speed = prev_1_DC_speed;
    prev_1_DC_speed = DC_motor_speed;

    
    DC_motor_speed = abs(DC_motor_speed)+75; //Since DC_dir controls the motor direction, and DC_motor_speed the PWM the absolute value is needed for the PWM.
    //+225
    if (DC_motor_speed > 1000) { //PWM value must be between 0-1000.
        DC_motor_speed = 1000;
    }
    
    DCMotorControl(DC_dir, DC_motor_speed);
    
    
     /* Stepper MOTOR */
    
     if(AoA_El < 0)
    {
       STEP_dir = 0; // 0 = up
       
    } else {
       STEP_dir = 1; //  1 = down
    }
    
    
    Step_integral = Step_integral + (AoA_El-AoA_EL_REF);
    Step_derivative = AoA_El - prev_AoA_El;
    
    if((prev_AoA_El > 0 && AoA_El < 0) || (prev_AoA_El < 0 && AoA_El > 0))
    {
        Step_integral = 0;
    }
     
    prev_AoA_El = AoA_El;
    
    //Transfer function (PID)
    STEP_speed = (int)(STEP_Kp*(AoA_El - AoA_EL_REF)+STEP_Ki*Step_integral+Step_derivative*STEP_Kd); //High value = Slow, Low value = fast
      
    STEP_speed = 65535-abs(STEP_speed); //Needs the absolute value for the same reason as the DC motor speed.
        
    StepperMotorControl(STEP_dir, STEP_speed);
    
    
    
    /* Checks if there is any signal available from the beacon */
    Amp = AmplitudeDFT(adc_sampleArray_1);
    if (Amp < AmpThreshold){ 
        state = 1;
    }   

}


int main()
{

    /* Channel configuration parameters for DMA */
    #define DMA_1_BYTES_PER_BURST 2
    #define DMA_1_REQUEST_PER_BURST 1
    #define DMA_1_SRC_BASE (CYDEV_PERIPH_BASE)
    #define DMA_1_DST_BASE (CYDEV_SRAM_BASE)
    
    #define DMA_2_BYTES_PER_BURST 2
    #define DMA_2_REQUEST_PER_BURST 1
    #define DMA_2_SRC_BASE (CYDEV_PERIPH_BASE)
    #define DMA_2_DST_BASE (CYDEV_SRAM_BASE)

	/* Enable global interrupt */
	CYGlobalIntEnable; 
	
	/* Start isr connected to collect samples pin */
	ISR_Sw_Start();
	
	/* Start isr connected to DMA nrq signal */
	ISR_DMA_1_Start();
    ISR_DMA_2_Start();
    
    

    /* Step 1: DmaInitialize - Initialize the DMA channel
	 * Burst count (Bytes per burst) = 2 bytes. Transfer 2-bytes from ADC to memory on each trigger.
	 * Request per burst = 1. Every burst transfer requires a separate request. 
	 * Upper source address = HI16(CYDEV_PERIPH_BASE)
	 * Upper destination address = HI16(CYDEV_SRAM_BASE)
     * DMA_Chan holds the channel handle returned by the ‘DmaInitialize’ function. This is 
	 * used for all further references of the channel 
	 */	
    DMA_1_Chan = DMA_1_DmaInitialize(DMA_1_BYTES_PER_BURST, DMA_1_REQUEST_PER_BURST, 
                                 HI16(DMA_1_SRC_BASE), HI16(DMA_1_DST_BASE));
    DMA_2_Chan = DMA_2_DmaInitialize(DMA_2_BYTES_PER_BURST, DMA_2_REQUEST_PER_BURST, 
                                 HI16(DMA_2_SRC_BASE), HI16(DMA_2_DST_BASE));

    /* Step 2: CyDmaTdAllocate - Allocate TD */
    DMA_1_TD[0] = CyDmaTdAllocate();
    DMA_2_TD[0] = CyDmaTdAllocate();

    /* Step 3: CyDmaTdSetConfiguration - Configures the TD:
	 * tdHandle = DMA_TD[0] - TD handle previously returned by CyDmaTdAlloc()
	 * transferCount = (2 * NO_OF_SAMPLES)
	 * nextTd = DMA_DISABLE_TD, Disable the DMA channel after the transfer is complete
	 * configuration = Increment Destination address after each burst transfer
	 *				   Generate termout when the transfer is finished.
	 *				   In PSoC 3, byte swap is enabled for endian swapping. This is not required for PSoC 5LP 
	 */

    CyDmaTdSetConfiguration(DMA_1_TD[0], (2 * NO_OF_SAMPLES), DMA_DISABLE_TD, 
				                            DMA_1__TD_TERMOUT_EN | TD_INC_DST_ADR);     
    CyDmaTdSetConfiguration(DMA_2_TD[0], (2 * NO_OF_SAMPLES), DMA_DISABLE_TD, 
				                            DMA_2__TD_TERMOUT_EN | TD_INC_DST_ADR);     
    
    /* Step 4: CyDmaTdSetAddress - Configure the lower 16 bit source and destination addresses 
	 * Source address = Lower 16 bits of ADC data register
	 * Destination address = Lower 16 bits of 'ADC_sample' array */
	CyDmaTdSetAddress(DMA_1_TD[0], LO16((uint32)ADC_SAR_1_SAR_WRK0_PTR), LO16((uint32)adc_sampleArray_1));
    CyDmaTdSetAddress(DMA_2_TD[0], LO16((uint32)ADC_SAR_2_SAR_WRK0_PTR), LO16((uint32)adc_sampleArray_2));
                           
    /* Step 5: Map the TD to the DMA Channel */
	CyDmaChSetInitialTd(DMA_1_Chan, DMA_1_TD[0]);
    CyDmaChSetInitialTd(DMA_2_Chan, DMA_2_TD[0]);

	/* Start ADC */
	ADC_SAR_1_Start();
    ADC_SAR_2_Start();
    
    /* Disable the ADC ISR as it is not required */
    ADC_SAR_1_IRQ_Disable();
    ADC_SAR_2_IRQ_Disable();

	/* Start ADC conversion */
	//ADC_SAR_1_StartConvert();
    //ADC_SAR_2_StartConvert();
    
    /*Start UART */
    UART_1_Start();
    
    // MUX Start
    AMux_1_Start(); 
    
    // use AMUX_1_Fastselec(xxx); to change mux 
    
    // motor setup
    MotorSetup();
    
    /* Pre calculate different values */ 
    for (int n = 0; n < NO_OF_SAMPLES; n++)
    {
        int N = NO_OF_SAMPLES;
        Cos_sampleArray[n] = cosf(n*2*pi*k/N);
        Sin_sampleArray[n] = sinf(n*2*pi*k/N);      
    }
    
    for(;;)
    {
      
	     /* DMADone_flag is set inside ISR_DMA_Done after the required number
		 * of ADC samples are buffered */
        
        if(state == 0)  //Setup
        {
            Setup();
            state = 1; 
        } else if(state == 1) { //Search
            search();
            
        } else if(state == 2) { //Point
           PinPointAoA(); 
        }
        
        if(switch_flag) //Reset
		{
            state = 0;
			/* Clear the Flag */
			switch_flag = 0;
			
		}/* If statement ends here */
        
		
    }/* for loop ends here */
        
	/* Place your application code here. */
}
