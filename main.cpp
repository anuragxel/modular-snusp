#include "SNUSP.h"

int main(int argc, char **argv) {
	try {	
		if(argc < 6)
			throw std::logic_error("fuck it.");
 		std::string user_submission(argv[5]);
		std::string input_file(argv[2]);
		std::string output_file(argv[4]);
		Snusp *s = new Snusp(user_submission,input_file,output_file);
		s->execute();	
		delete s;
	}
	catch(const std::logic_error e) {
		std::cerr << "Usage:\n\tsnusp -i [input_file] -o [output_file] [user_submission]\n";
		return -1;
	}
	//catch() {
	//	return -1;
	//}	
	return 0;
}
