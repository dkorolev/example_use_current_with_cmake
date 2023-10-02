#pragma once

#include "typesystem/struct.h"
#include "typesystem/reflection/reflection.h"

CURRENT_STRUCT(Number) {
  CURRENT_FIELD(value, uint32_t);
  CURRENT_CONSTRUCTOR(Number)(uint32_t value) : value(value) {
  }
  CURRENT_CONSTRUCTOR(Number)(int value) : value(static_cast<uint32_t>(value)) {
  }
};
