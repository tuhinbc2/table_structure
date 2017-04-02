#ifndef _TABLE_PIXEL_
#define _TABLE_PIXEL_

#include "dimension.h"

struct ObjDetails
{
	int x, y, width, height;
};

class TablePixel
{
public:
	TablePixel(int width, int height, int row, int column, int border_length);
	void reset(int width, int height, int row, int column, int border_length);
	int get_number_of_rows();
	int get_number_of_columns();
	int get_start_position(int row_no,int column_no, std::pair<int, int>* position);
	int get_end_position(int row_no,int column_no, std::pair<int, int>* position);
	int get_vertical_border_details(int border_no, ObjDetails *details);
	int get_horizontal_border_details(int border_no, ObjDetails *details);

private:
	Dimension x_,y_;
};

#endif //_TABLE_PIXEL_