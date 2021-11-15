#pragma once

#include "Domain/Hotel/HotelHandler.hpp"

namespace Domain::Hotel
{
  class Hotel : public Domain::Hotel::HotelHandler
  {
    public:
      // Constructors
      using HotelHandler::HotelHandler;  // inherit constructors

      // Operations
	  Domain::Reservation::Reservation reserveRoom(std::string roomID, time_t start, time_t end) override;
	  Room* getHotelRoom(std::string roomID) override;
	  std::string addHotelRoom(double price, RoomType roomType, BedType bedType, int bedCount, std::string desc) override;
	  std::vector<std::string> getHotelRooms() override;
	  std::vector<std::string> getAvailableHotelRooms(time_t start, time_t end) override;

     ~Hotel() noexcept override;
	private:
	  std::vector<Room> hotelRooms;
	  
	  char _roomIDSeedChar = 'A';
	  int _roomIDSeedInt = 1;
  }; // class Hotel


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline Hotel::~Hotel() noexcept{}


}  // namespace Domain::Hotel
