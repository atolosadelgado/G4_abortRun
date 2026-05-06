    #include "YourSteppingAction.hh"
    #include "G4RunManager.hh"

    YourSteppingAction::YourSteppingAction():
                G4UserSteppingAction()
                {}

    YourSteppingAction::~YourSteppingAction(){}

    void YourSteppingAction::UserSteppingAction(const G4Step * ){
        if( std::ifstream("abort_stepping").good() )
        {
            G4cout << "abort_stepping has been created, aborting" << G4endl;
            G4RunManager::GetRunManager()->AbortEvent();
            G4RunManager::GetRunManager()->AbortRun(true);
        }
    }
