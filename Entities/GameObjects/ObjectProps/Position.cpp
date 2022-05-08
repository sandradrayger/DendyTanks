//
// Created by true on 2022-04-27.
//
#include "Position.h"
#include <cmath>
#include <stdexcept>

Position& Position::operator+=(const Position &other) {
	x_+=other.x_;
	y_+=other.y_;
	z_+=other.z_;
	mDirection_=other.mDirection_;
	return *this;
}

Position& Position::operator+=(const Position &&other) {
	x_+=other.x_;
	y_+=other.y_;
	z_+=other.z_;
	mDirection_=other.mDirection_;
	return *this;
}

bool Position::isValid() const {
	if ((x_ <= -1 ) || (y_ <= -1) || (z_ <= -1) || (x_ >= 1000) || (y_ >= 1000) || (z_ >= 1000))
		return false;
	return true;
}

bool Position::operator==(const Position &rhs) const {
	return x_ == rhs.x_ &&
	       y_ == rhs.y_ &&
	       z_ == rhs.z_;
}

bool Position::operator!=(const Position &rhs) const {
	return !(rhs == *this);
}

bool Position::operator<(const Position &rhs) const {
	if (x_ < rhs.x_)
		return true;
	if (rhs.x_ < x_)
		return false;
	if (y_ < rhs.y_)
		return true;
	if (rhs.y_ < y_)
		return false;
	return z_ < rhs.z_;
}

bool Position::operator>(const Position &rhs) const {
	return rhs < *this;
}

bool Position::operator<=(const Position &rhs) const {
	return !(rhs < *this);
}

bool Position::operator>=(const Position &rhs) const {
	return !(*this < rhs);
}


Position Position::operator+(const Position &other) const {
	Position position;
	position.x_ = x_ + other.x_;
	position.y_ = y_ + other.y_;
	position.z_ = z_ + other.z_;
	position.mDirection_=other.mDirection_;
	return position;
}

Position Position::operator+(const Position &&other) const {
	Position position;
	position.x_ = x_ + other.x_;
	position.y_ = y_ + other.y_;
	position.z_ = z_ + other.z_;
	position.mDirection_=other.mDirection_;
	return position;
}

Position Position::operator-(const Position &other) const {
	Position position;
	position.x_ = x_ - other.x_;
	position.y_ = y_ - other.y_;
	position.z_ = z_ - other.z_;
	position.mDirection_=other.mDirection_;
	return position;
}

Position Position::operator-(const Position &&other) const {
	Position position;
	position.x_ = x_ - other.x_;
	position.y_ = y_ - other.y_;
	position.z_ = z_ - other.z_;
	position.mDirection_=other.mDirection_;
	return position;
}

Position& Position::operator-=(const Position &other) {
	x_-=other.x_;
	y_-=other.y_;
	z_-=other.z_;
	mDirection_=other.mDirection_;
	return *this;
}

Position& Position::operator-=(const Position &&other) {
	x_-=other.x_;
	y_-=other.y_;
	z_-=other.z_;
	mDirection_=other.mDirection_;
	return *this;
}

Position::operator bool() const {
	return isValid();
}

Position Position::operator-() const {
	Position minus = *this;
	minus.x_ = -minus.x_;
	minus.y_ = -minus.y_;
	minus.z_ = -minus.z_;
	if (mDirection_ == Direction::TOP){
		minus.mDirection_ = Direction::BOT;
	}
	if (mDirection_ == Direction::BOT){
		minus.mDirection_ = Direction::TOP;
	}
	if (mDirection_ == Direction::LEFT){
		minus.mDirection_ = Direction::RIGHT;
	}
	if (mDirection_ == Direction::LEFT){
		minus.mDirection_ = Direction::RIGHT;
	}
	return minus;
}

void Position::stepInDirection(bool inverse) {
	// TODO сложная логика, преобразовать поправить сделать единообразной
	if (inverse)
		reverseDirection();
	switch (mDirection_) {
		case Direction::TOP:{
			this->operator+=(Position{0,-1,0,Direction::TOP});
			break;
		}
		case Direction::BOT:{
			this->operator+=(Position{0,1,0,Direction::BOT});
			break;
		}
		case Direction::LEFT:{
			this->operator+=(Position{-1,0,0,Direction::BOT});
			break;
		}
		case Direction::RIGHT:{
			this->operator+=(Position{1,0,0,Direction::BOT});
			break;
		}
		case Direction::UNDEFINED:{
			throw std::logic_error("Move in unknow direction");
		}
	}
}

void Position::reverseDirection() {

	switch (mDirection_) {
		case Direction::TOP:{
			mDirection_ = Direction::BOT;
			break;
		}
		case Direction::BOT:{
			mDirection_ = Direction::TOP;
			break;
		}
		case Direction::LEFT:{
			mDirection_ = Direction::RIGHT;
			break;
		}
		case Direction::RIGHT:{
			mDirection_ = Direction::LEFT;
			break;
		}
		case Direction::UNDEFINED:{
			throw std::logic_error("Move in unknow direction");
		}
	}
}

double Position::calcDistance(const Position &other) const {
	return std::sqrt((x_ - other.x_) * (x_ - other.x_) +
	(y_ - other.y_) * (y_ - other.y_) +
	(z_ - other.z_) * (z_ - other.z_));
}

bool Position::isValidByWorldSize(size_t width, size_t height) const {
	if (x_ >= width || y_ >= height)
		return false;
	return true;
}
