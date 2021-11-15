#include "Domain/Hotel/Hotel.hpp"

namespace Domain::Hotel
{
	Domain::Reservation::Reservation Hotel::reserveRoom(std::string roomID, time_t start, time_t end){
		auto hotelRoom = getHotelRoom(roomID);
		
		//Create reservation
		Domain::Reservation::Reservation reservation{start, end};
		
		//Calculate cost
		double stay_duration = difftime(end, start);
		int days_stay = ((int)stay_duration) / 86400;
		if( (int)stay_duration % 86400 > 0 ){
			days_stay++;
		}
		double balance = hotelRoom->getPrice() * days_stay;
		reservation.setBalance( balance );
		
		hotelRoom->reserve( reservation );
		
		return reservation;
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
			if(hotelRoom.isAvailable(start, end)){
				hotelRoomIDs.push_back(hotelRoom.getRoomID());
			}
		}
		return hotelRoomIDs;
	}
}  // namespace Domain::Hotel
