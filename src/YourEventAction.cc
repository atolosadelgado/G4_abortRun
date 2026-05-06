    #include "YourEventAction.hh"
    #include "globals.hh"
    #include "G4Event.hh"

    YourEventAction::YourEventAction():
            G4UserEventAction(){}

    YourEventAction::~YourEventAction(){}

    void YourEventAction::BeginOfEventAction(const G4Event* evt){
        G4cout << "Begin Event action " << evt->GetEventID() << G4endl;
    }

    void YourEventAction::EndOfEventAction(const G4Event* evt){
        G4cout << "End of Event action " << evt->GetEventID() << G4endl;
    }
