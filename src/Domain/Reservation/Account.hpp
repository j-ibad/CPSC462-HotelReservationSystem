#pragma once

#include <unordered_map>
#include <vector>
#include "Domain/Reservation/ReservationHandler.hpp"
#include "Domain/Reservation/Reservation.hpp"
#include "Domain/Reservation/Transaction.hpp"

namespace Domain::Reservation
{
  class Account : public Domain::Reservation::ReservationHandler
  {
    public:
      // Constructors
	  Account();

      // Operations
	  double makePayment(std::string name, std::string addr, std::string email, CardType type, std::string cardNo, std::string expirationDate, int cvv) override;
	  void addReservation(Reservation res);
	  static Account* getInstance( std::string username );

      ~Account() noexcept override;
	  static std::unordered_map<std::string, Account*> guestAccounts;
	private:
	  std::vector<Reservation> reservations;
  }; // class Account


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline Account::~Account() noexcept{
	for(auto it = guestAccounts.begin(); it != guestAccounts.end(); ++it){
		delete (it->second);
	}
  }


}  // namespace Domain::Reservation
