/*
 * Author: Josh Ibad
 * Class: CPSC 462 - 02, Thomas Bettens
 * Date: November 15, 2021 - Elaboration 1
 *
 * Project: Hotel Reservation System - E1
 */
 
#include "Domain/Hotel/Hotel.hpp"

namespace Domain::Hotel
{
	std::string Room::getRoomID(){ return roomID; }
	double Room::getPrice(){ return price; }
	void Room::reserve(Domain::Reservation::Reservation reservation){
		reservedBy.push_back(reservation);
	}
	
	Room::Room()
	 : roomID(""), price(0.0), roomType(Standard), bedType(Twin), bedCount(0), desc(""){}
	 
	Room::Room(std::string roomID, double price, RoomType roomType, BedType bedType, int bedCount, std::string desc)
	 : roomID(roomID), price(price), roomType(roomType), bedType(bedType), bedCount(bedCount), desc(desc){}
	 
	std::string Room::serialize(){
		std::string roomStr = "{roomID: " + roomID + ", ";
		roomStr += "price: $" + std::to_string(price) + ", ";
		roomStr += "roomType: " + roomTypeToStr[ roomType ] + ", ";
		roomStr += "bedType: " + bedTypeToStr[ bedType ] + ", ";
		roomStr += "bedCount: " + std::to_string(bedCount) + ", ";
		return roomStr + "desc: " + desc + "}";
	}
	
	bool Room::isAvailable(time_t start, time_t end){
		for(auto& res: reservedBy){
			if( (start < res.getEnd() && start > res.getStart()) ||
				(end < res.getEnd() && end > res.getStart())
			){
				return false;
			}
		}
		return true;
	}
}  // namespace Domain::Hotel
