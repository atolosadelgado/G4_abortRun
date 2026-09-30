    #include "YourEventAction.hh"
    #include "globals.hh"
    #include "G4Event.hh"
    
	#include "G4StateManager.hh"
	#include "G4ApplicationState.hh"
	#include "G4RunManager.hh"
	#include "G4MTRunManager.hh"

    YourEventAction::YourEventAction():
            G4UserEventAction(){}

    YourEventAction::~YourEventAction(){}

    void YourEventAction::BeginOfEventAction(const G4Event* evt){
        G4cout << "Begin Event action " << evt->GetEventID() << G4endl;
    }
	void YourEventAction::EndOfEventAction(const G4Event* evt)
	{
		// Get Geant4 state
		G4StateManager* stateManager = G4StateManager::GetStateManager();

		G4ApplicationState state;
		if (stateManager)
		{
			state = stateManager->GetCurrentState();
		}

		// Get master MT run manager, if available
		G4MTRunManager* runMasterMTManager =
			G4MTRunManager::GetMasterRunManager();

		std::string ifAborted = "Not applicable"; // serial

		if (runMasterMTManager)
		{
			ifAborted = runMasterMTManager->IfAborted()
					? "Run aborted"
					: "Run not aborted";
		}

		auto stateToStr = [](G4ApplicationState s)
		{
			switch (s)
			{
				case G4State_PreInit:    return "PreInit";
				case G4State_Init:       return "Init";
				case G4State_Idle:       return "Idle";
				case G4State_GeomClosed: return "GeomClosed";
				case G4State_EventProc:  return "EventProc";
				case G4State_Quit:       return "Quit";
				case G4State_Abort:      return "Abort";
				default:                 return "Unknown";
			}
		};

		G4cout << "End of Event action"
			<< " | eventID=" << (evt ? evt->GetEventID() : -1)
			<< " | aborted=" << (evt ? evt->IsAborted() : false)
			<< " | state=" << stateToStr(state)
			<< " | runManagerState=" << ifAborted
			<< G4endl;
	}
