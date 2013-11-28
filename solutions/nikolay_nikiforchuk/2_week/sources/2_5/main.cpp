#include <string>
#include <market_message.h>
#include <stdint.h>
#include <vector>

std::string in_file = BINARY_DIR "/2.5_example.in";
std::string out_file = BINARY_DIR "/2.4_example.out";
const static boost::uint32_t max_type_value = 100000;
static const boost::uint32_t buffer_size = 2048;

bool isAllowedType(binary_reader::market_message &message){
	return message.type() <= max_type_value;
}

boost::uint32_t getMessageSize(binary_reader::market_message &message){
	boost::uint32_t size = 0;
	return sizeof(message);
}

int main(){
	std::ifstream is(in_file, std::ifstream::binary);
	std::ofstream os(out_file, std::ofstream::binary);
	std::vector<boost::uint32_t> buffer_container(max_type_value, 0);
	boost::uint32_t *buffer = new boost::uint32_t[buffer_size];
	if (is){
		while (!is.eof()){
			binary_reader::market_message *message = new binary_reader::market_message(is);
			if (!is.eof() && isAllowedType(*message)){

			}
		}
	}
	delete[] buffer;
}
