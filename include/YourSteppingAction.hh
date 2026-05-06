        #ifndef YourSteppingAction_hh
        #define YourSteppingAction_hh

        #include "G4UserSteppingAction.hh"

        class YourSteppingAction : public G4UserSteppingAction
        {
            public:
                YourSteppingAction();
                ~YourSteppingAction() override;

                void UserSteppingAction(const G4Step * step) override;
        };

        #endif // YourSteppingAction_hh
