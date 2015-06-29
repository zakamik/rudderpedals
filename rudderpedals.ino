#include "Wire.h"

// I2Cdev and HMC5883L must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "HMC5883L.h"

HMC5883L mag;

int16_t mx, my, mz, x, y, z;
float minheading=0, maxheading=0, heading=0, adjheading=0, CENTER=0, r_range=0, l_range=0, ADJ_C=0;
bool ready=false;
int i,cnt;

bool state=0;

void dataReady() {
  state=state==0 ? 1 : 0;
  ready=true;
  digitalWrite(4, 1);
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(4, OUTPUT);
    Wire.begin();

    Serial.begin(115200);

    attachInterrupt(4, dataReady, RISING);
    // initialize device
    Serial.println("Initializing I2C devices...");
    mag.initialize();
    mag.setDataRate(HMC5883L_RATE_15);
    mag.setGain(HMC5883L_GAIN_220);
    mag.setMode(HMC5883L_MODE_CONTINUOUS);
    delay(100);
    ready=mag.getReadyStatus();
    while(cnt < 30) {
      if(ready==true) {
        mag.getReadyStatus();
        ready=false;
        mag.getHeading(&mx, &my, &mz);
        CENTER+=atan2(my, mx);
        cnt++;
      } else {
        delay(5);
        Serial.println("not ready...");
      }
    }
    CENTER/=30;
}
#define BSIZE 3
int16_t dx[BSIZE], dy[BSIZE], dz[BSIZE];
int16_t posx=0,posy=0,posz=0;
int16_t prevx=0, prevy=0, prevz=0;
float dt=0, alpha=0, cx, cy, cz;
uint32_t now=0, lastupdate=0, dtr;
float mincx=0, maxcx=0, range=0;
const float RC=0.5f;


void loop() {
  int buttons;

  
  now=micros();
  if(ready) {
    mag.getReadyStatus();
    ready=false;
    digitalWrite(4,0);
    dtr=now-lastupdate;
    lastupdate=now;
    dt=dtr/1000000.0f;

    mag.getHeading(&mx, &my, &mz);

    dx[posx++]=mx;
    posx=posx>=BSIZE ? 0 : posx;
    dy[posy++]=my;
    posy=posy>=BSIZE ? 0 : posy;
    dz[posz++]=mz;
    posz=posz>=BSIZE ? 0 : posz;
    cx=0; cy=0, cz=0;
    for(int i=0; i < BSIZE; i++) {
      cx+=dx[i]; cy+=dy[i]; cz+=dz[i];
    }

    cx/=BSIZE; cy/=BSIZE; cz/=BSIZE;
    float heading=atan2(my, mx);

    minheading = heading < minheading ? heading : minheading;
    maxheading = heading > maxheading ? heading : maxheading;
    ADJ_C=CENTER-minheading;
    l_range=ADJ_C;
    r_range=maxheading-CENTER;
    range=maxheading-minheading;
    adjheading=heading < CENTER ? (heading-minheading)/l_range : (heading-CENTER)/r_range+1;
    adjheading=(1-adjheading)/2*65535;


    Serial.print("lowp:\t"); 
    Serial.print(dtr); Serial.print("\t");
    Serial.print("minmaxrange:"); Serial.print("\t");
    Serial.print(minheading); Serial.print("\t");
    Serial.print(maxheading); Serial.print("\t");
    Serial.print(range); Serial.print("\t");
    Serial.print("hdg:"); Serial.print("\t");
    Serial.print(heading,3); Serial.print("\t");
    Serial.print(adjheading); Serial.print("\t");
    Serial.print(CENTER,3); Serial.print("\t");
    Serial.print(ADJ_C,3); Serial.print("\t");
    Serial.print("range:"); Serial.print("\t");
    Serial.print(l_range); Serial.print("\t");
    Serial.print(r_range); Serial.print("\t");
    Serial.print("xyz:"); Serial.print("\t");
    Serial.print(mx); Serial.print("\t");
    Serial.print(my); Serial.print("\t");
    Serial.println(mz);
//    Serial.print(y); Serial.print("\t");
//    Serial.println(z);

    Joystick.move(x, y, round(adjheading));
  } else {
//    Serial.println("not ready");
  }

}

