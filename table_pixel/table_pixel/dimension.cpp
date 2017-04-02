#include "dimension.h"


Dimension::Dimension(){
}

Dimension::Dimension(int length, int number_of_cell, int each_border_length)	{
	reset(length, number_of_cell, each_border_length);
}

void Dimension::reset(int total_length, int cell, int border_length)	{
	total_length_ = total_length;
	cell_count_ = cell;
	border_length_ = border_length;

	start_position_.clear();
	
	int total_border_len = border_length_ * (cell_count_ - 1);
	int free_space_len = total_length_ - total_border_len;

	int estimated_cell_len = free_space_len / cell_count_;
	int extra_length = free_space_len % cell_count_;

	int processed_cell_length = 0;

	for (int i = 0; i < cell_count_;i++){
		start_position_.push_back(processed_cell_length);
		int current_cell_length = estimated_cell_len  + border_length_;
		if (extra_length){
			extra_length--;
			current_cell_length++;
		}

		processed_cell_length += current_cell_length;
	}
}

int Dimension::get_end_position(int cell_no){
	if (cell_no >= cell_count_){
		return INVALID_INDEX;
	}
	else if (cell_no == cell_count_ - 1){
		return total_length_ - 1;
	}
	return start_position_[cell_no + 1] - border_length_ - 1;
}

std::vector<int>& Dimension::get_start_positions(){
	return start_position_;
}

int Dimension::get_start_position(int cell_no){
	if (cell_no >= cell_count_){
		return INVALID_INDEX;
	}
	return start_position_[cell_no];
}

int Dimension::get_size(){
	return cell_count_;
}

int Dimension::get_border_length(){
	return border_length_;
}
