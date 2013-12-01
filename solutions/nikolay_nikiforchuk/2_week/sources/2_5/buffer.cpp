#include "buffer.h"

buffer::buffer(boost::uint32_t size){
	init_size = size;
}

bool buffer::write(binary_reader::market_message &message){
	if (current_time < message.time()){
		current_time = message.time();
		clear();
	}

	boost::uint32_t message_size = sizeof(message);
	if (size_in_use + message_size < init_size){
		message_count++;
		size_in_use = size_in_use + message_size;
		return true;
	}
	return false;
}

boost::uint32_t buffer::count(){
	return message_count;
}

void buffer::clear(){
	size_in_use = 0;
}

buffer::~buffer(){
}