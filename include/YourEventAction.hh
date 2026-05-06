    #ifndef YourEventAction_hh
    #define YourEventAction_hh

    #include "G4UserEventAction.hh"

    class YourEventAction : public G4UserEventAction
    {
        public:
            YourEventAction();
            ~YourEventAction() override;

            void BeginOfEventAction(const G4Event*) override;
            void EndOfEventAction(const G4Event*) override;
    };

    #endif // YourEventAction_hh
