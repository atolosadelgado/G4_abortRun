    #include "YourRunAction.hh"
    #include "G4Run.hh"
    #include "globals.hh"

	#include "G4StateManager.hh"
	#include "G4ApplicationState.hh"
	#include "G4RunManager.hh"
	#include "G4MTRunManager.hh"
		
    YourRunAction::YourRunAction():
            G4UserRunAction(){}

    YourRunAction::~YourRunAction(){}

    void YourRunAction::BeginOfRunAction(const G4Run *){
    	G4cout << "Begin run action" << G4endl;
    }

	void YourRunAction::EndOfRunAction(const G4Run* run)
	{
		int verbose = 0;

		if (verbose > 0)
		{
			G4StateManager* stateManager =
				G4StateManager::GetStateManager();

			G4MTRunManager* runMasterMTManager =
				G4MTRunManager::GetMasterRunManager();

			std::string ifAborted = "Not applicable"; // serial

			// Set ifAborted if running in MT
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

			// stateManager can be nullptr in MT mode
			const char* stateStr = stateManager
				? stateToStr(stateManager->GetCurrentState())
				: "Unknown";

			G4cout
				<< "End run action"
				<< " | runID=" << (run ? run->GetRunID() : -1)
				<< " | runManagerState=" << ifAborted
				<< " | Geant4State=" << stateStr
				<< G4endl;
		}
	}
