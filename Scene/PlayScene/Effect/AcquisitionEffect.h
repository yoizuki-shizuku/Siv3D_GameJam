#pragma once

//	Siv3DのIEffectを継承して作成
class AcquisitionEffect : public IEffect
{
public:
	//	各パーティクルを制御するための構造体
	struct Shape
	{
		int kinds;			//	テクスチャから切り取る図形の種類
		Vec2 velocity;		//	パーティクルの進行方向
		double startTime;	//	表示され始めるまでの時間
		ColorF color;		//	色
		double rotateSpeed;	//	回転速度
	};

	AcquisitionEffect(const Vec2& pos);

	//	IEffectのupdateをオーバーライド
	bool update(double t) override;

private:
	Array<Shape> m_particles;	//	パーティクルを制御
	Vec2 m_pos;					//	パーティクルの発生位置
	Texture m_tex;				//	画像
};

//	使用方法
/*
①	Effectクラスを作成　Siv3D側で用意されていて、このクラスが各IEffectクラスを管理しています

②　add<作成したIEffect継承クラス>(コンストラクタの引数))　関数でIEffectが生成され、アニメーションが開始されます

③　Effectクラスのupdate()関数を毎フレーム更新される関数内で呼び出す
*/
