﻿#include "AcquisitionEffect.h"

#define PARTICLE_NUM	(80)	//	パーティクルの発生数
#define PARTICLE_SPEED	(500.0)	//	パーティクルの移動速度

//	コンストラクタの引数にパーティクルの生成位置を入れる
AcquisitionEffect::AcquisitionEffect(const Vec2& pos) :
	m_pos(pos)
{
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		//	基準の角度から-20～20度分ランダムでずらす
		double rad = Random(Math::ToRadians(-20), Math::ToRadians(20));

		Shape shape{
			.kinds = Random(0, 4),	//	画像の切り取り位置
			.velocity = Vec2(cos(-Math::HalfPi + rad),sin(-Math::HalfPi + rad)),	//	移動方向
			.startTime = Random(-1.0, 0.0),		//	-方向の値が大きくなるほど遅く生成
			.color = RandomColorF(),
			.rotateSpeed = Random(-5.0, 5.0)
		};

		//	管理用配列へ追加
		m_particles << shape;
	}

	//	画像のパスは適宜変更
	m_tex = Texture{ U"../Resources/Texture/Particle.png" };
}

bool AcquisitionEffect::update(double t)
{
	for (const auto& particle : m_particles)
	{
		const double t2 = (particle.startTime + t);

		//	InRangeの3つ目の引数がパーティクルの生存時間
		if (not InRange(t2, 0.0, 1.0))
		{
			continue;
		}

		//	現在t2は0～1の範囲にしかならないためそのままlerpに入れている
		//	パーティクルの生存時間を変更した際は、
		//	生存時間に対しての割合になるように計算が必要
		//	生成されてから時間がたつと徐々に透明になるようにする
		ColorF col = particle.color;
		col.a = Math::Lerp(0.5, 0.0, t2);

		m_tex(400 * particle.kinds, 0, 400, 400)	//	画像の切り取り範囲を指定(切り取り始点x,切り取り始点y,サイズx,サイズy)
			.scaled(0.2)							//	大きさ
			.rotated(t2 * particle.rotateSpeed)		//	角度
			.draw(m_pos + particle.velocity * t2 * PARTICLE_SPEED, col);	//	表示位置と色(基準点に方向と経過時間を足して位置を算出)
	}

	//	falseが返るとエフェクトは自動で削除される
	//	生存時間はここで指定
	return (t < 2.0);
}
