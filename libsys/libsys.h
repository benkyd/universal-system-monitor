#pragma once

#include "common.h"
#include "sys.h"
#include "temp.h"

void initialize_libsys();

static CPU* __cpu;
static Memory* __mem;
static GPU* __gpu;
static System* __sys;
