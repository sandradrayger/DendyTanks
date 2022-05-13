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
	direction_=other.direction_;
	return *this;
}

Position& Position::operator+=(const Position &&other) {
	x_+=other.x_;
	y_+=other.y_;
	z_+=other.z_;
	direction_=other.direction_;
	return *this;
}

bool Position::isValid() const {
	if ((x_ <= -1 ) || (y_ <= -1) ||
	    (z_ <= -1) || (x_ >= 1000) ||
	    (y_ >= 1000) || (z_ >= 1000) ||
	    direction_ == Direction::UNDEFINED)
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
	position.direction_=other.direction_;
	return position;
}

Position Position::operator+(const Position &&other) const {
	Position position;
	position.x_ = x_ + other.x_;
	position.y_ = y_ + other.y_;
	position.z_ = z_ + other.z_;
	position.direction_=other.direction_;
	return position;
}

Position Position::operator-(const Position &other) const {
	Position position;
	position.x_ = x_ - other.x_;
	position.y_ = y_ - other.y_;
	position.z_ = z_ - other.z_;
	position.direction_=other.direction_;
	return position;
}

Position Position::operator-(const Position &&other) const {
	Position position;
	position.x_ = x_ - other.x_;
	position.y_ = y_ - other.y_;
	position.z_ = z_ - other.z_;
	position.direction_=other.direction_;
	return position;
}

Position& Position::operator-=(const Position &other) {
	x_-=other.x_;
	y_-=other.y_;
	z_-=other.z_;
	direction_=other.direction_;
	return *this;
}

Position& Position::operator-=(const Position &&other) {
	x_-=other.x_;
	y_-=other.y_;
	z_-=other.z_;
	direction_=other.direction_;
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
	if (direction_ == Direction::TOP){
		minus.direction_ = Direction::BOT;
	}
	if (direction_ == Direction::BOT){
		minus.direction_ = Direction::TOP;
	}
	if (direction_ == Direction::LEFT){
		minus.direction_ = Direction::RIGHT;
	}
	if (direction_ == Direction::LEFT){
		minus.direction_ = Direction::RIGHT;
	}
	return minus;
}

void Position::stepInDirection(bool inverse) {
	if (inverse)
		reverseDirection();
	switch (direction_) {
		case Direction::TOP:{
			this->operator+=(Position{0,-1,0,Direction::TOP});
			break;
		}
		case Direction::BOT:{
			this->operator+=(Position{0,1,0,Direction::BOT});
			break;
		}
		case Direction::LEFT:{
			this->operator+=(Position{-1,0,0,Direction::LEFT});
			break;
		}
		case Direction::RIGHT:{
			this->operator+=(Position{1,0,0,Direction::RIGHT});
			break;
		}
		case Direction::UNDEFINED:{
			throw std::logic_error("Move in unknown direction");
		}
	}
}

void Position::reverseDirection() {

	switch (direction_) {
		case Direction::TOP:{
			direction_ = Direction::BOT;
			break;
		}
		case Direction::BOT:{
			direction_ = Direction::TOP;
			break;
		}
		case Direction::LEFT:{
			direction_ = Direction::RIGHT;
			break;
		}
		case Direction::RIGHT:{
			direction_ = Direction::LEFT;
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
	if (x_ >= static_cast<ssize_t>(width) || y_ >= static_cast<ssize_t>(height))
		return false;
	return true;
}
