    #include "YourRunAction.hh"
    #include "globals.hh"

    YourRunAction::YourRunAction():
            G4UserRunAction(){}

    YourRunAction::~YourRunAction(){}

    void YourRunAction::BeginOfRunAction(const G4Run *){
    	G4cout << "Begin run action" << G4endl;
    }

    void YourRunAction::EndOfRunAction(const G4Run *){
        G4cout << "End run action" << G4endl;
    }
