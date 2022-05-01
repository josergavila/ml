#ifndef _DATA_H
#define _DATA_H

#include <vector>
#include "stdint.h"
#include "stdio.h"

class Data {
	std::vector<uint8_t> *feature_vector;
	uint8_t label;
	int enum_label; // A -> 1, B -> 2, ...

	public:
	Data();
	~Data();
	void setFeatureVector(std::vector<uint8_t> *);
	void appendToFeatureVector(uint8_t);
	void setLabel(uint8_t);
	void setEnumeratedLabel(int);

	int getFeatureVectorSize();
	uint8_t getLabel();
	uint8_t getEnumeratedLabel();

	std::vector<uint8_t> * getFeatureVector();


};

#endif
