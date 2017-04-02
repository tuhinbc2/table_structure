#include "tablepixel.h"

TablePixel::TablePixel(int width, int height, int row, int column, int border_length){
	reset(width, height, row, column, border_length);
}

void TablePixel::reset(int width, int height, int row, int column, int border_length){
	x_.reset(width, column, border_length);
	y_.reset(height, row, border_length);
}

int TablePixel::get_number_of_rows(){
	return y_.get_size();
}

int TablePixel::get_number_of_columns(){
	return x_.get_size();
}

int TablePixel::get_start_position(int row_no,int column_no, std::pair<int, int>* position){
	int x = x_.get_start_position(column_no);
	int y = y_.get_start_position(row_no);

	if((x == INVALID_INDEX) || (y == INVALID_INDEX)){
		return INVALID_INDEX;
	}
	position->first = x;
	position->second = y;

	return SUCCESS;
}

int TablePixel::get_end_position(int row_no,int column_no, std::pair<int, int>* position){
	int x = x_.get_end_position(column_no);
	int y = y_.get_end_position(row_no);

	if((x == INVALID_INDEX) || (y == INVALID_INDEX)){
		return INVALID_INDEX;
	}
	position->first = x;
	position->second = y;

	return SUCCESS;
}

int TablePixel::get_vertical_border_details(int border_no, ObjDetails *details){
	int max_border_idx = x_.get_size() - 2;
	if(border_no > max_border_idx){
		return INVALID_INDEX;
	}

	std::pair<int, int> start_pos;
	get_end_position(y_.get_size() - 1, border_no, &start_pos);
	details->x = start_pos.first + 1;
	details->y = 0;
	details->width = y_.get_border_length();
	details->height = start_pos.second + 1 ;
	return SUCCESS;
}

int TablePixel::get_horizontal_border_details(int border_no, ObjDetails *details){
	int max_border_idx = y_.get_size() - 2;
	if(border_no > max_border_idx){
		return INVALID_INDEX;
	}

	std::pair<int, int> start_pos;
	get_end_position(border_no, x_.get_size() - 1, &start_pos);
	details->y = start_pos.second + 1;
	details->x = 0;
	details->height = x_.get_border_length();
	details->width = start_pos.first + 1 ;
	return SUCCESS;
}

int TablePixel::get_cell_details(int row_no,int column_no, ObjDetails *details){
	std::pair<int, int> start, end;
	if(get_start_position(row_no, column_no, &start) != SUCCESS){
		return INVALID_INDEX;
	}
	if(get_end_position(row_no, column_no, &end) != SUCCESS){
		return INVALID_INDEX;
	}

	details->x = start.first;
	details->y = start.second;

	details->height = end.second - start.second;
	details->width = end.first - start.first;

	return SUCCESS;
}