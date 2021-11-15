/*
 * Author: Josh Ibad
 * Class: CPSC 462 - 02, Thomas Bettens
 * Date: November 15, 2021 - Elaboration 1
 *
 * Project: Hotel Reservation System - E1
 */
 
#include "Domain/Session/Session.hpp"

#include <string>
#include <any>
#include <vector>

namespace  // anonymous (private) working area
{
  // 1)  First define all system events (commands, actions, requests, etc.)
  #define STUB(functionName)  std::any functionName( Domain::Session::SessionBase & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  // Stubbed for now
  STUB( help );
  STUB( getHotelRooms );
  STUB( addHotelRoom );
  STUB( getHotelRoom );
  STUB( getAvailableHotelRooms );
  STUB( reserveRoom );
  STUB( makePayment );
}    // anonymous (private) working area



namespace Domain::Session
{
  SessionBase::SessionBase( const std::string & description, const UserCredentials & credentials ) : _credentials( credentials ), _name( description )
  {
    _logger << "Session \"" + _name + "\" being used and has been successfully initialized";
  }

  SessionBase::~SessionBase() noexcept
  {
    _logger << "Session \"" + _name + "\" shutdown successfully";
  }


  std::vector<std::string> SessionBase::getCommands()
  {
    std::vector<std::string> availableCommands;
    availableCommands.reserve( _commandDispatch.size() );

    for( const auto & [command, function] : _commandDispatch ) availableCommands.emplace_back( command );

    return availableCommands;
  }


  std::any SessionBase::executeCommand( const std::string & command, const std::vector<std::string> & args )
  {
    std::string parameters;
    for( const auto & arg : args )  parameters += '"' + arg + "\"  ";
    _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

    auto it = _commandDispatch.find( command );
    if( it == _commandDispatch.end() )
    {
      std::string message = __func__;
      message += " attempt to execute \"" + command + "\" failed, no such command";

      _logger << message;
      throw BadCommand( message );
    }

    auto results = it->second( *this, args);

    if( results.has_value() )
    {
      // The type of result depends on function called.  Let's assume strings for now ...
      _logger << "Responding with: \"" + std::any_cast<const std::string &>( results ) + '"';
    }

    return results;
  }


  // 2) Now map the above system events to roles authorized to make such a request.  Many roles can request the same event, and many
  //    events can be requested by a single role.
  GuestSession::GuestSession( const UserCredentials & credentials ) : SessionBase( "Guest", credentials )
  {
    _commandDispatch = { {"Help", help},
                         {"Get Available Hotel Rooms", getAvailableHotelRooms},
                         {"Get Hotel Room", getHotelRoom},
                         {"Reserve Room", reserveRoom},
                         {"Make Payment", makePayment}
						};
  }


  ManagementSession::ManagementSession( const UserCredentials & credentials ) : SessionBase( "Management", credentials )
  {
    _commandDispatch = { {"Help",       help},
                         {"Get Hotel Rooms", getHotelRooms},
                         {"Get Hotel Room", getHotelRoom}, 
                         {"Add Hotel Room", addHotelRoom}
						};
  }
}    // namespace Domain::Session
