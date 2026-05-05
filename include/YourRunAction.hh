    #ifndef YourRunAction_hh
    #define YourRunAction_hh

    #include "G4UserRunAction.hh"

    class YourPrimaryGeneratorAction;

    class YourRunAction : public G4UserRunAction
    {
        public:
            YourRunAction(YourPrimaryGeneratorAction * pgenerator);
            ~YourRunAction() override;

            void BeginOfRunAction(const G4Run * ) override;
            void EndOfRunAction(const G4Run * ) override;

            void AddEventEdep(G4double val){fEdepInTarget+=val;}
    private:
        G4double fEdepInTarget{0};
        YourPrimaryGeneratorAction * fPrimaryGeneratorAction;

    };

    #endif // YourRunAction_hh
