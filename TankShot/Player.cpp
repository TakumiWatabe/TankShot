#include "pch.h"
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Player::Player()
{
}


Player::~Player()
{
}

//初期化
void Player::Initialize()
{
	//自機パーツの読み込み
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);
	m_ObjPlayer[PLAYER_PARTS_BODY].LoadModel(L"Resources/Body.cmo");
	m_ObjPlayer[PLAYER_PARTS_NECK].LoadModel(L"Resources/Neck.cmo");
	m_ObjPlayer[PLAYER_PARTS_HEAD].LoadModel(L"Resources/Head.cmo");
	m_ObjPlayer[PLAYER_PARTS_LEGS].LoadModel(L"Resources/Legs.cmo");
	m_ObjPlayer[PLAYER_PARTS_WINGS].LoadModel(L"Resources/Wings.cmo");

	//パーツの親子関係をセット
	m_ObjPlayer[PLAYER_PARTS_HEAD].SetParent(&m_ObjPlayer[PLAYER_PARTS_NECK]);
	m_ObjPlayer[PLAYER_PARTS_NECK].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_LEGS].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);

	//////親からのオフセット(座標のずらし分)をセット
	m_ObjPlayer[PLAYER_PARTS_BODY].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//////変形前の設定
	m_ObjPlayer[PLAYER_PARTS_BODY].SetTrans(Vector3(0, 1.2f, 0));
	m_ObjPlayer[PLAYER_PARTS_NECK].SetScale(Vector3(1.2f, 1.2f, 1.2f));
	m_ObjPlayer[PLAYER_PARTS_HEAD].SetTrans(Vector3(0, 2, -12));
	m_ObjPlayer[PLAYER_PARTS_HEAD].SetRotation(Vector3(-1.5, 0, 0));
	m_ObjPlayer[PLAYER_PARTS_NECK].SetRotation(Vector3(-4.75, 0, 0));
	m_ObjPlayer[PLAYER_PARTS_NECK].SetTrans(Vector3(0, -8, 3));
	m_ObjPlayer[PLAYER_PARTS_BODY].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	m_ObjPlayer[PLAYER_PARTS_LEGS].SetRotation(Vector3(0, 0, 0));
	m_ObjPlayer[PLAYER_PARTS_LEGS].SetTrans(Vector3(0, 0, 0));

	returnTimer = 0;

	{//弾丸用の当たり判定を設定
		m_CollisionNodeBullet.Initialize();
		//親パーツを指定
		m_CollisionNodeBullet.SetParent(&m_ObjPlayer[PLAYER_PARTS_WINGS]);
		m_CollisionNodeBullet.SetOfset(Vector3(0, -3, 0));
		m_CollisionNodeBullet.SetLocalRadius(10.0f);
	}

	{//弾丸用の当たり判定を設定
		m_CollisionNodeBody.Initialize();
		//親パーツを指定
		m_CollisionNodeBody.SetParent(&m_ObjPlayer[0]);
		m_CollisionNodeBody.SetOfset(Vector3(0, -1, 0));
		m_CollisionNodeBody.SetLocalRadius(7.0f);
	}

}

