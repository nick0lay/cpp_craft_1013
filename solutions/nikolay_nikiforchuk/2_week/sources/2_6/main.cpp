#include <string>
#include <iostream>
#include <fstream>
#include <stock_data.h>
#include <stdint.h>

std::string in_file = BINARY_DIR "/2.6_example.in";
std::string out_file = BINARY_DIR "/2.6_example.out";

int main()
{
	std::ifstream is(in_file, std::ifstream::binary);
	std::ofstream os(out_file, std::ofstream::binary);
	if (is){
		while (!is.eof()){
			binary_reader::stock_data *data = new binary_reader::stock_data(is);
			if (!is.eof()){
				data->write(os);
			}
		}
	} else {
		std::cout << "No input file found " << in_file << std::endl;
	}
	is.close();
	os.close();
}
