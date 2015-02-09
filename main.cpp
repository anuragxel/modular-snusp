#include "SNUSP.h"

int main(int argc, char **argv) {
	try {
 		std::string str(argv[1]);
		Snusp *s = new Snusp(str);
		s->execute();	
		delete s;
	}
	catch(const std::logic_error e) {
		std::cerr << "Usage:\n\tsnuspInterpreter [filename]\n";
		return -1;
	}
	//catch() {
	//	return -1;
	//}	
	return 0;
}
