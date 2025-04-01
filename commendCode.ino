/*
Written by: Metin Biter
Purpose of the Code:
In our RF projects, we can easily introduce our remote control to our control board using simple, memory-less 433 MHz radio frequency
receivers (such as the RX470C module), and create a secure usage that prevents other remotes from communicating with our control board.

With this code, after connecting to any pin of the microprocessor that can trigger an interrupt (in this code, the 2nd pin of the Arduino,
which is the 0 interrupt pin), a digital peripheral trigger on pin 12 (INPUT) is activated. The remote control is introduced to 
the microprocessor by pressing any button on the remote.

Basic Algorithm of the Code:
A command is given to the microprocessor to recognize the remote control by pressing a button.
Then, the remote control is introduced to the microprocessor by pressing any button on the remote.
After the microprocessor recognizes the remote, it saves the remote's identity to the EEPROM, and even after the power is
cut off and the microprocessor is powered back on, it retains the ability to recognize the remote. The stored identity ensures
that the system will not respond to other RF remotes.
*/

#include <RCSwitch.h>
#include <EEPROM.h>

RCSwitch mySwitch = RCSwitch();
  long address = 0; // EEPROM'da veriyi saklayacağımız adres
  long readValue = 0;
  long button=0;
long buttonNum;
long bottonVal;
long commandRead=0;
long button1 =0 ;
long button2 =0 ;
long button3 =0 ;
long button4 =0 ;

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);

  digitalWrite(7,  HIGH);
  digitalWrite(5,  HIGH);
  

  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2

  delay(1000); // 

  // Reading data from EEPROM
 

  readValue |= (long)EEPROM.read(address ) << 16; //Get the third byte
  readValue |= (long)EEPROM.read(address + 1) << 8; // Get the second byte
  readValue |= (long)EEPROM.read(address+2); // Get the first byte

  // Writing the read value to the serial monitor
  Serial.print("Data read from EEPROM: ");
  Serial.println(readValue);

   bottonVal = readValue % 10;
     if(bottonVal == 6 ){
      button1 = button;
      button2 = button-4;
      button3 = button-6;
      button4 = button -7;
     }
     if(bottonVal == 2 ){
      button1 = button +4;
      button2 = button;
      button3 = button-2;
      button4 = button -3;
     }
      if(bottonVal == 0 ){
      button1 = button +6;
      button2 = button +2;
      button3 = button;
      button4 = button -1;
     }
      if(bottonVal == 9 ){
      button1 = button + 7;
      button2 = button + 3;
      button3 = button + 1;
      button4 = button;
     }

}




void loop() {
    if(digitalRead(12)==1){
      delay(200);
      commandRead++;
      if(commandRead>1){
        commandRead=0;
      }
      if(commandRead==1){
        digitalWrite(13, HIGH);
      }
      else{
        digitalWrite(13, LOW);
      }
    }
if (mySwitch.available() && commandRead == 1) {
     button = mySwitch.getReceivedValue();
     commandRead=0;
       //Writing data to EEPROM
  EEPROM.write(address,(button >> 16)  & 0xFF); // Write the first part of 1 byte
  EEPROM.write(address + 1, (button >> 8) & 0xFF); // Write the second part of 1 byte
  EEPROM.write(address + 2, button & 0xFF); //Write the third part of 1 byte

 

    bottonVal = button % 10;
     if(bottonVal == 6 ){
      button1 = button;
      button2 = button-4;
      button3 = button-6;
      button4 = button -7;
     }
     if(bottonVal == 2 ){
      button1 = button +4;
      button2 = button;
      button3 = button-2;
      button4 = button -3;
     }
      if(bottonVal == 0 ){
      button1 = button +6;
      button2 = button +2;
      button3 = button;
      button4 = button -1;
     }
      if(bottonVal == 9 ){
      button1 = button + 7;
      button2 = button + 3;
      button3 = button + 1;
      button4 = button;
     }
     
}
    

  if (mySwitch.available()  &&  mySwitch.getReceivedValue() == button1 | readValue == button2 | readValue == button3 | readValue == button4 ) {
    
    Serial.print("Received ");
    Serial.print( mySwitch.getReceivedValue() );
    Serial.print(" / ");
    
    Serial.println( button1 );
    Serial.print(" / ");
    Serial.println( button2 );
    Serial.print(" / ");
    Serial.println( button3 );
    Serial.print(" / ");
    Serial.println( button4 );



    if(mySwitch.getReceivedValue() == button1 ){
    digitalWrite(7, HIGH );
    delay(1000);
     digitalWrite(7, LOW );
  }
  // if(mySwitch.getReceivedValue() ==  8960097 ){
   
  // }

  if(mySwitch.getReceivedValue() ==  button2  ){
    digitalWrite(5,  LOW);
    delay(1000);

    digitalWrite(5,  HIGH);
  }
 


    mySwitch.resetAvailable();
  }
  
}
