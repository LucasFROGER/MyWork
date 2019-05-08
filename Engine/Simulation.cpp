#include "stdafx.h"
#include "Simulation.h"

#include "Engine/ResourceManagement/Explorer.h"

#include "Engine/SceneGraph/GameObject.h"
#include "Engine/CustomMonoBehaviour/Old/MovableObject.h"
#include "Engine/CustomMonoBehaviour/Gameplay/Player.h"
#include "Engine/CustomMonoBehaviour/Managers/GUIMgr.h"
#include "Engine/CustomMonoBehaviour/Managers/GameMgr.h"
#include "Engine/CustomMonoBehaviour/Gameplay/Pickable.h"
#include "Engine/CustomMonoBehaviour/Gameplay/Reseter.h"
#include "Engine/CustomMonoBehaviour/Gameplay/SolidButton.h"
#include "Engine/CustomMonoBehaviour/Gameplay/Trap.h"
#include "Engine/CustomMonoBehaviour/Old/ObjectMover.h"
#include "Engine/Loader/Importer.h"



#include "Engine/Resource/Mesh.h"
#include "Engine/Resource/Texture.h"
#include "Engine/Resource/Shader.h"
#include "Engine/Resource/ShaderProgram.h"
#include "Engine/Resource/Material.h"

#include "Engine/Engine.h"


#include "Engine/Component/SpecificComponentWrapper.h"
#include "Engine/Component/TextRenderer.h"
#include "Engine/Component/Lights/DirectionnalLight.h"
#include "Engine/Component/Lights/PointLight.h"

using namespace engine::fenestration::input::keys;
using namespace engine;
using namespace engine::scene_graph;
using namespace engine::component;
using namespace engine::component::physic;
using namespace engine::core::maths;


