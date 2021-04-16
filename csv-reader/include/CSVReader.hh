/*
 * CSVReader.hh
 *
 *  Created on: Apr 13, 2021
 *      Author: Green
 */

#ifndef CSVREADER_HH_
#define CSVREADER_HH_

#include <fstream>
#include <string>

typedef std::vector<std::string> Record;

struct Compare
{
	int index = 0;
	bool order = true;
	std::string dataType;
	bool operator()(Record & a, Record & b) const
	{
		if (order == true)
		{
			if (dataType.compare("number") == 0)
			{
				return std::stoi(a[index]) > std::stoi(b[index]);
			}
			else if (dataType.compare("alpha") == 0)
			{
				return std::lexicographical_compare(a[index].begin(), a[index].end(), b[index].begin(), b[index].end());
			}
			else
				return std::lexicographical_compare(a[index].begin(), a[index].end(), b[index].begin(), b[index].end());
		}
		else
		{
			if (dataType.compare("number") == 0)
			{
				return std::stoi(a[index]) < std::stoi(b[index]);
			}
			else if (dataType.compare("alpha") == 0)
			{
				return std::lexicographical_compare(b[index].begin(), b[index].end(), a[index].begin(), a[index].end());
			}
			else
				return std::lexicographical_compare(b[index].begin(), b[index].end(), a[index].begin(), a[index].end());
		}
		return std::lexicographical_compare(a[index].begin(), a[index].end(), b[index].begin(), b[index].end());
	}
};

/*******************************
 * Class declarations
 *******************************/

class Reader
{
private:
	std::string filename;
	char delimiter;
public:
	/* Constructor for custom delimiters. */
	Reader(std::string filenameIn, char customDelim);

	/* Default constructor requiring input file. */
	Reader(std::string filenameIn);

	/* Reads from the csv file based on params. */
	void read_all(std::vector<Record> & everything);
	void read_row(Record & row);
	void read_element(std::string element);

	/* Sorts the file by the order param and the specified column to order by.
	 * Returns the sorted list of records from the file.
	 * Order : true = ASC, false = DESC;*/
	std::vector<Record> sort_file(std::string columnName, std::string dataType, bool order, char delim);
	std::vector<Record> sort_file(int index, std::string dataType, bool order, char delim);

	/* Linearly searches through a file for a specific search token.
	 * Returns the line in the file where found.
	 * If the token is not found, std::string::npos is returned instead.
	 */
	size_t search_file(std::string searchToken, char delim);
};

class Writer
{
private:
	std::string filename;
	char delimiter;
public:
	/* Constructor */
	Writer(std::string filename);
	Writer(std::string filename, char customDelim);

	/* Writes to a csvfile based on the mode. */
	void write_all(std::vector<Record> & row);
	void write_row(Record & everything);
};

/*******************************
 * Functions (csv manipulation)
 *******************************/

/* Prints a single record. */
void print_record(Record record);

/* Prints a set of records. */
void print_records(std::vector<Record> records);

#endif /* CSVREADER_HH_ */
