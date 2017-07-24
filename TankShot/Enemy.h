#pragma once
#include <Keyboard.h>
#include <SimpleMath.h>
#include "FollowCamera.h"
#include "Obj3d.h"
#include <vector>
#include "CollisionNode.h"
#include "Collision.h"

class Enemy:public Obj3d
{
private:
	std::vector<Obj3d> m_ObjEnemy;
	//目標角度を保持
	float m_DistAngle;
	//弾丸用の当たり判定
	SphereNode CollisionNodeBody;
	
public:
	//自機パーツ
	enum ENEMY_PARTS
	{
		ENEMY_PARTS_BODY,
		ENEMY_PARTS_NUM
	};
	//コンストラクタ
	Enemy();
	//デストラクタ
	~Enemy();

	//初期化
	void Initialize();
	//更新
	void Update();
	//プレイヤーの描画
	void EnemyDraw();
	//親オブジェクトの回転角をセット
	void SetParentRotation(DirectX::SimpleMath::Vector3 rotate);
	//親オブジェクトの座標をセット
	void SetParentTrans(DirectX::SimpleMath::Vector3 trans);
	//親オブジェクトの回転角を取得
	const DirectX::SimpleMath::Vector3 GetParentRotation();
	//親オブジェクトの座標を取得
	const DirectX::SimpleMath::Vector3 GetParentTrans();
	//角度を補完する
	float GetShortAngleRad(float rot, float radian);
	//全身用の当たり判定を取得
	const SphereNode& GetCollisionNodeBody() { return CollisionNodeBody; };

protected:
	//タイマー
	int m_Timer;

};

