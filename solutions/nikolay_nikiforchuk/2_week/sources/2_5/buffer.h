#include <fstream>
#include <boost/cstdint.hpp>
#include <market_message.h>
#include <vector>

class buffer {
private:
	boost::uint32_t size_in_use = 0;
	boost::uint32_t message_count = 0;
	boost::uint32_t init_size = 2048;
	boost::uint32_t current_time = 0;

public:
	explicit buffer();
	bool write(binary_reader::market_message &message);
	boost::uint32_t count();
	void clear();
	~buffer();
};