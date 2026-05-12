    #include "YourEventAction.hh"
    #include "globals.hh"
    #include "G4Event.hh"
    
		#include "G4StateManager.hh"
		#include "G4ApplicationState.hh"
		
    YourEventAction::YourEventAction():
            G4UserEventAction(){}

    YourEventAction::~YourEventAction(){}

    void YourEventAction::BeginOfEventAction(const G4Event* evt){
        G4cout << "Begin Event action " << evt->GetEventID() << G4endl;
    }

    void YourEventAction::EndOfEventAction(const G4Event* evt){
	    			auto stateManager = G4StateManager::GetStateManager();
						auto state = stateManager->GetCurrentState();

						auto stateToStr = [](G4ApplicationState s)
						{
								switch(s)
								{
										case G4State_PreInit:      return "PreInit";
										case G4State_Init:         return "Init";
										case G4State_Idle:         return "Idle";
										case G4State_GeomClosed:   return "GeomClosed";
										case G4State_EventProc:    return "EventProc";
										case G4State_Quit:         return "Quit";
										case G4State_Abort:        return "Abort";
										default:                   return "Unknown";
								}
						};
            G4cout<< "End of Event action"
									<< " | eventID=" << (evt ? evt->GetEventID() : -1)
									<< " | aborted=" << (evt ? evt->IsAborted() : false)
									<< " | state=" << stateToStr(state)
									<< G4endl;
    }
