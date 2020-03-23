#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <string.h> 

SoftwareSerial mySerial(A4,A5);  //建立軟體串列埠腳位 (RX, TX)

AF_DCMotor motorleft1(4);
AF_DCMotor motorleft2(1);
AF_DCMotor motorright1(3);
AF_DCMotor motorright2(2);

double V1,V2,V3,V4;//motor speed
double x,y,a;

void setup() {  
	Serial.begin(57600);
  	Serial.println();
  	mySerial.begin(57600);

  	motorleft1.run(RELEASE);
    motorleft2.run(RELEASE);
    motorright1.run(RELEASE);
    motorright2.run(RELEASE);
}

void loop() {
	//接收資料和解析
	while (!mySerial.available()) {}
	char strC[1024];
	int index=0;
	String str="";
    while (mySerial.available()) {
        char c = mySerial.read();
        if(c!='\r'){
            strC[index] = c;
            index++;
            str+=c;
        }
        delay(5);
    }
    char* stringPtr;
    stringPtr = strtok(strC,",");
    int data[5];
    int n=0;
    while (stringPtr!= NULL)
    {
    	data[n]=String(stringPtr).toInt();
    	n++;
    	stringPtr = strtok(NULL,",");
    }
    Serial.print(str);
    //接收資料和解析 END
    //Data: LY,LX,RY,RX,L2

    if(data[4]){
    	y=map(data[0],-1,255,-1,1);
    	x=map(data[1],1,255,1,-1);
    	a=map(data[3],-1,255,-1,1);
    }else{
    	y=map(data[0],-1,255,1,-1);
    	x=map(data[1],1,255,-1,1);
    	a=map(data[3],-1,255,-1,1);
    }

    V1 = y - x + a;
  	V2 = y + x - a;
  	V3 = y - x - a;
  	V4 = y + x + a;   

  	motorR1speedcontrol(V1);
  	motorR2speedcontrol(V4);
  	motorL1speedcontrol(V2);
  	motorL2speedcontrol(V3);

}

void motorL1speedcontrol(double s)
{
  if(s>0){
    motorleft1.run(FORWARD);
    motorleft1.setSpeed(s*250);
  }
    if(s==0){
    motorleft1.run(RELEASE);
  }
    if(s<0){
    motorleft1.run(BACKWARD);
    motorleft1.setSpeed(-s*250);
  }
}
void motorL2speedcontrol(double s)
{
  if(s>0){
    motorleft2.run(FORWARD);
    motorleft2.setSpeed(s*250);
  }
    if(s==0){
    motorleft2.run(RELEASE);
  }
    if(s<0){
    motorleft2.run(BACKWARD);
    motorleft2.setSpeed(-s*250);
  }
}
void motorR1speedcontrol(double s)
{
  if(s>0){
    motorright1.run(FORWARD);
    motorright1.setSpeed(s*250);
  }
    if(s==0){
    motorright1.run(RELEASE);
  }
    if(s<0){
    motorright1.run(BACKWARD);
    motorright1.setSpeed(-s*250);
  }
}
void motorR2speedcontrol(double s)
{
  if(s>0){
    motorright2.run(FORWARD);
    motorright2.setSpeed(s*250);
  }
    if(s==0){
    motorright2.run(RELEASE);
  }
    if(s<0){
    motorright2.run(BACKWARD);
    motorright2.setSpeed(-s*250);
  }
}
