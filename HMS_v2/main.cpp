#include "hotel.h"

int main(int argc,const char* argv[])
{
	Hotel& hotel = Hotel::getHotel();
	hotel.load(argv[1]);
	hotel.business();
}
