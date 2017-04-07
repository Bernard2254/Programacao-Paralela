#ifndef DLAITONCHRONOPERF_H
#define DLAITONCHRONOPERF_H

#include <chrono>

using namespace std::chrono;

long getNanoSec(){
	return high_resolution_clock::now().time_since_epoch().count(); 
}

long getMicroSec(){
	return high_resolution_clock::now().time_since_epoch().count()/1000; 
}

long getMiliSec(){
	return high_resolution_clock::now().time_since_epoch().count()/1000000; 
}

#endif /* DLAITONCHRONOPERF_H */