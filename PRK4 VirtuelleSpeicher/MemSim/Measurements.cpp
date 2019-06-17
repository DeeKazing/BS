/*Messungen: Die Umgebung soll Messungen machen und am Ende der Simulation sie im Form eines Reports ausgeben.
Mindestens die Anzahl Seitenfehler soll gezählt und berichtet werden. 
Andere Messungen sollen nach Bedarf gemacht werden, 
sodass aussagekräftige Vergleiche zwischen verschiedenen virtuellen Speicher Algorithmen bzw. 
Systemen gemacht werden können.*/
#include "Measurements.h"

Measurements::~Measurements() {
}

void Measurements::tick() {
    ++mTime;
}

void Measurements::pageError() {
    ++mPageErrors;
    ++mPageAccess;
}

void Measurements::pageSuccess() {
    ++mPageSuccess;
    ++mPageAccess;
}

void Measurements::unhealthy() {
    mHealthy = false;
}

double Measurements::getPageAccess() const {
    return mPageAccess;
}

double Measurements::getPageSuccess() const {
    return mPageSuccess;
}

double Measurements::getPageErrors() const {
    return mPageErrors;
}

int Measurements::getTime() const {
    return mTime;
}

bool Measurements::getHealth() const {
    return mHealthy;
}
