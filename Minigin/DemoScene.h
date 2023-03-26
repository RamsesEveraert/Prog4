#pragma once

namespace dae
{
    class Scene;
    class DemoScene
    {
    public:

        DemoScene() = default;
        ~DemoScene() = default;

        void LoadDemoScene();

    private:
        void CreateBackground(Scene& scene);
        void CreateLogo(Scene& scene);
        void CreateTextObject(Scene& scene);
        void CreateFPSObject(Scene& scene);
        void CreateRotatingObjects(Scene& scene);
        void InputsExercice(Scene& scene);
        
    };
}



