    #ifndef YourEventAction_hh
    #define YourEventAction_hh

    #include "G4UserEventAction.hh"
    #include "globals.hh"

    class YourRunAction;

    class YourEventAction : public G4UserEventAction
    {
        public:
            YourEventAction(YourRunAction * runAction);
            ~YourEventAction() override;

            void BeginOfEventAction(const G4Event*) override;
            void EndOfEventAction(const G4Event*) override;

            void AddEdep(G4double edep){fEdepPerEvent+=edep;}

        private:
            G4double fEdepPerEvent{0};
            YourRunAction * fRunAction;
    };

    #endif // YourEventAction_hh
