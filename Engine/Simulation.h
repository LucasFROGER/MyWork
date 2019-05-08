#ifndef _SIMULATION_H_
#define _SIMULATION_H_

namespace engine 
{
	class Engine; 
	namespace camera 
	{ 
		class FreeCamera;
	}

	namespace fenestration { class Window; }
	namespace scene_graph { class Scene; }
}

class Simulation
{
public:
	Simulation(engine::Engine* engine);
	~Simulation();

	void Init();
	void Update();
	void Exit();
	void Clear();

private:
	engine::Engine* m_engine;
	engine::scene_graph::Scene* mainScene;
	engine::camera::FreeCamera* m_editorCamera;
	engine::fenestration::Window* m_wnd;
	int m_width = 800, m_height = 600;
	bool m_cursorLock;

	void MoveCamera();
	void UsefulInputs(engine::scene_graph::Scene* mainScene);

};

#endif // !_SIMULATION_H_
