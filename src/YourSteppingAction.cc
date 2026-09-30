    #include "YourSteppingAction.hh"
    #include "G4RunManager.hh"
    #include "G4Threading.hh"
    #include "G4Run.hh"
    #include "G4Event.hh"
    #include "G4MTRunManager.hh"

    #include "G4StateManager.hh"
    #include "G4ApplicationState.hh"

    YourSteppingAction::YourSteppingAction():
                G4UserSteppingAction()
                {}

    YourSteppingAction::~YourSteppingAction(){}

    void YourSteppingAction::UserSteppingAction(const G4Step * step){
        if( std::ifstream("abort_stepping").good() )
        {
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

            auto rm = G4RunManager::GetRunManager();

            G4int tid = G4Threading::G4GetThreadId();
            G4bool isWorker = G4Threading::IsWorkerThread();

            auto run = rm->GetCurrentRun();
            G4int runID = run ? run->GetRunID() : -1;

            auto event = rm->GetCurrentEvent();
            G4int eventID = event ? event->GetEventID() : -1;

            G4cout << "Stepping Action Message: [ABORT] file detected | "
                << "threadID=" << tid
                << " (" << (isWorker ? "worker" : "master") << ")"
                << " | runID=" << runID
                << " | eventID=" << eventID
                << " | stepID=" << step->GetTrack()->GetCurrentStepNumber()
                << " | state=" << stateToStr(state)
                << " | fAbortCounter=" << fAbortCounter
                << G4endl;

            ++fAbortCounter;

            //rm->AbortEvent();
            //rm->AbortRun(true);
            G4MTRunManager::GetMasterRunManager()->AbortRun(false);
        }
    }