//更新
void Player::Update()
{
	if (m_key.IsKeyDown(Keyboard::Keys::Space))
	{
		//ジャンプ開始
		StartJump();
	}

	// ジャンプ中
	if (m_isJump)
	{
		m_Velocity.y -= GRAVITY_ACC;
		// 速度制限
		if (m_Velocity.y <= -JUMP_SPEED_MAX)
		{
			m_Velocity.y = -JUMP_SPEED_MAX;
		}
	}

	Vector3 trans = this->GetTrans();
	trans += m_Velocity;
	this->SetParentTrans(trans);

	//Aキーが押されていたら左旋回
	if (m_key.A)
	{
		//自機の角度を回転させる
		float angle = GetParentRotation().y;
		SetParentRotation(Vector3(0, angle + 0.03f, 0));
	}
	//Dキーが押されていたら右旋回
	if (m_key.D)
	{
		//自機の角度を回転させる
		float angle = GetParentRotation().y;
		SetParentRotation(Vector3(0, angle - 0.03f, 0));
	}

	//Wキーが押されていたら前進
	if (m_key.W)
	{
		//移動ベクトル(Z座標)
		Vector3 moveV(0, 0, -0.1f);
		//移動量ベクトルを自機の角度分回転させる
		float angle = GetParentRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//自機の座標を移動させる
		Vector3 pos = GetParentTrans();
		SetParentTrans(pos + moveV);
	}
	//Sキーが押されていたら後退
	if (m_key.S)
	{
		//移動ベクトル(Z座標)
		Vector3 moveV(0, 0, 0.1f);
		//移動量ベクトルを自機の角度分回転させる
		float angle = GetParentRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//自機の座標を移動させる
		Vector3 pos = GetParentTrans();
		SetParentTrans(pos + moveV);
	}
	//SPACEキーで変形
	//if (m_key.Space)
	//{
	//	int cnt = 10;
	//	////通常状態
	//	//if (ModiFlag == true)
	// 	//{
	//	//	m_ObjPlayer[PLAYER_PARTS_BODY].SetTrans(Vector3(0, 1.2f, 0));
	//	//	m_ObjPlayer[PLAYER_PARTS_BODY].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//	//	m_ObjPlayer[PLAYER_PARTS_NECK].SetScale(Vector3(6, 6, 6));
	//	//	m_ObjPlayer[PLAYER_PARTS_HEAD].SetTrans(Vector3(0, 0, -0.2f));
	//	//	m_ObjPlayer[PLAYER_PARTS_NECK].SetTrans(Vector3(0, 0, -3.5f));
	//	//}
	//	////変形後
	//	//if (ModiFlag == false)
	//	//{
	//	if (ModiFlag == true)
	//	{
	//		m_ObjPlayer[PLAYER_PARTS_BODY].GetTrans();
	//		m_ObjPlayer[PLAYER_PARTS_BODY].GetRotation();
	//		m_ObjPlayer[PLAYER_PARTS_BODY].GetWorld();

	//		//変形後の設定
	//		m_ObjPlayer[PLAYER_PARTS_BODY].SetTrans(Vector3(0, 1.2f, 0));
	//		m_ObjPlayer[PLAYER_PARTS_BODY].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//		m_ObjPlayer[PLAYER_PARTS_NECK].SetScale(Vector3(1.2f, 1.2f, 1.2f));
	//		m_ObjPlayer[PLAYER_PARTS_HEAD].SetTrans(Vector3(0, 0, -0.2f));
	//		m_ObjPlayer[PLAYER_PARTS_HEAD].SetRotation(Vector3(0, 0, 0));
	//		m_ObjPlayer[PLAYER_PARTS_NECK].SetTrans(Vector3(0, 0.9, 0));
	//		m_ObjPlayer[PLAYER_PARTS_NECK].SetRotation(Vector3(0, 0, 0));
	//		m_ObjPlayer[PLAYER_PARTS_LEGS].SetRotation(Vector3(3.15, 0, 0));
	//		m_ObjPlayer[PLAYER_PARTS_LEGS].SetTrans(Vector3(0, -16.4, 3));


	//		ModiFlag = false;
	//	}

	//}
	////SPACEキーで変形
	//if (m_key.B)
	//{
	//	int cnt = 10;
	//	//通常状態
	//	if (ModiFlag == false)
	//	{
	//		m_ObjPlayer[PLAYER_PARTS_BODY].GetTrans();
	//		m_ObjPlayer[PLAYER_PARTS_BODY].GetRotation();
	//		m_ObjPlayer[PLAYER_PARTS_BODY].GetWorld();

	//		m_ObjPlayer[PLAYER_PARTS_BODY].SetTrans(Vector3(m_ObjPlayer[PLAYER_PARTS_BODY].GetTrans().x, 1.2f, m_ObjPlayer[PLAYER_PARTS_BODY].GetTrans().z));
	//		m_ObjPlayer[PLAYER_PARTS_HEAD].SetTrans(Vector3(0, 2, -12));
	//		m_ObjPlayer[PLAYER_PARTS_HEAD].SetRotation(Vector3(-1.5, 0, 0));
	//		m_ObjPlayer[PLAYER_PARTS_NECK].SetRotation(Vector3(-4.75, 0, 0));
	//		m_ObjPlayer[PLAYER_PARTS_NECK].SetTrans(Vector3(0, -8, 3));
	//		m_ObjPlayer[PLAYER_PARTS_BODY].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//		m_ObjPlayer[PLAYER_PARTS_LEGS].SetRotation(Vector3(0, 0, 0));
	//		m_ObjPlayer[PLAYER_PARTS_LEGS].SetTrans(Vector3(0, 0, 0));
	//		ModiFlag = true;

	//	}
	//}
	if (m_key.Space)
	{
		ShotFlag = false;
	}

	if (ShotFlag == false)
	{
		FireBullet();

		Vector3 pos = m_ObjPlayer[PLAYER_PARTS_WINGS].GetTrans();
		m_ObjPlayer[PLAYER_PARTS_WINGS].SetTrans(pos + m_BulletVel);
		returnTimer++;
		if (returnTimer >= 120)
		{
			ResetBullet();
			ShotFlag = true;
			returnTimer = 0;
		}
	}
	//if (m_key.IsKeyDown(Keyboard::Keys::D1))
	//{
	//	ChangeFlag();
	//}
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Update();
	}
	m_CollisionNodeBody.Update();
	m_CollisionNodeBullet.Update();
}

