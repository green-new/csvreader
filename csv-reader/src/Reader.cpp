/*
 * Reader.cpp
 *
 *  Created on: Apr 13, 2021
 *      Author: Green
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include "/include/CSVReader.hh"


/****************************************
 * Main functions
 ****************************************/

void print_records(std::vector<Record> records)
{
	for (unsigned int n = 0; n < records.size(); n++)
	{
		for (unsigned int m = 0; m < records[n].size(); m++)
		{
			std::cout << records[n][m] << ", ";
		}
		std::cout << std::endl;
	}
}

void print_record(Record record)
{
	for (unsigned int m = 0; m < record[m].size(); m++)
	{
		std::cout << record[m] << ", ";
	}
	std::cout << std::endl;
}

/****************************************
 * Reader class functions
 ****************************************/

Reader::Reader(std::string filenameIn, char customDelim)
{
	this->filename = filenameIn;
	this->delimiter = customDelim;
}

Reader::Reader(std::string filenameIn)
{
	this->filename = filenameIn;
	this->delimiter = ',';
}

void Reader::read_all(std::vector<Record> & everything)
{
	std::ifstream file (filename);
	std::string line;
	std::string token;
	Record record;
	std::vector<Record> values;

	if (file.is_open())
	{
		while (std::getline(file, line, '\n'))
		{
			record.clear();
			std::stringstream ss (line);

			while (std::getline(ss, token, this->delimiter))
			{
				record.push_back(token);
			}
			values.push_back(record);
		}
	}
	else
	{
		throw std::runtime_error("file not opened");
	}

	everything = values;

	file.close();
}

void Reader::read_row(Record & row)
{
	std::ifstream file (filename);
	std::string line;
	std::string token;
	Record values;

	if (file.is_open())
	{
		std::getline(file, line, '\n');
		std::stringstream ss (line);

		while (std::getline(ss, token, this->delimiter))
		{
			values.push_back(token);
		}
	}

	row = values;
	file.close();
}

void Reader::read_element(std::string element)
{
	std::ifstream file (filename);
	std::string line;
	std::string token;

	std::getline(file, token, this->delimiter);
}

std::vector<Record> Reader::sort_file(int index, std::string dataType, bool order, char delim)
{
	std::vector<Record> records;

	this->read_all(records);

	Compare cmp;

	cmp.index = index;
	cmp.order = order;
	cmp.dataType = dataType;
	std::sort(records.begin(), records.end(), cmp);

	return records;
}

std::vector<Record> Reader::sort_file(std::string columnName, std::string dataType, bool order, char delim)
{
	std::fstream file (filename);
	std::string header = "";
	std::string find = "";
	std::stringstream headerStream;
	int index = 0;
	// Get the index of the column to sort by
	if (!columnName.compare("none"))
	{
		std::getline(file, header);
		headerStream.str(header);
		while (std::getline(headerStream, find, delim) && find != columnName)
		{
			index++;
			if (headerStream.eof())
				index = 0; // Sort by the first record if not found
		}
		// Read in all records into records
		file.close();
		file.open(filename);
	}
	else
	{
		index = 0;
	}

	std::string recordBuffer;
	std::string fieldBuffer;
	std::vector<Record> records;

	this->read_all(records);

	// Sort by the element at the determined index
	// Requires sorting a 2-dimensional vector

	Compare cmp;

	cmp.index = index;
	cmp.order = order;
	cmp.dataType = dataType;
	std::sort(records.begin(), records.end(), cmp);
	file.close();

	return records;
}

size_t Reader::search_file(std::string searchToken, char delim)
{
	std::ifstream file (filename);
	std::string line;
	std::stringstream ss;

	for (size_t currentLine = 0; std::getline(file, line); currentLine++)
	{
	    if (line.find(searchToken) != std::string::npos)
	    {
	    	file.close();
	    	return currentLine;
	    }
	}
	file.close();
	return std::string::npos;
}

/****************************************
 * Writer class functions
 ****************************************/

Writer::Writer(std::string filenameIn, char customDelim)
{
	filename = filenameIn;
	delimiter = customDelim;
}

Writer::Writer(std::string filenameIn)
{
	filename = filenameIn;
	delimiter = ',';
}

void Writer::write_all(std::vector<Record> & everything)
{
	std::ofstream file;
	Record record;
	std::string entry;

	file.open(filename, std::ios_base::app);
	for (auto xit = everything.begin(); xit != everything.end(); xit++)
	{
		for (auto yit = record.begin(); yit != record.end(); yit++)
		{
			file << *yit;
			if (yit + 1 == record.end())
			{
				file << '\n';
			}
			else // usual, add commas
			{
				file << delimiter;
			}
		}
	}

	file.close();
}
void Writer::write_row(Record & row)
{
	std::ofstream file;
	std::string entry;

	file.open(filename, std::ios_base::app);
	for (auto xit = row.begin(); xit != row.end(); xit++)
	{
		file << *xit;
		if (xit + 1 == row.end())
		{
			file << '\n';
		}
		else // usual, add commas
		{
			file << delimiter;
		}
	}

	file.close();
}