float triangle[]
{
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

int index[]
{
	0, 1, 2
};

struct constBoeuf
{
	engine::core::maths::Mat4 wMat;
	engine::core::maths::Mat4 vpMat;
};

int triangleSize = sizeof(triangle);
int indexSize = sizeof(triangle);
constBoeuf boeuf{ { engine::core::maths::Mat4::CreateTranslationMatrix({ 0.0f, 0.0f, 5.0f, 1.0f })}, { engine::core::maths::Mat4::Identity()} };
float angle = 0.0f;
int childNb = 0;
int cbid = -1;
int count = 0;

Simulation::Simulation(engine::Engine* engine) :
	m_engine{ engine },
	m_cursorLock{ false }
{

}

Simulation::~Simulation()
{

}
engine::component::physic::CapsuleCollider* capsuleCollider;

void Simulation::Init()
{
	engine::rhi::RHI* rhi = m_engine->GetRHI();
	resource::ResourceMgr* resourceMgr = m_engine->GetResourceMgr();
	engine::resource_management::Explorer* explorer = m_engine->GetExplorer();
	engine::fenestration::WindowsWrapper* winWrap = m_engine->GetWindowsWrapper();
	engine::physic::PhysicMgr* physMgr = m_engine->GetPhysicMgr();
	m_wnd = winWrap->CreateWindow(m_width, m_height, "Window", false);

	m_editorCamera = new camera::FreeCamera((float)m_width, (float)m_height, 0.1f, 1000.f, 60.f, { 0.f,0.f, -10.f }, { 0.0f, 0.0f, 1.0f }, 0.01f, 0.0006f);
	m_wnd->SetClearColor(0.658824f, 0.811765f, 0.705882f, 1.0f);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	// Init

	resource::Folder* texturesFolder{ explorer->NewFolder(explorer->GetMainFolder(), "Textures") };
	resource::Folder* fontsFolder{ explorer->NewFolder(explorer->GetMainFolder(), "Fonts") };
	resource::Folder* shadersFolder{ explorer->NewFolder(explorer->GetMainFolder(), "Shaders") };

	// Load resources
	loader::Importer importer(resourceMgr, rhi);
	importer.Import("Data/OBJ/Cube.obj", explorer->GetMainFolder());
	importer.Import("Data/OBJ/Capsule.obj", explorer->GetMainFolder());
	importer.Import("Data/OBJ/CapUp.obj", explorer->GetMainFolder());
	importer.Import("Data/OBJ/CapCorp.obj", explorer->GetMainFolder());
	importer.Import("Data/OBJ/CapBot.obj", explorer->GetMainFolder());
	importer.Import("Data/OBJ/Sphere.obj", explorer->GetMainFolder());
	importer.Import("Data/OBJ/chara.obj", explorer->GetMainFolder());
	importer.Import("Data/FBX/ironman/IronManV3.obj", explorer->GetMainFolder());
	importer.Import("Data/Textures/braynzar.jpg", texturesFolder);
	importer.Import("Data/Textures/images.jpg", texturesFolder);
	importer.Import("Data/Textures/ironman.png", texturesFolder);
	importer.Import("Data/Textures/chara.png", texturesFolder);
	importer.Import("Data/Fonts/arial.fnt", fontsFolder);
	importer.Import("Data/Fonts/Chiller.fnt", fontsFolder);
	//importer.Import("Data/Fonts/arial.png", texturesFolder);
	//importer.Import("Data/Fonts/Chiller.png", texturesFolder);
	importer.Import("Data/Shaders/LightVertexShader.vs", shadersFolder);
	importer.Import("Data/Shaders/LightPixelShader.ps", shadersFolder);
	importer.Import("Data/Shaders/RedPixelShader.ps", shadersFolder);
	importer.Import("Data/Shaders/GreenPixelShader.ps", shadersFolder);
	importer.Import("Data/Shaders/BluePixelShader.ps", shadersFolder);
	importer.Import("Data/Shaders/PinkPixelShader.ps", shadersFolder);
	importer.Import("Data/Shaders/OrangePixelShader.ps", shadersFolder);
	importer.Import("Data/Shaders/BasicTextVertexShader.hlsl", shadersFolder);
	importer.Import("Data/Shaders/BasicTextPixelShader.hlsl", shadersFolder);


	// Get resources
	resource::Mesh* cubeMesh{ explorer->GetMainFolder()->GetMesh("Cube") };
	resource::Mesh* capsuleUpMesh{ explorer->GetMainFolder()->GetMesh("CapUp") };
	resource::Mesh* capsuleCorpMesh{ explorer->GetMainFolder()->GetMesh("CapCorp") };
	resource::Mesh* capsuleBotMesh{ explorer->GetMainFolder()->GetMesh("CapBot") };
	resource::Mesh* capsuleMesh{ explorer->GetMainFolder()->GetMesh("Capsule") };
	resource::Mesh* sphereMesh{ explorer->GetMainFolder()->GetMesh("Sphere") };
	resource::Mesh* charaMesh{ explorer->GetMainFolder()->GetMesh("chara") };
	resource::Mesh* ironManMesh{ explorer->GetMainFolder()->GetMesh("IronManV3") };
	resource::Texture* braynzarTexture{ texturesFolder->GetTexture("braynzar") };
	resource::Texture* imageTexture{ texturesFolder->GetTexture("images") };
	resource::Texture* ironmanTexture{ texturesFolder->GetTexture("ironman") };
	resource::Texture* charaTexture{ texturesFolder->GetTexture("chara") };
	//resource::Texture* arialTexture{ texturesFolder->GetTexture("arial") };
	//resource::Texture* chillerTexture{ texturesFolder->GetTexture("Chiller") };
	resource::Font* arialFont{ fontsFolder->GetFont("arial") };
	resource::Font* chillerFont{ fontsFolder->GetFont("Chiller") };
	resource::Shader* vertexShader{ shadersFolder->GetShader("LightVertexShader") };
	resource::Shader* pixelShader{ shadersFolder->GetShader("LightPixelShader") };
	resource::Shader* redPixelShader{ shadersFolder->GetShader("RedPixelShader") };
	resource::Shader* greenPixelShader{ shadersFolder->GetShader("GreenPixelShader") };
	resource::Shader* bluePixelShader{ shadersFolder->GetShader("BluePixelShader") };
	resource::Shader* orangePixelShader{ shadersFolder->GetShader("OrangePixelShader") };
	resource::Shader* pinkPixelShader{ shadersFolder->GetShader("PinkPixelShader") };
	resource::Shader* textVertexShader{ shadersFolder->GetShader("BasicTextVertexShader") };
	resource::Shader* textPixelShader{ shadersFolder->GetShader("BasicTextPixelShader") };

	// Make resources
	// shaders
	resource::ShaderProgram basicProgram(explorer->GetMainFolder()->GetAvailableName("basicProgram"));
	resource::ShaderProgram selectedProgram(explorer->GetMainFolder()->GetAvailableName("selectedProgram"));
	resource::ShaderProgram collProgram(explorer->GetMainFolder()->GetAvailableName("colliderProgram"));
	resource::ShaderProgram collTopProgram(explorer->GetMainFolder()->GetAvailableName("topColliderProgram"));
	resource::ShaderProgram collCorpProgram(explorer->GetMainFolder()->GetAvailableName("corpColliderProgram"));
	resource::ShaderProgram collBotProgram(explorer->GetMainFolder()->GetAvailableName("botColliderProgram"));
	resource::ShaderProgram textProgram(explorer->GetMainFolder()->GetAvailableName("TextProgram"));

	basicProgram.AddShader(vertexShader);
	basicProgram.AddShader(pixelShader);

	selectedProgram.AddShader(vertexShader);
	selectedProgram.AddShader(redPixelShader);

	collProgram.AddShader(vertexShader);
	collProgram.AddShader(greenPixelShader);

	collTopProgram.AddShader(vertexShader);
	collTopProgram.AddShader(bluePixelShader);

	collCorpProgram.AddShader(vertexShader);
	collCorpProgram.AddShader(pinkPixelShader);

	collBotProgram.AddShader(vertexShader);
	collBotProgram.AddShader(orangePixelShader);


	textProgram.AddShader(textVertexShader);
	textProgram.AddShader(textPixelShader);

	resource::ShaderProgram* basicProgramPtr{ resourceMgr->Add<resource::ShaderProgram>(basicProgram) };
	resource::ShaderProgram* selectedProgramPtr{ resourceMgr->Add<resource::ShaderProgram>(selectedProgram) };
	resource::ShaderProgram* collProgramPtr{ resourceMgr->Add<resource::ShaderProgram>(collProgram) };
	resource::ShaderProgram* collTopProgramPtr{ resourceMgr->Add<resource::ShaderProgram>(collTopProgram) };
	resource::ShaderProgram* collCorpProgramPtr{ resourceMgr->Add<resource::ShaderProgram>(collCorpProgram) };
	resource::ShaderProgram* collBotProgramPtr{ resourceMgr->Add<resource::ShaderProgram>(collBotProgram) };
	resource::ShaderProgram* textProgramPtr{ resourceMgr->Add<resource::ShaderProgram>(textProgram) };

	explorer->GetMainFolder()->Add(basicProgramPtr);
	explorer->GetMainFolder()->Add(selectedProgramPtr);
	explorer->GetMainFolder()->Add(collProgramPtr);
	explorer->GetMainFolder()->Add(collCorpProgramPtr);
	explorer->GetMainFolder()->Add(collTopProgramPtr);
	explorer->GetMainFolder()->Add(collBotProgramPtr);
	explorer->GetMainFolder()->Add(textProgramPtr);

	// materials
	resource::Material basicMaterial(explorer->GetMainFolder()->GetAvailableName("basicMaterial"));
	resource::Material ironmanMaterial(explorer->GetMainFolder()->GetAvailableName("ironmanMaterial"));
	resource::Material charaMaterial(explorer->GetMainFolder()->GetAvailableName("charaMaterial"));
	resource::Material imageMaterial(explorer->GetMainFolder()->GetAvailableName("imageMaterial"));
	resource::Material selectedMaterial(explorer->GetMainFolder()->GetAvailableName("selectedMaterial"));
	resource::Material collMaterial(explorer->GetMainFolder()->GetAvailableName("colliderMaterial"));
	resource::Material collTopMaterial(explorer->GetMainFolder()->GetAvailableName("colliderTopMaterial"));
	resource::Material collCorpMaterial(explorer->GetMainFolder()->GetAvailableName("colliderCorpMaterial"));
	resource::Material collBotMaterial(explorer->GetMainFolder()->GetAvailableName("colliderBotMaterial"));
	resource::Material arialMaterial(explorer->GetMainFolder()->GetAvailableName("arialMaterial"));
	resource::Material chillerMaterial(explorer->GetMainFolder()->GetAvailableName("chillerMaterial"));

	basicMaterial.SetShaderProgram(basicProgramPtr);
	ironmanMaterial.SetShaderProgram(basicProgramPtr);
	imageMaterial.SetShaderProgram(basicProgramPtr);
	charaMaterial.SetShaderProgram(basicProgramPtr);
	selectedMaterial.SetShaderProgram(selectedProgramPtr);
	collMaterial.SetShaderProgram(collProgramPtr);
	collTopMaterial.SetShaderProgram(collTopProgramPtr);
	collCorpMaterial.SetShaderProgram(collCorpProgramPtr);
	collBotMaterial.SetShaderProgram(collBotProgramPtr);
	arialMaterial.SetShaderProgram(basicProgramPtr);
	chillerMaterial.SetShaderProgram(basicProgramPtr);

	basicMaterial.Insert(0, braynzarTexture);
	ironmanMaterial.Insert(0, ironmanTexture);
	imageMaterial.Insert(0, imageTexture);
	charaMaterial.Insert(0, charaTexture);
	selectedMaterial.Insert(0, braynzarTexture);
	//arialMaterial.Insert(0, arialTexture);
	//chillerMaterial.Insert(0, chillerTexture);

	resource::Material* basicMaterialPtr{ resourceMgr->Add<resource::Material>(basicMaterial) };
	resource::Material* ironmanMaterialPtr{ resourceMgr->Add<resource::Material>(ironmanMaterial) };
	resource::Material* charaMaterialPtr{ resourceMgr->Add<resource::Material>(charaMaterial) };
	resource::Material* imageMaterialPtr{ resourceMgr->Add<resource::Material>(imageMaterial) };
	resource::Material* selectedMaterialPtr{ resourceMgr->Add<resource::Material>(selectedMaterial) };
	resource::Material* collMaterialPtr{ resourceMgr->Add<resource::Material>(collMaterial) };
	resource::Material* collTopMaterialPtr{ resourceMgr->Add<resource::Material>(collTopMaterial) };
	resource::Material* collCorpMaterialPtr{ resourceMgr->Add<resource::Material>(collCorpMaterial) };
	resource::Material* collBotMaterialPtr{ resourceMgr->Add<resource::Material>(collBotMaterial) };
	resource::Material* arialMaterialPtr{ resourceMgr->Add<resource::Material>(arialMaterial) };
	resource::Material* chillerMaterialPtr{ resourceMgr->Add<resource::Material>(chillerMaterial) };

	explorer->GetMainFolder()->Add(basicMaterialPtr);
	explorer->GetMainFolder()->Add(ironmanMaterialPtr);
	explorer->GetMainFolder()->Add(charaMaterialPtr);
	explorer->GetMainFolder()->Add(imageMaterialPtr);
	//explorer->GetMainFolder()->Add(basicMaterialPtr);
	explorer->GetMainFolder()->Add(selectedMaterialPtr);
	explorer->GetMainFolder()->Add(collMaterialPtr);
	explorer->GetMainFolder()->Add(collTopMaterialPtr);
	explorer->GetMainFolder()->Add(collCorpMaterialPtr);
	explorer->GetMainFolder()->Add(collBotMaterialPtr);
	explorer->GetMainFolder()->Add(arialMaterialPtr);
	explorer->GetMainFolder()->Add(chillerMaterialPtr);

	m_engine->GetPhysicMgr()->SetCapsuleMeshs(capsuleUpMesh, capsuleCorpMesh, capsuleBotMesh);
	m_engine->GetPhysicMgr()->SetCubeMesh(cubeMesh);
	m_engine->GetPhysicMgr()->SetSphereMesh(sphereMesh);
	m_engine->GetPhysicMgr()->SetPhysMaterial(collMaterialPtr);

	scene_graph::SceneMgr* sceneMgr = m_engine->GetSceneMgr();

	mainScene = sceneMgr->NewScene(explorer->GetMainFolder());
	sceneMgr->AddRenderWin(m_wnd->GetId());
	mainScene->SetEditorCamera(m_editorCamera);
	mainScene->GetPhysScene()->SetGravity(Vec3(0.f, -0.1f, 0.0f));
	sceneMgr->Add(mainScene);
	sceneMgr->Load(0);

	m_engine->GetLightMgr()->SetAmbientColor({ 1.f, 1.f, 1.f, 1.f });
	int id{ 0 };
	{
		mainScene->NewGameObject("Floor");
		GameObject* obj = mainScene->GetRoot()->GetChildren()[id];

		MeshRenderer* meshRenderer = obj->NewComponent<MeshRenderer>();
		CubeCollider* collider = obj->NewComponent<CubeCollider>();

		meshRenderer->SetMesh(cubeMesh);
		meshRenderer->SetMaterial(basicMaterialPtr);

		obj->GetTransform()->SetPosition(Vec3{ 0.f,-1.f,0.f });
		obj->GetTransform()->SetScale(Vec3{ 100.f,3.f,100.f });
		++id;
	}

	{
		mainScene->NewGameObject("Ceiling");
		GameObject* obj = mainScene->GetRoot()->GetChildren()[id];

		MeshRenderer* meshRenderer = obj->NewComponent<MeshRenderer>();
		CubeCollider* collider = obj->NewComponent<CubeCollider>();

		meshRenderer->SetMesh(cubeMesh);
		meshRenderer->SetMaterial(basicMaterialPtr);

		obj->GetTransform()->SetPosition(Vec3{ 0.f, 50.f,0.f });
		obj->GetTransform()->SetScale(Vec3{ 100.f,1.f,100.f });
		++id;
	}

	{
		mainScene->NewGameObject("Wall1");
		GameObject* obj = mainScene->GetRoot()->GetChildren()[id];

		MeshRenderer* meshRenderer = obj->NewComponent<MeshRenderer>();
		CubeCollider* collider = obj->NewComponent<CubeCollider>();

		meshRenderer->SetMesh(cubeMesh);
		meshRenderer->SetMaterial(basicMaterialPtr);

		obj->GetTransform()->SetPosition(Vec3{ 50.f,25.f,0.f });
		obj->GetTransform()->SetScale(Vec3{ 1.f,50.f,100.f });
		++id;
	}

	{
		mainScene->NewGameObject("Wall2");
		GameObject* obj = mainScene->GetRoot()->GetChildren()[id];

		MeshRenderer* meshRenderer = obj->NewComponent<MeshRenderer>();
		CubeCollider* collider = obj->NewComponent<CubeCollider>();

		meshRenderer->SetMesh(cubeMesh);
		meshRenderer->SetMaterial(basicMaterialPtr);

		obj->GetTransform()->SetPosition(Vec3{ -50.f,25.f,0.f });
		obj->GetTransform()->SetScale(Vec3{ 1.f,50.f,100.f });
		++id;
	}

	{
		mainScene->NewGameObject("Wall3");
		GameObject* obj = mainScene->GetRoot()->GetChildren()[id];

		MeshRenderer* meshRenderer = obj->NewComponent<MeshRenderer>();
		CubeCollider* collider = obj->NewComponent<CubeCollider>();

		meshRenderer->SetMesh(cubeMesh);
		meshRenderer->SetMaterial(basicMaterialPtr);

		obj->GetTransform()->SetPosition(Vec3{ 0.f ,25.f,50.f });
		obj->GetTransform()->SetScale(Vec3{ 100.f,50.f,1.f });
		++id;
	}

	{
		mainScene->NewGameObject("Wall4");
		GameObject* obj = mainScene->GetRoot()->GetChildren()[id];

		MeshRenderer* meshRenderer = obj->NewComponent<MeshRenderer>();
		CubeCollider* collider = obj->NewComponent<CubeCollider>();

		meshRenderer->SetMesh(cubeMesh);
		meshRenderer->SetMaterial(basicMaterialPtr);

		obj->GetTransform()->SetPosition(Vec3{ 0.f ,25.f,-50.f });
		obj->GetTransform()->SetScale(Vec3{ 100.f,50.f,1.f });
		++id;
	}

	{
		mainScene->NewGameObject("Player");
		GameObject* obj = mainScene->GetRoot()->GetChildren()[id];

		MeshRenderer* meshRenderer = obj->NewComponent<MeshRenderer>();
		CapsuleCollider* collider = obj->NewComponent<CapsuleCollider>();
		Rigidbody* rigidbody = obj->NewComponent<Rigidbody>();
		Player* player = obj->NewComponent<Player>();
		Reseter* reseter = obj->NewComponent<Reseter>();

		meshRenderer->SetMesh(ironManMesh);
		meshRenderer->SetMaterial(ironmanMaterialPtr);

		obj->GetTransform()->SetPosition(Vec3{ 0.f,1.f,0.f });
		obj->GetTransform()->SetRotation(Quaternion::Euler(Vec3{ 0.f,0.f,0.f }));
		obj->GetTransform()->SetScale(Vec3{ 1.f,1.f,1.f });
		++id;
	}

	{
		mainScene->NewGameObject("Pickable");
		GameObject* obj = mainScene->GetRoot()->GetChildren()[id];

		MeshRenderer* meshRenderer = obj->NewComponent<MeshRenderer>();
		CubeCollider* collider = obj->NewComponent<CubeCollider>();
		SphereCollider* trigger = obj->NewComponent<SphereCollider>();
		Rigidbody* rigidbody = obj->NewComponent<Rigidbody>();
		Pickable* pickable = obj->NewComponent<Pickable>();
		Reseter* reseter = obj->NewComponent<Reseter>();


		trigger->SetTrigger(true);
		trigger->SetRadius(5.f);

		meshRenderer->SetMesh(cubeMesh);
		meshRenderer->SetMaterial(charaMaterialPtr);

		obj->GetTransform()->SetPosition(Vec3{ 10.f,1.f,0.f });
		obj->GetTransform()->SetRotation(Quaternion::Euler(Vec3{ 0.f,0.f,0.f }));
		obj->GetTransform()->SetScale(Vec3{ 1.f,1.f,1.f });
		++id;
	}

	{
		mainScene->NewGameObject("Trap");
		GameObject* obj = mainScene->GetRoot()->GetChildren()[id];

		MeshRenderer* meshRenderer = obj->NewComponent<MeshRenderer>();
		CubeCollider* collider = obj->NewComponent<CubeCollider>();
		Reseter* reseter = obj->NewComponent<Reseter>();
		Trap* trap = obj->NewComponent<Trap>();

		trap->SetCompletedMaterial(selectedMaterialPtr);

		meshRenderer->SetMesh(cubeMesh);
		meshRenderer->SetMaterial(charaMaterialPtr);

		obj->GetTransform()->SetPosition(Vec3{ -10.f,0.7f,0.f });
		obj->GetTransform()->SetRotation(Quaternion::Euler(Vec3{ 0.f,0.f,0.f }));
		obj->GetTransform()->SetScale(Vec3{ 5.f,0.2f,5.f });
		++id;
	}

	//-----------------------
	{
		mainScene->NewGameObject("GameMgr");
	}
	GameMgr* gameMgr = mainScene->GetRoot()->GetChildren()[id]->NewComponent<GameMgr>();

	{	GameObject* obj = mainScene->GetRoot()->GetChildren()[id];
	++id;
	}
	//-----------------------
	{
		mainScene->NewGameObject("GUIMgr");
	}
	GUIMgr* guiMgr = mainScene->GetRoot()->GetChildren()[id]->NewComponent<GUIMgr>();
	{
		GameObject* obj = mainScene->GetRoot()->GetChildren()[id];
		TextRenderer* textInfoRenderer = obj->NewComponent<TextRenderer>();
		guiMgr->SetInfoTextRenderer(textInfoRenderer);

		textInfoRenderer->SetPosition({ 0.3f,0.3f });
		textInfoRenderer->SetPadding({ 0.f,0.f });
		textInfoRenderer->SetScale({ 1.f,1.f });
		textInfoRenderer->SetColor({ 1.f,1.f,1.f,1.f });
		textInfoRenderer->SetFont(chillerFont);
		textInfoRenderer->SetShaderProgram(textProgramPtr);
		++id;
	}
	//-----------------------

	{
		mainScene->NewGameObject("PauseMenu");
		TextRenderer* textRenderer = mainScene->GetRoot()->GetChildren()[id]->NewComponent<TextRenderer>();
		textRenderer->SetPosition({ 0.4f,0.3f });
		textRenderer->SetPadding({ 0.f,0.f });
		textRenderer->SetScale({ 2.f,2.f });
		textRenderer->SetColor({ 1.f,1.f,1.f,1.f });
		textRenderer->SetColor({ 1.f,1.f,1.f,1.f });
		textRenderer->SetFont(arialFont);
		textRenderer->SetShaderProgram(textProgramPtr);
	}
	Menu* menu = mainScene->GetRoot()->GetChildren()[id]->NewComponent<Menu>();
	guiMgr->SetPauseMenu(menu);
	++id;

	{
		mainScene->NewGameObject("Button1");
		GameObject* obj = mainScene->GetRoot()->GetChildren()[id];
		Button* button1 = obj->NewComponent<Button>();
		TextRenderer* textRenderer1 = obj->NewComponent<TextRenderer>();

		button1->SetText("Resume");
		button1->SetPosition({ 0.4f,0.5f });
		button1->SetFunction(std::function<void(void)>(std::bind(&GameMgr::Resume, gameMgr)));

		textRenderer1->SetPadding({ 0.f,0.f });
		textRenderer1->SetScale({ 1.f,1.f });
		textRenderer1->SetColor({ 1.f,1.f,1.f,1.f });
		textRenderer1->SetFont(arialFont);
		textRenderer1->SetShaderProgram(textProgramPtr);

		menu->AddButton(button1);
		++id;
	}

	{
		mainScene->NewGameObject("Button2");
		GameObject* obj = mainScene->GetRoot()->GetChildren()[id];
		Button* button2 = obj->NewComponent<Button>();
		TextRenderer* textRenderer2 = obj->NewComponent<TextRenderer>();

		button2->SetText("Exit");
		button2->SetPosition({ 0.4f,0.7f });
		button2->SetFunction(std::function<void(void)>(std::bind(&Simulation::Clear, this)));

		textRenderer2->SetPadding({ 0.f,0.f });
		textRenderer2->SetScale({ 1.f,1.f });
		textRenderer2->SetColor({ 1.f,1.f,1.f,1.f });
		textRenderer2->SetFont(arialFont);
		textRenderer2->SetShaderProgram(textProgramPtr);

		menu->AddButton(button2);
		++id;
	}
	{
		GameObject* obj = mainScene->NewGameObject("Spawner");
		MeshRenderer* meshRenderer = obj->NewComponent<MeshRenderer>();
		CubeCollider* collider = obj->NewComponent<CubeCollider>();
		SphereCollider* trigger = obj->NewComponent<SphereCollider>();
		Rigidbody* rigidbody = obj->NewComponent<Rigidbody>();
		SolidButton* pickable = obj->NewComponent<SolidButton>();


		trigger->SetTrigger(true);
		trigger->SetRadius(5.f);

		meshRenderer->SetMesh(cubeMesh);
		meshRenderer->SetMaterial(charaMaterialPtr);

		obj->GetTransform()->SetPosition(Vec3{ 20.f,1.f,0.f });
		obj->GetTransform()->SetRotation(Quaternion::Euler(Vec3{ 0.f,0.f,0.f }));
		obj->GetTransform()->SetScale(Vec3{ 1.f,1.f,1.f });
		++id;
	}

}

void Simulation::Update()
{
	UsefulInputs(mainScene);
	MoveCamera();

	if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_NUM_1))
		m_engine->GetSceneMgr()->Start();
	if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_NUM_2))
		m_engine->GetSceneMgr()->Exit();

}

