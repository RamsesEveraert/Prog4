#pragma once

namespace dae
{
    class Scene;
    class DemoSceneLoader
    {
    public:

        DemoSceneLoader();
        ~DemoSceneLoader() = default;

    private:
        void CreateBackground(Scene& scene);
        void CreateLogo(Scene& scene);
        void CreateTextObject(Scene& scene);
        void CreateFPSObject(Scene& scene);
        void CreateRotatingObjects(Scene& scene);
        void InputsExercice(Scene& scene);
        
    };
}



