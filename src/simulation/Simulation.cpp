/*
 * Simulation.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: ashton
 */

#include "Simulation.h"

Simulation::Simulation(int size) {
	//Set initial variables
	temperature = .1;
	
	//Reset the simulation
	reset(size);
}

Simulation::~Simulation() {
	mutex.lock();
	condition.wakeOne();
	mutex.unlock();
	
	wait();
}

void Simulation::reset(int size){
	QMutexLocker locker(&mutex);
	
	//Set thread parameters
	paused = true;
	
	//Set simulation parameters
	this->size = size;
	step = 0;
	nodes.resize(size*size);
	
	//Re-initialize with nodes aimed in random directions
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());
	
	for ( uint i = 0 ; i < nodes.size() ; i++ ){
		nodes[i] = ((double)qrand()/(double)RAND_MAX)*2.0*M_PI;
	}
}

void Simulation::setPaused(bool shouldBePaused){
	QMutexLocker locker(&mutex);
	paused = shouldBePaused;
}

void Simulation::setTemperature(double temperature){
	QMutexLocker locker(&mutex);
	this->temperature = temperature;
}


void Simulation::run(){
	//Constant frames per second
	const int FPS = 30;
	
	//Tracker for last render time
	qint64 oldTime;
	
	//Timer for timing rendering
	QElapsedTimer timer;
	timer.start();
	oldTime = timer.elapsed();
	
	//The main loop of the thread
	forever{
		//Simulate when not paused
		if ( !paused ){
			mutex.lock();
			simulate();
			mutex.unlock();
		}
		
		//Check if it is time to render
		qint64 dt = timer.elapsed() - oldTime;
		if ( dt > 1000.0/FPS ){
			oldTime = timer.elapsed();
			
			//Render the image and update variable observers
			mutex.lock();
			updateRender();
			emit setMeasurements(paused, temperature, step);
			mutex.unlock();
			
			//Sleep for a short time to allow other threads to interact
			msleep(1);
		}
	}
}

void Simulation::simulate(){
	// number of flips to do on this pass
	const int FLIPS_PER_PASS = size*size;
	// Maximum offset of each angle
	const double MAX_DELTA_THETA = 0.5;
	
	for ( int flipCounter = 0 ; flipCounter < FLIPS_PER_PASS ; flipCounter++ ){
		//Get random node index in [0,size*size)
		int nodeIndex = qrand()%(size*size);
		
		//Create random offset angle
		double deltaTheta = 2.0*((double)qrand()/(double)RAND_MAX)-1.0;
		deltaTheta *= MAX_DELTA_THETA;
		
		//Calculate the difference in energy for the flip
		double hi = calcHi(nodeIndex);
		nodes[nodeIndex]+=deltaTheta;
		double hf = calcHi(nodeIndex);
		nodes[nodeIndex]-=deltaTheta;
		
		double delH = hf-hi;
		
		//Use the metropolis condition for determining if a flip should occur
		double random = (double)qrand()/(double)RAND_MAX;
		bool condition = random < exp( -delH/temperature );
		if ( delH < 0 || condition ){
			nodes[nodeIndex]+=deltaTheta;
		}
	}
	
	step++;
}

void Simulation::updateRender(){
	//Create an image where each pixel is a node of the simulation
	QImage image(QSize(size,size), QImage::Format_RGB32);
	for ( int y = 0 ; y<size ; y++ ){
		uint* scanLine = reinterpret_cast<uint *>(image.scanLine(y));
		for ( int x = 0 ; x < size ; x++ ){
			double theta = nodes[y*size+x];
			*scanLine++ = (uint) getColor(theta);
		}
	}
	//Signal any render observers of the new image
	emit render(image);
}

double Simulation::calcHi(int nodeIndex){
	double hi = 0.0;
	
	double theta = nodes[nodeIndex];
	for ( int i = 0 ; i < 4 ; i++ ){
		double thetaNgbh = getNeighbor(nodeIndex, i);
		hi += cos( theta - thetaNgbh );
	}
	
	return -hi;
}

double Simulation::getNeighbor(int nodeIndex, int ngbhIndex){
	int index [2] = {nodeIndex % size, nodeIndex / size};
	
	index[ngbhIndex/2] += 2*(ngbhIndex%2) - 1;
	if ( index[ngbhIndex/2] >= size ){ index[ngbhIndex/2] -= size; }
	if ( index[ngbhIndex/2] < 0 ){ index[ngbhIndex/2] += size; }
	
	return nodes[ index[0]+index[1]*size];
}

uint Simulation::getColor(double theta){
	while ( theta > 2.0*M_PI ){
		theta -= 2.0*M_PI;
	}
	while ( theta < 0 ){
		theta += 2.0*M_PI;
	}
	//Ratio of the full circle
	double ratio = theta/(2.0*M_PI);
	
	int r = 0, g = 0, b = 0;
	
	double a = (1.-ratio)*5;
	int x = (int) a;
	int y = (int) 255*(a-x);
	
	switch(x){
	case 0:
		r = 255; 	g = y; 		b = 0;
		break;
	case 1:
		r = 255-y; 	g = 255; 	b = 0;
		break;
	case 2:
		r = 0; 		g = 255;	b = y;
		break;
	case 3:
		r = 0; 		g = 255-y; 	b = 255;
		break;
	case 4:
		r = y; 		g = 0; 		b = 255;
		break;
	case 5:
		r = 255; 	g = 0;		b = 255-y;
		break;
	}
	return qRgb(r, g, b);
}