//プレイヤーの描画
void Player::PlayerDraw()
{
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Draw();
	}

	//if (ReturnFlag()==false)
	//{
	m_CollisionNodeBody.Draw();
	//}
}

void Player::FireBullet()
{
	if (m_FireFlag) return;

	// 発射するパーツのフィールド行列を取得
	Matrix worldm = m_ObjPlayer[PLAYER_PARTS_WINGS].GetWorld();
	//ワールド行列から各要素を抽出
	Vector3 scale;				//ワールドスケーリング
	Quaternion rotation;		//ワールド回転
	Vector3 translation;		//ワールド座標
	worldm.Decompose(scale, rotation, translation);

	//発射パーツを親から分離して独立
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetParent(nullptr);
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetScale(scale);
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetRotationQ(rotation);
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetTrans(translation);

	//弾丸の速度を設定
	m_BulletVel = Vector3(0, 0, -0.3f);
	m_BulletVel = Vector3::Transform(m_BulletVel, rotation);

	m_FireFlag = true;
}

void Player::ResetBullet()
{
	//発射中でない
	if (!m_FireFlag)	return;
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetScale(Vector3(1, 1, 1));
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetRotation(Vector3(0, 0, 0));
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetTrans(Vector3(0, 0, 0));

	m_FireFlag = false;
}

//キーボードのセット
void Player::SetKeyBord(Keyboard::State key)
{
	m_key = key;
}

//親オブジェクトの回転角をセット
void Player::SetParentRotation(DirectX::SimpleMath::Vector3 rotate)
{
	m_ObjPlayer[PLAYER_PARTS_BODY].SetRotation(rotate);
}

//親オブジェクトの座標をセット
void Player::SetParentTrans(DirectX::SimpleMath::Vector3 trans)
{
	m_ObjPlayer[PLAYER_PARTS_BODY].SetTrans(trans);
}

//親オブジェクトの回転角を取得
const DirectX::SimpleMath::Vector3 Player::GetParentRotation()
{
	return m_ObjPlayer[PLAYER_PARTS_BODY].GetRotation();
}

//親オブジェクトの座標を取得
const DirectX::SimpleMath::Vector3 Player::GetParentTrans()
{
	return m_ObjPlayer[PLAYER_PARTS_BODY].GetTrans();
}

bool Player::ChangeFlag()
{
	DebugFlag = !DebugFlag;

	return DebugFlag;
}

bool Player::ReturnFlag()
{
	return DebugFlag;
}


/// <summary>
/// ジャンプ開始
/// </summary>
void Player::StartJump()
{
	//ジャンプ中でない
	if (!m_isJump)
	{
		//
		m_Velocity.y = JUMP_SPEED_FIRST;
		m_isJump = true;
	}
}

/// <summary>
/// 落下開始
/// </summary>
void Player::StartFall()
{
	//
	if (!m_isJump)
	{
		//
		m_Velocity.y = 0.0f;
		m_isJump = true;
	}
}
/// <summary>
/// ジャンプを終了する
/// <summary>
void Player::StopJump()
{
	m_isJump = false;
	m_Velocity = Vector3::Zero;
}