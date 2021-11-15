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

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"




namespace UI
{
  // Default constructor
  SimpleUI::SimpleUI()
  : _loggerPtr     ( TechnicalServices::Logging::LoggerHandler::create()            ),
    _persistentData( TechnicalServices::Persistence::PersistenceHandler::instance() ),
	_hotelHandler   ( std::make_unique<Domain::Hotel::Hotel>()                     )   // will replace these with factory calls in the next increment
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
		  **     parameters.
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
			std::vector<std::string> parameters( 5 );

			std::cout << " Room price:	";  std::cin >> std::ws;  std::getline( std::cin, parameters[0] );
			std::cout << " Room type:	";  std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
			std::cout << " Bed type:	";  std::cin >> std::ws;  std::getline( std::cin, parameters[2] );
			std::cout << " Bed count:	";  std::cin >> std::ws;  std::getline( std::cin, parameters[3] );
			std::cout << " Room description:	";  std::cin >> std::ws;  std::getline( std::cin, parameters[4] );
			
			double price = std::stod(parameters[0]);
			Domain::Hotel::RoomType roomType = Domain::Hotel::strToRoomType.at(parameters[1]);
			Domain::Hotel::BedType bedType = Domain::Hotel::strToBedType.at(parameters[2]);
			int bedCount = std::stoi(parameters[3]);
			
			auto results = _hotelHandler->addHotelRoom(price, roomType, bedType, bedCount, parameters[4]);
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
			
			std::vector<std::string> parameters( 2 );

			std::cout << " Start date:	";  std::cin >> std::ws;  std::getline( std::cin, parameters[0] );
			std::cout << " End date:	";  std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
			
			struct tm startDate;
			struct tm endDate;
			strptime(parameters[0].c_str(), "%m/%d/%Y %H:%M", &startDate);
			strptime(parameters[1].c_str(), "%m/%d/%Y %H:%M", &endDate);
			
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
			//
		  }
		  else if( selectedCommand == "Make Payment" )
		  {
			//
		  }
		  else if( selectedCommand == "Another command" ) { /* ... */ }
		  else sessionControl->executeCommand( selectedCommand, {} );
		} while( true );
	} while (stayLoggedIn);

    _logger << "Ending session and terminating";
  }
}
