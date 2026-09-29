#include "multiplex.h"

multiplex::multiplex(uint8_t tcaAddr) : _tcaAddr(tcaAddr){
}

void multiplex::init(){
    Wire.begin();

    //Slukker alle TCA porte
    Wire.beginTransmission(_tcaAddr);
    Wire.write(0x00);
    Wire.endTransmission();
}

uint8_t multiplex::getPort() const{
    Wire.requestFrom((int) _tcaAddr,1);

    if(Wire.available()){
        return Wire.read();
    }
    return 0xFF;
}

void multiplex::selectPort(uint8_t port){
    if (port > 7) return;

    Wire.beginTransmission(_tcaAddr);
    Wire.write(1 << port);
    Wire.endTransmission();
}
