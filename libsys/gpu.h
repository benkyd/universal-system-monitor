#pragma once 

class GPU {
public:
    GPU();

    virtual ~GPU();
};

static GPU* GPU_Instance;
