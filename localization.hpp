#ifndef LOCALIZATION_HPP
#define LOCALIZATION_HPP

#include <stdio.h>
#include <iostream> 
#include <string> //for time
#include <iomanip> // for GPS I/O
#include <ctime> //for converting time
#include <sstream> //provides string stream classes
#include <unistd.h> //for syslog
#include <syslog.h> //for syslog
#include <assert.h> //for asserts
#include <cmath>  //for finding distances between coordinates

#include <libgpsmm.h> // for GPS




using namespace std; //won't compile stings without this

//add class to .h file when created to match style guide.
class LOCATION
{
  private:
  //the lat/long data is in DBUS_TYPE_DOUBLE but will not compile.
  // will convert when necessary.
  double latitude, longitude;
  string timeStamp;
  
  public:
  //funcitons LOCATION
  int saveGPSData(double, double, string);
  double gpsComp(double,double);
  LOCATION();
  ~LOCATION();
  
};



void trackGPS();



#endif
