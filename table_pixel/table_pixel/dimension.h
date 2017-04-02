#ifndef _DIMENSION_
#define _DIMENSION_

#include<vector>

enum Constants{
	SUCCESS = 0,
	INVALID_INDEX = -1,

};

class Dimension
{
public:
	Dimension();
	Dimension(int length, int number_of_cell, int each_border_length);
	void reset(int total_length, int cell, int border_length);
	int get_end_position(int cell_no);
	std::vector<int>& get_start_positions();
	int get_start_position(int cell_no);
	int get_size();
	int get_border_length();

private:
	//in unit
	std::vector<int> start_position_;
	int border_length_;
	int total_length_;
	//////////////////////

	int cell_count_;
};

#endif //_DIMENSION_
