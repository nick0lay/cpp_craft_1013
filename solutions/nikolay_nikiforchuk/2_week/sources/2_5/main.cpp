#include <iostream>
#include <fstream>
#include <string>
#include <market_message.h>
#include <stdint.h>
#include <vector>
#include "buffer.h"
#include <map>

std::string in_file = BINARY_DIR "/2.5_example.in";
std::string out_file = BINARY_DIR "/2.5_example.out";
const static boost::uint32_t max_type_value = 100000;
static const boost::uint32_t max_buffer_size = 2048;
static std::map<boost::uint32_t, buffer> buffers_container;

bool isAllowedType(binary_reader::market_message &message){
	return message.type() <= max_type_value;
}

int main(){
	std::ifstream is(in_file, std::ifstream::binary);
	std::ofstream os(out_file, std::ofstream::binary);
	boost::uint32_t current_time = 0;
	if (is){
		while (!is.eof()){
			binary_reader::market_message *message = new binary_reader::market_message(is);
			if (!is.eof() && isAllowedType(*message)){
				if (current_time < message->time()){
					current_time = message->time();
				}
				std::map<boost::uint32_t, buffer>::iterator it;
				it = buffers_container.find(message->type());
				if (it != buffers_container.end()){
					(*it).second.write(*message);
				}
				else {
					buffer *buf = new buffer(max_buffer_size);
					buf->write(*message);
					buffers_container.insert(std::pair<boost::uint32_t, buffer>(message->type(), *buf));
				}
			}
		}
		std::map<boost::uint32_t, buffer>::iterator it;
		it = buffers_container.begin();

		while (it != buffers_container.end()){
			boost::uint32_t type = (*it).first;
			double average = static_cast<double>((*it).second.count()) / static_cast<double>(current_time);
			os.write(reinterpret_cast<char*>(&type), sizeof(type));
			os.write(reinterpret_cast<char*>(&average), sizeof(average));
			it++;
		}
		is.close();
		os.close();
	}
	else {
		std::cout << "No input file found " << in_file << std::endl;
	}
}
