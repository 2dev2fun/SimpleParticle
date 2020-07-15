#pragma once

#include <Math.h>
#include <Math/Vector2.h>
#include <Math/Vector2/Function.h>
#include <Math/Vector2/Operator.h>
#include <Math/Vector4.h>
#include <Math/Vector4/Function.h>
#include <Math/Vector4/Operator.h>

#include <cmath>
#include <array>

namespace simple {

template <size_t Effects, size_t Particles>
class ParticleSystem {
public:
	ParticleSystem() : mSize(0), mCapacity(Effects * Particles) {}

	void wake(Vec2 position) {
		if (mSize >= mCapacity) { kill(0); }

		mPosition    [mSize] = position;
		mVelocity    [mSize] = Vec2();
		mAcceleration[mSize] = math::linearRandom(mMinAcceleration, mMaxAcceleration);
		mColor       [mSize] = math::linearRandom(mMinColor,        mMaxColor);
		mTime        [mSize] = math::linearRandom(mMinTime,         mMaxTime);
		++mSize;
	}

	void kill(size_t id) {
		swap(id, --mSize);
	}

	size_t size() const {
		return mSize;
	}

	size_t capacity() const {
		return mCapacity;
	}

	void update(float deltaTime) {
		for (size_t i = 0; i < mSize; ++i) {
			mTime[i] -= deltaTime;
			if (mTime[i] <= 0) {
				if (math::linearRandom(0.0f, 1.0f) < mBurstProbability) {
					emit(mPosition[i].x, mPosition[i].y);
				}
				kill(i);
			}
		}

		for (size_t i = 0; i < mSize; ++i) {
			mAcceleration[i]   *= mDamping;
			mAcceleration[i].y -= mGravity * mMass;
		}

		for (size_t i = 0; i < mSize; ++i) {
			mVelocity[i] += deltaTime * mAcceleration[i];
		}

		for (size_t i = 0; i < mSize; ++i) {
			mPosition[i] += deltaTime * mVelocity[i];

			float x = mPosition[i].x;
			float y = mPosition[i].y;

			if (x > 1 || x < -1 || y > 1 || y < -1) { kill(i); }
		}
	}

	void emit(float xpos, float ypos) {
		if (mCapacity - mSize < 64) {
			for (size_t i = 0; i < 64; ++i) {
				kill(i);
			}
		}

		Vec2 position { static_cast<float>(xpos), static_cast<float>(ypos) };

		for (size_t i = 0; i < 64; ++i) {
			wake(position);
		}
	}

	auto& getPosition() {
		return mPosition;
	}

	auto& getVelocity() {
		return mVelocity;
	}

	auto& getAcceleration() {
		return mAcceleration;
	}

	auto& getColor() {
		return mColor;
	}
private:
	void swap(size_t left, size_t right) {
		std::swap(mPosition    [left], mPosition    [right]);
		std::swap(mVelocity    [left], mVelocity    [right]);
		std::swap(mAcceleration[left], mAcceleration[right]);
		std::swap(mColor       [left], mColor       [right]);
		std::swap(mTime        [left], mTime        [right]);
	}

	size_t mSize;
	size_t mCapacity;

	std::array<Vec2,  Effects * Particles> mPosition;
	std::array<Vec2,  Effects * Particles> mVelocity;
	std::array<Vec2,  Effects * Particles> mAcceleration;
	std::array<Vec4,  Effects * Particles> mColor;
	std::array<float, Effects * Particles> mTime;

	Vec2 mMinAcceleration { -10.0f };
	Vec2 mMaxAcceleration {  10.0f };

	Vec4 mMinColor { 1.0f, 0.0f, 0.0f, 0.5f };
	Vec4 mMaxColor { 1.0f, 0.5f, 0.0f, 1.0f };

	float mMinTime = 0.2f;
	float mMaxTime = 1.0f;

	float mBurstProbability = 0.01f;

	float mDamping = 0.9f;
	float mGravity = 9.8f;
	float mMass    = 0.01f;
};

} // namespace simple
