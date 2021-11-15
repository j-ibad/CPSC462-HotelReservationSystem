#include "Domain/Reservation/Reservation.hpp"

namespace Domain::Reservation
{
	Reservation::Reservation() : Reservation(time(NULL), time(NULL)){}
	Reservation::Reservation(time_t start, time_t end)
	{
		this->start = start;
		this->end = end;
	}
	time_t Reservation::getStart(){ return start; }
	time_t Reservation::getEnd(){ return end; }
}  // namespace Domain::Reservation
