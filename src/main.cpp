#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <vector>
#include "particle_sedimentation.h"
#include "particle_sedimentation.cpp"

using namespace std;

int main(){
  
 int selection; 
 double radius;
 bool end_programm=false;

 ParticleSedimentation calculate; 
 calculate.ReadTempMeter();
 calculate.ReadTempDichteViskositaet();
 calculate.DeleteContentFile();


 while(end_programm!=true){

printf("\n#########################################################################\n");
printf("\nBitte Wählen! \n");
printf("1) Sinkgeschwindigkeit berrechnen\n" 
       "2) Programm beenden\n" 
       "Auswahl: "); 
scanf("%d", &selection); 

//prüfen ob buchstabe oder zahl

switch(selection){
      case 1: printf("Partikelradius in Micrometer [µm] eingeben: "); 
              scanf("%lf", &radius);
              radius=radius/1000000;
              calculate.CalculationVelocity(radius);
              calculate.CalculationTime(radius);
              break;
      case 2: end_programm=true;
              break;
     default: printf("Falsche Auswahl!\n"
                      "Nur Zahlen zwischen 1 und 2!!!\n");
              break;
      }

}
 //destructor
 return 0;
}
 



