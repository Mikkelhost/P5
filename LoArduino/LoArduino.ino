#include <SPI.h>
#include <SD.h>

File myFile;
byte LE = 3;
unsigned long registers[13];
char charBuffer[50];
char sample[] = "0x1050C";
byte start, endofbyte;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  pinMode(LE, OUTPUT);
  digitalWrite(LE, HIGH); // sets up the LE pin
  SPI.begin();
  SPI.beginTransaction(SPISettings(600000, MSBFIRST, SPI_MODE0)); // SPI at 600 kHz

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  myFile = SD.open("adfsetup.txt"); // opens up the setupfile created by Analog Devices software.
  if (myFile){// If succesfully opened
    Serial.println("ADFx35x_register_values.txt:");

    // read from the file until there's nothing else in it:
    int counter = 0;
    int bufferCounter = 0;
    while (myFile.available()) { // while data is available from the file
      int tmp = myFile.read();
      if(tmp != 0xD){ //If the character read is not a Carriage return.
        
        charBuffer[bufferCounter]=tmp; // Write the tmp val to a charbuffer
        bufferCounter++;// Counts up.
      }else
      {
        int tmp = myFile.read(); // read the newline character and throw it away.
        Serial.print(charBuffer); Serial.print(" Sizeof: "); Serial.print(sizeof(charBuffer)); // debugging
        Serial.print(" Counter: "); Serial.println(counter); // debugging
        registers[12-counter] = strtoul(charBuffer, NULL, 16); // Converts the charbuffer into a base 16 integer(HEX) and stores in the registers array.
        Serial.println(registers[12-counter],HEX); // debugging
        bufferCounter = 0; // resets the buffercounter so the charbuffer can be rewritten.
        counter++; // Selects the next register to be written to.
        memset(charBuffer, 0, sizeof(charBuffer)); // resets all the values in the charbuffer.
      }  
    }
    // The last value to be written to a register comes here. This is because the last char of the file is not a Carriage return.
    Serial.print(charBuffer);// debugging
    Serial.print(" Counter: "); Serial.println(counter);// debugging
    registers[12-counter] = strtoul(charBuffer, NULL, 16);
    Serial.println("Printing registers");// debugging
    for(int i = 0; i < 13; i++){
      Serial.println(registers[12-i],HEX);// debugging, checks if the registers has been read the right way from the SD card.
    }
    // close the file:
    myFile.close(); // close the open .txt file.    
  }
  else{
    Serial.println("Error opening file adfsetup.txt"); // if the file does not exists
  }
  delay(2000);
  SPI.beginTransaction(SPISettings(600000, MSBFIRST, SPI_MODE0)); // Sets up the SPI-bus for another transaction this time for the ADF4355-3 IC.
  for(int i = 0; i < 13; i++){ // For loop runs 13 times because there are 13 registers.
    if(i == 12) delayMicroseconds(162); // According to the datasheet a 162 us delay is needed before the last register can be written to.
    WriteRegister32(registers[12-i]); // Writes the 32 bit integer over the SPI-bus.
  }
  
  /* testing the function WriteRegister32. */
  //WriteRegister32(0x1050C);
  //start = sample.indexOf('x');
  //endofbyte = sample.indexOf('\0');
  //String hexVal = sample.substring(start, endofbyte);
  //registers[0] = strtoul(sample, NULL, 16);
  //Serial.println(start);
  //Serial.println(endofbyte);
  //Serial.println(registers[0],BIN);
}
bool sent = false;
void loop() {
 
}

void WriteRegister32(const uint32_t value)
{ 
  digitalWrite(LE, LOW); // LE has to be LOW for the shiftregister in the IC is active.
  for (int i = 3; i >= 0; i--){ // Makes 4 consecutive writes of 8 bits which totals out as 32 bits.         
    SPI.transfer((value >> 8 * i) & 0xFF); 
  }
  digitalWrite(LE, HIGH);// A transition from LOW to HIGH on LE latches the 32 bit shifregisters values to one of the 13 latches in the IC specifiec by the controlbits
}
