/*
 * Author: Josh Ibad
 * Class: CPSC 462 - 02, Thomas Bettens
 * Date: November 15, 2021 - Elaboration 1
 *
 * Project: Hotel Reservation System - E1
 */
 
#include "Domain/Reservation/Reservation.hpp"

namespace Domain::Reservation
{
	Reservation::Reservation() : Reservation(time(NULL), time(NULL)){}
	Reservation::Reservation(time_t start, time_t end)
	{
		this->start = start;
		this->end = end;
		active = false;
	}
	time_t Reservation::getStart(){ return start; }
	time_t Reservation::getEnd(){ return end; }
	bool Reservation::isActive(){ return active;}
	void Reservation::setActive(bool flag){ active = flag; }
	double Reservation::getBalance(){ return balance; }
	void Reservation::setBalance(double balance){ this->balance = balance; }
}  // namespace Domain::Reservation
