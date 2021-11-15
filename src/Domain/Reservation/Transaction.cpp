#include "Domain/Reservation/Transaction.hpp"

namespace Domain::Reservation
{
	
	Transaction::Transaction(BillingMethod bill, Reservation res) : billing(bill), reservation(res) {
		paymentDate = time(NULL);
	}
}  // namespace Domain::Reservation