void Simulation::Exit()
{
	m_engine->GetWindowsWrapper()->DeleteWindow(m_wnd);
	delete m_editorCamera;
}

void Simulation::MoveCamera()
{
	if (mainScene->IsSimulate())
		return;

	engine::fenestration::WindowsWrapper* winWrap = m_engine->GetWindowsWrapper();
	float deltaTime = 1.4f;
	if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_W))
	{
		m_editorCamera->MoveForward(deltaTime);
	}
	if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_S))
	{
		m_editorCamera->MoveBackward(deltaTime);
	}
	if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_A))
	{
		m_editorCamera->MoveLeft(deltaTime);
	}
	if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_D))
	{
		m_editorCamera->MoveRight(deltaTime);
	}
	if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_SHIFT))
	{
		m_editorCamera->MoveDown(deltaTime);
	}
	if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_SPACE))
	{
		m_editorCamera->MoveUp(deltaTime);
	}

	if (winWrap->GetActiveWindow() != nullptr)
	{
		m_editorCamera->SetViewSize(winWrap->GetActiveWindow()->GetWidth(), winWrap->GetActiveWindow()->GetHeight(), 0.1f, 1000.0f);
		//Get Camera rotation
		engine::core::maths::Vec2 center{ round(static_cast<float>(winWrap->GetActiveWindow()->GetWidth()) / 2), round(static_cast<float>(winWrap->GetActiveWindow()->GetHeight()) / 2) };
		engine::core::maths::Vec2 pos{ round(winWrap->GetMousePos(winWrap->GetActiveWindow()).m_x), round(winWrap->GetMousePos(winWrap->GetActiveWindow()).m_y) };
		engine::core::maths::Vec2 diff{ (pos - center) };
		if (!m_cursorLock)
		{
			winWrap->SetMousePos(winWrap->GetActiveWindow(), center);
			m_editorCamera->MoveTarget(diff, deltaTime);
		}
	}
}

