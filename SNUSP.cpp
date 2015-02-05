#ifndef _SNUSP_CPP
#define _SNUSP_CPP

#include "SNUSP.h"

Snusp::Snusp(std::string file_name) {
	this->program_file.open(file_name, std::ios::in);
	this->data.fill('\0');

	while(not program_file.eof()) {
		std::string temp;
		std::getline(program_file,temp);
		instruction.push_back(temp);
	}

	this->data_ptr = 0;
	
	this->inst_ptr_x = 0;
	this->inst_ptr_y = 0;
	
	for(unsigned int i=0;i< this->instruction.size() ;i++) {  // This is y.
		for(unsigned int j=0;j<instruction[i].size();j++) { // This is x.
			if(instruction[i][j] == '$') {
				this->inst_ptr_x = j;
				this->inst_ptr_y = i;
				break;
			}
		}
	}
	this->ptr_direction = RIGHT;
}

Snusp::~Snusp() {

}

void Snusp::data_ptr_left() {
	this->data_ptr++;
}

void Snusp::data_ptr_right() {
	this->data_ptr--;
}

void Snusp::incr_data() {
	this->data[this->data_ptr]++;
}

void Snusp::decr_data() {
	this->data[this->data_ptr]--;
}

void Snusp::read_into_data() {
	std::cin >> this->data[this->data_ptr];
}

void Snusp::write_out_data() {
	std::cout << this->data[this->data_ptr];
}

void Snusp::inst_lurd() {
	switch(this->ptr_direction) {
		case LEFT:
			this->ptr_direction = UP;
			break;
		case RIGHT:
			this->ptr_direction = DOWN;
			break;
		case DOWN:
			this->ptr_direction = RIGHT;
			break;
		case UP:
			this->ptr_direction = LEFT;
			break;
	}
}

void Snusp::inst_ruld() {
	switch(this->ptr_direction) {
		case RIGHT:
			this->ptr_direction = UP;
			break;
		case LEFT:
			this->ptr_direction = DOWN;
			break;
		case DOWN:
			this->ptr_direction = LEFT;
			break;
		case UP:
			this->ptr_direction = RIGHT;
			break;
	}	
}

void Snusp::move_ahead() {
	switch(this->ptr_direction) {
		case RIGHT:
			this->inst_ptr_x++;
			break;
		case DOWN:
			this->inst_ptr_y++;
			break;
		case LEFT:
			this->inst_ptr_x--;
			break;
		case UP:
			this->inst_ptr_y--;
			break;
	}
}

char Snusp::next_instruction() {
	switch(this->ptr_direction) {
		
		case RIGHT:
			try {
				return this->instruction.at(this->inst_ptr_y + 1).at(this->inst_ptr_x);
			}
			catch (const std::out_of_range& str) {
				std::cerr <<"ff 1";
				return '\0';
			}
			break;


		case DOWN:
			try {
				return this->instruction.at(this->inst_ptr_y).at(this->inst_ptr_x + 1);
			}
			catch (const std::out_of_range& str) {
				std::cerr <<"ff 2";
				return '\0';
			}
			break;


		case LEFT:
			try {
				return this->instruction.at(this->inst_ptr_y - 1).at(this->inst_ptr_x);
			}
			catch (const std::out_of_range& str) {
				std::cerr <<"ff 3";
				return '\0';
			}
			break;

		case UP:
			try {
				return this->instruction.at(this->inst_ptr_y).at(this->inst_ptr_x - 1);
			}
			catch (const std::out_of_range& str) {
				std::cerr <<"ff 4";
				return '\0';
			}
			break;
	}
	return '\0';
}

char Snusp::current_instruction() {
	try {
		return this->instruction.at(this->inst_ptr_y).at(this->inst_ptr_x);
	}
	catch (const std::out_of_range& str) {
		return '\0';
	}
}

void Snusp::skip_inst() {
	this->move_ahead();
}

void Snusp::skip_z_inst() {
	if(this->data[this->data_ptr] == 0) {
		this->move_ahead();
	}
}

void Snusp::enter_function() {
	this->function_stack.push_back( std::make_pair(std::make_pair(this->inst_ptr_x, this->inst_ptr_y), this->ptr_direction) );
}

void Snusp::leave_function() {
	try {
		auto temp = function_stack.back();
		this->inst_ptr_x = temp.first.first;
		this->inst_ptr_y = temp.first.second;
		this->ptr_direction = temp.second;
		this->move_ahead();
		function_stack.pop_back();
	}
	catch (const std::out_of_range& str) {
		exit(0);
	}
	
}

void Snusp::execute() {
	while(current_instruction() != '\0') {
		//std::cout << " Pos " << this->inst_ptr_x << " " << this->inst_ptr_y << std::endl;
		switch(current_instruction()) {
			case '<':
				this->data_ptr_left();
				break;
			case '>':
				this->data_ptr_right();
				break;
			case '+':
				this->incr_data();
				break;
			case '-':
				this->decr_data();
				break;
			case ',':
				this->read_into_data();
				break;
			case '.':
				this->write_out_data();
				break;
			case '\\':
				this->inst_lurd();
				break;
			case '/':
				this->inst_ruld();
				break;
			case '!':
				this->skip_inst();
				break;
			case '?':
				this->skip_z_inst();
				break;
			case '@':
				this->enter_function();
				break;
			case '#':
				this->leave_function();
				break;	
		}
		this->move_ahead();
	}	
}

#endif
