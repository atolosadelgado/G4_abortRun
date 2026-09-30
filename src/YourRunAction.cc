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

    void YourRunAction::EndOfRunAction(const G4Run * run){
        	  auto stateManager = G4StateManager::GetStateManager();
			  G4RunManager* runManager = G4RunManager::GetRunManager();
			  G4MTRunManager * runMasterMTManager = dynamic_cast<G4MTRunManager*>(G4MTRunManager::GetMasterRunManager());
			  std::string ifAborted="Not applicable"; // serial
			  // set ifAborted if running in MT
			  if(runMasterMTManager)
			  {
				if(runMasterMTManager->IfAborted())
					ifAborted="Run aborted";
				else
				    ifAborted="Run not aborted";
			  }

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

						// sometimes stateManager is nullptr in MT mode
						auto state_str = stateManager? stateToStr(stateManager->GetCurrentState()) : "";
						G4cout
								<< "End run action"
								<< " | runID=" << (run ? run->GetRunID() : -1)
								<< " | runManagerState=" << ifAborted.c_str()
								<< " | Geant4State=" << state_str
								<< G4endl;
    }
