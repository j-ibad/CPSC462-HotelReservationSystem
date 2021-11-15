/*
 * Author: Josh Ibad
 * Class: CPSC 462 - 02, Thomas Bettens
 * Date: November 15, 2021 - Elaboration 1
 *
 * Project: Hotel Reservation System - E1
 */
 
#include "Domain/Reservation/Transaction.hpp"

namespace Domain::Reservation
{
	
	Transaction::Transaction(BillingMethod bill, Reservation res) : billing(bill), reservation(res) {
		paymentDate = time(NULL);
	}
}  // namespace Domain::Reservation
