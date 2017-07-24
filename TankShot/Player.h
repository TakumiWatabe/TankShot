#pragma once
#include <Keyboard.h>
#include <SimpleMath.h>
#include "FollowCamera.h"
#include "Obj3d.h"
#include <vector>
#include "CollisionNode.h"
#include "Collision.h"
class Player :public Obj3d
{
protected:
	std::vector<Obj3d> m_ObjPlayer;
	DirectX::Keyboard::State m_key;

	//変形するためのフラグ
	bool ModiFlag = true;
	//発射しているかどうかのフラグ
	bool m_FireFlag = false;
	//弾丸の速度ベクトル
	DirectX::SimpleMath::Vector3 m_BulletVel;
	//発射用のフラグ
	bool ShotFlag = true;
	//球を戻すためのタイマー
	float returnTimer;

	//弾丸用の当たり判定
	SphereNode m_CollisionNodeBody;
	SphereNode m_CollisionNodeBullet;
	bool DebugFlag = true;

	// 速度
	DirectX::SimpleMath::Vector3 m_Velocity;
	bool m_isJump;

public:
	// 重力加速度<m/frame^2>
	const float GRAVITY_ACC = 0.03f;
	// ジャンプ初速<m/frame>
	const float JUMP_SPEED_FIRST = 0.5f;
	// 落下速度制限<m/frame>
	const float JUMP_SPEED_MAX = 0.3f;

	//自機パーツ
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_BODY,
		PLAYER_PARTS_NECK,
		PLAYER_PARTS_HEAD,
		PLAYER_PARTS_LEGS,
		PLAYER_PARTS_WINGS,

		PLAYER_PARTS_NUM
	};
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	//初期化
	void Initialize();
	//更新
	void Update();
	//プレイヤーの描画
	void PlayerDraw();
	//弾丸を発射
	void FireBullet();
	//弾丸を再装填(リセット)
	void ResetBullet();
	//キーボードのセット
	void SetKeyBord(DirectX::Keyboard::State key);
	//親オブジェクトの回転角をセット
	void SetParentRotation(DirectX::SimpleMath::Vector3 rotate);
	//親オブジェクトの座標をセット
	void SetParentTrans(DirectX::SimpleMath::Vector3 trans);
	//親オブジェクトの回転角を取得
	const DirectX::SimpleMath::Vector3 GetParentRotation();
	//親オブジェクトの座標を取得
	const DirectX::SimpleMath::Vector3 GetParentTrans();
	//全身用の当たり判定を取得
	const SphereNode& GetCollisionNodeBullet() { return m_CollisionNodeBullet; };
	//全身用の当たり判定を取得
	const SphereNode& GetCollisionNodeBody() { return m_CollisionNodeBody; };
	const DirectX::SimpleMath::Vector3& GetVeclocity() { return m_BulletVel; };
	//フラグの値を返すための関数
	bool ChangeFlag();
	bool ReturnFlag();
	void StartJump();
	void StartFall();
	void StopJump();
};
