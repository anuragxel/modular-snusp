#ifndef _SNUSP_H
#define _SNUSP_H

#define DATA_ARRAY_SIZE 30000
#define FUNCTION_STACK_SIZE 10000;
#define TIME_LIMIT 2

#include <bits/stdc++.h>

enum ptr_direction_t {UP, DOWN, LEFT, RIGHT};

class Snusp {
	protected:
		std::fstream program_file;
		std::fstream input_file;
		std::fstream output_file;
		std::array <unsigned char, DATA_ARRAY_SIZE> data;
		int data_ptr;
		std::vector< std::string > instruction;
		int inst_ptr_x;
		int inst_ptr_y;
		ptr_direction_t ptr_direction;
		std::vector< std::pair< std::pair<int, int>, ptr_direction_t > > function_stack;
		time_t start_time;
	public:
		Snusp(std::string,std::string,std::string);
		~Snusp();
		void execute();
		void data_ptr_left();
		void data_ptr_right();
		void incr_data();
		void decr_data();
		void read_into_data();
		void write_out_data();
		void inst_lurd();
		void inst_ruld();
		void move_ahead();
		unsigned char current_instruction();
		void skip_inst();
		void skip_z_inst();
		void enter_function();
		void leave_function();
};
#endif
