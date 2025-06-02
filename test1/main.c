#include <reg52.h>
//#include "motor.h"

sbit a1 = P1^0;     //
sbit a2 = P1^1;
sbit b1 = P1^2;
sbit b2 = P1^3;
sbit c1 = P1^4;
sbit c2 = P1^5;
sbit d1 = P1^6;
sbit d2 = P1^7;
sbit ENa = P2^0;
sbit ENb = P2^1;
sbit ENc = P2^2;
sbit ENd = P2^3;

void IN1(int i){
    if (i){
    a1 = 1;
    a2 = 0;
    }
    else {
    a1 = 0;
    a2 = 1;
    }
}

void IN2(int i){
    if (i){
    c1 = 1;
    c2 = 0;
    }
    else {
    c1 = 0;
    c2 = 1;
    }
}

void IN3(int i){
    if (i){
    b1 = 1;
    b2 = 0;
    }
    else {
    b1 = 0;
    b2 = 1;
    }
}

void IN4(int i){
    if (i){
    d1 = 1;
    d2 = 0;
    }
    else {
    d1 = 0;
    d2 = 1;
    }
}

void ENA(int i){
    if (i){
    ENa = 1;
    ENc = 1;
    }
    else {
    ENa = 0;
    ENc = 0;
    }
}

void ENB(int i){
    if (i){
    ENb = 1;
    ENd = 1;
    }
    else {
    ENb = 0;
    ENd = 0;
    }
}

void main(){
    IN1(1);
    IN2(1);
    ENA(1);
    ENB(1);

}


