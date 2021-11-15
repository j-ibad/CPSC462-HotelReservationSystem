/*
 * Author: Josh Ibad
 * Class: CPSC 462 - 02, Thomas Bettens
 * Date: November 15, 2021 - Elaboration 1
 *
 * Project: Hotel Reservation System - E1
 */
 
#pragma once

#include <string>
#include <vector>
#include "Domain/Reservation/BillingMethod.hpp"

namespace Domain::Reservation
{
  // Library Package within the Domain Layer Abstract class
  class ReservationHandler
  {
    public:
      // Operations
      //   Work in progress ...
	  virtual double makePayment(std::string name, std::string addr, std::string email, CardType type, std::string cardNo, std::string expirationDate, int cvv) = 0;

      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~ReservationHandler() noexcept = 0;
  };    // class ReservationHandler





  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline ReservationHandler::~ReservationHandler() noexcept = default;


} // namespace Domain::Reservation
