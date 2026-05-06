    #include "YourEventAction.hh"
    #include "globals.hh"

    YourEventAction::YourEventAction():
            G4UserEventAction(){}

    YourEventAction::~YourEventAction(){}

    void YourEventAction::BeginOfEventAction(const G4Event*){
        G4cout << "Begin event action" << G4endl;
    }

    void YourEventAction::EndOfEventAction(const G4Event*){
        G4cout << "End of Event action "
               << G4endl;
    }
