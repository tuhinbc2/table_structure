#include <iostream>
#include <vector>

enum error_no{
	INVALID_INDEX = -1,
};

class Dimension
{
public:
	Dimension(int length, int number_of_block, int each_border_length)	{
		reset(length, number_of_block, each_border_length);
	}

	void reset(int total_length, int block, int border_length)	{
		total_length_ = total_length;
		block_count_ = block;
		border_length_ = border_length;

		start_position_.clear();
		
		int total_border_len = border_length_ * (block_count_ - 1);
		int free_space_len = total_length_ - total_border_len;

		int estimated_block_len = free_space_len / block_count_;
		int extra_length = free_space_len % block_count_;

		int processed_block_length = 0;

		for (int i = 0; i < block_count_;i++){
			start_position_.push_back(processed_block_length);
			int current_block_length = estimated_block_len  + border_length_;
			if (extra_length){
				extra_length--;
				current_block_length++;
			}

			processed_block_length += current_block_length;
		}
	}

	int get_end_position(int block_no){
		if (block_no >= block_count_){
			return INVALID_INDEX;
		}
		else if (block_no == block_count_ - 1){
			return total_length_ - 1;
		}
		return start_position_[block_no + 1] - border_length_ - 1;
	}

	std::vector<int>& get_start_positions(){
		return start_position_;
	}

	int get_start_position(int block_no){
		if (block_no >= block_count_){
			return INVALID_INDEX;
		}
		return start_position_[block_no];
	}
private:
	//in unit
	std::vector<int> start_position_;
	int border_length_;
	int total_length_;
	//////////////////////

	int block_count_;
};


class TablePixel
{
public:

private:
};


int main()
{
	Dimension x(100, 3, 10);
	std::vector<int> pos;
	pos = x.get_start_positions();
	for (int i = 0; i < pos.size();i++){
		printf("X: %d <---> %d\n", pos[i], x.get_end_position(i));
	}
	return 0;
}