//
// Created by true on 2022-04-27.
//

#ifndef SSDL_ERRORCODE_H
#define SSDL_ERRORCODE_H


class SdlErrorCodeExample {
public:
	enum Type{
		NO_ERRORS,
		NOT_INITIALIZED_OBJECT,
		CANNOT_MOVE
	};

	[[maybe_unused]] SdlErrorCodeExample(Type t); // NOLINT(google-explicit-constructor)
	virtual ~SdlErrorCodeExample();
	[[nodiscard]] Type getType() const;

private:
	Type type_;
};


#endif //SSDL_ERRORCODE_H
