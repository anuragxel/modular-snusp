#ifndef _SNUSP_H
#define _SNUSP_H

#define DATA_ARRAY_SIZE 30000
#define FUNCTION_STACK_SIZE 10000;

#include <bits/stdc++.h>

/*
    -------------- Modular SNUSP ---------------- 
    
    < LEFT - Move the data pointer left
    > RIGHT - Move the data pointer right
    + INCR - Increment the current data value by 1
    - DECR - Decrements the current data value by 1
    , READ - Read a byte into the current data cell from sysin
    . WRITE - Write a byte from the current data cell to sysout
    \ LURD - Move instruction pointer orientation according to the following rules:
        Up if going left
        Right if going down
        Down if going right
        Left if going up
    / RULD - Move instruction pointer orientation according to the following rules:
        Up if going right
        Left if going down
        Down if going left
        Right if going up
    ! SKIP - Move the instruction pointer forward one step
    ? SKIPZ _ Move the instruction pointer forward one step if the current memory cell is zero    
    @ ENTER - Push the current instruction pointer and orientation onto the stack
    # LEAVE - Pop the call stack and move the instruction pointer
    
    -------------- Optional - Bloated SNUSP ----------------
    : UP - Move the data pointer up
    ; DOWN - Move the data pointer down
    & SPLIT - Spawn a new thread and increment the parent thread's instruction pointer
    % RAND - Set the current data cell to a random value between 0 and the current value of the cell inclusively
*/

enum ptr_direction_t {UP, DOWN, LEFT, RIGHT};

class Snusp {
	protected:
		std::fstream program_file;
		std::array <char, DATA_ARRAY_SIZE> data;
		int data_ptr;
		std::vector< std::string > instruction;
		int inst_ptr_x;
		int inst_ptr_y;
		ptr_direction_t ptr_direction;
		std::vector< std::pair< std::pair<int, int>, ptr_direction_t > > function_stack;
	public:
		Snusp(std::string);
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
		char next_instruction();
		char current_instruction();
		void skip_inst();
		void skip_z_inst();
		void enter_function();
		void leave_function();
};
#endif
