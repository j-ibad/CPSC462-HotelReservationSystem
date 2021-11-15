#pragma once

#include <string>
#include <vector>
#include <ctime>

#include "Domain/Hotel/Room.hpp"

namespace Domain::Hotel
{
  // Library Package within the Domain Layer Abstract class
  class HotelHandler
  {
    public:
      // Operations
      //   Work in progress ...
	  virtual double reserveRoom(std::string roomID, time_t start, time_t end) = 0;
	  virtual Room* getHotelRoom(std::string roomID) = 0;
	  virtual std::string addHotelRoom(double price, RoomType roomType, BedType bedType, int bedCount, std::string desc) = 0;
	  virtual std::vector<std::string> getHotelRooms() = 0;
	  virtual std::vector<std::string> getAvailableHotelRooms(time_t start, time_t end) = 0;

      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~HotelHandler() noexcept = 0;

    protected:
      // Copy assignment operators, protected to prevent mix derived-type assignments
      HotelHandler & operator=( const HotelHandler &  rhs ) = default;  // copy assignment
      HotelHandler & operator=(       HotelHandler && rhs ) = default;  // move assignment
  };    // class HotelHandler





  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline HotelHandler::~HotelHandler() noexcept = default;


} // namespace Domain::Library
