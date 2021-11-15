#include "Domain/Hotel/Hotel.hpp"

namespace Domain::Hotel
{
	double Hotel::reserveRoom(std::string roomID, time_t start, time_t end){
		return 0.0;
	}
	
	Room* Hotel::getHotelRoom(std::string roomID){
		for(int i=0; i<hotelRooms.size(); i++){
			if(hotelRooms[i].getRoomID() == roomID){ return &(hotelRooms[i]); }
		}
		return nullptr;
	}
	
	std::string Hotel::addHotelRoom(double price, RoomType roomType, BedType bedType, int bedCount, std::string desc){
		std::string roomID = "";
		roomID += _roomIDSeedChar;
		roomID += std::to_string(_roomIDSeedInt++);
		Room newRoom = Room(roomID, price, roomType, bedType, bedCount, desc);
		hotelRooms.push_back(newRoom);
		return roomID;
	}
	
	std::vector<std::string> Hotel::getHotelRooms(){
		std::vector<std::string> hotelRoomIDs;
		for(Room& hotelRoom: hotelRooms){
			hotelRoomIDs.push_back(hotelRoom.getRoomID());
		}
		return hotelRoomIDs;
	}
	
	std::vector<std::string> Hotel::getAvailableHotelRooms(time_t start, time_t end){
		std::vector<std::string> placeholder;
		std::vector<std::string> hotelRoomIDs;
		for(Room& hotelRoom: hotelRooms){
			hotelRoomIDs.push_back(hotelRoom.getRoomID());
		}
		return hotelRoomIDs;
	}
}  // namespace Domain::Hotel
