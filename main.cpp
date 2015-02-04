#include "SNUSP.h"

int main(int argc, char **argv) {
	std::string str(argv[1]);
	Snusp *s = new Snusp(str);
	s->execute();	
	delete s;
	return 0;
}
