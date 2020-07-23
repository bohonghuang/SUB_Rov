#include "Oilvalve.h"

Oilvalve::Oilvalve(){
    this->oils = new quint16[5]{0,25,50,100,255};
}

bool Oilvalve::ResetOils(quint16* value){
    if(value==nullptr)
        return false;
    this->oils = value;
    return true;
}
quint16 Oilvalve::GetOilAddLevelAndOfIndex(){
    if(index<4)
        index++;
    
    return oils[index];
}

quint16 Oilvalve::GetOilSubOilAndOfIndex(){
    if(index>0)
        index--;
    
    return oils[index];
}

quint16 Oilvalve::GetOil(){
    return oils[index];
}
