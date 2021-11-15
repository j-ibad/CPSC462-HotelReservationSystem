/*
 * Author: Josh Ibad
 * Class: CPSC 462 - 02, Thomas Bettens
 * Date: November 15, 2021 - Elaboration 1
 *
 * Project: Hotel Reservation System - E1
 */
 
#pragma once

#include <string>
#include <time.h>
#include "Domain/Reservation/BillingMethod.hpp"
#include "Domain/Reservation/Reservation.hpp"

namespace Domain::Reservation
{
  class Transaction
  {
    public:
      // Constructors
	  Transaction(BillingMethod bill, Reservation res);
	
      // Operations
	  
     ~Transaction() noexcept;
	private:
	  time_t paymentDate;
	  BillingMethod billing;
	  Reservation reservation;
  }; // class Transaction


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline Transaction::~Transaction() noexcept {}

}  // namespace Domain::Reservation
