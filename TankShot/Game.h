//
// Game.h
//

#pragma once

#include "StepTimer.h"
#include <VertexTypes.h>
#include <PrimitiveBatch.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>
#include "DebugCamera.h"
#include <Keyboard.h>
#include "Camera.h"
#include "FollowCamera.h"
#include <vector>
#include "Obj3d.h"
#include "Player.h"
#include "Enemy.h"
#include "ModelEffect.h"
#include <SpriteFont.h>
#include "LandShape.h"

#define MAX_BALL 10
#define MAX_TEAPOD 20
// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:
	//���@�p�[�c
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_BODY,
		PLAYER_PARTS_NECK,
		PLAYER_PARTS_HEAD,
		PLAYER_PARTS_LEGS,
		PLAYER_PARTS_WINGS,

		PLAYER_PARTS_NUM
	};


	Game();

	// Initialization and management
	void Initialize(HWND window, int width, int height);

	// Basic game loop
	void Tick();

	// Messages
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowSizeChanged(int width, int height);

	// Properties
	void GetDefaultSize(int& width, int& height) const;


private:

	void Update(DX::StepTimer const& timer);
	void Render();

	void Clear();
	void Present();

	void CreateDevice();
	void CreateResources();

	void OnDeviceLost();


	// Device resources.
	HWND                                            m_window;
	int                                             m_outputWidth;
	int                                             m_outputHeight;

	D3D_FEATURE_LEVEL                               m_featureLevel;
	Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

	Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
	Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

	// Rendering loop timer.
	DX::StepTimer                                   m_timer;

	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> spriteFont;


	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_batch;
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	//�L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> keyboardTracker;
	//�f�o�b�O�J����
	std::unique_ptr<DebugCamera> m_debugCamera;

	//�G�t�F�N�g�t�@�N�g���[
	std::unique_ptr<DirectX::EffectFactory> m_factory;
	//�V�����f��
	Obj3d m_objSkydorm;
	//�n�ʃ��f��
	std::unique_ptr<DirectX::Model> m_modelGround;
	//�����f��
	std::unique_ptr<DirectX::Model> m_modelBall;
	//�e�B�[�|�b�g���f��
	std::unique_ptr<DirectX::Model> m_modelTeapod;
	//���{�b�g(�^���N)���f��
	std::unique_ptr<DirectX::Model> m_modelTank;

	//�����[���h�s��
	DirectX::SimpleMath::Matrix m_worldBall1[MAX_BALL];
	DirectX::SimpleMath::Matrix m_worldBall2[MAX_BALL];
	//�e�B�[�|�b�h���[���h�s��
	DirectX::SimpleMath::Matrix m_worldTeapod[MAX_TEAPOD];
	////���{�b�g(�^���N)���[���h�s��
	//DirectX::SimpleMath::Matrix m_worldTank;
	////���{�b�g(�^���N)���[���h�s��2
	//DirectX::SimpleMath::Matrix m_worldTank2;


	//��]�����邽�߂̕ϐ�
	float rotateBall1 = 0.0f;
	float rotateBall2 = 0.0f;

	//�����_���̕ϐ�(�p�x�A����)
	float angle = 0.0f;
	float range = 0.0f;
	float value = 0.0f;

	//���@�̍��W
	DirectX::SimpleMath::Vector3 tank_pos;
	float tank_angle;

	//���@��3D�I�u�W�F�N�g
	std::vector<Obj3d> m_ObjPlayer;
	//std::vector<Obj3d> m_ObjPlayer;

	//�J����
	std::unique_ptr<FollowCamera> m_Camera;


	//Player
	std::unique_ptr<Player> m_player;

	//�G�l�~�[
	std::vector<std::unique_ptr<Enemy>> m_enemies;

	//�n�`
	LandShape m_landshape;

	////�ό`�O�̍��W
	//Vector3 BeforeHeadPos;
	//Vector3 BeforeNeckPos;
	//Vector3 BeforeLegsPos;
	////�ό`��̍��W
	//Vector3 AfterHeadPos;
	//Vector3 AfterNeckPos;
	//Vector3 AfterLegsPos;

	bool ClearFlag = true;
};