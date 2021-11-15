#include "Domain/Reservation/BillingMethod.hpp"

namespace Domain::Reservation
{
	
	BillingMethod::BillingMethod(std::string cardHolder, std::string billingAddress, std::string billingEmail,
		CardType cardType, std::string cardNumber, std::string expiration, int cvv)
	: cardHolder(cardHolder), billingAddress(billingAddress), billingEmail(billingEmail),
		cardType(cardType), cardNumber(cardNumber), expiration(expiration), cvv(cvv) { }
}  // namespace Domain::Reservation
