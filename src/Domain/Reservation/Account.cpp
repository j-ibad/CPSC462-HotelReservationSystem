/*
 * Author: Josh Ibad
 * Class: CPSC 462 - 02, Thomas Bettens
 * Date: November 15, 2021 - Elaboration 1
 *
 * Project: Hotel Reservation System - E1
 */
 
#include "Domain/Reservation/Account.hpp"

namespace Domain::Reservation
{
	std::unordered_map<std::string, Account*> Account::guestAccounts{};
	
	Account::Account(){}
	
	double Account::makePayment(std::string name, std::string addr, std::string email, 
		CardType type, std::string cardNo, std::string expirationDate, int cvv)
	{
		
		BillingMethod bill{name, addr, email, type, cardNo, expirationDate, cvv };
		Reservation latestReservation;
		int i=reservations.size()-1;
		for(; i>=0; i--){
			if( !reservations[i].isActive() ){
				latestReservation = reservations[i];
				break;
			}
		}
		if(i >= 0){
			Transaction trans{bill, latestReservation};
			latestReservation.setActive( true );
			double paidBalance = latestReservation.getBalance();
			latestReservation.setBalance( 0 );
			return paidBalance;
		}
		return -1.0;
	}
	
	
	void Account::addReservation(Reservation res){ reservations.push_back(res); }
	
	Account* Account::getInstance( std::string username ){
		if( guestAccounts.find(username) == guestAccounts.end() ){
			guestAccounts.insert( { username, new Account() } );
		}
		return guestAccounts.at( username );
	}
}  // namespace Domain::Reservation
