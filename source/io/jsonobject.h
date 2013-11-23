#ifndef JSONOBJECT
#define JSONOBJECT

#include "rapidjson/document.h"

class JsonObject
{
public:
	virtual bool ToJson(rapidjson::Value& val, rapidjson::Document& doc) =0;
	virtual bool FromJson(const rapidjson::Value& val) = 0;
};

#endif