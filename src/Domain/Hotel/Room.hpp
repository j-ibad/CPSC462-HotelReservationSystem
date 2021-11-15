#pragma once

#include <unordered_map>
#include <vector>
#include <time.h>

#include "Domain/Reservation/Reservation.hpp"

namespace Domain::Hotel
{
  enum RoomType {
	  Standard,
	  Deluxe,
	  Joint,
	  Connecting,
	  Suite
  };
  static std::unordered_map<std::string,RoomType> const strToRoomType = {
	  {"Standard", RoomType::Standard},
	  {"Deluxe", RoomType::Deluxe},
	  {"Joint", RoomType::Joint},
	  {"Connecting", RoomType::Connecting},
	  {"Suite", RoomType::Suite} 
  };
  static const std::string roomTypeToStr[] = {"Standard", "Deluxe", "Joint", "Connecting", "Suite"};
  
  enum BedType {
	  Twin,
	  Queen,
	  King
  };
  static std::unordered_map<std::string,BedType> const strToBedType = {
	  {"Twin", BedType::Twin},
	  {"Queen",BedType::Queen},
	  {"King", BedType::King}
  };
  static const std::string bedTypeToStr[] = {"Twin", "Queen", "King"};
  
  class Room
  {
    public:
      // Constructors
	  Room();
	  Room(std::string roomID, double price, RoomType roomType, BedType bedType, int bedCount, std::string desc);
	
      // Operations
	  std::string getRoomID();
	  std::string serialize();
	  double getPrice();
	  bool isAvailable(time_t start, time_t end);
	  void reserve(Domain::Reservation::Reservation);
	  
     ~Room() noexcept;
	private:
	  std::string roomID;
	  double price;
	  int bedCount;
	  std::string desc;
	  BedType bedType;
	  RoomType roomType;
	  std::vector<Domain::Reservation::Reservation> reservedBy;
  }; // class Room


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline Room::~Room() noexcept {}

}  // namespace Domain::Hotel
