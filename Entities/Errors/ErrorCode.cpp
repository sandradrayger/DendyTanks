
//
// Created by true on 2022-04-27.
//

#include "ErrorCode.h"

SdlErrorCodeExample::SdlErrorCodeExample(Type t):type_(t) {}

SdlErrorCodeExample::Type SdlErrorCodeExample::getType() const {
	return type_;
}

SdlErrorCodeExample::~SdlErrorCodeExample() = default;
