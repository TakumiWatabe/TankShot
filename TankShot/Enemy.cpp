#include "pch.h"
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Enemy::Enemy()
{
	//Initialize();
	
}


Enemy::~Enemy()
{
}

//初期化
void Enemy::Initialize()
{

	////自機パーツの読み込み
	m_ObjEnemy.resize(ENEMY_PARTS_NUM);
	m_ObjEnemy[ENEMY_PARTS_BODY].LoadModel(L"Resources/Body.cmo");
	//m_ObjEnemy[PLAYER_PARTS_NECK].LoadModel(L"Resources/Neck.cmo");
	//m_ObjEnemy[PLAYER_PARTS_HEAD].LoadModel(L"Resources/Head.cmo");
	//m_ObjEnemy[PLAYER_PARTS_LEGS].LoadModel(L"Resources/Legs.cmo");
	//m_ObjEnemy[PLAYER_PARTS_WINGS].LoadModel(L"Resources/Wings.cmo");

	////パーツの親子関係をセット
	//m_ObjEnemy[PLAYER_PARTS_HEAD].SetParent(&m_ObjEnemy[PLAYER_PARTS_NECK]);
	//m_ObjEnemy[PLAYER_PARTS_NECK].SetParent(&m_ObjEnemy[PLAYER_PARTS_BODY]);
	//m_ObjEnemy[PLAYER_PARTS_LEGS].SetParent(&m_ObjEnemy[PLAYER_PARTS_BODY]);
	//m_ObjEnemy[PLAYER_PARTS_WINGS].SetParent(&m_ObjEnemy[PLAYER_PARTS_BODY]);

	////////親からのオフセット(座標のずらし分)をセット
	m_ObjEnemy[ENEMY_PARTS_BODY].SetScale(Vector3(0.2f, 0.2f, 0.2f));
	////////変形前の設定
	m_ObjEnemy[ENEMY_PARTS_BODY].SetTrans(Vector3(0, 1.2f, 0));
	//m_ObjEnemy[PLAYER_PARTS_NECK].SetScale(Vector3(1.2f, 1.2f, 1.2f));
	//m_ObjEnemy[PLAYER_PARTS_HEAD].SetTrans(Vector3(0, 2, -12));
	//m_ObjEnemy[PLAYER_PARTS_HEAD].SetRotation(Vector3(-1.5, 0, 0));
	//m_ObjEnemy[PLAYER_PARTS_NECK].SetRotation(Vector3(-4.75, 0, 0));
	//m_ObjEnemy[PLAYER_PARTS_NECK].SetTrans(Vector3(0, -8, 3));
	//m_ObjEnemy[PLAYER_PARTS_BODY].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//m_ObjEnemy[PLAYER_PARTS_LEGS].SetRotation(Vector3(0, 0, 0));
	//m_ObjEnemy[PLAYER_PARTS_LEGS].SetTrans(Vector3(0, 0, 0));
	
	//初期配置
	Vector3 pos;
	pos.x = rand() % 15;
	pos.z = rand() % 10;
	//pos.y = 10;
	//pos.x = 0;
	//pos.z = 0;
	pos.y = 2;

	this->SetParentTrans(pos);

	m_Timer = 0;
	m_DistAngle = 0;

	{//弾丸用の当たり判定を設定
		CollisionNodeBody.Initialize();
		//親パーツを指定
		CollisionNodeBody.SetParent(&m_ObjEnemy[ENEMY_PARTS_BODY]);
		CollisionNodeBody.SetOfset(Vector3(0, -1, 0));
		CollisionNodeBody.SetLocalRadius(7.0f);
	}

}

//更新
void Enemy::Update()
{
	//定期的に進行方向を変える
	m_Timer--;
	if (m_Timer < 0)
	{
		//カウントが0に達したら
		m_Timer = 60;

		//目標角度を変更
		float TargetAngle = (float)rand() / RAND_MAX - 0.5f;
		TargetAngle *= 180.0f;
		m_DistAngle += TargetAngle;
	}

	//目標地点に向かって、機体の角度をじわじわ補間する
	Vector3 rotv = m_ObjEnemy[ENEMY_PARTS_BODY].GetRotation();

	//目標角度への最短角度を取得
	float angle = m_DistAngle - rotv.y;
	
	//180°を超えていた場合、逆回りのほうが近い
	if (angle>XM_PI)
	{
		angle -= XM_2PI;
	}

	if (angle<-XM_PI)
	{
		angle += XM_2PI;
	}

	//補間
	rotv.y += angle*0.01f;

	SetParentRotation(rotv);

	//機体の向いている方向に進む

	//// 移動量のベクトル
	//Vector3 moveV(0, 0, -0.1f);
	//// 移動量ベクトルを自機の角度分回転させる
	////moveV = Vector3::TransformNormal(moveV, tank_world);
	//angle = m_ObjEnemy[ENEMY_PARTS_BODY].GetRotation().y;
	//Matrix rotmat = Matrix::CreateRotationY(angle);
	//moveV = Vector3::TransformNormal(moveV, rotmat);
	//// 自機の座標を移動させる
	//Vector3 pos = m_ObjEnemy[ENEMY_PARTS_BODY].GetTrans();
	//m_ObjEnemy[ENEMY_PARTS_BODY].SetTrans(pos + moveV);

	//今の座標を取得
	Vector3 trans = m_ObjEnemy[ENEMY_PARTS_BODY].GetTrans();
	Vector3 move(0.2f, 0, -0.2f);
	Matrix  rotm= Matrix::CreateRotationY(rotv.y);
	move = Vector3::TransformNormal(move, rotm);
	//座標を移動
	trans += move;
	//移動後の座標をセット
	m_ObjEnemy[ENEMY_PARTS_BODY].SetTrans(trans);


	for (std::vector<Obj3d>::iterator it = m_ObjEnemy.begin(); it != m_ObjEnemy.end(); it++)
	{
		it->Update();
	}
	CollisionNodeBody.Update();
}

//プレイヤーの描画
void Enemy::EnemyDraw()
{
	for (std::vector<Obj3d>::iterator it = m_ObjEnemy.begin(); it != m_ObjEnemy.end(); it++)
	{
		it->Draw();
	}
	CollisionNodeBody.Draw();
}

//親オブジェクトの回転角をセット
void Enemy::SetParentRotation(DirectX::SimpleMath::Vector3 rotate)
{
	m_ObjEnemy[ENEMY_PARTS_BODY].SetRotation(rotate);
}

//親オブジェクトの座標をセット
void Enemy::SetParentTrans(DirectX::SimpleMath::Vector3 trans)
{
	m_ObjEnemy[ENEMY_PARTS_BODY].SetTrans(trans);
}

//親オブジェクトの回転角を取得
const DirectX::SimpleMath::Vector3 Enemy::GetParentRotation()
{
	return m_ObjEnemy[ENEMY_PARTS_BODY].GetRotation();
}

//親オブジェクトの座標を取得
const DirectX::SimpleMath::Vector3 Enemy::GetParentTrans()
{
	return m_ObjEnemy[ENEMY_PARTS_BODY].GetTrans();
}

//float Enemy::GetShortAngleRad(float rot, float radian)
//{
//	float timestep = 0;
//	timestep += 0.01f;
//	Vector3::Lerp(Vector3(rot), Vector3(radian), timestep);
//}
