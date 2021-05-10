#include "particle_sedimentation.h"


ParticleSedimentation::ParticleSedimentation(){}

ParticleSedimentation::~ParticleSedimentation(){}

/**
 * @brief Delete content of the files to write results into 
 *
 */

void ParticleSedimentation::DeleteContentFile(){
  fstream file1;
  file1.open("../data/result.txt", ios::out);
  file1.close();

  fstream file2;
  file2.open("../data/calculation.txt", ios::out);
  file2.close();
}


/**
 * @brief Reads the measured temperature at a certain deepness (meter) of the lake 
 *        and saves both temperature and deepness in a vector
 *
 */
void ParticleSedimentation::ReadTempMeter(){ 

  string line, deepness, temperature, dump1, dump2;
    
  fstream readfile;
  readfile.open("../data/Temperature.txt", ios::in);
  stringstream linestream(line);

  while(!getline(readfile, line).eof()){

    stringstream linestream(line);
    linestream >> deepness >> dump1 >> temperature >> dump2;
    
    meter.push_back(atof(deepness.c_str()));
    measured_temp.push_back(atof(temperature.c_str()));
    }
  
  readfile.close();        
}

/**
 * @brief Reads density and viscosity of water (given values from measurments) 
 *        for different temperature from a file and save values in vector.
 *        Needed to calculate the sedimentation velocity for the given particel size
 *
 */
void ParticleSedimentation::ReadTempDichteViskositaet(){ 

    string line, fdump, sdump, tdump, dump;
    
    fstream readfile;
    readfile.open("../data/daten.txt", ios::in);
  
    stringstream linestream(line);
    
    while(!getline(readfile, line).eof()){
        stringstream linestream(line);
        linestream >> fdump >> dump >> sdump >> tdump;
        temp.push_back(atof(fdump.c_str()));
        density.push_back(atof(sdump.c_str()));
        viscosity.push_back(atof(tdump.c_str()));
        }

   readfile.close(); 
}

/**
 * @brief Calculate the sedimentation velocity for certain temperature (5°C - 17°C)
 *        Save the sedimentation velocity for each temperature in a file
 *
 * @param v        calculated sedimentation velocity
 * @param r        particel radius
 * @param p_p_min  particel density [kg/m3]
 *
 */
void ParticleSedimentation::CalculationVelocity(double r){
 
  double v; 

  fstream writefile;
  fstream writecalculation;
  writefile.open("../data/info.txt", ios::app);
  writecalculation.open("../data/calculation.txt", ios::app);
  writecalculation << "#############################################################" << endl << endl;
  writecalculation << "Radius(r)= " << r << " m" << endl; 
  writecalculation << "v[T] = (2/9)* (r*r*g*(density_solid-density_water[T]))/(viscosity[T]))*1000000" << endl << endl;
 
  //geschwindigkeit wird nach temperatur berechnet
  for(int i=0; i<13; i++){
    v=((2.0/9.0)*(r*r*g*(p_p_min-density[i]))/(viscosity[i]))*1000000;
    v_p.push_back(v);
    writefile << temp[i] << " " << v << endl;
    writecalculation << v << "[" << temp[i] << "°C]" << " = " << "2/9" << " * (" << r*r << " * "<< g << " * (" 
                     << p_p_min << " - " << density[i] << ")) / (" <<  viscosity[i] 
                     << ")) * 1000000" << endl;
  }
  writefile << endl;
  writecalculation << endl;
  writefile.close();
  writecalculation.close();
}

/**
 * @brief Calculate the time for particle sedimentation
 *        Values of the sedimentation velocity for tempearature from 5°C to 17°C saved in info.txt
 *        For-loop take each measured temperature value 
 *        While-loop go through all values written in file info.txt and compare the temperature
 *        to the actuelle measured temperature
 *        If the values of the measured temperature and the value written in the file info.txt
 *        are equal take the sedimentation velocity for that temperature and multiply it by the 
 *        the factor diff
 * 
 * @param diff        calculate the difference of meters between the current value and the next
 *                    value in the vektor meter (because thedifference is not always 1 meter
 *                    so in cae of e.g. 5 meters the sedimentation velocity will calculate 
 *                    by multiplying that value by factor 5)
 * @param timedummy   Calculate the sedimentation time (seconds) for one meter
 * @param time        Calculate the sedimentation time for the given distance of the temperatur detectors
 * @param days        Calculate to convert the sedimentation time (seconds) into days
 * 
 */

void ParticleSedimentation::CalculationTime(double r){

 double diff, timedummy, days, time=0;
 int tmp;
 string line, v; 

 fstream writecalculation;
 writecalculation.open("../data/calculation.txt", ios::app);
 writecalculation << "time[T] = distance/velocity[T]"  <<  endl;


 for(int i=0; i<(int)meter.size(); i++){
 
   fstream readfile;
   readfile.open("../data/info.txt" , ios::in);
   
     
   if(((int)meter.size()-1)==i)
       diff=1;
   else
       diff=meter[i+1]-meter[i];

   while(!getline(readfile, line).eof()){
           
           stringstream linestream(line);
           linestream >> tmp >> v ;
   
           if(tmp==(int)measured_temp[i]){
              double velocity=atof(v.c_str());
              timedummy=1/velocity; 
              time+=diff*timedummy;
              
             writecalculation << timedummy << " [" << measured_temp[i] << "°C] = 1 /" <<  velocity 
                               << endl;
              break;
              }
          }

    readfile.close();
    
 }
  writecalculation.close();

  days=time/(60*60*24);  
  
  fstream writefile;
  writefile.open("../data/result.txt", ios::app);
  writefile << "Radius[m]: " << r << endl;
  writefile << "Zeit[s]: " << time << endl;
  writefile << "Tage: " << days << endl;
  writefile << endl;
  writefile.close();

}