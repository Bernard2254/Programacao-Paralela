#ifndef DLAITONPERF_H
#define DLAITONPERF_H

#include <time.h>

long getNanoTime(){
	return ((double)clock()/CLOCKS_PER_SEC)*1000000000; 
}

long getMicroTime(){
	return ((double)clock()/CLOCKS_PER_SEC)*1000000; 
}

long getMiliTime(){
	return ((double)clock()/CLOCKS_PER_SEC)*1000; 
}

long getTime(){
	return getMicroTime(); 
}

#endif /* DLAITONPERF_H */