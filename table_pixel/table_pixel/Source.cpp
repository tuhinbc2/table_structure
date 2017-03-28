#include <iostream>
#include <vector>

enum Constants{
	SUCCESS = 0,
	INVALID_INDEX = -1,

};

struct ObjDetails
{
	int x, y, width, height;
};

class Dimension
{
public:
	Dimension(){

	}

	Dimension(int length, int number_of_cell, int each_border_length)	{
		reset(length, number_of_cell, each_border_length);
	}

	void reset(int total_length, int cell, int border_length)	{
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

	int get_end_position(int cell_no){
		if (cell_no >= cell_count_){
			return INVALID_INDEX;
		}
		else if (cell_no == cell_count_ - 1){
			return total_length_ - 1;
		}
		return start_position_[cell_no + 1] - border_length_ - 1;
	}

	std::vector<int>& get_start_positions(){
		return start_position_;
	}

	int get_start_position(int cell_no){
		if (cell_no >= cell_count_){
			return INVALID_INDEX;
		}
		return start_position_[cell_no];
	}

	int get_size(){
		return cell_count_;
	}

	int get_border_length(){
		return border_length_;
	}
private:
	//in unit
	std::vector<int> start_position_;
	int border_length_;
	int total_length_;
	//////////////////////

	int cell_count_;
};


class TablePixel
{
public:
	TablePixel(int width, int height, int row, int column, int border_length){
		reset(width, height, row, column, border_length);
	}

	void reset(int width, int height, int row, int column, int border_length){
		x_.reset(width, column, border_length);
		y_.reset(height, row, border_length);
	}

	int get_number_of_rows(){
		return y_.get_size();
	}

	int get_number_of_columns(){
		return x_.get_size();
	}

	int get_start_position(int row_no,int column_no, std::pair<int, int>* position){
		int x = x_.get_start_position(column_no);
		int y = y_.get_start_position(row_no);

		if((x == INVALID_INDEX) || (y == INVALID_INDEX)){
			return INVALID_INDEX;
		}
		position->first = x;
		position->second = y;

		return SUCCESS;
	}
//ToDo: fix ambiguous order.
	int get_end_position(int row_no,int column_no, std::pair<int, int>* position){
		int x = x_.get_end_position(column_no);
		int y = y_.get_end_position(row_no);

		if((x == INVALID_INDEX) || (y == INVALID_INDEX)){
			return INVALID_INDEX;
		}
		position->first = x;
		position->second = y;

		return SUCCESS;
	}

	int get_vertical_border_details(int border_no, ObjDetails *details){
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

	int get_horizontal_border_details(int border_no, ObjDetails *details){
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
private:
	Dimension x_,y_;
};


int main()
{
	/*Dimension x(100, 10, 10);
	std::vector<int> pos;
	pos = x.get_start_positions();
	for (int i = 0; i < (int)pos.size();i++){
		printf("X: %d <---> %d\n", pos[i], x.get_end_position(i));
	}*/

	TablePixel table(100, 100, 3, 3, 10);
	std::pair<int, int> val;

	for (int i = 0; i < (int)table.get_number_of_rows();i++){
		for(int j = 0; j < (int)table.get_number_of_columns();j++){
			if(table.get_start_position(i, j, &val) == INVALID_INDEX) return (-1);
			printf("< (%d,%d) X:%2d Y:%2d ----->", i, j, val.first, val.second);

			if(table.get_end_position(i, j, &val) == INVALID_INDEX) return (-1);
			printf(" X:%2d Y:%2d >\n", val.first, val.second);
		}

		ObjDetails details;
		if(table.get_vertical_border_details(i, &details) == SUCCESS){
			printf("|| no: %d x:%d y:%d height:%d width:%d\n", i, details.x, details.y, details.height, details.width);
			if(table.get_horizontal_border_details(i, &details) == SUCCESS){
				printf("-- no: %d x:%d y:%d height:%d width:%d\n", i, details.x, details.y, details.height, details.width);
			}else{
				printf("-- no. invalid\n");
			}
		}else{
			printf("|| no. invalid\n");
		}
	}

	return 0;
}