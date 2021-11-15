#pragma once

#include <time.h>

namespace Domain::Reservation
{
  class Reservation
  {
    public:
      // Constructors
	  Reservation();
	  Reservation(time_t start, time_t end);
	  
      // Operations
	  time_t getStart();
	  time_t getEnd();
	  
     ~Reservation() noexcept;
	private:
	  int reservationID;
	  time_t start;
	  time_t end;
	  bool active;
	  double balance;
	  
	  int _reserveSeed = 1;
  }; // class Reservation


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline Reservation::~Reservation() noexcept {}

}  // namespace Domain::Reservation
