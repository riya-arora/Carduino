/*
Arduino Turn LED On/Off using Serial Commands
Created April 22, 2015
Hammad Tariq, Incubator (Pakistan)

It's a simple sketch which waits for a character on serial
and in case of a desirable character, it turns an LED on/off.

Possible string values:
a (to turn the LED on)
b (tor turn the LED off)
*/
#include <SoftwareSerial.h>
#include <Stepper.h>
#define RxD 0
#define TxD 1
SoftwareSerial bluetoothSerial(RxD,TxD);

const int stepsPerRevolution = 500;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 10, 11, 12, 13);
char junk;
String inputString="";
int buzzerpin=8;
int panic=5;
int w1,w2;
void setup()
// run once, when the sketch starts
{
  bluetoothSerial.begin(9600);
Serial.begin(9600);            // set the baud rate to 9600, same should be of your Serial Monitor
 myStepper.setSpeed(80);
// pinMode(RxD,INPUT);
 //pinMode(TxD,OUTPUT);
 //setupBlueToothConnection();
}

void loop()
{
  Serial.println('x');
  if(Serial.available()){
  while(Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
    Serial.println(inputString);
    while (Serial.available() > 0)  
    { junk = Serial.read() ; }      // clear the serial buffer
    if(inputString == "a"){         //in case of 'a' turn the LED on
       myStepper.step(stepsPerRevolution);
       delay(500);  
    }else if(inputString == "b"){//incase of 'b' turn the LED off
      myStepper.step(-stepsPerRevolution);
      delay(500);
    }
    else if(inputString == "s"){// incase input=='s'beep sound
      tone(buzzerpin,1000,500);
      }
    else if(inputString=="chk"){
     w1=digitalRead(6);
     w2=digitalRead(7);
     {if(w1==w2)
     {
     Serial.print('c');
     }
     }
     }
    inputString = "";
  }

if(panic==LOW)
{
Serial.println('p');  
}
}
/*void setupBlueToothConnection()
{
b+



































































































































































































































































































































































...............luetoothSerial.begin(9600);// BluetoothBee BaudRate to default baud rate 38400
bluetoothSerial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
bluetoothSerial.print("\r\n+STNA=HC-05\r\n"); //set the bluetooth name as "SeeedBTSlave"
bluetoothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
bluetoothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
delay(2000); // This delay is required.
bluetoothSerial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
Serial.println("The slave bluetooth is inquirable!");
delay(2000); // This delay is required.
bluetoothSerial.flush();
}*/
