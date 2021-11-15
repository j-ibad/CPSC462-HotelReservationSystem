#include "Domain/Hotel/Hotel.hpp"

namespace Domain::Hotel
{
	std::string Room::getRoomID(){ return roomID; }
	
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
		
	}
}  // namespace Domain::Hotel
