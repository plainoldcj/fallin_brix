// math.h

#ifndef __MATH_H__
#define __MATH_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <sfml/graphics.hpp>

#define BIG_EPS 0.1f

namespace Math
{
	template<class Type>
	static Type Min(const Type& lhp, const Type& rhp) {
		if(lhp <= rhp) return lhp;
		return rhp;
	}

	template<class Type>
	static Type Max(const Type& lhp, const Type& rhp) {
		if(lhp <= rhp) return rhp;
		return lhp;
	}

	template<class Type>
	static Type VectorLength(const sf::Vector2<Type>& vec)
	{
		return sqrt(vec.x * vec.x + vec.y * vec.y); 
	}

	template<class Type>
	static void NormalizeVector(sf::Vector2<Type>& vec)
	{
		Type l = VectorLength(vec);
		vec.x /= l;
		vec.y /= l;
	}

	template<class Type>
	static sf::Vector2<Type> RandomDirectionVector(void)
	{
		sf::Vector2<Type> randVec;
		randVec.x = sf::Randomizer::Random(0.0f, 1.0f);
		randVec.y = sf::Randomizer::Random(0.0f, 1.0f);
		Math::NormalizeVector<Type>(randVec);
		return randVec;
	}

	template<class Type>
	static Type VectorDistance(const sf::Vector2<Type>& lhp,
		const sf::Vector2<Type>& rhp)
	{
		return VectorLength<Type>(lhp - rhp);
	}

	static bool AlmostEqual(float lhp, float rhp, float eps = BIG_EPS)
	{
		if((lhp * lhp) - (rhp * rhp) < eps) return true;
		return false;
	}
}

#endif