#pragma once
#include <memory>

namespace dae
{
    class Scene;
    class GameObject;
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
        void ExerciceLivesDisplay(Scene& scene);

        void BindControllerButtons(GameObject* player);
        void BindKeyboardKeys(GameObject* player);
        
    };
}