void Simulation::Clear()
{
	engine::fenestration::WindowsWrapper* winWrap = m_engine->GetWindowsWrapper();
	if (winWrap->GetActiveWindow() != nullptr)
		winWrap->DeleteWindow(winWrap->GetActiveWindow());
}

void Simulation::UsefulInputs(Scene* mainScene)
{
	engine::resource_management::Explorer* explorer = m_engine->GetExplorer();
	engine::rhi::RHI* rhi = m_engine->GetRHI();

	engine::fenestration::WindowsWrapper* winWrap = m_engine->GetWindowsWrapper();

	if (winWrap->IsKeyDown(EKeyCode::INPUT_KEY_F1))
	{
		if (winWrap->GetActiveWindow() != nullptr)
			winWrap->DeleteWindow(winWrap->GetActiveWindow());
	}
	if (winWrap->IsKeyDown(EKeyCode::INPUT_KEY_Q))
	{
		m_cursorLock = !m_cursorLock;
	}
	if (winWrap->IsKeyDown(EKeyCode::INPUT_KEY_P))
	{
		int cbvTextShader = rhi->GenShader("Data/Shaders/CBTextVertexShader.hlsl", engine::rhi::resources::EShaderEnum::VERTEX_SHADER);
		int cbpTextShader = rhi->GenShader("Data/Shaders/CBTextPixelShader.hlsl", engine::rhi::resources::EShaderEnum::PIXEL_SHADER);

		int bvTextShader = rhi->GenShader("Data/Shaders/BasicTextVertexShader.hlsl", engine::rhi::resources::EShaderEnum::VERTEX_SHADER);
		int bpTextShader = rhi->GenShader("Data/Shaders/BasicTextPixelShader.hlsl", engine::rhi::resources::EShaderEnum::PIXEL_SHADER);

		int cbShaders[2]{ cbvTextShader, cbpTextShader };
		int bShaders[2]{ bvTextShader, bpTextShader };

		cbid = rhi->GenConstantBuffer(&boeuf, sizeof(boeuf), 0);
		int basicSampler = rhi->GenStaticSampler(D3D12_FILTER_MIN_MAG_MIP_POINT, 0, 0, 0.0f, D3D12_FLOAT32_MAX);

		int font = rhi->GenFont("Data/Fonts/arial.fnt");
		int font2 = rhi->GenFont("Data/Fonts/Chiller.fnt");

		std::string counter = "bonjour = ";
		std::string characters = "1234567890-=!@#$%^&*()_+qwertyuiop[]\asdfghjkl;'zxcvbnm,./QWERTYUIOP{}|ASDFGHJKL:ZXCVBNM<>? ";
		std::string temp = "Yes maggle";
		std::string temp2 = "WOLOLO = ";
		std::string temp3 = "XxXxX -  - XxXxX";
		//int text = rhi->GenText(counter.c_str(), cbShaders, 2, &cbid, 1, &basicSampler, 1, font2, { 0.0f, 0.0f }, { 5.0f, 5.0f }, { 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f, 1.0f });
		int text4 = rhi->GenText(temp2.c_str(), bShaders, 2, nullptr, 0, &basicSampler, 1, font2, { 0.5f, 0.1f }, { 1.0f, 1.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
		//int text2 = rhi->GenText(characters.c_str(), bShaders, 2, nullptr, 0, &basicSampler, 1, font, { 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
		//int text3 = rhi->GenText(temp.c_str(), bShaders, 2, nullptr, 0, &basicSampler, 1, font2, { 0.3f, 0.3f }, { 1.0f, 1.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
		//int text5 = rhi->GenText(temp3.c_str(), bShaders, 2, nullptr, 0, &basicSampler, 1, font, { 0.2f, 0.2f }, { 1.0f, 1.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });

		//rhi->SetActive(text, true, winWrap->GetActiveWindow()->GetId(), true);
		//rhi->SetActive(text2, true, winWrap->GetActiveWindow()->GetId(), true);
		//rhi->SetActive(text3, true, winWrap->GetActiveWindow()->GetId(), true);
		rhi->SetActive(text4, true, winWrap->GetActiveWindow()->GetId(), true);
		//rhi->SetActive(text5, true, winWrap->GetActiveWindow()->GetId(), true);
	}
}
