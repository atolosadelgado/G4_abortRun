    #ifndef YourRunAction_hh
    #define YourRunAction_hh

    #include "G4UserRunAction.hh"


    class YourRunAction : public G4UserRunAction
    {
        public:
            YourRunAction();
            ~YourRunAction() override;

            void BeginOfRunAction(const G4Run * ) override;
            void EndOfRunAction(const G4Run * ) override;

    };

    #endif // YourRunAction_hh
