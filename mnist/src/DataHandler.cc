#include "../include/DataHandler.hpp"
#include <iostream>
#include <algorithm>

DataHandler::DataHandler()
{
	dataArray = new std::vector<Data *>;
	trainingData = new std::vector<Data *>;
	trainingData = new std::vector<Data *>;
	validationData = new std::vector<Data *>;
}

DataHandler::~DataHandler()
{
	/* FREE Dynamically Allocated Data */
}

void DataHandler::readInputData(std::string path)
{
	uint32_t header[4]; // MAGIC|NUM IMAGES|ROWSIZE|COLSIZE
	unsigned char bytes[4];
	FILE *f = fopen(path.c_str(), "r");
	if(f) 
	{
		for (int i = 0; i < 4; i++)
		{
			if (fread(bytes, sizeof(bytes), 1, f))
			{
				header[i] = format(bytes);

			}
		}
		printf("Done getting input file header.\n");
		int image_size = header[2]*header[3];
		for (int i = 0; i < header[1]; i++) 
		{
			Data *d = new Data();
			uint8_t element[1];
			for (int j = 0; j < image_size; j++) 
			{
				if (fread(element, sizeof(element), 1, f))
				{

					d->appendToFeatureVector(element[0]);
				} else 
				{
					printf("Error reading from file.\n");
					exit(1);
				}
			}
			dataArray->push_back(d);
		}
		printf("Succesfully read and stored %lu feature vectors.\n", dataArray->size());
	} else 
	{
		printf("Could not find file.\n");
		exit(1);
	}
}

void DataHandler::readLabelData(std::string path)
{
	uint32_t header[2]; // MAGIC|NUM IMAGES
	unsigned char bytes[4];
	FILE *f = fopen(path.c_str(), "r");
	if(f) 
	{
		for (int i = 0; i < 2; i++)
		{
			if (fread(bytes, sizeof(bytes), 1, f))
			{
				header[i] = format(bytes);

			}
		}
		printf("Done getting label file header.\n");
		for (int i = 0; i < header[1]; i++) 
		{
			uint8_t element[1];
			if (fread(element, sizeof(element), 1, f))
			{
				dataArray->at(i)->setLabel(element[0]);
			} else  
			{
				printf("Error reading from file.\n");
				exit(1);
			}
		}
		printf("Succesfully read and stored %lu labels.\n", dataArray->size());
	} 
	else 
	{
		printf("Could not find file.\n");
		exit(1);
	}
}

void DataHandler::splitData()
{
	std::unordered_set<int> used_indexes;
	int train_size = dataArray->size() * TRAIN_SET_PERCENT;
	int test_size = dataArray->size() * TEST_SET_PERCENT;
	int valid_size = dataArray->size() * VALIDATION_SET_PERCENT;

	std::random_shuffle(dataArray->begin(), dataArray->end());
	
	/* TRAINING DATA */
	int count = 0;
	int index = 0;
	while(count < train_size)
	{
		trainingData->push_back(dataArray->at(index++));
		count++;
	}

	/* TEST DATA */
	count = 0;
	while(count < test_size)
	{
		testData->push_back(dataArray->at(index++));
		count++;
	}

	/* VALIDATION DATA */
	count = 0;
	while(count < valid_size)
	{
		validationData->push_back(dataArray->at(index++));
		count++;
	}

	printf("Training Data Size %lu.\n", trainingData->size());
	printf("Test Data Size %lu.\n", testData->size());
	printf("Validation Data Size %lu.\n", validationData->size());
}

void DataHandler::countClasses()
{
	int count = 0;
	for(unsigned i = 0; i < dataArray->size(); i++)
	{
		if(classFromInt.find(dataArray->at(i)->getLabel()) == classFromInt.end())
		{
			classFromInt[dataArray->at(i)->getLabel()] = count;
			dataArray->at(i)->setEnumeratedLabel(count);
			count++;
		} else
		{
			dataArray->at(i)->setEnumeratedLabel(classFromInt[dataArray->at(i)->getLabel()]);
		}
	}
	class_counts = count;
	/* for(Data *data : *dataArray) */
	/* 	data->setClassVector(class_counts); */
	printf("Succesfully extracted %d unique classes.\n", class_counts);
}

uint32_t DataHandler::format(const unsigned char* bytes)
{
	return (uint32_t) ((bytes[0] << 24)  | 
						(bytes[1] << 16) |
						(bytes[2] << 8)  |
						(bytes[3]));

}

std::vector<Data *> * DataHandler::getTrainingData()
{
	return trainingData;
}

std::vector<Data *> * DataHandler::getTestData()
{
	return testData;
}

std::vector<Data *> * DataHandler::getValidationData()
{
	return validationData;
}

int main()
{
	DataHandler *dh = new DataHandler();
	dh->readInputData("./train-images.idx3-ubyte");
	dh->readLabelData("./train-labels.idx1-ubyte");
	dh->splitData();
	dh->countClasses();

}
