#ifndef _PARTICLESEDIMENTATION_H
#define _PARTICLESEDIMENTATION_H

#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

class ParticleSedimentation{
    
private: 
    vector <double> meter;
    vector <double> measured_temp;
    vector <double> temp;
    vector <double> density;
    vector <double> viscosity;
    vector <double> v_p;
    double p_p_min=1850;  //Dichte Partikels kg/m3
    double p_p_max=2100;
    double g=9.81;
    double R= 8.314462618;

public:
    ParticleSedimentation();
    ~ParticleSedimentation();
    void DeleteContentFile();
    void ReadTempMeter();
    void ReadTempDichteViskositaet();
    void CalculationVelocity(double radius);
    void CalculationTime(double radius);
    
 
};

#endif