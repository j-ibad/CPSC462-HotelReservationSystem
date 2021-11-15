#pragma once

#include <string>
#include <unordered_map>

namespace Domain::Reservation
{
  enum CardType {
	  Visa,
	  MasterCard,
	  American_Express,
	  Discover
  };
  static std::unordered_map<std::string,CardType> const strToCardType = {
	  {"Visa", CardType::Visa},
	  {"MasterCard", CardType::MasterCard},
	  {"American_Express", CardType::American_Express},
	  {"Discover", CardType::Discover} 
  };
  static const std::string cardTypeToStr[] = {"Visa", "MasterCard", "American_Express", "Discover"};
  
  
  class BillingMethod
  {
    public:
      // Constructors
	  BillingMethod(std::string cardHolder, std::string billingAddress, std::string billingEmail,
		CardType cardType, std::string cardNumber, std::string expiration, int cvv);
	
      // Operations
	  
     ~BillingMethod() noexcept;
	private:
	  std::string cardNumber;
	  std::string expiration;
	  int cvv;
	  std::string cardHolder;
	  std::string billingAddress;
	  std::string billingEmail;
	  CardType cardType;
  }; // class BillingMethod


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline BillingMethod::~BillingMethod() noexcept {}

}  // namespace Domain::Reservation
