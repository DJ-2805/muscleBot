#include <SoftwareSerial.h>
SoftwareSerial BT(7, 6); // RX | TX: choose whatever, it doesn't matter
// read and write, a single char at a time:
// BT.read(); BT.write(char);

const long BTBaudRate = 38400; 
const long BTPeriod = 10; // millisec
const int LEFT = 4;
const int RIGHT = 2;
char c;

void setup(){
	BT.begin(BTBaudRate);  
	pinMode(LEFT, OUTPUT);
	pinMode(RIGHT, OUTPUT);
}

void loop(){
	if (!BT.available())
		return;
	c = BT.read();
	switch(c){
		case 'w':
		case 'a':
		case 's':
		case 'd':
			move(c);
			break;
	}
}

void move(char c){
	Serial.println("hwer");
	switch(c){
		case 'w':
			digitalWrite(LEFT, HIGH);
			digitalWrite(RIGHT, HIGH);
			delay(BTPeriod);
			digitalWrite(LEFT, LOW);
			digitalWrite(RIGHT, LOW);
			break;
		case 'd':
			digitalWrite(RIGHT, HIGH);
			delay(BTPeriod);
			digitalWrite(RIGHT, LOW);
			break;
		case 'a':
			digitalWrite(LEFT, HIGH);
			delay(BTPeriod);
			digitalWrite(LEFT, LOW);
			break;
		case 's':
			break;
	}
}
