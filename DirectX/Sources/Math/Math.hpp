# pragma once

# include <cmath>

# include <initializer_list>

# include <algorithm>

namespace Math
{
	/// <summary>弧度法</summary>
	static const float Radian = 0.017453292519f;

	/// <summary>度数法</summary>
	static const float Degree = 57.295779513082f;

	/// <summary>円周率</summary>
	static const float Pi = 3.141592653589f;

	/// <summary>π/2</summary>
	static const float HalfPi = 1.570796326795f;

	/// <summary>π/3</summary>
	static const float Div3Pi = 1.047197551197f;

	/// <summary>π/4</summary>
	static const float Div4Pi = 0.785398163398f;

	/// <summary>度数法を弧度法に変換</summary>
	/// <param name="x">度数法</param>
	/// <returns>弧度法</returns>
	float ToRadian(float x);

	/// <summary>弧度法を度数法に変換</summary>
	/// <param name="x">弧度法</param>
	/// <returns>度数法</returns>
	float ToDegree(float x);

	/// <summary>サインを計算</summary>
	/// <param name="x">角度</param>
	/// <returns>サイン</returns>
	float Sin(float x);

	/// <summary>コサインを計算</summary>
	/// <param name="x">角度</param>
	/// <returns>コサイン</returns>
	float Cos(float x);

	/// <summary>タンジェントを計算</summary>
	/// <param name="x">角度</param>
	/// <returns>タンジェント</returns>
	float Tan(float x);

	/// <summary>アークサインを計算</summary>
	/// <param name="x">比率</param>
	/// <returns>アークサイン</returns>
	float Asin(float x);

	/// <summary>アークコサインを計算</summary>
	/// <param name="x">比率</param>
	/// <returns>アークサイン</returns>
	float Acos(float x);

	/// <summary>アークタンジェントを計算</summary>
	/// <param name="x">比率</param>
	/// <returns>アークタンジェント</returns>
	float Atan(float x);

	/// <summary>アークタンジェントを計算</summary>
	/// <param name="y">y成分</param>
	/// <param name="x">x成分</param>
	/// <returns>アークタンジェント</returns>
	float Atan2(float y, float x);

	/// <summary>x以下で最大の整数を返す</summary>
	/// <param name="x">基準値</param>
	/// <returns>x以下で最大の整数</returns>
	float Floor(float x);

	/// <summary>x以上で最大の整数を返す</summary>
	/// <param name="x">基準値</param>
	/// <returns>x以上で最大の整数</returns>
	float Ceiling(float x);

	/// <summary>四捨五入した値を返す</summary>
	/// <param name="x">値</param>
	/// <returns>四捨五入した値</returns>
	float Round(float x);

	/// <summary>符号を返す</summary>
	/// <param name="x">値</param>
	/// <returns>符号</returns>
	float Sign(float x);

	/// <summary>累乗を返す</summary>
	/// <param name="x">値</param>
	/// <param name="x">乗数</param>
	/// <returns>累乗</returns>
	float Pow(float x, float y);

	/// <summary>平方根を返す</summary>
	/// <param name="x">値</param>
	/// <returns>平方根</returns>
	float Sqrt(float x);

	/// <summary>指定した値の間にクランプする</summary>
	/// <param name="x">値</param>
	/// <param name="y">最小値</param>
	/// <param name="z">最大値</param>
	/// <returns>クランプされた値</returns>
	float Clamp(float x, float y, float z);

	/// <summary>指定桁数でならす</summary>
	/// <param name="x">値</param>
	/// <param name="y">桁数</param>
	/// <returns>ならした値</returns>
	float Smooth(float x, int y);

	/// <summary>0から1の間にクランプする</summary>
	/// <param name="x">値</param>
	/// <returns>0から1の間にクランプされた値</returns>
	float Saturate(float x);

	/// <summary>最大の値を返す</summary>
	/// <param name="args">値の初期化リスト</param>
	/// <returns>最大値</returns>
	template <typename Type>
	Type Max(std::initializer_list<Type> args)
	{
		return *std::max_element(args.begin(), args.end());
	}

	/// <summary>最小の値を返す</summary>
	/// <param name="args">値の初期化リスト</param>
	/// <returns>最小値</returns>
	template <typename Type>
	Type Min(std::initializer_list<Type> args)
	{
		return *std::min_element(args.begin(), args.end());
	}
}
