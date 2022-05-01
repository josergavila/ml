#include "../include/data.hpp"

Data::Data()
{
	feature_vector = new std::vector<uint8_t>;
}

Data::~Data(){}

void Data::setFeatureVector(std::vector<uint8_t> *vect)
{
	feature_vector = vect;
}

void Data::appendToFeatureVector(uint8_t val)
{
	feature_vector->push_back(val);
}

void Data::setLabel(uint8_t val)
{
	label = val;
}

void Data::setEnumeratedLabel(int val)
{
	enum_label = val;
}

int Data::getFeatureVectorSize()
{
	return feature_vector->size();
}

uint8_t Data::getLabel()
{
	return label;
}

uint8_t Data::getEnumeratedLabel()
{
	return enum_label;
}

std::vector<uint8_t> * Data::getFeatureVector()
{
	return feature_vector;
}
