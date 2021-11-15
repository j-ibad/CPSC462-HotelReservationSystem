#include "UI/SimpleUI.hpp"

#include <any>         // any_cast()
#include <iomanip>     // setw()
#include <iostream>    // streamsize
#include <limits>      // numeric_limits
#include <memory>      // unique_ptr, make_unique<>()
#include <string>      // string, getline()
#include <vector>
#include <time.h>

#include "Domain/Hotel/Hotel.hpp"
#include "Domain/Session/SessionHandler.hpp"
#include "Domain/Reservation/Account.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"




namespace UI
{
  // Default constructor
  SimpleUI::SimpleUI()
  : _loggerPtr     ( TechnicalServices::Logging::LoggerHandler::create()            ),
    _persistentData( TechnicalServices::Persistence::PersistenceHandler::instance() ),
	_hotelHandler   ( std::make_unique<Domain::Hotel::Hotel>() 						)
  {
    _logger << "Simple UI being used and has been successfully initialized";
  }




  // Destructor
  SimpleUI::~SimpleUI() noexcept
  {
    _logger << "Simple UI shutdown successfully";
  }




  // Operations
  void SimpleUI::launch() {
    // 1) Fetch Role legal value list
    std::vector<std::string> roleLegalValues = _persistentData.findRoles();


    // 2) Present login screen to user and get username, password, and valid role
    Domain::Session::UserCredentials credentials  = {"", "", {""}};           // ensures roles[0] exists
    auto &                           selectedRole = credentials.roles[0];     // convenience alias

    std::unique_ptr<Domain::Session::SessionHandler> sessionControl;

	bool stayLoggedIn;
	do {
		stayLoggedIn = false;
		do {
		  std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );

		  std::cout << "  name: ";
		  std::getline( std::cin, credentials.userName );

		  std::cout << "  pass phrase: ";
		  std::getline( std::cin, credentials.passPhrase );

		  unsigned menuSelection;
		  do  {
			for( unsigned i = 0; i != roleLegalValues.size(); ++i )   std::cout << std::setw( 2 ) << i << " - " << roleLegalValues[i] << '\n';
			std::cout << "  role (0-" << roleLegalValues.size()-1 << "): ";
			std::cin  >> menuSelection;
		  } while( menuSelection >= roleLegalValues.size() );

		  selectedRole = roleLegalValues[menuSelection];


		  // 3) Validate user is authorized for this role, and if so create session
		  sessionControl = Domain::Session::SessionHandler::createSession( credentials );
		  if( sessionControl != nullptr ) {
			_logger << "Login Successful for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";
			break;
		  }

		  std::cout << "** Login failed\n";
		  _logger << "Login failure for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";

		} while( true );


		// 4) Fetch functionality options for this role
		do {
		  auto        commands = sessionControl->getCommands();
		  std::string selectedCommand;
		  unsigned    menuSelection;

		  do {
			for( unsigned i = 0; i != commands.size(); ++i ) std::cout << std::setw( 2 ) << i << " - " << commands[i] << '\n';
			std::cout << std::setw( 2 ) << commands.size() << " - " << "Log out\n";
			std::cout << std::setw( 2 ) << commands.size()+1 << " - " << "Quit\n";

			std::cout << "  action (0-" << commands.size()+1 << "): ";
			std::cin >> menuSelection;
		  } while( menuSelection > commands.size()+1 );

		  if( menuSelection >= commands.size() ) 
		  {
			  if(menuSelection == commands.size()){
				stayLoggedIn = true;
				std::cout << "Logging out..." << std::endl << std::endl;
			  }
			  break;
		  }

		  selectedCommand = commands[menuSelection];
		  _logger << "Command selected \"" + selectedCommand + '"';


		  /******************************************************************************************************************************
		  **  5) The user interface will collect relevant information to execute the chosen command.  This section requires the UI to
		  **     know what information to collect, and hence what the available commands are.  Our goal is loose (minimal) coupling, not
		  **     no coupling. This can be achieved in a variety of ways, but one common way is to pass strings instead of strong typed
		  **     args.
		  ******************************************************************************************************************************/
		  if( selectedCommand == "Get Hotel Rooms" )
		  {
			auto results = _hotelHandler->getHotelRooms();
			std::string resultStr = "[";
			for(int i=0; i<results.size(); i++){
				resultStr += results[i];
				if(i<results.size()-1) { resultStr += ", "; }
			}
			resultStr += "]";
			_logger << "Received reply: \"" + resultStr+ '"';
		  }
		  else if( selectedCommand == "Add Hotel Room" )
		  {
			std::vector<std::string> args( 5 );

			std::cout << " Room price:	";  std::cin >> std::ws;  std::getline( std::cin, args[0] );
			std::cout << " Room type:	";  std::cin >> std::ws;  std::getline( std::cin, args[1] );
			std::cout << " Bed type:	";  std::cin >> std::ws;  std::getline( std::cin, args[2] );
			std::cout << " Bed count:	";  std::cin >> std::ws;  std::getline( std::cin, args[3] );
			std::cout << " Room description:	";  std::cin >> std::ws;  std::getline( std::cin, args[4] );
			
			double price = std::stod(args[0]);
			Domain::Hotel::RoomType roomType = Domain::Hotel::strToRoomType.at(args[1]);
			Domain::Hotel::BedType bedType = Domain::Hotel::strToBedType.at(args[2]);
			int bedCount = std::stoi(args[3]);
			
			auto results = _hotelHandler->addHotelRoom(price, roomType, bedType, bedCount, args[4]);
			_logger << "Received reply: \"" + results+ '"';
		  }
		  else if (selectedCommand == "Get Hotel Room")
		  {
			std::string param = "";
			std::cout << " Room ID:	";  std::cin >> std::ws;  std::getline( std::cin, param );
			
			auto room = _hotelHandler->getHotelRoom( param );
			_logger << "Received reply: \"" + room->serialize() + '"';
		  }
		  else if (selectedCommand == "Get Available Hotel Rooms")
		  {
			std::vector<std::string> args( 2 );

			std::cout << " Start date:	";  std::cin >> std::ws;  std::getline( std::cin, args[0] );
			std::cout << " End date:	";  std::cin >> std::ws;  std::getline( std::cin, args[1] );
			
			struct tm startDate;
			struct tm endDate;
			strptime(args[0].c_str(), "%m/%d/%Y %H:%M", &startDate);
			strptime(args[1].c_str(), "%m/%d/%Y %H:%M", &endDate);
			
			time_t start = mktime(&startDate);
			time_t end = mktime(&endDate);
			
			
			auto results = _hotelHandler->getAvailableHotelRooms(start, end);
			std::string resultStr = "[";
			for(int i=0; i<results.size(); i++){
				resultStr += results[i];
				if(i<results.size()-1) { resultStr += ", "; }
			}
			resultStr += "]";
			_logger << "Received reply: \"" + resultStr+ '"';
		  }
		  else if( selectedCommand == "Reserve Room" )
		  {
			std::vector<std::string> args( 3 );

			std::cout << " Room ID:	";  std::cin >> std::ws;  std::getline( std::cin, args[0] );
			std::cout << " Start date:	";  std::cin >> std::ws;  std::getline( std::cin, args[1] );
			std::cout << " End date:	";  std::cin >> std::ws;  std::getline( std::cin, args[2] );
			
			struct tm startDate;
			struct tm endDate;
			strptime(args[1].c_str(), "%m/%d/%Y %H:%M", &startDate);
			strptime(args[2].c_str(), "%m/%d/%Y %H:%M", &endDate);
			
			time_t start = mktime(&startDate);
			time_t end = mktime(&endDate);
			
			auto reservation = _hotelHandler->reserveRoom(args[0], start, end);
			
			Domain::Reservation::Account* _reservationHandler = Domain::Reservation::Account::getInstance( credentials.userName );
			_reservationHandler->addReservation( reservation );
			_logger << "Received reply: \"Total charges: $"+ std::to_string(reservation.getBalance()) + ".\"";
			//
		  }
		  else if( selectedCommand == "Make Payment" )
		  {
			std::vector<std::string> args( 7 );

			std::cout << " Cardholder Name:	";  std::cin >> std::ws;  std::getline( std::cin, args[0] );
			std::cout << " Billing Address:	";  std::cin >> std::ws;  std::getline( std::cin, args[1] );
			std::cout << " Billing Email:	";  std::cin >> std::ws;  std::getline( std::cin, args[2] );
			std::cout << " Card Type:		";  std::cin >> std::ws;  std::getline( std::cin, args[3] );
			std::cout << " Card Number:		";  std::cin >> std::ws;  std::getline( std::cin, args[4] );
			std::cout << " Expiration Date:	";  std::cin >> std::ws;  std::getline( std::cin, args[5] );
			std::cout << " CVV Code:		";  std::cin >> std::ws;  std::getline( std::cin, args[6] );
			
			auto cardType = Domain::Reservation::strToCardType.at(args[3]);
			int cvv = std::stoi(args[6]);
			
			Domain::Reservation::Account* _reservationHandler = Domain::Reservation::Account::getInstance( credentials.userName );
			auto res = _reservationHandler->makePayment( args[0], args[1], args[2], cardType, args[4], args[5], cvv);
			if(res >= 0.0){
				_logger << "Received reply: \"Room reserved succesfully. Card " + args[3] + "charges $"+ std::to_string(res) + ".\""; 
			}else{
				_logger << "Received reply: \"Transaction failed. Try to pay again.\""; 
			}
		  }
		  else if( selectedCommand == "Another command" ) { /* ... */ }
		  else sessionControl->executeCommand( selectedCommand, {} );
		} while( true );
	} while (stayLoggedIn);

    _logger << "Ending session and terminating";
  }
}
