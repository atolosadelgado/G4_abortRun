    #include "YourSteppingAction.hh"
    #include "G4RunManager.hh"
    #include "G4Threading.hh"
    #include "G4Run.hh"
    #include "G4Event.hh"

    YourSteppingAction::YourSteppingAction():
                G4UserSteppingAction()
                {}

    YourSteppingAction::~YourSteppingAction(){}

    void YourSteppingAction::UserSteppingAction(const G4Step * ){
        if( std::ifstream("abort_stepping").good() )
        {
            auto rm = G4RunManager::GetRunManager();

            G4int tid = G4Threading::G4GetThreadId();
            G4bool isWorker = G4Threading::IsWorkerThread();

            auto run = rm->GetCurrentRun();
            G4int runID = run ? run->GetRunID() : -1;

            auto event = rm->GetCurrentEvent();
            G4int eventID = event ? event->GetEventID() : -1;

            G4cout << "[ABORT] file detected | "
                << "threadID=" << tid
                << " (" << (isWorker ? "worker" : "master") << ")"
                << " | runID=" << runID
                << " | eventID=" << eventID
                << " | fAbortCounter=" << fAbortCounter
                << G4endl;

            ++fAbortCounter;

            rm->AbortEvent();
            rm->AbortRun(true);
        }
    }
