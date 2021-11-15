/*
 * Author: Josh Ibad
 * Class: CPSC 462 - 02, Thomas Bettens
 * Date: November 15, 2021 - Elaboration 1
 *
 * Project: Hotel Reservation System - E1
 */
 
#include "Domain/Reservation/BillingMethod.hpp"

namespace Domain::Reservation
{
	
	BillingMethod::BillingMethod(std::string cardHolder, std::string billingAddress, std::string billingEmail,
		CardType cardType, std::string cardNumber, std::string expiration, int cvv)
	: cardHolder(cardHolder), billingAddress(billingAddress), billingEmail(billingEmail),
		cardType(cardType), cardNumber(cardNumber), expiration(expiration), cvv(cvv) { }
}  // namespace Domain::Reservation
